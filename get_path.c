/*
  get_path.c
  Ben Miller

  Just a little sample function that gets the PATH env var, parses it and
  puts "components" into a linked list, which is returned.
*/
#include "get_path.h"

struct pathelement *get_path()
{
  /* path is a copy of the PATH and p is a temp pointer */
  char *path, *p;

  /* tmp is a temp point used to create a linked list and pathlist is a
     pointer to the head of the list */
  struct pathelement *tmp, *pathlist = NULL;

  p = getenv("PATH");   // get a pointer to the PATH env var.
}
