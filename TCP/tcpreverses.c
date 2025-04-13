#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<strings.h>
int reverse(int num)
{
	int digit=0,reversed=0;
	while(num!=0)
	{
		digit=num%10;
		reversed=reversed*10+digit;
		num/=10;
	}
	return reversed;
}
int main()
{
	int serversocket,clientsocket,num,result,port;
	struct sockaddr_in serveraddr,clientaddr;
	socklen_t len;
	serversocket=socket(AF_INET,SOCK_STREAM,0);
	bzero((char*)&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	printf("enter the port number \n");
	scanf("%d",&port);
	serveraddr.sin_port=htons(port);
	serveraddr.sin_addr.s_addr=INADDR_ANY;
	bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	listen(serversocket,5);
	bzero((char*)&clientaddr,sizeof(clientaddr));
	len=sizeof(clientaddr);
	printf("Waiting for client connection.... \n");
	clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&len);
	printf("Client connected..\n");
	printf("receving number from client \n");
	read(clientsocket,&num,sizeof(num));
	printf("number recivied is %d..sending back result to client \n",num);
	result=reverse(num);
	write(clientsocket,&result,sizeof(result));
	printf("THe reversed number is %d",result);
	close(serversocket);
	close(clientsocket);
}

