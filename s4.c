#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include<time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>


int main() {
  pid_t pid, sid;

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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  //int ingatdiet=1;
  while(1) {
    struct stat file_status;

    stat("/home/najaslanardo/Documents/makanan/makan_enak.txt",&file_status);
    if(file_status.st_atime + 30 > time(NULL)){int ingatdiet =1;
      while(1){
        char tempstr[50]= "";
        char newfile[350] = "/home/najaslanardo/Documents/makanan/makan_sehat";
        sprintf(tempstr,"%d.txt",ingatdiet);strcat(newfile, tempstr);
        FILE *temp = fopen(newfile, "r");
        if(!temp){
          FILE *temp1 = fopen(newfile,"w");
          fclose(temp1);break;
        }
        fclose(temp);
        ingatdiet++;
      }
    }

    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
