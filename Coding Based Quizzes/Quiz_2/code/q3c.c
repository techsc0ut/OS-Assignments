/* Name: Rahul Khatoliya
   Roll_Number: 2019265 */
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 501 

int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	struct sockaddr_in servaddr, cliaddr; 

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	servaddr.sin_family = AF_INET; // IPv4 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 

	if ( bind(sockfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 ){ 
		perror("SOCKET SERVER "); 
		exit(EXIT_FAILURE); 
	} 
	printf("\n");
	int lines = 2;// Since we have to Wait only for two clients , for para1.txt and para2.txt.
    while (lines) {
		int len, n;
		len = sizeof(cliaddr);  //len is value/resuslt
		n = recvfrom(sockfd, (char*) buffer,500, MSG_WAITALL, (struct sockaddr*) &cliaddr, &len);
		buffer[n] = '\0';
		if (n > 0 && buffer[n-1] == '\n') {
			lines--;
			buffer[n-1] = '\0';
		}
		if(n==0){
			lines--;
		}
		printf("%s\n", buffer);
	}
	printf("\n");
	return 0; 
} 
