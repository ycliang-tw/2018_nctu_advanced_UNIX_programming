#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

void ps();					/* read file */
void show();				/* print info */
void usage();				/* program usage */
void mapping();				/* tty's name and device number mapping */
void pstree();

enum sort_option{
	spid = 1,
	sppid, spgid, ssid,
};

enum mode{
	current_user = 0,		/* default, list processes that have the same euid with current user */
	all_ps = 1,				/* list all processes in the system */
	ps_wout_terminal = 2,	/* list processes without terminal */
};

struct sort_info{
	int pid, ppid, pgid, sid;
};

struct dev_info{
	int major, minor;
	char name[15];
};

int comp1(const void *a, const void *b){
	struct sort_info *pa = (struct sort_info*)a;
	struct sort_info *pb = (struct sort_info*)b;
	return pa->ppid - pb->ppid;
}
int comp2(const void *a, const void *b){
	struct sort_info *pa = (struct sort_info*)a;
	struct sort_info *pb = (struct sort_info*)b;
	return pa->pgid - pb->pgid;
}
int comp3(const void *a, const void *b){
	struct sort_info *pa = (struct sort_info*)a;
	struct sort_info *pb = (struct sort_info*)b;
	return pa->sid - pb->sid;
}

int sort_opt = spid;
int mode_opt = current_user;
int dev_idx  = 0;
struct dev_info dev[200];


int main(int argc, char* argv[]){
	int opt;
	while((opt = getopt(argc, argv, "axpqrst")) != -1){
		switch(opt){
			case 'a':
				mode_opt |= all_ps;
				//printf("mode_opt = %d\n", mode_opt);
				break;
			case 'x':
				mode_opt |= ps_wout_terminal;
				//printf("mode_opt = %d\n", mode_opt);
				break;
			case 'p':
				sort_opt = spid;
				//printf("sort_opt = %d\n", sort_opt);
				break;
			case 'q':
				sort_opt = sppid;
				//printf("sort_opt = %d\n", sort_opt);
				break;
			case 'r':
				sort_opt = spgid;
				//printf("sort_opt = %d\n", sort_opt);
				break;
			case 's':
				sort_opt = ssid;
				//printf("sort_opt = %d\n", sort_opt);
				break;
			case 't':
				pstree();
				break;
			default:
				usage();
				break;
		}
	}
	mapping();
	ps();
	return 0;
}

