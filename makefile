CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++0x
EXEC=a.out

all: main.o graph.o
	$(CC) $(CFLAGS) -o $(EXEC) main.o graph.o

clean:
	rm *.out
	rm *.o
