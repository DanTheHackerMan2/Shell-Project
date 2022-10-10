//Co-Developers: Daniel Stahovich and Gavin Schrader
#include "get_path.h"

extern int pid;
int sh( int argc, char **argv, char **envp);
char *which(char *command, struct pathelement *pathlist);
char *where(char *command, struct pathelement *pathlist);
void list();
void printenv(char **envp);
void trim(char * str);
int pwdfunc();
int printpwdfunc(char* currentD, char* pre);

#define PROMPTMAX 32
#define MAXARGS 10


//struct wherepath
//{
 // char *whereelement;                        /* a dir in the path */
 // struct wherepath *next;             /* pointer to next node */
 // struct wherepath *first;
//};

