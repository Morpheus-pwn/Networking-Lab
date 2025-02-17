#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 5000
#define MAXLINE 1000
int main()
{
	char buffer[MAXLINE];
	char message[MAXLINE];
	int sockfd, n;
	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
		{
			printf("\nError: Connect Failed\n");
			exit(0);
		}
	printf("Enter message to send: ");
	fgets(message, sizeof(message), stdin);
	sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)NULL, sizeof(servaddr));
	recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)NULL, NULL);
	printf("Response from server: %s\n", buffer);
	close(sockfd);
	return 0;
}
