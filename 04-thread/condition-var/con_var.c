#include <stdio.h>        
#include <stdlib.h>       
#include <string.h>       
#include <unistd.h>       // For sleep function
#include <pthread.h>      // For POSIX thread functions and data structures

#define THRESHOLD 5       // Defines the threshold value for the global counter

// Global variables
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;    // Mutex to protect critical section (access to the shared counter)
pthread_cond_t con1 = PTHREAD_COND_INITIALIZER;      // Condition variable used to synchronize threads

int counter; // Shared global variable (critical section) representing the counter

// Struct to hold arguments for threads
typedef struct {
    char name[30];   // Name for the thread (used in this example for personalized output)
    char msg[30];    // Message (not used in this code, could be used for additional functionality)
} thread_args_t;

// Thread handler function for the first thread
static void *handle_th1(void *args)
{
    thread_args_t *thr = (thread_args_t *)args;   // Cast the argument to the correct struct type

    pthread_mutex_lock(&lock);   // Lock the mutex to safely modify the shared resource (counter)

    printf("Hello %s khong sao dau!\n", thr->name);   // Print a message with the thread name

    // Increment the counter until it reaches the defined threshold
    while (counter < THRESHOLD)
    {   
        counter++;               // Increment the global counter
        printf("Counter: %d\n", counter);  
        sleep(1);                // Pause for 1 second to simulate work
    }

    // Signal the condition variable to notify waiting threads that the threshold is reached
    pthread_cond_signal(&con1);
    printf("thread1 handler, counter = %d\n", counter);  

    pthread_mutex_unlock(&lock);   // Unlock the mutex, allowing other threads to access the critical section
    pthread_exit(NULL);   // Exit the thread function, returning no value
}

int main(int argc, char const *argv[])
{
    int ret;                      // Variable to store return values from thread creation functions
    thread_args_t thr;             // Struct to hold arguments for the thread
    pthread_t thread_id1;          // Thread ID for the first thread

    memset(&thr, 0x0, sizeof(thread_args_t));   // Initialize the thread argument struct with zero
    strncpy(thr.name, "TungNHS", sizeof(thr.name));   // Set the thread's name to "TungNHS"

    // Create the first thread and run the handle_th1 function
    if ((ret = pthread_create(&thread_id1, NULL, &handle_th1, &thr)))   // Create the thread and check for errors
    {
        printf("pthread create() error number = %d\n", ret);   
        return -1;   // Return an error code if thread creation failed
    }

    pthread_mutex_lock(&lock);   // Lock the mutex to wait for the condition signal

    // Main thread waits for the condition signal from thread 1
    while (1)
    {
        // Wait for the condition variable to be signaled by thread 1
        pthread_cond_wait(&con1, &lock);   // Unlocks the mutex while waiting, re-locks upon waking
        if (counter == THRESHOLD)   // Check if the counter has reached the defined threshold
        {
            printf("Global variable counter = %d\n", counter);  
            break;   // Exit the loop when the threshold is reached
        }
    }

    pthread_mutex_unlock(&lock);   // Unlock the mutex after receiving the condition signal

    // Wait for the first thread to finish executing
    pthread_join(thread_id1, NULL);   // Join thread 1 to ensure it completes execution before the program terminates

    return 0;   // Return success code
}
