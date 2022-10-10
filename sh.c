//Co-Developers: Daniel Stahovich and Gavin Schrader

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "sh.h"
#include "errno.h"
struct wherepath *temp = NULL;
struct wherepath *start = NULL;

int sh( int argc, char **argv, char **envp )
{
  char *prompt = calloc(PROMPTMAX, sizeof(char));
  char *commandline = calloc(MAX_CANON, sizeof(char));
  char *command, *arg, *commandpath, *p, *pwd, *owd;
  char **args = calloc(MAXARGS, sizeof(char*));
  int uid, i, status, argsct, go = 1;
  struct passwd *password_entry;
  char *homedir;
  struct pathelement *pathlist;
  char input[30];
  char commandinput[20];
  char path;
  char* parse[2];
  char* prefix=calloc(PROMPTMAX, sizeof(char));
  char* currentDir=calloc(PROMPTMAX, sizeof(char));
  uid = getuid();
  password_entry = getpwuid(uid);               /* get passwd info */
  homedir = password_entry->pw_dir;             /* Home directory to start
                                                 out with*/
if ( (pwd = getcwd(NULL, PATH_MAX+1)) == NULL )
  {
    perror("getcwd");
    exit(2);
  }
  owd = calloc(strlen(pwd) + 1, sizeof(char));
  memcpy(owd, pwd, strlen(pwd));
  prompt[0] = ' '; prompt[1] = '\0';

  /* Put PATH into a linked list */
  pathlist = get_path();


getcwd(currentDir, sizeof(currentDir));


while ( go ){
        /* print your prompt */
	printpwdfunc(currentDir,prefix);
        /* get command line and process */
/* check for each built in command and implement */
// for running the while loop to seperate these values

        const char a[2] = " ";
	char *com1; //com1 takes first word, com1 will be set = to most commands such as which and where
	char *com2;
	char *com3;
	char *com4;
	int inc = 1;	//used to keep track of what word is set to each variable
	char *token; //keeps track odf each word
	fgets(input, 30, stdin);
	trim(input);
	token = strtok(input, " ");
	com1 = token;
	while( inc <5 ) { //seperates string into seperate words
	        inc++;
	        if(inc==3){
	                com2 = token;
	        }
	        if(inc==4){
	                com3 = token;
	        }
	        if(inc==5){
	                com4 = token;
	        }
      token = strtok(NULL, " ");
   }

//	printf("testing input %s %s %s %s\n", com1, com2, com3, com4);

        if((strcmp(com1, "exit") == 0)){
                //exits
                printf("exiting\n");
//                free(currentDir);
                free(prefix);
                free(args);
                free(prompt);
                free(commandline);
                free(owd);
		free(temp);
                free(start);

                return 0;
        }
       else if(strcmp(com1, "which") == 0){
                which(com2, get_path());
        }
	else if(strcmp(com1, "where") == 0){
                where(com2, get_path());
        }
        else if(strcmp(com1, "cd") == 0){
              printf("cd is running\n");
              if(com2!=NULL &com3==NULL){
                chdir(com2);
                pwdfunc(currentDir);
              }
              else if(com2==NULL){
                chdir(homedir);
                currentDir=homedir;
              }
              if(com3!=NULL){
                printf("Too many arguments\n");
              }

        }
        else if(strcmp(com1, "pwd") == 0){
                pwdfunc(currentDir);
        }
        else if(strcmp(com1, "list") == 0){
//                printf("List is printing\n");
                list(currentDir);
        }
        else if(strcmp(com1, "pid") == 0){
                printf("Printing Shell PID: %d\n", getpid());
        }
        else if(strcmp(com1, "kill") == 0){
            //if(com2!=NULL){
            //kill(com2, SIGKILL);
            //}
            printf("Only Kills Current Process");
            kill(getpid(), SIGKILL);

        }
        else if(strcmp(com1, "prompt") == 0){
                if(com2!=NULL){
                        prefix=com2;
                }
                else{
                        printf("input prompt prefix:");
                        fgets(prefix, 30, stdin);
                        com2=prefix;

                }
        }

        else if(strcmp(com1, "printenv") == 0){
        }
        else if(strcmp(com1, "setenv") == 0){

        }
	else{
         fprintf(stderr, "%s: Command not found.\n", args[0]);
        }
        /*  else  program to exec */
        {
        /*
        pid=fork();
                if(pid==0){
                        execvc(fullpath,args, environment); Get environment from extern **char environ;
                        exit(-1); idk if this works
                }
                else{//Parent
                int status;// asked to print if non zero
                        waitpid(pid,&status,0);
                }
        */
        /* find it */
        /* do fork(), execve() and waitpid() */

        /* else */
/*	else{
         fprintf(stderr, "%s: Command not found.\n", args[0]);
        }*/
	}
        }
  	return 0;
} /* sh() */

char *which(char *command, struct pathelement *pathlist ){
        int found = 0;
       // printf("which function is running\n");
        /* loop through pathlist until finding command and return it.  Return
        NULL when not found. */
        if(pathlist->element == NULL){
                printf("empty pathlist\n");
                return 0;
        }
        while(pathlist->next != NULL || found==1){
         //       printf("searching\n");
                if(strcmp(pathlist->element, command) == 0){
                        found = 1;
      //          printf("found\n");
                printf("Path:%s\n",pathlist->element);
                return pathlist->element;
                }
                else{
                        pathlist = pathlist->next;
}
        }
        // remember that if there is a specific type of code entered, I belive /xyz, he wants us to try directly
        //activating it to see if it works
        if(found == 0){
                printf("command not found\n");
                return NULL;
        }
    //    printf("done which\n");
} /* which() */


char *where(char *command, struct pathelement *pathlist ){
	char allpaths[100] = "";
	const char s[2] = "-";
//        printf("where function is running\n");
        if(pathlist->element == NULL){
                printf("empty pathlist\n");
                return 0;
        }
        while(pathlist->next != NULL){
  //              printf("searching\n");
                printf("%s\n", pathlist->element);
                if(strcmp(pathlist->element, command) == 0){
//                printf("found one\n");
		strcat(allpaths, pathlist->element);
		strcat(allpaths, "-");
		pathlist = pathlist->next;
                }
		else{
			pathlist = pathlist->next;
}

        }//while
	char *token;
//	printf("start printing\n");

	token =strtok(allpaths, s);
	while(token != NULL){
                printf("Path: %s\n", token);
                token = strtok(NULL, s);
        }
  //      printf("done where\n");
	return 0;
} /* where()*/


int pwdfunc(char* currentD){
	char cwd[PATH_MAX];
	if(getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("Current Directory is:  %s\n", cwd);
	}
	return 0;
}


int printpwdfunc(char* currentD, char* pre){
	char cwd[PATH_MAX];
	if(getcwd(cwd, sizeof(cwd)) != NULL & pre!=NULL) {
        	printf("%s [%s]>> ", pre, cwd);
	}
	else{
		printf("[%s]>> ", cwd);
	}
	return 0;
}


void list(){
	DIR *d;
	d = opendir(".");
	struct dirent *dir;
	if(d){
		while ((dir = readdir(d)) != NULL){
		printf("%s\n", dir->d_name);
		}
	closedir(d);
	}
//free(dir);
}


void trim(char * str){ //used for trimming white space off end of input
	int index = -1;
	int i = 0;
	while(str[i] != '\0'){
        	if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t'){
			index= i;
		}
		i++;
	}
	str[index + 1] = '\0';
}
