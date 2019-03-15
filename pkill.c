#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int main()
{
  pid_t npid;
	FILE * gpid;

	gpid = fopen ("gpid.txt", "r");
	fscanf(gpid, "%d", &npid);
	kill(npid,SIGKILL);
	fclose(gpid);
	return 0;
}
