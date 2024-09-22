#include <stdio.h>          // Standard input/output library
#include <stdlib.h>         // Standard library, used for memory management, random numbers, etc.
#include <string.h>         // Library for string manipulation functions like memset(), strncmp(), etc.
#include <errno.h>          // Error handling with perror(), etc.
#include <sys/socket.h>     // Provides socket-related structures and functions (like socket(), connect())
#include <netinet/in.h>     // Contains constants and structures needed for internet domain addresses (like sockaddr_in)
#include <arpa/inet.h>      // Functions for manipulating IP addresses (like inet_pton())
#include <unistd.h>         // Standard symbolic constants and types, provides close(), read(), and write() functions

#define BUFF_SIZE 256       // Define a buffer size constant
#define handle_error(msg) \
    do { perror(msg); \
             exit(EXIT_FAILURE); \
        } \
    while (0)  // Macro to handle errors: prints the error message and exits the program

/* Function to handle the chat communication between the client and server */
void chat_func(int server_fd) {
    int numb_write, numb_read;                  // Variables to store the number of bytes written and read
    char recvbuff[BUFF_SIZE];                   // Buffer for receiving messages from the server
    char sendbuff[BUFF_SIZE];                   // Buffer for sending messages to the server
    
    while (1) {                                 // Infinite loop to continuously send and receive messages
        memset(sendbuff, '0', BUFF_SIZE);       // Clear the send buffer (initialize with '0')
        memset(recvbuff, '0', BUFF_SIZE);       // Clear the receive buffer (initialize with '0')
        
        printf("Please enter the message: ");   // Prompt the user to enter a message
        fgets(sendbuff, BUFF_SIZE, stdin);      // Get the user input and store it in the send buffer
        
        /* Write the message from the client to the server */
        numb_write = write(server_fd, sendbuff, sizeof(sendbuff));  // Send the content of the send buffer to the server
        if (numb_write == -1)                   // If writing fails, handle the error
            handle_error("write()");

        /* Check if the client wants to exit */
        if (strncmp("exit", sendbuff, 4) == 0) { // Compare the first 4 characters to see if the user typed "exit"
            printf("Client exit ...\n");        // Inform the client is exiting
            break;                              // Break the loop and end the chat function
        }

        /* Read the message from the server */
        numb_read = read(server_fd, recvbuff, sizeof(recvbuff));    // Read the server's response into the receive buffer
        if (numb_read < 0)                    // If reading fails, handle the error
            handle_error("read()");

        /* Check if the server has sent an exit message */
        if (strncmp("exit", recvbuff, 4) == 0) {  // If the server sends "exit", end the communication
            printf("Server exit ...\n");        // Inform that the server has exited
            break;                              // Break the loop and end the chat function
        }

        printf("\nMessage from Server: %s\n", recvbuff);   // Print the message received from the server
    }

    close(server_fd);  // Close the socket connection when done
}

int main(int argc, char *argv[]) {
    int portno;                          // Variable to store the port number
    int server_fd;                       // File descriptor for the socket connection
    struct sockaddr_in serv_addr;        // Structure to hold the server address (IP and port)
    memset(&serv_addr, '0', sizeof(serv_addr));  // Initialize the server address structure with '0'

    /* Check if the correct number of arguments is passed (server address and port number) */
    if (argc < 3) {    // If less than 3 arguments are provided
        printf("command : ./client <server address> <port number>\n");  // Show the correct command format
        exit(1);       // Exit the program if arguments are missing
    }
    
    /* Convert the port number (from string to integer) */
    portno = atoi(argv[2]);   // Convert the second argument (port number) from string to integer
    
    /* Set up the server address */
    serv_addr.sin_family = AF_INET;            // Set address family to AF_INET for IPv4
    serv_addr.sin_port = htons(portno);        // Set the port number and convert it to network byte order using htons()
    
    // Convert the server address from text (argv[1]) to binary form, and store it in serv_addr.sin_addr
    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) == -1) 
        handle_error("inet_pton()");   // If conversion fails, handle the error
    
    /* Create the socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);   // Create a TCP socket (SOCK_STREAM specifies TCP protocol)
    if (server_fd == -1)                           // Check if the socket creation was successful
        handle_error("socket()");                  // If socket creation fails, handle the error

    /* Connect the client to the server */
    if (connect(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) 
        handle_error("connect()");                 // If the connection fails, handle the error

    /* Start the chat function to communicate with the server */
    chat_func(server_fd);  // Call the chat function, passing the server file descriptor (socket)

    return 0;              // End the program
}
