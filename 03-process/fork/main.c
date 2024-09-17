#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char const *argv[]) // Cap phat stack frame cho ham main
{
	pid_t child_pid; // Luu trng stack frame cua main()
	int counter = 2; // Luu trong frame cua main()
	
	printf("Gia tri cua khoi tao counter %d\n", counter);
	
	child_pid = fork();
	if (child_pid >= 0)
	{
		if(0 == child_pid) /* process con */
		{
			printf("\nIn the child_process, counter: %d\n", ++counter);
			//getpid(): process tien trinh hien tai la tien trinh con
			//getppid(): process la tien trinh cha
			printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid()); //getpid(): process tien hinh hien tai la tien trinh con
		}
		else{            /* process cha */
			// sleep(2); process cọn hay cha chay truoc phu thuoc vao bo lap lich cua he thong, co the dung sleep
			printf("\nin the parent_process, counter: %d\n", ++counter);
			printf("My PID is: %d\n", getpid());
			while(1);
		}
	}
	else{
		printf("fork () unsucessfully \n"); // fork() return -1 neu loi
	}
}
