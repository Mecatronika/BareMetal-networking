// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/ipv6.h>

void libnet_ipv6_address_init(struct libnet_ipv6_address *address)
{
	for (size_t i = 0; i < sizeof(address->octets); i++)
		address->octets[i] = 0;
}

int libnet_ipv6_address_parse(struct libnet_ipv6_address *address,
                              const char *str, size_t str_size)
{
	(void) address;
	(void) str;
	(void) str_size;
	return -1;
}
