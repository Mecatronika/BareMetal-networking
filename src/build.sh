#!/bin/sh

set -e

CC=gcc
CFLAGS="${CFLAGS} -I../include"

$CC $CFLAGS -c buffer.c -o buffer.o
$CC $CFLAGS -c ethernet.c -o ethernet.o
$CC $CFLAGS -c mac.c -o mac.o
$CC $CFLAGS -c pipe.c -o pipe.o
$CC $CFLAGS -c protocol.c -o protocol.o
$CC $CFLAGS -c stack.c -o stack.o

AR=ar
ARFLAGS=rcs

$AR $ARFLAGS libnet.a \
	buffer.o \
	ethernet.o \
	mac.o \
	pipe.o \
	protocol.o \
	stack.o

$CC $CFLAGS mac-test.c -o mac-test libnet.a
$CC $CFLAGS ethernet-test.c -o ethernet-test libnet.a
