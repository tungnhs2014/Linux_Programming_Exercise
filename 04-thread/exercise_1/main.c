#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

// Declare two thread identifiers
pthread_t thread_id1, thread_id2;

// Structure to store information about a person
typedef struct human 
{
    char name[30];      // Person's name
    int year;           // Year of birth
    char phone[11];     // Phone number
    char hometown[30];  // Hometown
} thr_human;

// Function to be executed by threads
static void *thr_handle(void *args)
{
    // Cast the void* argument to a human structure pointer
    thr_human *data = (thr_human *)args;

    // Get the ID of the current thread
    pthread_t thr_id = pthread_self();

    // Check which thread is currently running and perform different actions
    if (pthread_equal(thr_id, thread_id1))  // If it's thread_id1
    {
        printf("\nHello everyone!\n");  // Print greeting message
    }
    else if (pthread_equal(thr_id, thread_id2))  // If it's thread_id2
    {
        // Print the information stored in the data structure
        printf("\nName: %s", data->name);
        printf("\nYear: %d", data->year);
        printf("\nPhone: %s", data->phone);
        printf("\nHome town: %s\n", data->hometown);
    }

    // Exit the thread once the task is done
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    thr_human thr_data;  // Structure to store thread data
    int ret;             // Variable to store the return value of thread creation

    // Initialize the thr_data structure to zero
    memset(&thr_data, 0x00, sizeof(thr_human));

    // Fill the structure with specific data
    strncpy(thr_data.name, "Nguyen Huu Son Tung", sizeof(thr_data.name));    
    thr_data.year = 2000;
    strncpy(thr_data.phone, "095435436", sizeof(thr_data.phone)); 
    strncpy(thr_data.hometown, "Dong Nai", sizeof(thr_data.hometown));    

    while (1)
    {
        // Create the first thread (thread_id1)
        if ((ret = pthread_create(&thread_id1, NULL, thr_handle, NULL)) != 0)  // No data is passed to thread 1
        {
            printf("pthread_create() error number %d\n", ret);
            return -1;
        }

        // Pause the main thread for 2 seconds to simulate some waiting time
        sleep(1);

        // Create the second thread (thread_id2) and pass thr_data as the argument
        if ((ret = pthread_create(&thread_id2, NULL, thr_handle, &thr_data)) != 0)
        {
            printf("pthread_create() error number %d\n", ret);
            return -1;
        }

        // Pause the main thread for 2 seconds to simulate some waiting time
        sleep(2);
    }

    // Wait for the first thread (thread_id1) to finish
    pthread_join(thread_id1, NULL);

    // Wait for the second thread (thread_id2) to finish
    pthread_join(thread_id2, NULL);

    // Return 0 to indicate successful completion of the program
    return 0;
}
