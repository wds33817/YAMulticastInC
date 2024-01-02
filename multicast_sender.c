// multicast_sender.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define MULTICAST_GROUP "239.0.0.1"
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in multicast_addr;
    char buffer[BUFFER_SIZE];

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set up multicast address structure
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, MULTICAST_GROUP, &multicast_addr.sin_addr);

    // Send multicast messages
    while (1) {
        printf("Enter message to send: ");
        fgets(buffer, sizeof(buffer), stdin);

        if (sendto(sockfd, buffer, strlen(buffer), 0,
                   (struct sockaddr*)&multicast_addr, sizeof(multicast_addr)) == -1) {
            perror("sendto");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
    }

    // Close the socket (not reached in this example)
    close(sockfd);

    return 0;
}

