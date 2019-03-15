#include <time.h>
#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main() {
  pid_t pid, sid,child;
  int status;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/yudhis/Documents")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
	FILE * gpid;
	gpid = fopen ("/home/yudhis/Documents/gpid.txt", "w+");
	fprintf(gpid, "%d",getpid());
	fclose(gpid);

  while(1) {
	time_t t=time(NULL);
	struct tm tm = *localtime(&t);
	char waktu[50];
	char dpath[100]= "/home/yudhis/Documents/";
	static int i = 0;

	if(i%30==0){
	sprintf(waktu,"%d-%d-%d-%d:%d",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900,tm.tm_hour, tm.tm_min);
	printf("%s\n",waktu);
	}
	i++;	
	child = fork();
	if(child==0){
		char *argv[] = {"mkdir", waktu, NULL};
		execv("/bin/mkdir", argv);
	}
//	while ((wait(&status)) > 0);
//	kill(child, SIGKILL);

	strcat(dpath,waktu);
	strcat(dpath,"/");
	char data[100];
	child = fork();
	if(child==0){
	sprintf(data,"log%d.log",i);
	strcat(dpath,data);
	char *argv[] = {"cp", "/var/log/syslog",dpath, NULL};
	    execv("/bin/cp", argv);
	}
//	while ((wait(&status)) > 0);
//	kill(child, SIGKILL);
sleep(60);
	
  }
  
  exit(EXIT_SUCCESS);
}
