#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler_SIGINT(int num)
{
    printf("\nI'm signal handler SIGINT: %d\n", num);
    exit(EXIT_SUCCESS);
}

void handler_SIGUSR1(int num)
{
    printf("\nI'm signal handler SIGUSR1: %d\n", num);
    exit(EXIT_SUCCESS);
}

void handler_SIGUSR2(int num)
{
    printf("\nI'm signal handler SIGUSR2: %d\n", num);
    exit(EXIT_SUCCESS);
}




int main(int argc, char const *argv[])
{
    if(signal(SIGINT, handler_SIGINT) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR1, handler_SIGUSR1) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGUSR2, handler_SIGUSR2) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGUSR1\n");
        exit(EXIT_FAILURE);
    }

    while(1);

    return 0;
}
