CC=gcc
CFLAGS=-I -Wall
DEPS = 
OBJ = myshell.c

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
