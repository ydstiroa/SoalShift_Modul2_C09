#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/home/yudhis/Documents/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
   DIR *d;
    struct dirent *dir;
    d = opendir("/home/yudhis/Documents/");

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
	    char namaFile[500];
	    int len = (int) strlen(dir->d_name);
	    char *name = dir->d_name;
	    if(name[len-1] == 'g' && name[len-2] == 'n' && name[len-3] == 'p' && name[len-4] == '.'){
            	printf("%s %d\n", dir->d_name, (int) strlen(dir->d_name));
		strcpy(namaFile, "/home/yudhis/Documents/modul2/gambar/");
		strcat(namaFile, name);
		len = (int)strlen(namaFile); //deletefile
		namaFile[len-4] = '\0';
		strcat(namaFile, "_grey.png");
		if(fork()==0){
		char *argv[] = {"mv", name, namaFile, NULL};
		execv("/bin/mv", argv);
		}
		printf("%s\n", namaFile);
	    }
        }
        closedir(d);
    }
 	sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
