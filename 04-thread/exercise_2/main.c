#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>

// Struct to hold student information
typedef struct 
{
    char name[30];       // Student name
    char date[15];       // Student date of birth
    char hometown[30];   // Student hometown
} student_t;

// Global variables
student_t student;       // Shared student struct to store input data
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;    // Mutex to protect shared resources
pthread_cond_t cond_input = PTHREAD_COND_INITIALIZER; // Condition variable for input control
pthread_cond_t cond_write = PTHREAD_COND_INITIALIZER; // Condition variable for writing control
int ready_to_write = 0, ready_to_read = 0;  // Flags to manage thread synchronization

// Thread 1: Handles student input from the user
static void *input_thread(void *args)
{
    while (1)
    {
        pthread_mutex_lock(&lock);  // Lock to ensure thread-safe operations
        
        // Get student name from the user
        printf("Enter student name: ");
        fgets(student.name, sizeof(student.name), stdin);
        student.name[strcspn(student.name, "\n")] = 0; // Remove the newline character

        // Get student date of birth
        printf("Enter student date of birth: ");
        fgets(student.date, sizeof(student.date), stdin);
        student.date[strcspn(student.date, "\n")] = 0; // Remove the newline character

        // Get student hometown
        printf("Enter student hometown: ");
        fgets(student.hometown, sizeof(student.hometown), stdin);
        student.hometown[strcspn(student.hometown, "\n")] = 0; // Remove the newline character

        // Set flag to signal the write thread that data is ready
        ready_to_write = 1;
        pthread_cond_signal(&cond_write);  // Signal the write thread to process the data
        pthread_cond_wait(&cond_input, &lock);  // Wait until the read thread is done printing

        pthread_mutex_unlock(&lock);  // Unlock mutex
    }
    pthread_exit(NULL);  // Terminate the thread
}

// Thread 2: Writes student data to a file
static void *write_thread(void *args)
{   
    int fd;
    char buffer[256];   
    while(1)
    {
        pthread_mutex_lock(&lock);  // Lock mutex for safe writing

        // Wait until input data is ready
        while(!ready_to_write)
        {
            pthread_cond_wait(&cond_write, &lock);  // Wait until signaled by the input thread
        }

        // Open the file for writing (create if it doesn't exist, append mode)
        fd = open("thongtinsinhvien.txt", O_WRONLY | O_CREAT | O_APPEND, 0664);
        if (fd == -1)
        {
            printf("Error opening file\n");
            pthread_mutex_unlock(&lock);
            continue;
        }

        // Format and write the student data to the file
        snprintf(buffer, sizeof(buffer), "Name: %s\nDate: %s\nHometown: %s\n\n", student.name, student.date, student.hometown);
        write(fd, buffer, strlen(buffer));
        close(fd);  // Close the file

        // Signal that the data is ready to be read and reset the flags
        ready_to_read = 1;
        ready_to_write = 0;
        pthread_cond_signal(&cond_write);  // Signal the read thread to start reading
        pthread_mutex_unlock(&lock);  // Unlock mutex
    }
    pthread_exit(NULL);  // Terminate the thread
}

// Thread 3: Reads the student data from the file and prints it to the terminal
static void *read_thread(void *args)
{
    int fd;
    char buffer[256];
    size_t byte_read;

    while(1)
    {
        pthread_mutex_lock(&lock);  // Lock mutex for safe reading

        // Wait until the file data is ready to be read
        while(!ready_to_read)
        {
            pthread_cond_wait(&cond_write, &lock);  // Wait until signaled by the write thread
        }

        // Open the file for reading
        fd = open("thongtinsinhvien.txt", O_RDONLY);
        if (fd == -1)
        {
            printf("Error opening file\n");
            pthread_mutex_unlock(&lock);
            continue;
        }

        // Read data from the file and print it to the terminal
        printf("\n==== Reading student information from file ====\n");
        while((byte_read = read(fd, buffer, sizeof(buffer) -1 )) > 0)
        {
            buffer[byte_read] = '\0';  // Null-terminate the string
            printf("%s", buffer);      // Print the data
        }
        printf("\n");
        close(fd);  // Close the file

        // Reset the flag and signal the input thread to continue
        ready_to_read = 0;
        pthread_cond_signal(&cond_input);  // Signal the input thread to input new data
        pthread_mutex_unlock(&lock);  // Unlock mutex
    }
    pthread_exit(NULL);  // Terminate the thread
}

int main(int argc, char const *argv[])
{
    pthread_t pthread_id1, pthread_id2, pthread_id3;  // Thread IDs

    int ret;
    // Create the threads

    // Create the input thread (thread 1)
    if ((ret = pthread_create(&pthread_id1, NULL, input_thread, NULL)) != 0)  
    {
        printf("pthread_create() error number %d\n", ret);  // Error if thread creation fails
        return -1;
    }

    // Create the write thread (thread 2)
    if ((ret = pthread_create(&pthread_id2, NULL, write_thread, NULL)) != 0)
    {
        printf("pthread_create() error number %d\n", ret);  // Error if thread creation fails
        return -1;
    }

    // Create the read thread (thread 3)
    if ((ret = pthread_create(&pthread_id3, NULL, read_thread, NULL)) != 0)
    {
        printf("pthread_create() error number %d\n", ret);  // Error if thread creation fails
        return -1;
    }

    // Wait for all threads to complete
    pthread_join(pthread_id1, NULL);
    pthread_join(pthread_id2, NULL);
    pthread_join(pthread_id3, NULL);

    return 0; 
}
