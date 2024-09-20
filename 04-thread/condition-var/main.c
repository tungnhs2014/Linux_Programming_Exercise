#include <stdio.h>        
#include <stdlib.h>       
#include <string.h>       
#include <unistd.h>      
#include <pthread.h>      // For POSIX thread functions and data structures

#define THRESHOLD 5       // Define the threshold value when the condition should be satisfied

// Global variables
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;    // Mutex to protect critical section

int counter; // Shared global resource (critical section)

// Struct to hold arguments for threads
typedef struct {
    char name[30];   // Name of the thread
    char msg[30];    // Message (not used in this code)
} thread_args_t;

// Thread handler function for thread 1
static void *handle_th1(void *args)
{
    thread_args_t *thr = (thread_args_t *)args;   // Cast the argument to the proper type

    pthread_mutex_lock(&lock);   // Lock the mutex to enter the critical section

    printf("Hello %s khong sao dau !\n", thr->name);   // Print a message with the thread name

    // Increment the counter until it reaches the threshold
    while (counter < THRESHOLD)
    {   
        counter++;               // Increment the global counter
        printf("Counter: %d\n", counter);   // Print the current value of the counter
        sleep(1);                // Sleep for 1 second
    }

    printf("thread1 handler, counter = %d\n", counter);   // Print the final counter value

    pthread_mutex_unlock(&lock);   // Unlock the mutex after leaving the critical section
    return NULL;   // Return NULL as this is a void function
}

int main(int argc, char const *argv[])
{
    int ret;                      // Variable to store return values of thread functions
    thread_args_t thr;             // Struct to hold thread arguments
    pthread_t thread_id1;          // Thread ID for thread 1

    memset(&thr, 0x0, sizeof(thread_args_t));   // Initialize the thread argument struct to zero
    strncpy(thr.name, "TungNHS", sizeof(thr.name));   // Copy the name "TungNHS" to the struct

    // Create the first thread that runs the handle_th1 function
    if((ret = pthread_create(&thread_id1, NULL, &handle_th1, &thr)))
    {
        printf("pthread create() error number = %d\n", ret);   // Print error if thread creation fails
        return -1;   // Return an error code
    }

    // Main thread waits for the condition signal from thread 1
    while (1)
    {
        if(counter == THRESHOLD)   // Check if the counter has reached the threshold
        {
            printf("Global variable counter = %d\n", counter);   // Print the final counter value
            break;   // Exit the loop
        }
    }

    // Wait for the first thread to finish
    pthread_join(thread_id1, NULL);   // Join thread 1 to ensure it completes

    return 0;   // Return success code
}
