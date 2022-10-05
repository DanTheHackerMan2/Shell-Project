#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[10];

int main(){

printf("enter a command\n");
scanf("%s", input);
while(strcmp(input, "exit") != 0){
	printf("enter a command\n");
	scanf("%s", input);
	}
printf("exiting\n");
}
