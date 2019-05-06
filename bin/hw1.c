#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>

#define sin 	0
#define sout 	1
#define MAX		1024
#define true	1
#define false	0
#define _default 100

int cmd_prompt();
char** parse_cmd(char* input);
int cmd_exec(char** cmd);

int _cat(char** cmdlist);		/*ok*/
int _cd(char** cmdlist);		/*ok*/
int _chmod(char** cmdlist);		/*ok*/
int _echo(char** cmdlist);		/*ok*/
int _find(char** cmdlist);		/*ok*/
int _help();					/*ok*/
int _id();						/*ok*/
int _mkdir(char** cmdlist);		/*ok*/
int _pwd();						/*ok*/
int _rm(char** cmdlist);		/*ok*/
int _rmdir(char** cmdlist);		/*ok*/
int _stat(char** cmdlist);		/*ok*/
int _touch(char** cmdlist);		/*ok*/
int _umask(char** cmdlist);		/*ok*/

int main(int argc, char** argv){
	if(argc < 3){
		fprintf(stderr, "[error]: usage: ./main <euid> <egid>!\n");
		fprintf(stderr, "euid, egid are set by default!\n");
	}else if(argc > 3){
		fprintf(stderr, "[error]: Too many arguments!\n");
		fprintf(stderr, "euid, egid are set by default!\n");
	}else{
		uid_t euid = strtoul(argv[1], NULL, 10);
		gid_t egid = strtoul(argv[2], NULL, 10);
		if(setegid(egid) < 0){
			fprintf(stderr, "[set egid error]: %s!\n", strerror(errno));
		}
		if(seteuid(euid) < 0){
			fprintf(stderr, "[set euid error]: %s!\n", strerror(errno));
		}
	}
		
	int status = true;
	while(status == true){
		status = cmd_prompt();
	}
	return 0;
}

int cmd_prompt(){
	const char prompt[] = "SIS>";
	char input[MAX] = {0};
	char **cmdlist;
	int status = true;
	printf("%s ", prompt);
	fflush(stdout);
	if(fgets(input, MAX, stdin) == NULL){
		return status;
	}
	cmdlist = parse_cmd(input);
	if(cmdlist == NULL)
		return status;
	status  = cmd_exec(cmdlist);
	return status;
}

char** parse_cmd(char* input){
	if(input[0] == '\n') return NULL;	
	const char space[] = "\t\n\r ";
	char **cmdlist = (char**)calloc(_default, sizeof(char*));
	for(int i = 0; i < _default; i++){
		cmdlist[i] = (char*)calloc(_default, sizeof(char));
	}

	int i = 0;
	char* temp = strtok(input, space);
	while(temp != NULL && i < _default-1){
		cmdlist[i++] = temp;
		temp = strtok(NULL, space);
	}
	cmdlist[i] = NULL;
	return cmdlist;
}

int cmd_exec(char** cmdlist){
	int i = 0, flag = 0;
	if(cmdlist[0] == NULL)	return true;
	if(strcmp(cmdlist[0], "cat") == 0){
		return _cat(cmdlist);
	}else if(strcmp(cmdlist[0], "cd") == 0){
		return	_cd(cmdlist);
	}else if(strcmp(cmdlist[0], "chmod") == 0){
		return	_chmod(cmdlist);
	}else if(strcmp(cmdlist[0], "echo") == 0){
		return	_echo(cmdlist);
	}else if(strcmp(cmdlist[0], "exit") == 0){
		return false;
	}else if(strcmp(cmdlist[0], "find") == 0){
		return	_find(cmdlist);
	}else if(strcmp(cmdlist[0], "help") == 0){
		return	_help();
	}else if(strcmp(cmdlist[0], "id") == 0){
		return	_id();
	}else if(strcmp(cmdlist[0], "mkdir") == 0){
		return	_mkdir(cmdlist);
	}else if(strcmp(cmdlist[0], "pwd") == 0){
		return	_pwd();
	}else if(strcmp(cmdlist[0], "rm") == 0){
		return	_rm(cmdlist);
	}else if(strcmp(cmdlist[0], "rmdir") == 0){
		return	_rmdir(cmdlist);
	}else if(strcmp(cmdlist[0], "stat") == 0){
		return	_stat(cmdlist);
	}else if(strcmp(cmdlist[0], "touch") == 0){
		return	_touch(cmdlist);
	}else if(strcmp(cmdlist[0], "umask") == 0){
		return	_umask(cmdlist);
	}else{
		fprintf(stderr, "[error]: [%s] command not found!\n", cmdlist[0]);
	}
	return true;
}


