#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//uses a lex file for parsing from git
extern char **getln();

void TheTime(void){


	fprintf(stdout, "unix time: %ld\n",time(NULL));

}

void printArgs(char** Argument, int i){
	int j = 0;
	fprintf(stdout, "argc = %d, args = ",i - 1);
	for (j = 1; j < i; j++){
		fprintf(stdout, "%s ",Argument[j]);
	}
	fprintf(stdout,"\n");
}

void addTheArgs (char **Arguments){
	int j = 0;
	int sum = 0;
	for (j = 1; Arguments[j] != NULL; j++){
		char hex[20];
		strncpy(hex, Arguments[j], 20);
		printf("%s\n",hex);
     	int length = 0;
		int base = 16;
		int i;
		int total = 0;
		int baseValue = 0;

		if (strstr(hex,"0x") != NULL){
			length = strlen(hex) - 1;
			for (i = 2; i <= length; i++){

				baseValue = pow(base,length-(i));

				if (hex[i] >= '0' && hex[i]<= '9'){
					total = hex[i] - 48;
				}
				else if (hex[i] >= 'a' && hex[i]<= 'f'){
					total = hex[i] - 87;
				}
				else if (hex[i] >= 'A' && hex[i]<= 'F'){
					total = hex[i] - 55;
				}
				sum += total * baseValue;
			}
		}
		else {
			sum += atoi(Arguments[j]);
		}
	}
	printf("total Value = %d\n",sum);

}


int main(void) {
	int check, i, j = 0;
	int fileType;
	int fileName = 0;
	char **args;
	char **rebuilt;
	char **BeforePunc;
	
	while(1) {
		args = getln();
		check = 0;
		rebuilt = (char **)malloc(1 * sizeof (char*));
		BeforePunc = (char **)malloc(1 * sizeof (char*));
		j = 0;
		fileType = 0;
		for(i = 0; args[i] != NULL; i++) {
			if (strstr(args[i],">") == NULL && strstr(args[i],"<") == NULL){
				rebuilt = realloc(rebuilt, (j+1) * sizeof(char *));
				rebuilt[j] = (char *)malloc (100 * sizeof (char)); 
				rebuilt[j] = args[i];
				if (check == 0){
					BeforePunc = realloc(BeforePunc, (j+1) * sizeof(char *));
					BeforePunc[j] = (char *)malloc (100 * sizeof (char)); 
					BeforePunc[j] = args[i];
				}
				j++;
			}
			else {
				check++;
				fileType = 1;
				if (strstr(args[i],">") != NULL){
					fileType = 2;
				}
			}
		}
		rebuilt = realloc(rebuilt, (i+1) * sizeof(char *));
		rebuilt[i] = (char *)malloc (100 * sizeof (char)); 
		rebuilt[i] = NULL;
		BeforePunc = realloc(BeforePunc, (i+1) * sizeof(char *));
		BeforePunc[i] = (char *)malloc (100 * sizeof (char)); 
		BeforePunc[i] = NULL;
		fileName = i - 2;


		if (strstr(rebuilt[0],"add") != NULL){
			addTheArgs(rebuilt);
		}
		if(strcmp("arg",rebuilt[0]) == 0 ){
			printArgs(rebuilt,i);
		}
		if(strcmp("TheTime",rebuilt[0]) == 0 ){
			TheTime();
		}


	int status;
	pid_t pid;
	pid = fork();

	if (pid < 0) {
		fprintf(stdout, "failed to fork\n");
		exit(1);		
	}
	else if (pid == 0){
		FILE *fp;
		
		if (fileType == 2){
				fp = freopen(rebuilt[fileName],"w+",stdout);
						execvp(rebuilt[0],BeforePunc);
		}
		else if (fileType == 1) {
				fp = freopen(rebuilt[fileName],"r+",stdout);
						execvp(rebuilt[0],rebuilt);
		}
		else{
					execvp(rebuilt[0],rebuilt);
		}

	
		fclose(fp);
		exit(0);
	}
	else{
		pid = wait(&status);
		if (strcmp("exit",rebuilt[0]) == 0){
			exit(1);
		}
	}

		for (i = 0;rebuilt[i] != NULL; i++){
			free(rebuilt[i]);
		}

		free(rebuilt);
		free(BeforePunc);

	}
return (0);
}

