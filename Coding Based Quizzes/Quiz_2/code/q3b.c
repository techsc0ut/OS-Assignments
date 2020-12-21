/* Name: Rahul Khatoliya
   Roll_Number: 2019265 */
#include <stdio.h> 
#include <errno.h>
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT	 8080 
#define MAXLINE 1024 

struct msgEntity {
	long type;
	char message[501];
};

struct msgEntity* get_tokens(int* len) {
	int index = 0;
	struct msgEntity* Tokens = (struct msgEntity*) malloc(sizeof(struct msgEntity));
	Tokens[0].type = 1;
	Tokens[0].message[0] = '\0';
	FILE* fileD = fopen("para2.txt", "r");
	char* line = NULL;
	size_t len2 = 0;
	ssize_t check;
	if (fileD == NULL) {
		return NULL;
	}
	while ((check = getline(&line, &len2, fileD)) > 0) {
		line[check-1] = '\0';
		int started = 0;
		int linIndex = 0;
		while (line[linIndex] != '\0') {
			if (started) {
				if (line[linIndex] != ' ') {	
					Tokens[index].message[started] = line[linIndex];
					started++;
				} else {
					Tokens[index].message[started] = '\0';
					started = 0;
				}
			} else {
				 if(line[linIndex] != ' '){
					index++;
					Tokens = (struct msgEntity*) realloc(Tokens, sizeof(struct msgEntity) * (index+1));
					Tokens[index].type = 1;
					Tokens[index].message[started] = line[linIndex];
					started = 1;
				} 			
			}
			linIndex++;
		}
		if (started) {
			Tokens[index].message[started] = '\0';
			started = 0;
		}
	}
	*len = index;
	fclose(fileD);
	return Tokens;
}

int main() { 
	int sockfd; 
	struct sockaddr_in	 servaddr; 

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ){ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	int n, len; 
	struct msgEntity* Tokens = get_tokens(&len);
	if(Tokens==NULL){
		perror("Token Error:");
		return -errno;
	}
	int index = 0;
	int empty_check = 0;
	while (++index < len){
		char* message = Tokens[index].message;
		sendto(sockfd, (const char *) message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	}
	if (index == len){
		char* message = strcat(Tokens[index].message, "\n");
		sendto(sockfd, (const char *) message, strlen(message), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	}
	if (!empty_check) {
		sendto(sockfd, (const char *) "", 0, MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));
	}
	close(sockfd); 
	return 0; 
} 
