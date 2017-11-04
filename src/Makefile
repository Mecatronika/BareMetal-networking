DESTDIR ?=
PREFIX ?= /usr/local

CC ?= gcc

CFLAGS += -Wall -Wextra -Werror -Wfatal-errors -std=c99
CFLAGS += -I ../include

VPATH += ../include/libnet

.PHONY: all
all: libnet.a crc-test ethernet-test mac-test

libnet.a: \
	buffer.o \
	crc.o \
	ethernet.o \
	mac.o \
	mutator.o \
	pipe.o \
	protocol.o \
	stack.o
	$(AR) $(ARFLAGS) $@ $^

buffer.o: buffer.c buffer.h

crc.o: crc.c crc.h

crc-test.o: crc-test.c crc.h

crc-test: crc-test.o -lnet

ethernet.o: ethernet.c ethernet.h mac.h

ethernet-test.o: ethernet-test.c ethernet.h protocol.h stack.h pipe.h

ethernet-test: ethernet-test.o -lnet

mac.o: mac.c mac.h

mac-test.o: mac-test.c mac.h

mac-test: mac-test.o -lnet

mutator.o: mutator.c mutator.h

pipe.o: pipe.c pipe.h

protocol.o: protocol.c protocol.h

stack.o: stack.c stack.h protocol.h pipe.h

.PHONY: clean
clean:
	$(RM) buffer.o ethernet.o mac.o pipe.o protocol.o stack.o
	$(RM) mac-test.o mac-test
	$(RM) libnet.a

.PHONY: test
test: crc-test mac-test ethernet-test
	./crc-test
	./mac-test
	./ethernet-test

.PHONY: install
install:
	cp libnet.a $(DESTDIR)$(PREFIX)/lib/libnet.a
