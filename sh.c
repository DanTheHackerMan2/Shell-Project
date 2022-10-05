
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
  char input[10];
  char commandinput[20];
  char path;

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

  while ( go )
  {
    /* print your prompt */
printf("enter a command\n");
    /* get command line and process */
scanf("%s", input);
    /* check for each built in command and implement */
if(strcmp(input, "exit") == 0){
                //exits
	printf("exiting\n");
	return 0;
        }
if(strcmp(input, "which") == 0){
	//path = get_path();
	printf("enter command to search\n");
	scanf("%s", commandinput);

	which(commandinput, get_path());
}
     /*  else  program to exec */
    {
       /* find it */
       /* do fork(), execve() and waitpid() */

      /* else */
        /* fprintf(stderr, "%s: Command not found.\n", args[0]); */
    }
  }
  return 0;
} /* sh() */

char *which(char *command, struct pathelement *pathlist )
{
int found;
	printf("which function is running\n");
   /* loop through pathlist until finding command and return it.  Return
   NULL when not found. */
if(pathlist->element == NULL){
printf("test1\n");
printf("empty pathlist\n");
return 0;
}
while(pathlist->next != NULL){
	printf("test2");
	if(pathlist->element == command){
	found = 1;
	return command;
	}
	else{
	pathlist = pathlist->next;
}
}
if(found == 0){
printf("test3");
printf("command not found\n");
return NULL;
}
printf("test4");
} /* which() */

char *where(char *command, struct pathelement *pathlist )
{
  /* similarly loop through finding all locations of command */
} /* where() */

void list ( char *dir )
{
  /* see man page for opendir() and readdir() and print out filenames for
  the directory passed */
} /* list() */







/* ---------------------------------------------
char input[10];

printf("enter a command\n");
scanf("%s", input);
while(strcmp(input, "exit") != 0){
        printf("enter a command\n");
        scanf("%s", input);
        if(strcmp(input, "which") == 0){
                //call which function
        }
        if(strcmp(input, "where") == 0){
                //call where function
        }
}
printf("exiting\n");
*/





