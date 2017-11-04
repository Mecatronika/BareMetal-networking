// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/mac.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

static void test_parse(void)
{
	struct libnet_mac mac;

	libnet_mac_init(&mac);

	const char addr1[] = "010203040506";
	int err = libnet_mac_parse(&mac, addr1, sizeof(addr1));
	assert(err == 0);
	assert(mac.octets[0] == 0x01);
	assert(mac.octets[1] == 0x02);
	assert(mac.octets[2] == 0x03);
	assert(mac.octets[3] == 0x04);
	assert(mac.octets[4] == 0x05);
	assert(mac.octets[5] == 0x06);

	const char addr2[] = "07-08-09-0a-0b-0c";
	err = libnet_mac_parse(&mac, addr2, sizeof(addr2));
	assert(err == 0);
	assert(mac.octets[0] == 0x07);
	assert(mac.octets[1] == 0x08);
	assert(mac.octets[2] == 0x09);
	assert(mac.octets[3] == 0x0a);
	assert(mac.octets[4] == 0x0b);
	assert(mac.octets[5] == 0x0c);

	const char addr3[] = "0d:0e:0f:10:11:12";
	err = libnet_mac_parse(&mac, addr3, sizeof(addr3));
	assert(err == 0);
	assert(mac.octets[0] == 0x0d);
	assert(mac.octets[1] == 0x0e);
	assert(mac.octets[2] == 0x0f);
	assert(mac.octets[3] == 0x10);
	assert(mac.octets[4] == 0x11);
	assert(mac.octets[5] == 0x12);
}

static void test_write(void)
{
	struct libnet_mac mac;

	mac.octets[0] = 0x13;
	mac.octets[1] = 0x14;
	mac.octets[2] = 0x15;
	mac.octets[3] = 0x16;
	mac.octets[4] = 0x17;
	mac.octets[5] = 0x18;

	char buf[18];

	// This should fail because the buffer
	// is too small.
	int err = libnet_mac_write(&mac, buf, 17);
	assert(err != 0);

	err = libnet_mac_write(&mac, buf, sizeof(buf));
	assert(err == 0);
	assert(strcmp(buf, "13-14-15-16-17-18") == 0);
}

int main(void)
{
	test_parse();
	test_write();
	return EXIT_SUCCESS;
}