int _cat(char** cmdlist){
	int i = 1, fd;
	char buf[MAX];
	if(cmdlist[1] == NULL){
		printf("missing input file\n");
		return true;
	}
	while(cmdlist[i] != NULL){
		if(access(cmdlist[i], F_OK) < 0){
			fprintf(stderr, "[error]: [%s] doesn't exist!\n", cmdlist[i]);
		}else if(access(cmdlist[i], R_OK) < 0){
			fprintf(stderr, "[error]: not permitted to read [%s]!\n", cmdlist[i]);
		}else{
			fd = open(cmdlist[i], O_RDONLY);
			if(fd < 0){
				fprintf(stderr, "[error]: cannot open %s!\n", strerror(errno));
				return true;
			}
			int size = 1;
			while(size != 0){
				size = read(fd, buf, MAX);
				write(sout, buf, size);
			}
			close(fd);
		}
		i++;
	}
	return true;
}

int _cd(char** cmdlist){
	if(chdir(cmdlist[1]) == -1){
		fprintf(stderr, "[error]: cannot change to %s!\n", strerror(errno));
	}
	return true;
}
int _chmod(char** cmdlist){
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing argument!\n");
	}else if(cmdlist[2] == NULL){
		fprintf(stderr, "[error]: missing file/dir name!\n");
	}else{
		unsigned int mode = strtol(cmdlist[1], NULL, 8);
	//	printf("mode = %u\n", mode);
		if(chmod(cmdlist[2], mode) < 0){
			fprintf(stderr, "[error]: cannot change permission %s!\n", strerror(errno));
		}
	}
	return true;
}
int _echo(char** cmdlist){
	int i = 2, fd;
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing arguments!\n");
	}else if(cmdlist[2] == NULL){
		printf("%s\n", cmdlist[1]);
	}else{
		if(access(cmdlist[2], F_OK) < 0){
			fprintf(stderr, "[error]: [%s] file not exist!\n", cmdlist[2]);
		}else if(access(cmdlist[2], W_OK) < 0){
			fprintf(stderr, "[error]: not permitted to write to [%s]!\n", cmdlist[2]);
		}else{
			fd = open(cmdlist[2], O_WRONLY | O_APPEND);
			if(fd < 0){
				fprintf(stderr, "[error]: permission denied %s!\n", strerror(errno));
				return true;
			}
			dprintf(fd, "%s\n", cmdlist[1]);
			close(fd);
		}
	}
	return true;
}
int _find(char** cmdlist){
	char dir[MAX];
	DIR *dp;
	struct dirent *dirp;
	struct stat mystat;
	
	if(cmdlist[1] == NULL){
		getcwd(dir, MAX);
		dp = opendir(dir);
		if(dp == NULL){
			fprintf(stderr, "[error]: cannot open directory!\n");
		}else{
			
			printf("file type\t\t\tsize\t\t\tname\n\n");
			while((dirp = readdir(dp)) != NULL){
				
				stat(dirp->d_name, &mystat);

				if(dirp->d_type == DT_REG){		// should use switch instead
					printf("file");
				}else if(dirp->d_type == DT_DIR){
					printf("dir.");			// directory
				}else if(dirp->d_type == DT_FIFO){
					printf("fifo");
				}else if(dirp->d_type == DT_SOCK){
					printf("socket");
				}else if(dirp->d_type == DT_CHR){
					printf("c device");		// character device 
				}else if(dirp->d_type == DT_BLK){
					printf("b device"); 	// block device 
				}else if(dirp->d_type == DT_LNK){
					printf("sym. link");	// symbolic link
				}else{
					printf("unknown");
				}

				printf("\t\t\t\t%ld\t\t\t%s\n", mystat.st_size, dirp->d_name);
			}
		}
		closedir(dp);
	}else{
		dp = opendir(cmdlist[1]);
		if(dp == NULL){
			fprintf(stderr, "[error]: cannot open directory!\n");
		}else{
			
			printf("file type\t\t\tsize\t\t\tname\n\n");
			while((dirp = readdir(dp)) != NULL){
				sprintf(dir, "%s/%s", cmdlist[1], dirp->d_name);
				stat(dir, &mystat);

				if(dirp->d_type == DT_REG){		// should use switch instead
					printf("file");
				}else if(dirp->d_type == DT_DIR){
					printf("dir.");			// directory
				}else if(dirp->d_type == DT_FIFO){
					printf("fifo");
				}else if(dirp->d_type == DT_SOCK){
					printf("socket");
				}else if(dirp->d_type == DT_CHR){
					printf("c device");		// character device 
				}else if(dirp->d_type == DT_BLK){
					printf("b device"); 	// block device 
				}else if(dirp->d_type == DT_LNK){
					printf("sym. link");	// symbolic link
				}else{
					printf("unknown");
				}

				printf("\t\t\t\t%ld\t\t\t%s\n", mystat.st_size, dirp->d_name);
			}
		}
		closedir(dp);
	}
	return true;
}
int _help(){
	printf("\
	cat {file}:              Display content of {file}.\n\
	cd {dir}:                Switch current working directory to {dir}.\n\
	chmod {mode} {file/dir}: Change the mode (permission) of a file or directory.\n\
	                         {mode} is an octal number.\n\
	echo {str} [filename]:   Display {str}. If [filename] is given,\n\
	                         open [filename] and append {str} to the file.\n\
	exit:                    Leave the shell.\n\
	find [dir]:              List files/dirs in the current working directory\n\
	                         or [dir] if it is given.\n\
	                         Minimum outputs contatin file type, size, and name.\n\
	help:                    Display help message.\n\
	id:                      Show current euid and egid number.\n\
	mkdir {dir}:             Create a new directory {dir}.\n\
	pwd:                     Print the current working directory.\n\
	rm {file}:               Remove a file.\n\
	rmdir {dir}:             Remove an empty directory.\n\
	stat {file/dir}:         Display detailed information of the given file/dir.\n\
	touch {file}:            Create {file} if it does not exist,\n\
	                         or update its access and modification timestamp.\n\
	umask {mode}:            Change the umask of the current session.\n");
	return true;
}
int _id(){
	uid_t euid = geteuid();
	gid_t egid = getegid();
	printf("euid:\t %u, egid:\t %u\n", euid, egid);
	return true;
}
int _mkdir(char** cmdlist){
	int i = 1;
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing argument!\n");
	}else{
		while(cmdlist[i] != NULL){
			if(mkdir(cmdlist[i], 0775) < 0){
				fprintf(stderr, "[error]: cannot create %s!\n", cmdlist[i]);
			}
			i++;
		}
	}
	return true;
}
int _pwd(){
	char buf[MAX];
	getcwd(buf, MAX);
	printf("%s\n", buf);
	return true;
}
int _rm(char** cmdlist){
	int i = 1;
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing filename!\n");
	}else{
		while(cmdlist[i] != NULL){
			if(remove(cmdlist[i]) < 0){
				fprintf(stderr, "[error]: cannot remove %s!\n", strerror(errno));
			}
			i++;
		}
	}
	return true;
}
int _rmdir(char** cmdlist){
	int i = 1;
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing argument!\n");
	}else{
		while(cmdlist[i] != NULL){
			if(rmdir(cmdlist[i]) < 0){	
				fprintf(stderr, "[error]: cannot remove %s!\n", strerror(errno));
			}
			i++;
		}
	}
	return true;
}
int _stat(char** cmdlist){
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing file or directory!\n");
	}else{
		struct stat mystat;
		if(stat(cmdlist[1], &mystat) < 0){
			fprintf(stderr, "[error]: cannot retrieve info %s!\n", strerror(errno));
		}
		else{
			printf("hard link count \t uid \t gid \t block size \t block count \t\n");
			printf("%lu \t\t\t %d \t %d \t %ld \t\t %ld \n", mystat.st_nlink, mystat.st_uid, mystat.st_gid, mystat.st_size, mystat.st_blksize);
			printf("\nlast modification time: %slast access time: %s", ctime(&mystat.st_mtime), ctime(&mystat.st_atime));
		}
	}
	return true;
}
int _touch(char** cmdlist){
	int i = 1;
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing filename!\n");
	}else{
		while(cmdlist[i] != NULL){
			if(access(cmdlist[i], F_OK) < 0){
				if(creat(cmdlist[i], 0644) < 0){
					fprintf(stderr, "[error]: cannot create %s!\n", strerror(errno));
				}	
			}else{
				if(utime(cmdlist[i], NULL) < 0){
					fprintf(stderr, "[error]: cannot modifiy time of %s!\n", strerror(errno));
				}
			}
			i++;
		}	
	}
	return true;
}
int _umask(char** cmdlist){
	if(cmdlist[1] == NULL){
		fprintf(stderr, "[error]: missing argument!\n");
	}else{
		unsigned int mode = strtol(cmdlist[1], NULL, 8);
		umask(mode);
	}
	
	return true;
}

