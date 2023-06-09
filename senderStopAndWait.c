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
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];

    // create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        die("socket creation failed");

    memset(&servaddr, 0, sizeof(servaddr));

    // fill server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;
    for (int i = 0; i < 5; i++)
    {
        // send message
        sprintf(buffer, "Packet %d", i);
        sendto(sockfd, buffer, strlen(buffer), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
        printf("Packet %d sent\n", i);

        // receive acknowledgement
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';
        printf("Acknowledgement received for packet %d: %s\n", i, buffer);
    }

    close(sockfd);
    return 0;
}

