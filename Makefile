CC = mpicc
CFLAGS = -g -Wall

main: main.o process.o function.o
	$(CC) $(CFLAGS) -o main main.o process.o function.o

process.o: process.c process.h
	$(CC) $(CFLAGS) -c process.c

function.o: function.c function.h
	$(CC) $(CFLAGS) -c function.c

main.o: main.c process.h function.h
	$(CC) $(CFLAGS) -c main.c

clean: 
	rm -rf *.o
