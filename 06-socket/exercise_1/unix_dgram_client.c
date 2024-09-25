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
    struct sockaddr_un server_addr;  // Structure to hold server address
    char buffer[BUFFER_SIZE];  // Buffer to store received messages

    // Create a Unix Datagram Socket
    sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket error");  // Print error if socket creation fails
        exit(EXIT_FAILURE);
    }

    // Configure server address
    memset(&server_addr, 0, sizeof(struct sockaddr_un));  // Clear the memory for the server address structure
    server_addr.sun_family = AF_UNIX;  // Set address family to Unix domain
    strncpy(server_addr.sun_path, SERVER_SOCKET_PATH, sizeof(server_addr.sun_path) - 1);  // Set the server socket path

    // Send a message to the server
    const char *message = "Hello from client!";  // Message to send
    if (sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) == -1) {
        perror("sendto error");  // Print error if sending the message fails
        exit(EXIT_FAILURE);
    }

    // Receive a response from the server
    ssize_t numBytes = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);  // Receive data from the server
    if (numBytes == -1) {
        perror("recvfrom error");  // Print error if receiving data fails
        exit(EXIT_FAILURE);
    }
    buffer[numBytes] = '\0';  // Null-terminate the received message
    printf("Response from server: %s\n", buffer);  // Print the server's response

    // Close the socket after communication is done
    close(sockfd);
    return 0;
}
