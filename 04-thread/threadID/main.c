#include <stdio.h>     
#include <string.h>    // provide like strncpy
#include <unistd.h>    // provide sleep function
#include <pthread.h>   // provide using pthreads (POSIX threads)

// Declare two thread identifiers
pthread_t thread_id1, thread_id2;

// Define a structure to hold thread data
typedef struct
{
    char name[30];  // Name of the person
    char msg[30];   // Message to be displayed

} thr_data_t;  // Alias for the struct as 'thr_data_t'

// Function to handle thread execution
static void *thr_handle_1(void *args)
{
    // Get the current thread ID
    pthread_t thr_id = pthread_self();

    // Cast the argument to the correct type (thr_data_t)
    thr_data_t *data = (thr_data_t *)args;

    // Check if this is thread_id1
    if(pthread_equal(thr_id, thread_id1))
    {
        printf("I'm the thread_id1\n"); 
    }
    // Check if this is thread_id2
    else if(pthread_equal(thr_id, thread_id2))
    {
        printf("\nI'm the thread_id2\n"); 
        printf("Hello %s, welcome to join the %s\n", data->name, data->msg);
    }

    return NULL;  // Return NULL as the thread has completed its execution
}

int main(int argc, char const *argv[])
{  
    int ret;  // Variable to store return values from thread creation functions
    thr_data_t data = {0};  // Initialize thread data to zero (clear memory)

    // Copy a name and message into the 'data' structure
    strncpy(data.name, "TungNHS", sizeof(data.name));  // Copy name into 'data.name'
    strncpy(data.msg, "Tung learns thread programing\n", sizeof(data.msg));  // Copy message into 'data.msg'

    // Infinite loop to continuously create threads
    while(1)
    {
        // Create thread 1 but do not pass any data (NULL as argument)
        ret = pthread_create(&thread_id1, NULL, &thr_handle_1, NULL); // ret is 0 if create is successful
        if(ret)  // If pthread_create fails, print an error and exit
        {
            printf("pthread_create() error number %d\n", ret);
            return -1;
        }

        sleep(2);  // Sleep for 2 seconds to simulate delay between thread creations

        // Create thread 2 and pass the 'data' structure to the thread
        ret = pthread_create(&thread_id2, NULL, &thr_handle_1, &data);// ret is 0 if create is successful
        if(ret)  // If pthread_create fails, print an error and exit
        {
            printf("pthread_create() error number %d\n", ret);
            return -1;
        }
        
        sleep(3);  // Sleep for 3 seconds before creating the next set of threads
    }

    return 0; 
}