void ps(){
	DIR *dp = opendir("/proc");
	struct dirent *dir;
	struct sort_info proc[1000];
	int proc_cnt = 0;
	while( (dir = readdir(dp)) != NULL){
		if( isdigit(dir->d_name[0]) ){
			char file_stat[100] = {}, buf1[100] = {}, buf2[100] = {}, buf3 = 0;
			snprintf(file_stat, 100, "/proc/%s/stat", dir->d_name);
			FILE *fp = fopen(file_stat, "r");
			fgets(buf1, 100, fp);
			sscanf(buf1, "%d %s %c %d %d %d", &proc[proc_cnt].pid, buf2, &buf3, &proc[proc_cnt].ppid, &proc[proc_cnt].pgid, &proc[proc_cnt].sid);
			proc_cnt++;
			fclose(fp);
		}
	}
	closedir(dp);
	
	/* sort_option */
	switch(sort_opt){
		case spid:
			break;
		case sppid:
			qsort( (void*)proc, proc_cnt, sizeof(proc[0]), comp1 );
			break;
		case spgid:
			qsort( (void*)proc, proc_cnt, sizeof(proc[0]), comp2 );
			break;
		case ssid:
			qsort( (void*)proc, proc_cnt, sizeof(proc[0]), comp3 );
			break;
		default:
			break;
	}

	/* output mode */
	show();
	int euid = geteuid();
	for(int i = 0; i < proc_cnt; i++){
		char file[100] = {}, file_stat[100] = {}, file_cmd[100] = {};
		char buffer_stat[100] = {};
		struct stat buf;
		FILE *fp_stat, *fp_cmd;
		int fd;

		/* output purpose */
		char cmd[1001] = {}, img[20] = {}, tty[20] = {}, status = 0; 
		int pid, ppid, pgid, sid, tty_nr;
		/**/

		snprintf(file, 100, "/proc/%d", proc[i].pid);
		snprintf(file_stat, 100, "/proc/%d/stat", proc[i].pid);
		snprintf(file_cmd, 100, "/proc/%d/cmdline", proc[i].pid);
		stat(file, &buf);
		fp_stat = fopen(file_stat, "r");
		fd = open(file_cmd, O_RDONLY);
		
		fgets(buffer_stat, 100, fp_stat);
		sscanf(buffer_stat, "%d %s %c %d %d %d %d", &pid, img, &status, &ppid, &pgid, &sid, &tty_nr);
		int num = read(fd, cmd, 1000);
		for(int k = 0; k < num; k++){
			if(cmd[k] == '\0'){
				cmd[k] = ' ';
			}
		}
		cmd[num-1] = '\0';
		if(tty_nr != 0){
			for(int j = 0; j < dev_idx; j++){
				if(major(tty_nr) == dev[j].major && minor(tty_nr) == dev[j].minor)
					snprintf(tty, 15, "%s", dev[j].name);
				}
			}
		else{
			snprintf(tty, 20, "%s", "-");
		}
		close(fd);
		fclose(fp_stat);

		//printf("pid: %d, ppid: %d, pgid: %d, sid: %d, sidst_uid %d\n", proc[i].pid, proc[i].ppid, proc[i].pgid, proc[i].sid, buf.st_uid);
		switch(mode_opt){
			case current_user:
				if(euid == buf.st_uid){
					printf("%5d%6d%6d%6d%6d%6d%9s %2c %-s %s\n", pid, buf.st_uid, buf.st_gid, ppid, pgid, sid, tty, status, img, cmd);
				}	
				break;

			case all_ps:
				printf("%5d%6d%6d%6d%6d%6d%9s %2c %-s %s\n", pid, buf.st_uid, buf.st_gid, ppid, pgid, sid, tty, status, img, cmd);
				break;

			case ps_wout_terminal:
				if(euid == buf.st_uid && tty_nr == 0){
					printf("%5d%6d%6d%6d%6d%6d%9s %2c %-s %s\n", pid, buf.st_uid, buf.st_gid, ppid, pgid, sid, tty, status, img, cmd);
				}	
				break;

			case (all_ps + ps_wout_terminal):
				if(tty_nr == 0){
					printf("%5d%6d%6d%6d%6d%6d%9s %2c %-s %s\n", pid, buf.st_uid, buf.st_gid, ppid, pgid, sid, tty, status, img, cmd);
				}
				break;
			default:
				break;
		}
	}
		
	//printf("pid: %d, ppid: %d, pgid: %d, sid: %d\n", proc[i].pid, proc[i].ppid, proc[i].pgid, proc[i].sid);
	//printf("proc_cnt: %d\n", proc_cnt);
}

void pstree(){}

void show(){
	int pid = 10, uid = 1000, gid = 10000, ppid = 1000, pgid = 1000, sid = 100;
	char tty[] = "pts/13", St = 'S', img[] = "(bash)", cmd[] = "-bash";
	printf("  pid   uid   gid  ppid  pgid   sid      tty St (img) cmd\n");
	//printf("%5d%6d%6d%6d%6d%6d%9s %2c %-s %s\n", pid, uid, gid, ppid, pgid, sid, tty, St, img, cmd);
}

void usage(){
	printf("usage: ./ps [option]\n");
}

void mapping(){
	DIR *dp = opendir("/dev");
	struct dirent *dir;
	struct stat buf;
	while( (dir = readdir(dp)) != NULL ){
		char name[30];
		snprintf(name, 30, "/dev/%s", dir->d_name);
		stat(name, &buf);
		if(major(buf.st_rdev) == 4 || major(buf.st_rdev) == 5){
			dev[dev_idx].major = major(buf.st_rdev);
			dev[dev_idx].minor = minor(buf.st_rdev);
			snprintf(dev[dev_idx].name, 15, "%s", dir->d_name);
			dev_idx++;
		}
	}
	closedir(dp);

	dp = opendir("/dev/pts");
	while( (dir = readdir(dp)) != NULL ){
		if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)	continue;
		char name[30];
		snprintf(name, 30, "/dev/pts/%s", dir->d_name);
		stat(name, &buf);
		dev[dev_idx].major = major(buf.st_rdev);
		dev[dev_idx].minor = minor(buf.st_rdev);
		snprintf(dev[dev_idx].name, 15, "pts/%s", dir->d_name);
		dev_idx++;
	}
	/*
	for(int i = 0; i < dev_idx; i++){
		printf("dev_name: %s, major: %d, minor: %d\n", dev[i].name, dev[i].major, dev[i].minor);
	}
	*/
}
