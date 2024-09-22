#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>     // Contains structures needed for socket programming
#include <netinet/in.h>     // Contains constants and structures for internet domain addresses
#include <arpa/inet.h>
#include <unistd.h>

#define LISTEN_BACKLOG 50   // Maximum number of connections in the listening queue
#define BUFF_SIZE 256       // Buffer size for messages
#define handle_error(msg) \
    do { perror (msg); \
         exit(EXIT_FAILURE); \
        } \
    while (0)   // Macro for error handling: print error and exit program

/* Chat function for communication between server and client */
void chat_func(int new_socket_fd) {
    int numb_read, numb_write;                // Variables to store the number of bytes read and written
    char sendbuff[BUFF_SIZE];                 // Buffer to store the message to send
    char recvbuff[BUFF_SIZE];                 // Buffer to store the message received
    
    while (1) {
        // Clear the buffers before each communication
        memset(sendbuff, '0', BUFF_SIZE);
        memset(recvbuff, '0', BUFF_SIZE);

        /* Read data from the socket */
        /* The read function blocks until data is available */
        numb_read = read(new_socket_fd, recvbuff, BUFF_SIZE);  // Read the client's message
        if(numb_read == -1)  // Error handling if reading from the socket fails
            handle_error("read()");
        
        // If the message from the client is "exit", end the chat
        if (strncmp("exit", recvbuff, 4) == 0) {
            system("clear");  // Clear the terminal screen (for aesthetic purposes)
            break;            // Exit the loop
        }
        
        printf("\nMessage from Client: %s\n", recvbuff);  // Display the message received from the client

        /* Get a response from the server operator (via keyboard input) */
        printf("Please respond to the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);   // Get input from the server operator
        
        /* Write data to the client via the socket */
        numb_write = write(new_socket_fd, sendbuff, sizeof(sendbuff));  // Send the server's response to the client
        if (numb_write == -1)  // Error handling if writing to the socket fails
            handle_error("write()");
        
        // If the server sends "exit", end the chat
        if (strncmp("exit", sendbuff, 4) == 0) {
            system("clear");  // Clear the terminal screen
            break;            // Exit the loop
        }

        sleep(1);  // Introduce a 1-second delay for smoother communication flow
    }
    close(new_socket_fd);  // Close the socket once the chat session is finished
}

int main(int argc, char const *argv[]) {
    int port_no, len, opt = 1;  // Variables for port number, address length, and socket options
    int server_fd, new_socket_fd;  // File descriptors for the server and new client sockets
    struct sockaddr_in serv_addr, client_addr;  // Structures to hold server and client addresses

    /* Get the port number from the command line */
    if (argc < 2) {  // If no port number is provided
        printf("No port provided\ncommand: ./server <port number>\n");  // Inform the user to provide a port number
        exit(EXIT_FAILURE);  // Exit the program
    } else {
        port_no = atoi(argv[1]);  // Convert the command line argument (string) to an integer (port number)
    }

    /* Clear the server and client address structures */
    memset(&serv_addr, 0x00, sizeof(struct sockaddr_in));  // Clear server address structure
    memset(&client_addr, 0x00, sizeof(struct sockaddr_in));  // Clear client address structure

    /* Create a socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);  // Create a TCP socket (SOCK_STREAM) for IPv4 (AF_INET)
    if(server_fd == -1)  // Error handling if socket creation fails
        handle_error("socket()");

    /* Avoid "address already in use" error */
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) == -1)
        handle_error("setsockopt()");

    /* Initialize server address */
    serv_addr.sin_family = AF_INET;  // Set address family to IPv4
    serv_addr.sin_port = htons(port_no);  // Set port number and convert it to network byte order using htons()
    serv_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available network interfaces (local IP addresses)

    /* Bind the socket to the server address */
    if (bind(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)  // Bind the socket to the IP and port
        handle_error("bind()");

    /* Listen for incoming connections (up to LISTEN_BACKLOG connections in the queue) */
    if (listen(server_fd, LISTEN_BACKLOG) == -1)
        handle_error("listen()");

    /* Length of the client address */
    len = sizeof(client_addr);

    /* Server enters an infinite loop to accept and handle client connections */
    while (1) {
        printf("Server is listening on port: %d \n....\n", port_no);  // Inform that the server is ready to accept connections

        /* Accept a new connection from a client */
        new_socket_fd = accept(server_fd, (struct sockaddr*)&client_addr, (socklen_t *)&len);  // Accept a new client connection
        if (new_socket_fd == -1)  // Error handling if accepting connection fails
            handle_error("accept()");

        system("clear");  // Clear the terminal screen when a new connection is accepted

        printf("Server: got connection\n");  // Inform that a connection has been established
        chat_func(new_socket_fd);  // Call the chat function to handle communication with the client
    }

    /* Close the server socket when done */
    close(server_fd);

    return 0;
}
