#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/if_ether.h>
#include <signal.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>

#define PACKET_SIZE	1024
#define STDIN		0


typedef struct network_interface_device{
	int index;
	char name[15];
	char mac_msg[100];
	unsigned char mac[ETH_ALEN];
}IF;

void zero(char *addr);
void recv_packet(int signal);
void close_socket(int signal);


// globalize the socket
int packet_socket;


int main(){

	/* network interfaces  */
	IF network_if[10] = {};
	int if_arr_idx = 0;
	struct ifaddrs *interfaces, *free;
	struct ifreq ifinfo;
	if( getifaddrs(&interfaces) == -1 ){
		fprintf(stderr, "[error]: %s\n", strerror(errno));
	}
	free = interfaces;
	
	puts("Enumerated network interfaces:");
	while(interfaces != NULL){
		if(strcmp(interfaces->ifa_name, "lo") == 0)	{interfaces = interfaces->ifa_next; continue;}
		if(interfaces->ifa_addr->sa_family != AF_INET){interfaces = interfaces->ifa_next; continue;}
		
		int infofd = socket(AF_INET, SOCK_DGRAM, 0);
		char ifip[INET_ADDRSTRLEN], ifmask[INET_ADDRSTRLEN], ifbroadcast[INET_ADDRSTRLEN], ifmac[INET_ADDRSTRLEN*2];
		if(infofd < 0)	perror("info socket");
		strcpy(ifinfo.ifr_name, interfaces->ifa_name);
		if(ioctl(infofd, SIOCGIFHWADDR, &ifinfo) < 0)	perror("ioctl");	
		
		void *tmp = NULL;
		tmp = &(((struct sockaddr_in*)interfaces->ifa_addr)->sin_addr);			// retrieve IP
		inet_ntop(AF_INET, tmp, ifip, INET_ADDRSTRLEN);
		zero(ifip);
		tmp = &(((struct sockaddr_in*)interfaces->ifa_netmask)->sin_addr);		// retrieve netmask
		inet_ntop(AF_INET, tmp, ifmask, INET_ADDRSTRLEN);
		unsigned int mask = inet_network(ifmask);
		tmp = &(((struct sockaddr_in*)interfaces->ifa_broadaddr)->sin_addr);	// retrieve broadcast
		inet_ntop(AF_INET, tmp, ifbroadcast, INET_ADDRSTRLEN);
		zero(ifbroadcast);
		unsigned char* mac = (unsigned char*)ifinfo.ifr_hwaddr.sa_data;
		snprintf(ifmac, INET_ADDRSTRLEN*2, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);	
		
		strcpy(network_if[if_arr_idx].name, interfaces->ifa_name);
		memcpy(network_if[if_arr_idx].mac, mac, ETH_ALEN);
		strcpy(network_if[if_arr_idx].mac_msg, ifmac);
		network_if[if_arr_idx].index = if_nametoindex(interfaces->ifa_name);

		printf("%u - %-11s     %s %#x (%s) %s\n", network_if[if_arr_idx].index, interfaces->ifa_name, ifip, mask, ifbroadcast, ifmac);
		interfaces = interfaces->ifa_next;
		close(infofd);
		if_arr_idx++;
	}
	freeifaddrs(free);

	/* get name */
	char name[1024] = {};
	printf("Enter your name: ");
	scanf("%s", name);
	printf("Welcome, '%s'!\n", name);


	/* prepare signal handler, fd_set, packet_socket */
	packet_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP + 1));
	signal(SIGUSR1, recv_packet);
	signal(SIGINT, close_socket);

	fd_set readfds, buffds;
	FD_ZERO(&readfds);
	FD_ZERO(&buffds);
	FD_SET(STDIN, &readfds);
	FD_SET(packet_socket, &readfds);
	int maxfd = packet_socket + 1;	


	/* command line */
	while(1){
		char input[1024] = {};
		buffds = readfds;
		
		printf(">>> ");
		fflush(stdout);
		select(maxfd, &buffds, NULL, NULL, NULL);
		
		if(FD_ISSET(packet_socket, &buffds)){
			raise(SIGUSR1);
		}
		
		read(STDIN, input, 1024);
		
		/* prepare packets to be sent */
		char sendbuf[PACKET_SIZE] = {};
		char *sendmsg = sendbuf + sizeof(struct ethhdr);
		struct ethhdr *sendhdr = (struct ethhdr*)sendbuf;
		struct sockaddr_ll dest_addr;

		sendhdr->h_dest[0] = 0xff;
		sendhdr->h_dest[1] = 0xff;
		sendhdr->h_dest[2] = 0xff;
		sendhdr->h_dest[3] = 0xff;
		sendhdr->h_dest[4] = 0xff;
		sendhdr->h_dest[5] = 0xff;
		sendhdr->h_proto = htons(ETH_P_IP + 1);
		
		dest_addr.sll_family = AF_PACKET;
		dest_addr.sll_protocol = htons(ETH_P_IP + 1);
		dest_addr.sll_halen = ETH_ALEN;		
	
		for(int i = 0; i < if_arr_idx; i++){

			memcpy(sendhdr->h_source, network_if[i].mac, ETH_ALEN);

			dest_addr.sll_ifindex = network_if[i].index;		
			memcpy(dest_addr.sll_addr, network_if[i].mac, ETH_ALEN);
			
			snprintf(sendmsg, PACKET_SIZE - sizeof(struct ethhdr), "<%s> [%s]: %s", network_if[i].mac_msg, name, input);

			int sendlen = sizeof(struct ethhdr) + strlen(sendmsg);
			sendto(packet_socket, sendbuf, sendlen, 0, (struct sockaddr*)&dest_addr, sizeof(struct sockaddr_ll));

		}


		
			
	}
	return 0;
}


void zero(char *addr){
	char tmp[INET_ADDRSTRLEN];
	int dot[5] = {0, 4, 8, 12, 16}, num = 0, x = 0;
	strcpy(tmp, addr);
	for(int i = 0; i < strlen(tmp)+1; i++){
		if(tmp[i] == '.' || i == strlen(tmp)){
			int offset = 3-num;
			for(int j = dot[x], k = 0; j < dot[x+1]; j++){
				if(offset > 0){
					addr[j] = '0';
					offset--;
				}else{
					addr[j] = tmp[i-num+k];
					k++;
				}
			}
			num = 0;
			x++;
			if(i == strlen(tmp))	break;
		}else 	num++;
	}
}

void recv_packet(int signal){
	char recvbuf[PACKET_SIZE] = {};
	char *recvmsg = recvbuf + sizeof(struct ethhdr);
	recvfrom(packet_socket, recvbuf, PACKET_SIZE, 0, NULL, NULL);
	printf("%s", recvmsg);
	return;
}

void close_socket(int signal){
	puts("closing socket");
	close(packet_socket);
	exit(0);
}
	
