CC = gcc
CFLAGS = -Wextra -Wall -Wpedantic
LDLIBS = -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

PROGRAM = main

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

run: $(PROGRAM)
	./$<

clean:
	$(RM) $(OBJS)
