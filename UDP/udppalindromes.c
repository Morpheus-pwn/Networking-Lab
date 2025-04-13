#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>

int isPalindrome(int num) {
    int reversed = 0, digit;
    int temp = num;
    
    while (temp > 0) {
        digit = temp % 10;
        reversed = reversed * 10 + digit;
        temp /= 10;
    }

    return reversed == num;
}

int main() {
    int sockfd, port, num, result;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    printf("Enter port: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("Server waiting for input...\n");

    len = sizeof(clientaddr);
    recvfrom(sockfd, &num, sizeof(num), 0, (struct sockaddr*)&clientaddr, &len);

    printf("Received: %d\n", num);
    result = isPalindrome(num);

    sendto(sockfd, &result, sizeof(result), 0, (struct sockaddr*)&clientaddr, len);
    printf("Sent result back to client: %s\n", result ? "Palindrome" : "Not Palindrome");

    close(sockfd);
    return 0;
}
