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
	
#define PORT 6784
	
int main()
{
struct sockaddr_in address;
int master_socket,new_socket;
int max_clients=30,client_socket[30];

char buffer[200];
fd_set readfds;
int i;
for(i=0;i<max_clients;i++)
{
client_socket[i]=0;
}
master_socket = socket(AF_INET,SOCK_STREAM,0);
if(master_socket<0)  
    {  
        printf("socket creation failed");  
        return 0; 
    } 
bzero(&(address),sizeof(address));
address.sin_family = AF_INET;  
address.sin_addr.s_addr = INADDR_ANY;  
address.sin_port = htons( PORT );  

if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        printf("bind failed");  
        return 0;
    }  
    
if (listen(master_socket, 3) < 0)
	{
		printf("listen error");
		return 0;
	}
int addrlen = sizeof(address);
int sd;
int j;
int max_sd,a,msg;
char message[100]="hai!client";
while(1)
{
FD_ZERO(&readfds);
FD_SET(master_socket, &readfds);  
max_sd = master_socket;  
        for (i=0 ; i < max_clients ; i++)  
        {  
            sd = client_socket[i];  

            if(sd > 0) 
            { 
                FD_SET(sd,&readfds);  
            }
            if(sd>max_sd)  
            {
                max_sd=sd; 
            } 
        }  
     
        a = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((a < 0))  
        {  
            printf("selection error");  
        } 
        
       if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket,(struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                printf("accept error");  
                return 0; 
            }  
             
            
            printf("new client with socket fd is %d , ip is : %s , port : %d is connected\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
            if( send(new_socket, message, strlen(message), 0) <0 )  
            {  
                printf("sending error");  
            }  
                
            for (i = 0; i < max_clients; i++)  
            {  
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket; 
                    break;  
                }
            }
        }
        
		for (i = 0; i < max_clients; i++)
		{
			sd = client_socket[i];
				
			if (FD_ISSET( sd , &readfds))
			{
                                int msg=read(sd,buffer,200);
				if (strcmp(buffer,"exit")==0)
				{
					getpeername(sd , (struct sockaddr*)&address ,(socklen_t*)&addrlen);
					printf("Client %d disconnected , ip %s , port %d \n" ,i,inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
					char word[200]="one of the client left";
					for(j=0;j<max_clients;j++)
					{
					if(client_socket[j]>0 && client_socket[j]!=sd)
					{
					send(client_socket[j] , word , strlen(word) , 0 );
					}
					}
					close( sd );
					client_socket[i] = 0;
				}
					
				else
				{
					buffer[msg] = '\0';
					char word1[2000];
					sprintf(word1,"%d client sent %s",i,buffer);
					for(j=0;j<max_clients;j++)
					{
					if(client_socket[j]>0 && client_socket[j]!=sd)
					{
					send(client_socket[j],word1,strlen(word1),0);
					}
					}
					
				}
			}
		}
	}
		
	return 0;		
}
