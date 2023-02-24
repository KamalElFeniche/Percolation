SRCS = percolation.c easyppm.c function.c grid.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = percolation


CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG) 200 200 1000

runwin: $(PROG)
	$(PROG).exe 200 200 1000
