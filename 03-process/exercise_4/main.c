#include <stdio.h>       
#include <stdlib.h>  
#include <unistd.h>      // Provides the fork()
#include <string.h>      
#include <fcntl.h>       // Provides for file control operations (e.g., open() with different flags)
#include <sys/wait.h>    // Provides the waitpid()
#include <sys/stat.h>    // Provides permission settings for file creation

// Function to write a given message to a file
void write_to_file(char *message, char *file_path);

int main(int argc, char const *argv[])
{
    pid_t pid_B, pid_C, pid_child_B, pid_child_C;  // Variables to store process IDs for processes B, C, and their children
    char *file_name = "output.txt";               // The name of the file to which the processes will write

    // Process A creates process B using fork()
    pid_B = fork(); 
    if (pid_B == 0)
    {
        // Code executed by process B
        pid_child_B = fork();  // Process B creates its own child process B'
        if (pid_child_B == 0)
        {
            // Code executed by process B'
            write_to_file("Hello I'm  B' process\n", file_name);  // B' writes its message to the file
            exit(EXIT_SUCCESS);  
        }
        else
        {
            // Code executed by process B after B' has completed
            waitpid(pid_child_B, NULL, 0);  // Wait for B' to finish execution
            write_to_file("Hello I'm B process\n", file_name);  // B writes its own message
            exit(EXIT_SUCCESS);  
        }
    }
    else
    {
        // Process A creates process C using fork()
        pid_C = fork();
        if (pid_C == 0)
        {
            // Code executed by process C
            pid_child_C = fork();  // Process C creates its own child process C'
            if (pid_child_C == 0)
            {
                // Code executed by process C'
                write_to_file("Hello I'm  C' process\n", file_name);  // C' writes its message to the file
                exit(EXIT_SUCCESS); 
            }
            else
            {
                // Code executed by process C after C' has completed
                waitpid(pid_child_C, NULL, 0);  // Wait for C' to finish execution
                write_to_file("Hello I'm C process\n", file_name);  // C writes its own message
                exit(EXIT_SUCCESS);  
            }
        }
        else
        {
            // Code executed by process A after both B and C processes have completed
            waitpid(pid_C, NULL, 0);  // Wait for process C to finish first

            // Then, wait for process B to finish
            waitpid(pid_B, NULL, 0);  
        }
    }

    return 0;
}

void write_to_file(char *message, char *file_path)
{
    // Open the file for writing; create the file if it doesn't exist, and append new data
    int fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND , 0777);  
    if (fd < 0)
    {
        perror("Error opening file\n");  
    }

    // Write the message to the file
    int write_byte = write(fd, message, strlen(message));  
    if (write_byte < 0)
    {
        perror("Error writing file\n");  
        exit(EXIT_FAILURE); 
    }
    close(fd);  // Close the file descriptor 
}
