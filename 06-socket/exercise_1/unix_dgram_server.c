#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SERVER_SOCKET_PATH "./unix_dgram_socket"  // Path to the server socket
#define BUFFER_SIZE 128  // Buffer size for messages

int main() {
    int sockfd;  // Socket file descriptor
    struct sockaddr_un server_addr, client_addr;  // Structures to hold server and client addresses
    socklen_t client_addr_len;  // Length of the client's address structure
    char buffer[BUFFER_SIZE];  // Buffer to store received messages

    // Create a Unix Datagram Socket
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket error");  // Print error if socket creation fails
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(struct sockaddr_un));  // Zero out the memory for server address structure
    server_addr.sun_family = AF_UNIX;  // Set the address family to Unix domain
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);  // Set the path to the server's socket file

    // Bind the socket to the address
    unlink(SERVER_SOCKET_PATH);  // Remove any existing file at the socket path
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("bind error");  // Print error if binding fails
        exit(EXIT_FAILURE);
    }

    printf("Server is listening at: %s\n", SERVER_SOCKET_PATH);  // Inform that the server is ready

    // Loop to receive data from clients and send responses
    while (1) {
        client_addr_len = sizeof(struct sockaddr_un);  // Set the length of the client's address structure
        // Receive data from the client
        ssize_t numBytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (numBytes == -1) {
            perror("recvfrom error");  // Print error if receiving data fails
            exit(EXIT_FAILURE);
        }
        buffer[numBytes] = '\0';  // Null-terminate the received string
        printf("Received message from client: %s\n", buffer);  // Print the client's message

        // Send a response back to the client
        const char *response = "Server has received your message!";
        if (sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, client_addr_len) == -1) {
            perror("sendto error");  // Print error if sending the response fails
            exit(EXIT_FAILURE);
        }
    }

    // Close the socket after communication ends (although in this loop, the program runs indefinitely)
    close(sockfd);
    return 0;
}
