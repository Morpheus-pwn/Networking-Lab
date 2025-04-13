#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>

int main() {
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    socklen_t len;
    int number, result;

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char*)&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(serveraddr);

    printf("Enter a number to check for Armstrong: ");
    scanf("%d", &number);

    sendto(clientsocket, &number, sizeof(number), 0, (struct sockaddr*)&serveraddr, len);
    printf("Number sent to server. Waiting for result...\n");

    recvfrom(clientsocket, &result, sizeof(result), 0, (struct sockaddr*)&serveraddr, &len);

    if (result == 1) {
        printf("It is an Armstrong number.\n");
    } else {
        printf("It is NOT an Armstrong number.\n");
    }

    close(clientsocket);
    return 0;
}
