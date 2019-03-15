#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h> 
#include <stdio.h> 
#include <string.h>

int main() {
  int child_id;
  pid_t anakchild_id;
  int statuschild_id;
  int statusanakchild_id;
  int orangdalam[2];
   char listnama[1000]="";

  child_id = fork();
  if (pipe(orangdalam)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

    if (child_id == 0) {
        char *argv[] = {"unzip", "campur2.zip", NULL};
        execv("/usr/bin/unzip", argv);
    }
    else {
        while((wait(&child_id))>0);
        anakchild_id = fork();

	      if (anakchild_id < 0) {
    	    exit(EXIT_FAILURE);
      	}

        if (anakchild_id == 0) {
           while(wait(&statusanakchild_id) > 0);
            //printf("ini\n");
            chdir("/home/najaslanardo/Documents/Sisop/modul2/campur2");
            //find . -type f -name "*.txt"
            char *arg[] = {"find", ".","-type","f","-name","*.txt",  NULL};
            //char *arg[] = {"","-c","ls campur2/*.txt | awk 'BEGIN{(FS=\"/\")} {print $2}' > daftar.txt",NULL};
            dup2(orangdalam[1], 1);
            close(orangdalam[0]);
            close(orangdalam[1]);
            execv("/usr/bin/find",arg); 
     }
        else {
	        while((wait(&anakchild_id)) > 0);
          //printf("bangsat\n");
          close(orangdalam[1]);
          FILE *daftar = fopen("daftar.txt","w+");
          int namanya = read(orangdalam[0], listnama, sizeof(listnama));
          //close(orangdalam[0]);
          //printf("%d\n",strlen(listnama));
          fprintf(daftar,"%.*s\n",namanya, listnama);
          fclose(daftar);
          char *arg[] = {"chmod","777","daftar.txt", NULL};
          execv("/bin/chmod", arg);          
          //write(orangdalam[1],daftar, 350);
  }
    }
  return 0;
}