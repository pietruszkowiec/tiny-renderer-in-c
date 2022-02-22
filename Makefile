CC = gcc
CFLAGS = -Wextra -Wall -Wpedantic
LIBS = -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

PROGRAM = main

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

run: $(PROGRAM)
	./$<

clean:
	$(RM) $(OBJS)
