#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include<sys/types.h>
 void handler()
  {      FILE *fptr;
   fptr = fopen("/home/fagr/Desktop/trial/logfile.txt","a");
   fprintf(fptr ,"child process is terminated\n");
   fclose(fptr);
  }
  void program(char **command){
  int test=0;
  int state;
  pid_t child_pid;
     if(command[1]!=NULL)
        {  if(strcmp(command[1],"&")== 0)
          {
            test=1;
             command[1]=NULL;
            }
        }
        if (strcmp(command[0], "cd") == 0) {
           chdir(command[1]);
             //printf("Invalid");
            }
      else if(strcmp(command[0], "exit") == 0)
            { exit(1);}
        else
         {
          child_pid = fork();
          if (child_pid < 0) {
          //no memory for new processes , exit terminates enitre program as it works with parent process
          //  printf("Fork failed"); //balash print bt3la2 kolo ?? 1 will indicate when returned
            exit(2);}
       signal(SIGCHLD, handler); //child finsih, signal sent to parent to resume
        if (child_pid == 0) {
        //child
            execvp(command[0], command);
        printf("errrrorrr in ex"); //doesnt return
             }
        else {
        //parent
        //execution of parent suspended until child terminates
          if(test==0)
            {waitpid(child_pid,&state,0);}// 0 waiting any child process
          test=0;
        }
        }
  }
  char** get_input(char *input) {
      char **command = malloc(100);
    char *separator = " ";
    char *parsed;
   int index = 0;
    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;
        parsed = strtok(NULL, separator);
    }
    command[index] = NULL;
    return(command);
}
int main()
 {char input[100];
 char **c;
   while(1)
  {
   gets(input);
 c=get_input(input);
 program(c);
    //fgets(input,50,stdin); leeh ghalat??
    }
    free(c);
   return 0;
}
