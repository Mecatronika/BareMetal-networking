#!/bin/sh

CC=gcc
CFLAGS="${CFLAGS} -I../include"

$CC $CFLAGS -c buffer.c -o buffer.o
$CC $CFLAGS -c protocol.c -o protocol.o
$CC $CFLAGS -c stack.c -o stack.o

AR=ar
ARFLAGS=rcs

$AR $ARFLAGS libnet.a buffer.o protocol.o stack.o
