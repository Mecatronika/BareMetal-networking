// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

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

int main(void)
{
	test_port_parsing();
	return EXIT_SUCCESS;
}
