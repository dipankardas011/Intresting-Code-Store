CC = gcc
CFLAGS = -g -Wall
OBJS = main.o matrix.o ui.o

all: main

main: $(OBJS)
	# $(CC) $(CFLAGS) -o $@ $^ -lncurses -std=c99
	$(CC) $(CFLAGS) -o $@ $^ -lncursesw -std=c99

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o main