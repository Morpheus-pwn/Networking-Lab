#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
#include<arpa/inet.h>

int factorial(int n) {
    if (n <= 1) return 1;
    else return n * factorial(n - 1);
}

int main() {
    int serversocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    int num, result;

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char*)&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("\nWaiting for number from client...\n");

    bzero((char*)&clientaddr, sizeof(clientaddr));
    len = sizeof(clientaddr);

    recvfrom(serversocket, &num, sizeof(num), 0, (struct sockaddr*)&clientaddr, &len);
    printf("Received number: %d\n", num);

    result = factorial(num);

    printf("Sending factorial: %d\n", result);
    sendto(serversocket, &result, sizeof(result), 0, (struct sockaddr*)&clientaddr, len);

    close(serversocket);
    return 0;
}
