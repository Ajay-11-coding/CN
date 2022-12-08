#include<stdio.h>                                                                                                                              
#include<sys/types.h>                                                                                                                          
#include<sys/socket.h>                                                                                                                         
#include<netinet/in.h>                                                                                                                         
#include<stdlib.h>                                                                                                                             
#include<strings.h>                                                                                                                            
#include<string.h>                                                                                                                             
#include<unistd.h>                                                                                                                             
#define PORT 5000                                                                                                                              
                                                                                                                                               
void dostuff(int);                                                                                                                             
void error(char* msg){                                                                                                                         
        perror(msg);                                                                                                                           
        exit(1);                                                                                                                               
}                                                                                                                                              
                                                                                                                                               
int main(){                                                                                                                                    
        int sockfd, newsockfd, portno, clilen, pid;                                                                                            
        struct sockaddr_in serv_addr, cli_addr;                                                                                                
        sockfd=socket(AF_INET, SOCK_STREAM,0);                                                                                                 
        if(sockfd<0)                                                                                                                           
                error("Error on opening socket");                                                                                              
        bzero((char*)&serv_addr, sizeof(serv_addr));                                                                                           
        portno=PORT;                                                                                                                           
        serv_addr.sin_family=AF_INET;                                                                                                          
        serv_addr.sin_addr.s_addr=INADDR_ANY;                                                                                                  
        serv_addr.sin_port=htons(portno);                                                                                                      
        if(bind(sockfd,(struct sockaddr*) &serv_addr, sizeof(serv_addr))<0)                                                                    
                error("Error on binding");                                                                                                     
        listen(sockfd,5);                                                                                                                      
        clilen=sizeof(cli_addr);                                                                                                               
        while(1){                                                                                                                              
                newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);                                                                  
                if(newsockfd<0)                                                                                                                
                        error("Error on accept");                                                                                              
                pid=fork();                                                                                                                    
                if(pid<0)                                                                                                                      
                        error("Error on fork");                                                                                                
                if(pid==0){                                                                                                                    
                        close(sockfd);                                                                                                         
                        dostuff(newsockfd);                                                                                                    
                        exit(0);                                                                                                               
                }                                                                                                                              
                else                                                                                                                           
                        close(newsockfd);                                                                                                      
        }                                                                                                                                      
        return 0;                                                                                                                              
}                                                                                                                                              
                                                                                                                                               
void dostuff(int sock){                                                                                                                        
        int n;                                                                                                                                 
        char buffer[256];                                                                                                                      
        bzero(buffer,256);                                                                                                                     
        n=read(sock,buffer,255);                                                                                                               
        if(n<0)                                                                                                                                
                error("Error reading from socket");                                                                                            
        printf("Here is the message: %s\n", buffer);                                                                                           
        n=write(sock,"I got the message",18);                                                                                                  
        if(n<0)                                                                                                                                
                error("Error writing to socket");                                                                                              
}                                                                                                                                              
  
