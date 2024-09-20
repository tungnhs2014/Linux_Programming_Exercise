#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handle1(int num)
{
    printf("\nI'm a signal handler 1: %d\n", num);

    exit(EXIT_SUCCESS);
}

void signal_handle2(int num)
{
    printf("\nI'm a signal handler 2: %d\n", num);

}

void signal_handle3(int num)
{
    printf("\nI'm a signal handler 3: %d\n", num);
    exit(EXIT_SUCCESS);
}


int main(int argc, char const *argv[])
{
    if(signal(SIGINT, signal_handle1) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }
    
    signal(SIGKILL, signal_handle2);
    signal(SIGTERM, signal_handle3);
    sleep(3);
    kill(getpid(), SIGINT);


    printf("Process ID: %d\n", getpid());

    while (1)
    {
        printf("hello\n");
        sleep(2);
    }
    
    return 0;
}
