#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 50005

int main(){
	int opt = 1;
	int s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	struct sockaddr_in serv_addr;
	char buffer[2048] = {0};
	int addrlen = sizeof(address);

	setsockopt(s , SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
	
	address.sin_family = AF_INET;
	address.sin_addr.s_addr= INADDR_ANY;
	address.sin_port = htons ( PORT );

	if (bind(s, (struct sockaddr *)&address, sizeof(address))<0){ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	if (listen(s, 10) < 0) { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	int new_sock, valread;
	while (1){
	if ((new_sock = accept(s, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0){ 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
	valread = read( new_sock , buffer, 1024); 
	printf("%s\n",buffer ); 
	
	//connect to the next client
	//then send the message
	
	if ((new_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(50002); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(new_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
   	
	send(new_sock , buffer , strlen(buffer) , 0 ); 
	//printf("%s\n", buffer); 
	}
	return 0; 
	//bind(s, ( struct sockaddr *)& address, sizeof(address));
	//listen(s, 10)
}
