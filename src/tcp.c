// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/tcp.h>

#include <limits.h>

static int parse_port(unsigned int *port_ptr,
                      const char *str, size_t str_size)
{
	// using an unsigned long int ensures
	// that if a number greater than 65535
	// is passed, we can detect that it is
	// greater than the 16-bit max (unsigned
	// int, on some platforms, may only be
	// 16-bits).
	unsigned long int port = 0;

	if (str_size > 5)
	{
		// 65535 is the max, so
		// if more than five digits
		// have been passed, only five
		// will be used.
		str_size = 5;
	}

	for (size_t i = 0; i < str_size; i++)
	{
		char c = str[i];
		if ((c >= '0') && (c <= '9'))
		{
			port *= 10;
			port += c - '0';
		}
		else
			return -1;
	}

	// port exceeds maximum
	if (port > 65535)
		return -1;

	*port_ptr = (unsigned int) port;

	return 0;
}

void libnet_tcp_init(struct libnet_tcp *tcp)
{
	tcp->source = 0;
	tcp->destination = 0;
	tcp->sequence = 0;
	tcp->acknowledgment = 0;
	tcp->data_offset = 5;
	tcp->control_bits = 0;
	tcp->window_size = 1;
	tcp->checksum = 0;
	tcp->urgent_pointer = 0;
}

int libnet_tcp_set_source(struct libnet_tcp *tcp,
                          const char *str,
                          size_t str_size)
{
	return parse_port(&tcp->source, str, str_size);
}

int libnet_tcp_set_destination(struct libnet_tcp *tcp,
                               const char *str,
                               size_t str_size)
{
	return parse_port(&tcp->destination, str, str_size);
}
