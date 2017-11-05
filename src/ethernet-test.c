// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/ethernet.h>
#include <libnet/buffer.h>
#include <libnet/stack.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void test_pack(void)
{
	// Setup the ethernet protocol
	struct libnet_ethernet ethernet;
	libnet_ethernet_init(&ethernet);
	int err = libnet_ethernet_set_source(&ethernet, "12:34:56:78:9a:bc", 17);
	assert(err == 0);
	err = libnet_ethernet_set_destination(&ethernet, "11:22:33:44:55:66", 17);
	assert(err == 0);

	// Setup the buffer
	unsigned char bufdata[128];
	memset(bufdata, 0, sizeof(bufdata));
	strcpy((char *) bufdata, "msg");
	struct libnet_buffer buffer;
	buffer.data = bufdata;
	buffer.size = 64;
	buffer.reserved = sizeof(bufdata);

	err = libnet_ethernet_pack(&ethernet, &buffer);
	assert(err == 0);
	// check buffer size is set correctly
	//   data size: 64
	//   header size: 14
	//   footer size: 4
	//   total: 64 + 14 + 4 == 82
	assert(buffer.size == 82);
	// check destination
	assert(bufdata[0] == 0x11);
	assert(bufdata[1] == 0x22);
	assert(bufdata[2] == 0x33);
	assert(bufdata[3] == 0x44);
	assert(bufdata[4] == 0x55);
	assert(bufdata[5] == 0x66);
	// check source
	assert(bufdata[6] == 0x12);
	assert(bufdata[7] == 0x34);
	assert(bufdata[8] == 0x56);
	assert(bufdata[9] == 0x78);
	assert(bufdata[10] == 0x9a);
	assert(bufdata[11] == 0xbc);
	// check ethertype (in this case, payload size)
	assert(bufdata[12] == 0x00);
	assert(bufdata[13] == 0x40);
	// check payload
	assert(bufdata[14] == 'm');
	assert(bufdata[15] == 's');
	assert(bufdata[16] == 'g');
	assert(bufdata[17] == 0);
	// check crc32 (verified with WireShark)
	assert(bufdata[14 + 64 + 0] == 96);
	assert(bufdata[14 + 64 + 1] == 161);
	assert(bufdata[14 + 64 + 2] == 247);
	assert(bufdata[14 + 64 + 3] == 21);
}

int main(void)
{
	test_pack();
	return EXIT_SUCCESS;
}
