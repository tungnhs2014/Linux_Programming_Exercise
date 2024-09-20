#include <stdio.h>     
#include <stdlib.h>     
#include <string.h>     
#include <unistd.h>
#include <pthread.h>    // POSIX threads for multi-threading

// Global mutexes for synchronizing critical sections between threads
pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

// Global shared variable (critical resource)
int counter = 2; // Shared variable/resource (global variable)

// Struct to hold arguments passed to threads
typedef struct {
    char name[30];  // Thread name (used in this case for thread-specific output)
    char msg[30];   // Additional message (not used in this example)
} thread_args_t;

// Thread handler function for thread 1
static void *handle_th1(void *args) 
{   
    // Cast the argument back to the correct type (thread_args_t)
    thread_args_t *thr = (thread_args_t *)args;

    // Lock the mutex before entering the critical section
    pthread_mutex_lock(&lock1);

    // Critical section: safely access and modify shared resources
    printf("hello %s !\n", thr->name);     // Print the name from thread arguments
    printf("thread1 handler, counter: %d\n", ++counter); 
    sleep(5);   // Simulate work by sleeping for 5 seconds

    // Unlock the mutex after leaving the critical section
    pthread_mutex_unlock(&lock1);

    // Exit the thread
    pthread_exit(NULL); 
}

// Thread handler function for thread 2
static void *handle_th2(void *args) 
{
    // Lock the mutex before entering the critical section
    pthread_mutex_lock(&lock1);

    // Critical section: safely access and modify shared resources
    printf("thread2 handler, counter: %d\n", ++counter); 

    // Unlock the mutex after leaving the critical section
    pthread_mutex_unlock(&lock1);

    // Exit the thread
    pthread_exit(NULL); 
}

int main(int argc, char const *argv[])
{
    int ret;                  // Variable to store the return value of pthread_create
    thread_args_t thr;         // Struct to hold arguments for threads
    pthread_t thread_id1, thread_id2;   // Variables to hold thread IDs

    // Initialize the thread argument structure to zero
    memset(&thr, 0x0, sizeof(thread_args_t));
    // Copy the name "TungnHS" into the thread argument struct
    strncpy(thr.name, "TungnHS", sizeof(thr.name));

    // Create thread 1 and run the handle_th1 function
    if (ret = pthread_create(&thread_id1, NULL, &handle_th1, &thr)) {
        printf("pthread_create() error number=%d\n", ret); 
        return -1;  // Return error code if thread creation fails
    }

    // Create thread 2 and run the handle_th2 function
    if (ret = pthread_create(&thread_id2, NULL, &handle_th2, NULL)) {
        printf("pthread_create() error number=%d\n", ret);  
        return -1;  // Return error code if thread creation fails
    }
    
    // Wait for thread 1 to finish before proceeding
    pthread_join(thread_id1, NULL);  
    // Wait for thread 2 to finish before proceeding
    pthread_join(thread_id2, NULL);

    return 0;  // Return success code
}
