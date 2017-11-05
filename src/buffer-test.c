// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/buffer.h>

#include <assert.h>
#include <stdlib.h>

static void test_shift(void)
{
	char bufdata[8] = "msg\0\0\0\0\0";

	struct libnet_buffer buffer;
	buffer.data = bufdata;
	buffer.size = 3;
	buffer.reserved = sizeof(bufdata);

	// this should fail because the shift
	// size is greater than or equal to the
	// buffer size.
	int err = libnet_buffer_shift(&buffer, sizeof(bufdata));
	assert(err != 0);

	err = libnet_buffer_shift(&buffer, 2);
	assert(err == 0);
	assert(bufdata[2] == 'm');
	assert(bufdata[3] == 's');
	assert(bufdata[4] == 'g');
	assert(bufdata[5] == 0);
	// 3 is the data size, 2 is
	// the shift size
	assert(buffer.size == (3 + 2));
}

int main(void)
{
	test_shift();
	return EXIT_SUCCESS;
}
