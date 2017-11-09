VPATH += ../include/netstack
VPATH += ../src

CFLAGS += -Wall -Wextra -Werror -Wfatal-errors -std=c99
CFLAGS += -I ../include

.PHONY: all
all: example1 tcp-pack

tcp-pack.o: tcp-pack.c stack.h

tcp-pack: tcp-pack.o -lnet

example1.o: example1.c stack.h

example1: example1.o -lnet

.PHONY: clean
clean:
	$(RM) tcp-pack tcp-pack.o
	$(RM) example1 example1.o

.PHONY: test
test:

.PHONY: install
install:

