#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


void sig_handler1(int signum)
{
    printf("\nI'm signal handler1\n");
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    sigset_t new_set, old_set;

    if(signal(SIGINT, sig_handler1) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    sigemptyset(&new_set);
    sigemptyset(&old_set);

    sigaddset(&new_set, SIGINT);
    // sigaddset(&new_set, SIGKILL);

    printf("new set is %x\n", new_set);

    if(sigprocmask(SIG_SETMASK, &new_set, &old_set) == 0)
    {
        if(sigismember(&new_set, SIGINT) ==1)
        {
            printf("SIGINT exist\n");
        }
        else if(sigismember(&new_set, SIGINT) == 0)
        {
            printf("SIGINT does not exist\n");
        }
    }

    while(1);
    
    return 0;
}
