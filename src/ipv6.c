// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/ipv6.h>

#include <libnet/buffer.h>
#include <libnet/mutator.h>

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

void libnet_ipv6_init(struct libnet_ipv6 *ipv6)
{
	ipv6->hop_limit = 255;
	ipv6->protocol = LIBNET_IP_TCP;
	libnet_ipv6_address_init(&ipv6->source);
	libnet_ipv6_address_init(&ipv6->destination);
}

int libnet_ipv6_set_source(struct libnet_ipv6 *ipv6,
                           const char *src, size_t src_size)
{
	return libnet_ipv6_address_parse(&ipv6->source, src, src_size);
}

int libnet_ipv6_set_destination(struct libnet_ipv6 *ipv6,
                           const char *dst, size_t dst_size)
{
	return libnet_ipv6_address_parse(&ipv6->destination, dst, dst_size);
}

int libnet_ipv6_pack(struct libnet_ipv6 *ipv6,
                     struct libnet_buffer *buffer)
{
	if (buffer->reserved < buffer->size)
		return -1;

	size_t data_size = buffer->size;

	int err = libnet_buffer_shift(buffer, 40);
	if (err != 0)
		return err;

	unsigned char *header = (unsigned char *) buffer->data;

	// zero the header up until the source
	// and destination address
	for (size_t i = 0; i < 8; i++)
		header[i] = 0;

	// this is version 6 of internet protocol
	header[0] |= 0x60;

	// write data size
	header[4] |= (data_size & 0x0000ff00) >> 8;
	header[5] |= (data_size & 0x000000ff) >> 0;

	if (ipv6->protocol == LIBNET_IP_TCP)
		header[6] = 0x06;
	else if (ipv6->protocol == LIBNET_IP_UDP)
		header[6] = 0x17;
	else
		// unsupported protocol
		return -1;

	header[7] = ipv6->hop_limit & 0xff;

	for (size_t i = 0; i < 16; i++)
	{
		header[8 + i] = ipv6->source.octets[i];
		header[8 + i + 16] = ipv6->destination.octets[i];
	}

	return 0;
}

int libnet_ipv6_unpack(struct libnet_ipv6 *ipv6,
                       struct libnet_buffer *buffer)
{
	if (buffer->size < 40)
		return -1;

	unsigned char *header = buffer->data;

	if ((header[0] & 0xf0) != 0x60)
		// Not an IPv6 protocol
		return -1;

	(void) ipv6;

	return 0;
}

int libnet_ipv6_mutate(struct libnet_ipv6 *ipv6,
                       const struct libnet_mutator *mutator)
{
	if (mutator->mutate_ipv6 == NULL)
		return 0;

	return mutator->mutate_ipv6(mutator->data, ipv6);
}
