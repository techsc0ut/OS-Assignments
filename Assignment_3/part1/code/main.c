#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
	
	pid_t child_pid, w;
	int status;
	child_pid = fork();
	
	if (child_pid == -1) {
		
		perror("fork");
		exit(EXIT_FAILURE);
		
	}
/* Code executed by child process */
	if (child_pid == 0) {                                                  
		
		printf("<<<<<<<<<<<<<<<<<<______________________________Section - A__________________________>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

		FILE *fp = fopen("data.csv", "r");

		if (!fp) {
			printf("Can't open file\n");
			return 0;
		}

		char buf[1024];
		int student_count = 0;
		int detail_count = 0;
		int avg=0;
		
		while (fgets(buf, 1024, fp)) {
			
			detail_count = 0;
			student_count++;
			if (student_count == 1) {
				continue;
			}

        /* Checking Section of the Student */
			char check_line[1024];
			strcpy(check_line,buf);

			char *section=strtok(check_line," ");
			
			section=strtok(NULL," ");
			
        // printf("%s\n",check );
			if(strcmp(section,"A")==0){
				
				char *student_details = strtok(buf, " ");
				
				while (student_details) {

					if (detail_count == 0) {
						printf("Student ID :\t");
					}
					if (detail_count == 1) {
						printf("Section :\t");
					}
					if (detail_count == 2) {
						printf("Assignment-1 :\t");
						avg+=atoi(student_details);
					}
					if (detail_count == 3) {
						printf("Assignment-2 :\t");
						avg+=atoi(student_details);
					}
					if (detail_count == 4) {
						printf("Assignment-3 :\t");
						avg+=atoi(student_details);
					}
					if (detail_count == 5) {
						printf("Assignment-4 :\t");
						avg+=atoi(student_details);
					}
					if(detail_count<=5){
						if(detail_count==4){
							printf("%s\n", student_details);
							student_details = strtok(NULL, ","); 
							
						}else{
							printf("%s\n", student_details);
							student_details = strtok(NULL, " ");
						}
						detail_count++;
					}else{
						break;
					}
					
				}
				avg/=4;
				printf("Average : %d\n",avg);
				printf("\n");
			}
			
		}
		fclose(fp);

		printf("<<<<<<<<<<<<<<<<<<______________________________Section - A finished__________________________>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n\n\n");

		exit(EXIT_SUCCESS);
	}

/* Code executed by parent process */
	else {                                                            
		w = waitpid(child_pid, &status, WUNTRACED | WCONTINUED);
/* WUNTRACED: Reports on stopped child processes as well as terminated ones. */
/* WCONTINUED: Reports the status of any continued child processes as well as terminated ones. */

		if (w == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		else if (WIFEXITED(status)) {
			printf("<<<<<<<<<<<<<<<<<<______________________________Section - B__________________________>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
			
			FILE *fp = fopen("data.csv", "r");

			if (!fp) {
				printf("Can't open file\n");
				return 0;
			}

			char buf[1024];
			int student_count = 0;
			int detail_count = 0;
			int avg=0;
			
			while (fgets(buf, 1024, fp)) {
				
				detail_count = 0;
				student_count++;
				if (student_count == 1) {
					continue;
				}

        /* Checking Section of the Student */
				char check_line[1024];
				strcpy(check_line,buf);

				char *section=strtok(check_line," ");
				
				section=strtok(NULL," ");
				
        // printf("%s\n",check );
				if(strcmp(section,"B")==0){
					
					char *student_details = strtok(buf, " ");
					
					while (student_details) {

						if (detail_count == 0) {
							printf("Student ID :\t");
						}
						if (detail_count == 1) {
							printf("Section :\t");
						}
						if (detail_count == 2) {
							printf("Assignment-1 :\t");
							avg+=atoi(student_details);
						}
						if (detail_count == 3) {
							printf("Assignment-2 :\t");
							avg+=atoi(student_details);
						}
						if (detail_count == 4) {
							printf("Assignment-3 :\t");
							avg+=atoi(student_details);
						}
						if (detail_count == 5) {
							printf("Assignment-4 :\t");
							avg+=atoi(student_details);
						}
						if(detail_count<=5){
							if(detail_count==4){
								printf("%s\n", student_details);
								student_details = strtok(NULL, ","); 
								
							}else{
								printf("%s\n", student_details);
								student_details = strtok(NULL, " ");
							}
							detail_count++;
						}else{
							break;
						}
						
					}
					avg/=4;
					printf("Average : %d\n",avg);
					printf("\n");
				}
				
			}
			fclose(fp);
			printf("<<<<<<<<<<<<<<<<<<______________________________Section - B finished__________________________>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

		} 
	}
	exit(EXIT_SUCCESS);
}
