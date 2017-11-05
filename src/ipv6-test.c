// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/ipv6.h>

#include <assert.h>
#include <stdlib.h>

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

int main(void)
{
	test_address_parse();
	return EXIT_SUCCESS;
}
