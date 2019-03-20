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

  if ((chdir("/home/najaslanardo/Documents")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
	FILE * gpid;
	gpid = fopen ("/home/najaslanardo/Documents/gpid.txt", "w+");
	fprintf(gpid, "%d",getpid());
	fclose(gpid);

int i =0;
char waktu[50];
  while(1) {
	time_t t=time(NULL);
	struct tm tm = *localtime(&t);
	char dpath[100]= "/home/najaslanardo/Documents/";
  i = i % 30;
	if(i==0){
	    sprintf(waktu,"%d-%d-%d-%d:%d",tm.tm_mday,tm.tm_mon + 1,tm.tm_year + 1900,tm.tm_hour, tm.tm_min);
	    printf("%s\n",waktu);

    child = fork();
	    if(child==0){
            char *argv[] = {"mkdir", waktu, NULL};
            execv("/bin/mkdir", argv);
	    }else{
            while(wait(&status)>0);
        }
    }else
    {
        strcat(dpath,waktu);
        strcat(dpath,"/");
        char data[100];
        child = fork();
        if(child==0){
            sprintf(data,"log%d.log",i);
            strcat(dpath,data);
            char *argv[] = {"cp", "/var/log/syslog",dpath, NULL};
            execv("/bin/cp", argv);
        }else{
            while(wait(&status)>0);
        }
    }
    i++;
    sleep(2);
	
  }
  
  exit(EXIT_SUCCESS);
}
