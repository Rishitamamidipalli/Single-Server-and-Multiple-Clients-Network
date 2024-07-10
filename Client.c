#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <errno.h>
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include<pthread.h> 
	

#define PORT 6784
#define MAXI 200
int s;
int flag=0;

void fun_write()
{
char buff[MAXI],msg[MAXI];
bzero(&(buff),sizeof(buff));
while(1)
{
fgets(buff,MAXI,stdin);
buff[strlen(buff)-1]=0;
write(s,buff,strlen(buff));
if(strcmp(buff,"exit")==0)
{
printf("I am leaving");
break;
}
bzero(&(buff),sizeof(buff));
}
flag=1;
}

void fun_read()
{
char buff[MAXI];
while(1)
{
bzero(&(buff),sizeof(buff));
read(s,buff,MAXI);
printf("%s\n",buff);
bzero(&(buff),sizeof(buff));
}
}
	
int main(int argc , char *argv[])
{
        int ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	s = socket(AF_INET,SOCK_STREAM, 0);
        bzero(&(serverAddr),sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(PORT);
	serverAddr.sin_addr.s_addr=INADDR_ANY;
	memset(&(serverAddr.sin_zero),'\0',8);
	ret = connect(s,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
	if(ret<0)
	{
	printf("connection error");
	}
	else
	{
	printf("Connected to Server.\n");
	}
	pthread_t read_t,write_t;
	pthread_create(&read_t,NULL,(void *)fun_read,NULL);
	pthread_create(&write_t,NULL,(void *)fun_write,NULL);
	
	while(1)
	{
	if(flag)
	{
	break;
	}
	}
	
	return 0;
}
