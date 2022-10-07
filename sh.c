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
  char* cmndDir[10];
  char* parse[2];
  int builtIn=0;//tells if it is a built in command
  int numBuiltIn=9;
  //int inc = 1;
  //const char a[2] = " "; //used for strtok in input
//  const char s[2] = "-";
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
  cmndDir[1]="exit";
  cmndDir[2]="which";
  cmndDir[3]="where";
  cmndDir[4]="cd";
  cmndDir[5]="pwd";
  cmndDir[6]="list";
  cmndDir[7]="pid";
  cmndDir[8]="kill";
  cmndDir[9]="prompt";
while ( go ){
        /* print your prompt */
        printf("enter a command\n");
        /* get command line and process */
//        scanf("%s", input);
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
//	scanf("%s", input);
	trimTrailing(input);
//	printf("trimmed input %s\n", input);
	token = strtok(input, " ");
	com1 = token;
	while( inc <5 ) { //seperates string into seperate words
//printf(" %s\n", token);
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

	printf("testing input %s %s %s %s\n", com1, com2, com3, com4);

        if((strcmp(com1, "exit") == 0)){
                //exits
                printf("exiting\n");
                return 0;
        }
        if(strcmp(com1, "which") == 0){
                //path = get_path();
               // printf("enter command to search\n");
               // scanf("%s", commandinput);
                which(com2, get_path());
        }
	if(strcmp(com1, "where") == 0){
                //path = get_path();
//                printf("enter command to search\n");
  //              scanf("%s", commandinput);
                where(com2, get_path());
        }
        }
        /*  else  program to exec */
        {
        /* find it */
        /* do fork(), execve() and waitpid() */

        /* else */
        /* fprintf(stderr, "%s: Command not found.\n", args[0]); */
        }
	//}
  	return 0;
} /* sh() */

char *which(char *command, struct pathelement *pathlist ){
        int found = 0;
        printf("which function is running\n");
        /* loop through pathlist until finding command and return it.  Return
        NULL when not found. */
        if(pathlist->element == NULL){
                printf("empty pathlist\n");
                return 0;
        }
        while(pathlist->next != NULL || found==1){
                printf("searching\n");
                if(strcmp(pathlist->element, command) == 0){
                        found = 1;
                printf("found\n");
                printf("Path:%s\n",pathlist->element);
                return pathlist->element;
                }
                else{
                        pathlist = pathlist->next;
}
        }
        if(found == 0){
                printf("command not found\n");
                return NULL;
        }
        printf("done which\n");
} /* which() */


char *where(char *command, struct pathelement *pathlist ){
	char allpaths[100] = "";
	const char s[2] = "-";
        printf("where function is running\n");
        if(pathlist->element == NULL){
                printf("empty pathlist\n");
                return 0;
        }//if
        while(pathlist->next != NULL){
                printf("searching\n");
                printf("%s\n", pathlist->element);
                if(strcmp(pathlist->element, command) == 0){
                printf("found one\n");
		strcat(allpaths, pathlist->element);
		strcat(allpaths, "-");
//		temp->whereelement = pathlist->element;
//                temp = temp->next;
		pathlist = pathlist->next;
                }//if
		else{
			pathlist = pathlist->next;
}

        }//while
	char *token;
	printf("start printing\n");

	token = strtok(allpaths, s);
	while(token != NULL){
printf("%s\n", token);
token = strtok(NULL, s);
}

//	printf("%s\n", allpaths);
        printf("done where\n");
	return 0;
} /* where()*/



void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */


void trimTrailing(char * str) //used for trimming white space off end of input
{
    int index, i;

    /* Set default index */
    index = -1;

    /* Find last index of non-white space character */
    i = 0;
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index= i;
        }

        i++;
    }

    /* Mark next character to last non-white space character as NULL */
    str[index + 1] = '\0';
}
