#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main()
{
	printf("Run command <ls -lah> after 2 seconds\n");
	sleep(2);
	// execl("/bin/ls", "ls", "-l", "-a", "-h", NULL);
	kill(getpid(), SIGKILL);
	while(1)
	{
		printf("Hello\n");
		sleep(2);
	}
	return 0;
}
