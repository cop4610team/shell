CC=gcc
CFLAGS= -Wall -pedantic

main.x: shell.c
	$(CC) $(CFLAGS) -g -o main.x shell.c

clean:
	rm -f *.o *.x
