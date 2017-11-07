// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/buffer.h>
#include <libnet/tcp.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void test_port_parsing(void)
{
	struct libnet_tcp tcp;

	libnet_tcp_init(&tcp);

	int err = libnet_tcp_set_source(&tcp, "1", 1);
	assert(err == 0);
	assert(tcp.source == 1);

	err = libnet_tcp_set_destination(&tcp, "65535", 5);
	assert(err == 0);
	assert(tcp.destination == 65535);

	// this should fail because 65536 is
	// out of range for a port number
	err = libnet_tcp_set_source(&tcp, "65536", 5);
	assert(err != 0);
}

static void test_pack(void)
{
	struct libnet_tcp tcp;

	libnet_tcp_init(&tcp);

	int err = libnet_tcp_set_source(&tcp, "80", 2);
	assert(err == 0);

	err = libnet_tcp_set_destination(&tcp, "513", 3);
	assert(err == 0);

	unsigned char bufdata[128];
	memset(bufdata, 0, sizeof(bufdata));
	strcat((char *) bufdata, "Hello, TCP!");

	struct libnet_buffer buffer;
	libnet_buffer_init(&buffer);
	buffer.data = bufdata;
	buffer.size = strlen((char *) bufdata);
	buffer.reserved = sizeof(bufdata);

	tcp.sequence = 0x01020304;
	tcp.acknowledgment = 0xa0b0c0d0;
	tcp.control_bits = LIBNET_TCP_NS | LIBNET_TCP_FIN;
	tcp.window_size = 0x5566;
	tcp.urgent_pointer = 0x7788;

	err = libnet_tcp_pack(&tcp, &buffer);
	assert(err == 0);
	// check source port
	assert(bufdata[0] == 0);
	assert(bufdata[1] == 80);
	// check destination port
	assert(bufdata[2] == 2);
	assert(bufdata[3] == 1);
	// check sequence number
	assert(bufdata[4] == 0x01);
	assert(bufdata[5] == 0x02);
	assert(bufdata[6] == 0x03);
	assert(bufdata[7] == 0x04);
	// check acknowledgment
	assert(bufdata[8] == 0xa0);
	assert(bufdata[9] == 0xb0);
	assert(bufdata[10] == 0xc0);
	assert(bufdata[11] == 0xd0);
	// check data offset
	assert(((bufdata[12] & 0xf0) >> 4) == 5);
	// check control bits
	assert((bufdata[12] & 0x0f) == 1); // NS
	assert((bufdata[13] & 0xff) == 1); // FIN
	// check window size
	assert(bufdata[14] == 0x55);
	assert(bufdata[15] == 0x66);
	// TODO : check checksum
	//   assert(bufdata[16] == 0x00);
	//   assert(bufdata[17] == 0x00);
	// check urgent pointer
	assert(bufdata[18] == 0x77);
	assert(bufdata[19] == 0x88);
	// check new buffer size
	assert(buffer.size == (strlen((char *) &bufdata[20]) + 20));
	// check data
	assert(strcmp((char *) &bufdata[20], "Hello, TCP!") == 0);
}

static void test_unpack(void)
{
	unsigned char bufdata[32];
	// set source port (32)
	bufdata[0] = 0x00;
	bufdata[1] = 0x20;
	// set destination port (128)
	bufdata[2] = 0x01;
	bufdata[3] = 0x00;
	// set sequence number (0x01020102)
	bufdata[4] = 0x01;
	bufdata[5] = 0x02;
	bufdata[6] = 0x01;
	bufdata[7] = 0x02;
	// set acknowledgment (0x40304030)
	bufdata[8] = 0x40;
	bufdata[9] = 0x30;
	bufdata[10] = 0x40;
	bufdata[11] = 0x30;
	// set data offset (5) and control bits (NS)
	bufdata[12] = 0x51;
	// control bits
	bufdata[13] = 0;
	// window size
	bufdata[14] = 0x21;
	bufdata[15] = 0x12;
	// TODO : checksum
	bufdata[16] = 0;
	bufdata[17] = 0;
	// urgent pointer
	bufdata[18] = 0x11;
	bufdata[18] = 0x99;

	struct libnet_buffer buffer;
	buffer.data = bufdata;
	buffer.size = 12;
	buffer.reserved = sizeof(buffer);

	struct libnet_tcp tcp;
	libnet_tcp_init(&tcp);

	int err = libnet_tcp_unpack(&tcp, &buffer);
	assert(err == 0);
	assert(tcp.source == 0x20);
	assert(tcp.destination = 0x100);
	assert(tcp.sequence == 0x01020102);
	assert(tcp.acknowledgment == 0x40304030);
	assert((tcp.control_bits & LIBNET_TCP_NS) == LIBNET_TCP_NS);
	assert(tcp.window_size == 0x2112);
	assert(tcp.urgent_pointer == 0x1199);
}

int main(void)
{
	test_port_parsing();
	test_pack();
	test_unpack();
	return EXIT_SUCCESS;
}
