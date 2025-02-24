#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

struct frame {
    int packet[40];
};

struct ack {
    int acknowledge[40];
};

int main() {
    int clientsocket;
    struct sockaddr_in serveraddr;
    socklen_t len;
    struct hostent *server;
    struct frame f1;
    int windowsize, totalpackets, totalframes, i = 0, j = 0, framesreceived = 0, k, l, buffer;
    struct ack acknowledgement;
    char req[50];

    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientsocket < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5018);
    
    server = gethostbyname("127.0.0.1");
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    
    bcopy((char*)server->h_addr, (char*)&serveraddr.sin_addr.s_addr, sizeof(server->h_addr));

    printf("Sending request to the server\n");
    sendto(clientsocket, "HI IAM CLIENT", strlen("HI IAM CLIENT"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("\nWaiting for reply\n");
    recvfrom(clientsocket, req, sizeof(req), 0, (struct sockaddr*)&serveraddr, &len);
    printf("\nThe server has to send:\t%s\n", req);

    printf("\nEnter the window size\n");
    scanf("%d", &windowsize);

    printf("\nSending window size\n");
    sendto(clientsocket, (char*)&windowsize, sizeof(windowsize), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("\nWaiting for the server response\n");
    recvfrom(clientsocket, (char*)&totalpackets, sizeof(totalpackets), 0, (struct sockaddr*)&serveraddr, &len);
    printf("\nTotal packets are :\t%d\n", totalpackets);
    sendto(clientsocket, "RECEIVED", strlen("RECEIVED"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    recvfrom(clientsocket, (char*)&totalframes, sizeof(totalframes), 0, (struct sockaddr*)&serveraddr, &len);
    printf("\nTotal number of frames or windows are:\t%d\n", totalframes);
    sendto(clientsocket, "RECEIVED", strlen("RECEIVED"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("\nStarting the process of receiving\n");
    while (i < totalpackets) {
        printf("\nInitializing the received buffer\n");
        printf("\nThe expected frame is %d with packets:", framesreceived);
        
        j = 0;
        buffer = i;
        while (j < windowsize && i < totalpackets) {
            printf("%d", i);
            i++;
            j++;
        }
        
        printf("\nWaiting for the frame\n");
        recvfrom(clientsocket, (char*)&f1, sizeof(f1), 0, (struct sockaddr*)&serveraddr, &len);
        printf("\nReceived frame %d\n\nEnter -1 to send negative acknowledgement for the following packets\n", framesreceived);
        
        j = 0;
        i = buffer;
        k = 0;
        l = buffer;
        
        while (j < windowsize && i < totalpackets) {
            printf("\nPacket:%d\n", f1.packet[j]);
            scanf("%d", &acknowledgement.acknowledge[j]);
            
            if (acknowledgement.acknowledge[j] == -1) {
                if (k == 0) {
                    i = f1.packet[j];
                    k = 1;
                }
            }
            j++;
            l++;
        }
        
        framesreceived++;
        sendto(clientsocket, (char*)&acknowledgement, sizeof(acknowledgement), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    }

    printf("\nAll frames received successfully\nClosing connection with the server\n");
    close(clientsocket);
    return 0;
}
 
