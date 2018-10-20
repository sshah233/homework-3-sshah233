#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void sig_handler(int sig)
{
	char msg[] = " SIGINT Handled.\nCS361>";
	write(1, msg, sizeof(msg));
	//exit(0);
}

void sig_handler1(int sig)
{
	char msg[] = " SIGTSTP Handled.\nCS361>";
	write(1, msg, sizeof(msg));
	//exit(0);
}


int main(){
  
  signal(SIGINT, sig_handler);
  signal(SIGTSTP, sig_handler1);

  //create some space for our strings
  char line[500];
  char *argsarr[21];
  char* exitLine = "exit";
  int redirect=0;
  
 while(1){
  //print prompt
  printf("CS361 > ");
  //read line from terminal
  fgets(line, 500, stdin);
  line[strcspn(line, "\n")] = 0;
  //break the string up into words
  if(strcmp(line,"exit")==0){
	exit(0);
  }
  char *word = strtok(line, " ");
  int i = 0;
// char *filename = (char *)malloc(sizeof(char) * 50);
  while (word) {
      if((strcmp(word, ">") == 0) || (strcmp(word, "<") == 0) || (strcmp(word, ";") == 0))
        {
           if(strcmp(word, ">") == 0){
                redirect = 1;
	   	}
           if(strcmp(word, "<") == 0){
                redirect = 2;
	  }
           if(strcmp(word, ";") == 0){
                redirect = 3;
          }
           word = strtok(NULL, " ");
                                // copy a word to the filename
           //strcpy(filename, word);
           //word = strtok(NULL, " ");
                        }
     else{
    printf("word: %s\n", word);
    //copy a word to the arg array
    argsarr[i]=word;
    //get next word
    word = strtok(NULL, " ");
    i = i + 1;
  }

  //print out our array

  argsarr[i] = NULL;
}
 int pid = fork();
 
  if (pid == 0) {
    int line_num;
    if(redirect==1){
	line_num = open(filename,O_RDWR |O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IROTH);
	dup2(line_num,1);
        close(line_num);
    }
    if(redirect==2){
	line_num = open(filename,O_WRONLY | O_APPEND);
	dup2(line_num,1);
	close(line_num);
    }
    if(redirect==3){
	line_num = open(filename, O_RDONLY);
	if(line_num<0){
	}
	else{
	dup2(line_num,0);
	close(line_num);
        }
    }
    printf("pid:%d\n", getpid());
    execvp(argsarr[0], argsarr);
    exit(0);
  } 
  else 
   {
    int status;
    //printf(" status number %d\n", status);
    //wait(status);
     waitpid(-1,&status,0);
     int ex = WEXITSTATUS(status);
     printf("pid:%d status:%d\n",pid,ex);
   }  

  
}
 return 0;
}






