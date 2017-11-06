// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/ipv6.h>

#include <libnet/buffer.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void test_address_parse(void)
{
	struct libnet_ipv6_address address;

	libnet_ipv6_address_init(&address);

	const char address_str[] = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";

	int err = libnet_ipv6_address_parse(&address,
	                                    address_str,
	                                    sizeof(address_str) - 1);
	assert(err == 0);

	assert(address.octets[0] == 0x20);
	assert(address.octets[1] == 0x01);

	assert(address.octets[2] == 0x0d);
	assert(address.octets[3] == 0xb8);

	assert(address.octets[4] == 0x85);
	assert(address.octets[5] == 0xa3);

	assert(address.octets[6] == 0x00);
	assert(address.octets[7] == 0x00);

	assert(address.octets[8] == 0x00);
	assert(address.octets[9] == 0x00);

	assert(address.octets[10] == 0x8a);
	assert(address.octets[11] == 0x2e);

	assert(address.octets[12] == 0x03);
	assert(address.octets[13] == 0x70);

	assert(address.octets[14] == 0x73);
	assert(address.octets[15] == 0x34);

}

static void test_pack(void)
{
	struct libnet_ipv6 ipv6;
	libnet_ipv6_init(&ipv6);

	int err = libnet_ipv6_set_source(&ipv6, "0011:2233:4455:6677:8899:aabb:ccdd:eeff", 39);
	assert(err == 0);

	err = libnet_ipv6_set_destination(&ipv6, "ff00:ee11:dd22:cc33:bb44:aa55:9966:8877", 39);
	assert(err == 0);

	unsigned char bufdata[128];
	memset(bufdata, 0, sizeof(bufdata));
	strcpy((char *) bufdata, "msg");

	struct libnet_buffer buffer;
	libnet_buffer_init(&buffer);
	buffer.data = bufdata;
	buffer.size = 4;
	buffer.reserved = sizeof(bufdata);

	err = libnet_ipv6_pack(&ipv6, &buffer);
	assert(err == 0);
	// check for IP version 6
	assert((bufdata[0] & 0xf0) == 0x60);
	// check for data length
	assert(bufdata[4] == 0x00);
	assert(bufdata[5] == 0x04);
	// check for TCP number
	assert(bufdata[6] == 0x06);
	// check HOP limit
	assert(bufdata[7] == 0xff);
	// check source address
	assert(memcmp(&bufdata[8], "\x00\x11\x22\x33\x44\x55\x66\x77\x88\x99\xaa\xbb\xcc\xdd\xee\xff", 16) == 0);
	// check destination address
	assert(memcmp(&bufdata[8 + 16], "\xff\x00\xee\x11\xdd\x22\xcc\x33\xbb\x44\xaa\x55\x99\x66\x88\x77", 16) == 0);
}

static void test_unpack(void)
{
	unsigned char bufdata[128];
	// IP version
	bufdata[0] = 0x60;
	// traffic class / flow label
	bufdata[1] = 0x00;
	bufdata[2] = 0x00;
	bufdata[3] = 0x00;
	// payload length (4)
	bufdata[4] = 0x00;
	bufdata[5] = 0x04;
	// next header (UDP)
	bufdata[6] = 0x11;
	// hop limit
	bufdata[7] = 0xfe;
	// source address
	bufdata[8] = 0x12;
	bufdata[9] = 0x21;
	bufdata[10] = 0x12;
	bufdata[11] = 0x21;
	bufdata[12] = 0x12;
	bufdata[13] = 0x21;
	bufdata[14] = 0x12;
	bufdata[15] = 0x21;
	bufdata[16] = 0x12;
	bufdata[17] = 0x21;
	bufdata[18] = 0x12;
	bufdata[19] = 0x21;
	bufdata[20] = 0x12;
	bufdata[21] = 0x21;
	bufdata[22] = 0x12;
	bufdata[23] = 0x21;
	// destination address
	bufdata[24] = 0x55;
	bufdata[25] = 0x66;
	bufdata[26] = 0x55;
	bufdata[27] = 0x66;
	bufdata[28] = 0x55;
	bufdata[29] = 0x66;
	bufdata[30] = 0x55;
	bufdata[31] = 0x66;
	bufdata[32] = 0x55;
	bufdata[33] = 0x66;
	bufdata[34] = 0x55;
	bufdata[35] = 0x66;
	bufdata[36] = 0x55;
	bufdata[37] = 0x66;
	bufdata[38] = 0x55;
	bufdata[39] = 0x66;
	// payload
	bufdata[40] = 't';
	bufdata[41] = 'e';
	bufdata[42] = 's';
	bufdata[43] = 't';

	struct libnet_buffer buffer;
	buffer.data = bufdata;
	buffer.size = 40;
	buffer.reserved = sizeof(bufdata);

	struct libnet_ipv6 ipv6;
	libnet_ipv6_init(&ipv6);

	int err = libnet_ipv6_unpack(&ipv6, &buffer);
	assert(err == 0);
	assert(ipv6.protocol == LIBNET_IP_UDP);
	assert(ipv6.length == 4);
	assert(ipv6.hop_limit == 0xfe);
	assert(memcmp(ipv6.source.octets, "\x12\x21\x12\x21\x12\x21\x12\x21\x12\x21\x12\x21\x12\x21\x12\x21", 16) == 0);
	assert(memcmp(ipv6.destination.octets, "\x55\x66\x55\x66\x55\x66\x55\x66\x55\x66\x55\x66\x55\x66\x55\x66", 16) == 0);
}

int main(void)
{
	test_address_parse();
	test_pack();
	test_unpack();
	return EXIT_SUCCESS;
}
