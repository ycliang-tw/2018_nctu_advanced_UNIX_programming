#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>
#include <signal.h>

#define	PSIZE	2048
#define IF_NAME	"enp3s0"
#define STDIN	0

int send_socket;
void recv_print(int signal);

int main(){
	
	char test[] = "test message\n";
	char sendbuf[PSIZE] = {}, recvbuf[PSIZE] = {};
	struct ethhdr *sendhdr = (struct ethhdr*)sendbuf, *recvhdr = (struct ethhdr*)recvbuf;
	char *sendmsg = sendbuf + sizeof(struct ethhdr),  *recvmsg = recvbuf + sizeof(struct ethhdr);
	struct ifreq if_info;
	struct sockaddr_ll dest_addr;

	send_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP + 1));
	if(send_socket < 0)	perror("send socket");
//	int recv_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL + 1));
//	if(recv_socket < 0)	perror("recv socket");

	int sendlen = sizeof(struct ethhdr) + strlen(test);

	strcpy(if_info.ifr_name, IF_NAME);
	if(ioctl(send_socket, SIOCGIFHWADDR, &if_info) < 0)	perror("ioctl");
	int index = if_nametoindex(IF_NAME);
	unsigned char *mac = (unsigned char *)if_info.ifr_hwaddr.sa_data;
	memcpy(sendhdr->h_source, mac, ETH_ALEN);
	
	sendhdr->h_dest[0] = 0xff;
	sendhdr->h_dest[1] = 0xff;
	sendhdr->h_dest[2] = 0xff;
	sendhdr->h_dest[3] = 0xff;
	sendhdr->h_dest[4] = 0xff;
	sendhdr->h_dest[5] = 0xff;
	sendhdr->h_proto = htons(ETH_P_IP+1);
//	strcpy(sendmsg, test);
	
	dest_addr.sll_family = AF_PACKET;
	dest_addr.sll_protocol = htons(ETH_P_IP + 1);
	dest_addr.sll_ifindex = index;
	dest_addr.sll_halen = ETH_ALEN;
	memcpy(dest_addr.sll_addr, mac, ETH_ALEN);

	fd_set readfds, buffds;
	struct timeval tv;
	
	tv.tv_sec = 5;
	tv.tv_usec = 500000;
	
	signal(SIGUSR1, recv_print);
	
	FD_ZERO(&readfds);
	FD_ZERO(&buffds);
	FD_SET(STDIN, &readfds);
	FD_SET(send_socket, &readfds);

	
//	recvfrom(send_socket, recvbuf, 1024, 0, NULL, NULL);
//	printf("%s\n", recvmsg);

	while(1){
		
		tv.tv_sec = 5;
		tv.tv_usec = 500000;
		
		char input[PSIZE] = {};
		buffds = readfds;
		printf(">>> ");
		fflush(stdout);
		select(send_socket+1, &buffds, NULL, NULL, &tv);
	
//		recvfrom(send_socket, recvbuf, 1024, 0, NULL, NULL);
		if(FD_ISSET(send_socket, &buffds)){
			puts("recv");
			raise(SIGUSR1);
		}
		
		scanf("%s", input);
		strcpy(sendmsg, input);
		sendlen = sizeof(struct ethhdr) + strlen(input) + 1;
		sendto(send_socket, sendbuf, sendlen, 0, (struct sockaddr*)&dest_addr, sizeof(struct sockaddr_ll));
	}

	
	

	close(send_socket);
//	close(recv_socket);
	return 0;
}

void recv_print(int signal){
	char recvmsg[1024];
	int size = recvfrom(send_socket, recvmsg, 1024, 0, NULL, NULL);
	printf("size = %d,\t%s\n", size, recvmsg + sizeof(struct ethhdr));
	return;
}
