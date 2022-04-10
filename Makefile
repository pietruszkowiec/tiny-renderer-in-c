CC = gcc
CFLAGS = -std=c11 -Wall
LDLIBS = -lm

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

PROGRAM = render

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

run: $(PROGRAM)
	./$<

clean:
	$(RM) $(OBJS)
