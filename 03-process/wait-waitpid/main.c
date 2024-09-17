#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t child_pid;
    int status, return_value;

    child_pid = fork();
    if(child_pid >= 0)
    {
        if (child_pid == 0)
        {
            printf("In the child process, my PID: %d\n", getpid());
            while (1);
            //sleep(5);
            // exit(EXIT_SUCCESS);
        }
        else{
            // while(1);
            return_value = wait(&status);
            if(return_value == -1)
            {
                printf("Wait() unsucessful\n");
            }
            printf("\nIn the parent process, PID child process: %d\n", return_value);

            if (WIFEXITED(status))
            {
                printf("Normally termination, status = %d\n", WEXITSTATUS(status));
            }else if (WIFSIGNALED(status))
            {
                printf("Killed by signal, value = %d\n", WTERMSIG(status));
            }
            
        }
    }
    else{
         printf("fork() unsuccessfully\n");      // fork() return -1 neu loi.
    }
    return 0;
}

