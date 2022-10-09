#Co-Developers: Daniel Stahovich and Gavin Schrader
# choose your compiler
CC=gcc
#CC=gcc -Wall

mysh: sh.o get_path.o main.c
	$(CC) -g main.c sh.o get_path.o -o mysh
#       $(CC) -g main.c sh.o get_path.o bash_getcwd.o -o mysh

sh.o: sh.c sh.h
	$(CC) -g -c sh.c

get_path.o: get_path.c get_path.h
	$(CC) -g -c get_path.c

clean:
	rm -f *.o mysh

test: get_path_main.c get_path.c
	$(CC) -g  -o test get_path_main.c get_path.c
