#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler for SIGINT
void handle_SIGINT(int sig)
{
    printf("\nI'm the handle for signal SIGINT: %d\n", sig);
    exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
    sigset_t sigset;
    sigset_t oldset;

    // Register handler for SIGINT signal
    if (signal(SIGINT, handle_SIGINT) == SIG_ERR)
    {
        fprintf(stderr, "Cannot handle SIGINT\n");
        exit(EXIT_FAILURE);
    }

    // Initialize signal sets
    sigemptyset(&sigset);
    sigemptyset(&oldset);
    
    sigaddset(&sigset, SIGINT);

    // Check if SIGINT is blocked initially
    if (sigprocmask(SIG_BLOCK, NULL, &oldset) == 0)
    {
        if (sigismember(&oldset, SIGINT))
        {
            printf("SIGINT is initially blocked\n");
        }
        else
        {
            printf("SIGINT is initially not blocked\n");
        }
    }

    // Block SIGINT signal
    printf("Blocking SIGINT signal...\n");
    if (sigprocmask(SIG_BLOCK, &sigset, NULL) == 0)
    {
        // Check again if SIGINT is blocked
        sigprocmask(SIG_BLOCK, NULL, &oldset);  // Update oldset
        if (sigismember(&oldset, SIGINT))
        {
            printf("SIGINT is now blocked\n");
        }
        else
        {
            printf("SIGINT is still not blocked\n");
        }
    }

    // Wait for 5 seconds to allow testing Ctrl+C (SIGINT will be blocked)
    printf("Waiting for 5 seconds, try Ctrl+C...\n");
    sleep(5);

    // Unblock SIGINT signal
    printf("Unblocking SIGINT signal...\n");
    sigprocmask(SIG_UNBLOCK, &sigset, NULL);

    // Check the state of SIGINT again
    if (sigprocmask(SIG_BLOCK, NULL, &oldset) == 0)
    {
        if (sigismember(&oldset, SIGINT))
        {
            printf("SIGINT is still blocked\n");
        }
        else
        {
            printf("SIGINT is now unblocked\n");
        }
    }

    // Wait for another 5 seconds to allow testing Ctrl+C (SIGINT will not be blocked)
    printf("Waiting for another 5 seconds, try Ctrl+C again...\n");
    sleep(5);

    return 0;
}
