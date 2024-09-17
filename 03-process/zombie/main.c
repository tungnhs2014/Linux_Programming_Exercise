#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t child_pid;
    int status;
    int counter = 0;

    child_pid = fork();
    if(child_pid >= 0)
    {
        if (child_pid == 0)
        {
            printf("Child process termination\n");
            //while(1);
        }
        else{
           // while(1);
            wait(&status);
        }
    }
    else{
         printf("fork() unsuccessfully\n");      // fork() return -1 neu loi.
    }
    return 0;
}

