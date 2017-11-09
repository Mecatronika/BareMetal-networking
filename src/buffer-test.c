// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/buffer.h>

#include <assert.h>
#include <stdlib.h>

static void test_shift(void)
{
	char bufdata[8] = "msg\0\0\0\0\0";

	struct netstack_buffer buffer;
	buffer.data = bufdata;
	buffer.size = 3;
	buffer.reserved = sizeof(bufdata);

	// this should fail because the shift
	// size is greater than or equal to the
	// buffer size.
	int err = netstack_buffer_shift(&buffer, sizeof(bufdata));
	assert(err != 0);

	err = netstack_buffer_shift(&buffer, 2);
	assert(err == 0);
	assert(bufdata[2] == 'm');
	assert(bufdata[3] == 's');
	assert(bufdata[4] == 'g');
	assert(bufdata[5] == 0);
	// 3 is the data size, 2 is
	// the shift size
	assert(buffer.size == (3 + 2));
}

static void test_shift_left(void)
{

	char bufdata[8] = "\0\0\0\0\0msg";

	struct netstack_buffer buffer;
	buffer.data = bufdata;
	buffer.size = 8;
	buffer.reserved = 8;

	// you can't shift more data than
	// what's available in the buffer.
	int err = netstack_buffer_shift_left(&buffer, 9);
	assert(err != 0);

	err = netstack_buffer_shift_left(&buffer, 5);
	assert(err == 0);
	assert(buffer.size == 3);
	assert(buffer.reserved == 8);
	assert(bufdata[0] == 'm');
	assert(bufdata[1] == 's');
	assert(bufdata[2] == 'g');
}

int main(void)
{
	test_shift();
	test_shift_left();
	return EXIT_SUCCESS;
}
