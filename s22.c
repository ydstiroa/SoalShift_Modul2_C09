#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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

  if ((chdir("/home/yudhis/Documents/hatiku/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    struct stat ls;
    char dpath[50]="/home/yudhis/Documents/hatiku/elen.ku";
    char tname[20]="www-data";
    
    stat(dpath, &ls);

    struct passwd *pw = getpwuid(ls.st_uid);
    struct group  *gr = getgrgid(ls.st_gid);

    if(((strcmp(pw->pw_name,tname))==0)){
	if(((strcmp(gr->gr_name,tname))==0))
		{
			remove(dpath);
		}
	}
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
