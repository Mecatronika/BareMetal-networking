VPATH += ../include/libnet
VPATH += ../src

CFLAGS += -Wall -Wextra -Werror -Wfatal-errors -std=c99
CFLAGS += -I ../include

.PHONY: all
all: example1 ipv6-pack

ipv6-pack.o: ipv6-pack.c stack.h

ipv6-pack: ipv6-pack.o -lnet

example1.o: example1.c stack.h

example1: example1.o -lnet

.PHONY: clean
clean:
	$(RM) ipv6-pack ipv6-pack.o
	$(RM) example1 example1.o

.PHONY: test
test:

.PHONY: install
install:

