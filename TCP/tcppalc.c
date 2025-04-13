#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<strings.h>
int main()
{
	int clientsocket,port,num,result;
	struct sockaddr_in serveraddr;
	socklen_t len;
	clientsocket=socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&serveraddr,sizeof(serveraddr));
	len=sizeof(serveraddr);
	serveraddr.sin_family=AF_INET;
	printf("enter the port number \n");
	scanf("%d",&port);
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	printf("Connecting to the server \n");
	connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	printf("Connected to the server \n");
	printf("enter the number\n");
	scanf("%d",&num);
	printf("sending number to the server \n");
	send(clientsocket,&num,sizeof(num),0);
	printf("Number sent to server..Waiting for result \n");
	recv(clientsocket,&result,sizeof(result),0);
	if(result==1)
	{
		printf("the number is pallindrome \n");
	}
	else
	{
		printf(" the number is not pallindrome \n");
	}
	close(clientsocket);
}

