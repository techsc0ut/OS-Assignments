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
	char token[501];
};
int main(int argc, char* argv[]) {
	int ID = msgget(75, 0666 | IPC_CREAT );
	struct msgEntity message;
	printf("\n");
	while ((msgrcv(ID, &message, sizeof(struct msgEntity),1, IPC_NOWAIT)) != -1) {
		printf("%s ", message.token);
	}
	printf("\n");
	printf("\n");
	msgctl(ID, IPC_RMID , NULL);
	return 0;
}

