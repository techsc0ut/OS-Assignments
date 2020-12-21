/* Name: Rahul Khatoliya
   Roll_Number: 2019265 */

#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/types.h>

struct msgEntity {
	long type;
	char message[501];
};

struct msgEntity* get_tokens(int* len) {
	int index = 0;
	struct msgEntity* Tokens = (struct msgEntity*) malloc(sizeof(struct msgEntity));
	Tokens[0].type = 1;
	Tokens[0].message[0] = '\0';
	FILE* fileD = fopen("para1.txt", "r");
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

int main(int argc, char* argv[]) {
	int ID = msgget(75, 0666 | IPC_CREAT);
	int len,index = 0;
	struct msgEntity* Tokens = get_tokens(&len);
	if (Tokens == NULL) {
		perror("Parsing Error");
		return -errno;
	}
	/*Sending Message to the Message Queues*/
	while (++index <= len) {
		msgsnd(ID, (Tokens + index), sizeof(struct msgEntity), IPC_NOWAIT);
	}
	return 0;
}


