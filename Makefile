CC=gcc
CCFLAGS= -Wall -pedantic

main.x: shell.c
	$(CC) $(CCFLAGS) -g -o main.x shell.c

clean:
	rm -f *.o *.x
