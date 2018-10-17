//Name : Shruti Shah
// Note: I have used lab 4-5 codes provided my the professor to do this homework. 

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


void sig_handler(int sig)
{
	char msg[] = " SIGINT Handled.\nCS361>";
	write(1, msg, sizeof(msg));
	exit(0);
}

void sig_handler1(int sig)
{
	char msg[] = " SIGTSTP Handled.\nCS361>";
	write(1, msg, sizeof(msg));
	exit(0);
}



int main()
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler1);
	
	char line [500];			//create space
	char argsarr[20][100] = {"/bin/ls", "-l", (char) 0};
	//char buf1[50];
	//char buf2[50];

	while (1)
	{
		printf("CS361> ");		//it prints the prompt
		
        	//read line from terminal
        	fgets(line,500,stdin);
		line[strcspn(line, "\n")] = 0;
		
        	//break string into words
        	char *word = strtok(line, " ");
        	int i = 0;
			
		if(strcmp(line,"exit")==0){
			exit(0);
		}


        	while(word)
        	{
                	printf("word: %s\n", word);
                	strcpy(argsarr[i], word);     //copy word to array
                	word = strtok(NULL, " ");	//to get next word
                	i = i + 1;
                }
        	
		
        	//print array
        	int j=0;
		
        	for (;j<i;j++)
		{
                	printf("argsarr[%d]: %s\n", j, argsarr[j]);

		}
		//args[j] = NULL;
        	        
        	int pid = fork();
        	if(pid == 0)
      		{
         		int file1 = open("sample1.txt", O_RDONLY);
			int file2 = open("sample2.txt", O_RDONLY);
			
			/*
			read(file1,buf1,19);
			buf1[19] = '\0';
			printf("%s\n",buf1);

			read(file2,buf2,19);
			buf2[19] = '\0';
			printf("%s\n",buf2);

			dup2(file1,file2);
			*/

			printf("PID : %d ", getpid());		//Child's PID
                	exit(0);
        	}

        	else
		{
			//printf("I am the parent.  I am waiting for my child %d to die.\n", pid);
                	int status;
                	wait(&status);
             		printf(" Status: %d. \n");		//Child's exit status

        	}	

	}
	
	//return 0;
}


