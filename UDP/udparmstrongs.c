#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>

int isArmstrong(int num) {
    int temp = num, sum = 0, digits = 0;

    while (temp != 0) {
        digits++;
        temp /= 10;
    }
    temp = num;
    
    while (temp != 0) {
        int digit = temp % 10;
        int power = 1;

        for (int i = 0; i < digits; i++) {
            power *= digit;
        }

        sum += power;
        temp /= 10;
    }

    return sum == num;
}

int main() {
    int serversocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len;
    int number, result;

    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char*)&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    printf("Enter the port number: ");
    scanf("%d", &port);
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("\nWaiting for a number from client...\n");

    bzero((char*)&clientaddr, sizeof(clientaddr)); 
    len = sizeof(clientaddr);

    recvfrom(serversocket, &number, sizeof(number), 0, (struct sockaddr*)&clientaddr, &len);
    printf("Received number: %d\n", number);

    if (isArmstrong(number)) {
        result = 1;
    } else {
        result = 0;
    }

    if (result == 1) {
        printf("Sending result: Armstrong\n");
    } else {
        printf("Sending result: Not Armstrong\n");
    }

    sendto(serversocket, &result, sizeof(result), 0, (struct sockaddr*)&clientaddr, len);
    close(serversocket);
    return 0;
}
