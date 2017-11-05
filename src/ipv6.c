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
	size_t quartet_index = 0;

	// TODO : handle '::'

	for (size_t i = 0; i < str_size; i++)
	{
		unsigned char value = 0;

		char c = str[i];
		if (c == ':')
			continue;

		if ((c >= 'A') && (c <= 'F'))
			value = (unsigned char)(c - 'A') + 10;
		else if ((c >= 'a') && (c <= 'f'))
			value = (unsigned char)(c - 'a') + 10;
		else if ((c >= '0') && (c <= '9'))
			value = (unsigned char)(c - '0');
		else
			// malformed string
			return -1;

		if ((quartet_index % 2) == 0)
			value <<= 4;

		size_t octet_index = quartet_index / 2;

		address->octets[octet_index] |= value;

		quartet_index++;
	}

	return 0;
}
