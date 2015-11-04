CC = gcc
CFLAGS = -Wall -ansi -pthread
SRC = barber_customer.c driver.c semaphore.c
OBJS = $(SRC:.c=.o)

EXEC = run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $< -c $^

clean:
	rm $(EXEC) *.o
