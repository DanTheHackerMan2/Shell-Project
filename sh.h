#include "get_path.h"

//int pid;
int sh( int argc, char **argv, char **envp);
char *which(char *command, struct pathelement *pathlist);
char *where(char *command, struct pathelement *pathlist);
void list ( char *dir );
void printenv(char **envp);
void trimTrailing(char * str);

#define PROMPTMAX 32
#define MAXARGS 10


//struct wherepath
//{
 // char *whereelement;                        /* a dir in the path */
 // struct wherepath *next;             /* pointer to next node */
 // struct wherepath *first;
//};

