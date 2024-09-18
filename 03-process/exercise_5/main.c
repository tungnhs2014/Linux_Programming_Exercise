#include <stdio.h>      
#include <stdlib.h>     
#include <unistd.h>     // Provides fork() and sleep()
#include <sys/wait.h>   // Provides the wait
#include <signal.h>     // Provides  signal()

// Function to handle the SIGCHLD signal, which is sent when a child process terminates
void func_wait()
{
    printf("\nI'm in the function wait\n");  
    wait(NULL);  // Reap the terminated child process to prevent zombie processes
}

int main(int argc, char const *argv[])
{
    // Create a new child process using fork()
    pid_t child_pid = fork();

    // Check if fork() was successful
    if (child_pid >= 0)  // fork() returns a non-negative value if successful
    {
        if (child_pid == 0)  // This is the child process (child_pid == 0)
        {
            // Code for the child process
            printf("\nIn the child process, PID: %d\n", getpid()); 
            exit(EXIT_SUCCESS);  
        }
        else  // This is the parent process (child_pid > 0)
        {
            // Register the signal handler for SIGCHLD to handle child process termination
            signal(SIGCHLD, func_wait);
            printf("\nIn the parent process, PID: %d\n", getpid()); 

            // Parent process sleeps for 5 seconds to keep the program running
            sleep(5);
        }
    }
    else  // fork() failed
    {
        // Print an error message if fork() was unsuccessful
        printf("fork() failed\n");
    }
    
    return 0;  // Return 0 to indicate successful execution
}
