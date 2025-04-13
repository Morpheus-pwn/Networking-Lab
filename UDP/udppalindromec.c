#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sockfd, port, num, result;
    struct sockaddr_in serveraddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    printf("Enter port: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(serveraddr);

    printf("Enter a number to check: ");
    scanf("%d", &num);

    sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr*)&serveraddr, len);
    printf("Sent number to server, waiting for reply...\n");

    recvfrom(sockfd, &result, sizeof(result), 0, (struct sockaddr*)&serveraddr, &len);

    if (result == 1)
        printf("Result: It is a Palindrome number.\n");
    else
        printf("Result: It is NOT a Palindrome number.\n");

    close(sockfd);
    return 0;
}
