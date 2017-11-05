DESTDIR ?=
PREFIX ?= /usr/local

CC ?= gcc

CFLAGS += -Wall -Wextra -Werror -Wfatal-errors -std=c99
CFLAGS += -I ../include

VPATH += ../include/libnet

libfiles += accessor.o
libfiles += buffer.o
libfiles += crc.o
libfiles += crc32.o
libfiles += ethernet.o
libfiles += ipv6.o
libfiles += mac.o
libfiles += mutator.o
libfiles += pipe.o
libfiles += protocol.o
libfiles += stack.o
libfiles += tcp.o

tests += buffer-test
tests += crc-test
tests += ethernet-test
tests += ipv6-test
tests += mac-test
tests += tcp-test

.PHONY: all
all: libnet.a $(tests)

libnet.a: $(libfiles)
	$(AR) $(ARFLAGS) $@ $^

buffer.o: buffer.c buffer.h

buffer-test.o: buffer-test.c buffer.h

buffer-test: buffer-test.o -lnet

crc.o: crc.c crc.h

crc-test.o: crc-test.c crc.h

crc-test: crc-test.o -lnet

crc32.o: crc32.c

ethernet.o: ethernet.c ethernet.h mac.h

ethernet-test.o: ethernet-test.c ethernet.h protocol.h stack.h pipe.h

ethernet-test: ethernet-test.o -lnet

ipv6.o: ipv6.c ipv6.h

ipv6-test.o: ipv6-test.c ipv6.h

ipv6-test: ipv6-test.o -lnet

mac.o: mac.c mac.h

mac-test.o: mac-test.c mac.h

mac-test: mac-test.o -lnet

mutator.o: mutator.c mutator.h

pipe.o: pipe.c pipe.h

protocol.o: protocol.c protocol.h

stack.o: stack.c stack.h protocol.h pipe.h

tcp.o: tcp.c tcp.h

tcp-test.o: tcp-test.c tcp.h

tcp-test: tcp-test.o -lnet

.PHONY: clean
clean:
	$(RM) $(libfiles)
	$(RM) $(tests) $(tests:=.o)
	$(RM) libnet.a

.PHONY: test
test: buffer-test crc-test mac-test ethernet-test ipv6-test
	./buffer-test
	./crc-test
	./mac-test
	./ethernet-test
	./ipv6-test
	./tcp-test

.PHONY: install
install:
	cp libnet.a $(DESTDIR)$(PREFIX)/lib/libnet.a
