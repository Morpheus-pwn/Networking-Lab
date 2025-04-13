#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
#include<arpa/inet.h>

int main() {
    int clientsocket, port, num;
    struct sockaddr_in serveraddr;
    socklen_t len;
    struct hostent *server;
    char buffer[50];

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char*)&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;

    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    len = sizeof(serveraddr);

    printf("Enter a number to find its factorial: ");
    scanf("%d", &num);

    sendto(clientsocket, &num, sizeof(num), 0, (struct sockaddr*)&serveraddr, len);
    printf("\nNumber sent to server. Waiting for factorial...\n");

    int result;
    recvfrom(clientsocket, &result, sizeof(result), 0, (struct sockaddr*)&serveraddr, &len);

    printf("Factorial received from server: %d\n", result);

    close(clientsocket);
    return 0;
}
