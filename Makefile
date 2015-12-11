CC = mpicc
CFLAGS = -g -Wall

main: main.o function.o
	$(CC) $(CFLAGS) -o main main.o function.o

function.o: function.c function.h
	$(CC) $(CFLAGS) -c function.c

main.o: main.c function.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf *.o
