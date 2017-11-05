#!/bin/sh

set -e

CC=gcc
CFLAGS="${CFLAGS} -I../include"

$CC $CFLAGS -c accessor.c -o accessor.o
$CC $CFLAGS -c buffer.c -o buffer.o
$CC $CFLAGS -c crc.c -o crc.o
$CC $CFLAGS -c crc32.c -o crc32.o
$CC $CFLAGS -c ethernet.c -o ethernet.o
$CC $CFLAGS -c ipv6.c -o ipv6.o
$CC $CFLAGS -c mac.c -o mac.o
$CC $CFLAGS -c mutator.c -o mutator.o
$CC $CFLAGS -c pipe.c -o pipe.o
$CC $CFLAGS -c protocol.c -o protocol.o
$CC $CFLAGS -c stack.c -o stack.o
$CC $CFLAGS -c tcp.c -o tcp.o

AR=ar
ARFLAGS=rcs

$AR $ARFLAGS libnet.a \
	buffer.o \
	crc.o \
	crc32.o \
	ethernet.o \
	ipv6.o \
	mac.o \
	mutator.o \
	pipe.o \
	protocol.o \
	stack.o \
	tcp.o

$CC $CFLAGS buffer-test.c -o buffer-test libnet.a
$CC $CFLAGS crc-test.c -o crc-test libnet.a
$CC $CFLAGS mac-test.c -o mac-test libnet.a
$CC $CFLAGS ethernet-test.c -o ethernet-test libnet.a
$CC $CFLAGS ipv6-test.c -o ipv6-test libnet.a
