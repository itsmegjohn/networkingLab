#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888
#define MAXLINE 1024

void die(char *s)
{
    perror(s);
    exit(1);
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[MAXLINE];

    // create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        die("socket creation failed");

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        die("bind failed");

    int n, len;
    for (int i = 0; i < 5; i++)
    {
        // receive message
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';
        printf("Packet received from sender: %s\n", buffer);

        // send acknowledgement
        sendto(sockfd, "ACK", 3, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        printf("Acknowledgement sent for packet %d\n", i);
    }

    close(sockfd);
    return 0;
}

