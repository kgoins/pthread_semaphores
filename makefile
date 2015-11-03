CC = gcc
CFLAGS = -Wall -ansi -pthread
SRC = semaphore.c
OBJS = $(SRC:.c=.o)

EXEC = semaphore

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $< -c $^

clean:
	rm $(EXEC) *.o
