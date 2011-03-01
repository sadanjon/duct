SRC=duct.c grid.c node.c queue.c
OBJ=$(SRC:.c=.o)

CC=gcc
CFLAGS=-Wall -O3 -DNDEBUG

all: duct tags

duct: $(OBJ) 
	$(CC) $(CFLAGS) $^ -o $@ 

%.o: %.c
	$(CC) $(CFLAGS) -c $<

grid.o: grid.h
node.o: node.h
duct.o: duct.h
queue.o: queue.h

.PHONY: clean
clean:
	rm -f $(OBJ) duct tags

tags:
	ctags -R .
