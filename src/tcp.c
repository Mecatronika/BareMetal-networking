// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/tcp.h>

#include <libnet/buffer.h>

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

int libnet_tcp_pack(struct libnet_tcp *tcp,
                    struct libnet_buffer *buffer)
{
	int err = libnet_buffer_shift(buffer, 20);
	if (err != 0)
		return err;

	unsigned char *header = buffer->data;

	// source port
	header[0] = (0xff00 & tcp->source) >> 8;
	header[1] = (0x00ff & tcp->source) >> 0;
	// destination port
	header[2] = (0xff00 & tcp->destination) >> 8;
	header[3] = (0x00ff & tcp->destination) >> 0;
	// sequence number
	header[4] = (0xff000000 & tcp->sequence) >> 24;
	header[5] = (0x00ff0000 & tcp->sequence) >> 16;
	header[6] = (0x0000ff00 & tcp->sequence) >> 8;
	header[7] = (0x000000ff & tcp->sequence) >> 0;
	// acknowledgment
	header[8]  = (0xff000000 & tcp->acknowledgment) >> 24;
	header[9]  = (0x00ff0000 & tcp->acknowledgment) >> 16;
	header[10] = (0x0000ff00 & tcp->acknowledgment) >> 8;
	header[11] = (0x000000ff & tcp->acknowledgment) >> 0;
	// zero fields that require bit shifting
	header[12] = 0;
	header[13] = 0;
	// data offset (5 32-bit words)
	header[12] = (5 << 4);
	// control bits
	if (tcp->control_bits & LIBNET_TCP_NS)
		header[12] |= 0x01;
	if (tcp->control_bits & LIBNET_TCP_CWR)
		header[13] |= 0x80;
	if (tcp->control_bits & LIBNET_TCP_ECE)
		header[13] |= 0x40;
	if (tcp->control_bits & LIBNET_TCP_URG)
		header[13] |= 0x20;
	if (tcp->control_bits & LIBNET_TCP_ACK)
		header[13] |= 0x10;
	if (tcp->control_bits & LIBNET_TCP_PSH)
		header[13] |= 0x08;
	if (tcp->control_bits & LIBNET_TCP_RST)
		header[13] |= 0x04;
	if (tcp->control_bits & LIBNET_TCP_SYN)
		header[13] |= 0x02;
	if (tcp->control_bits & LIBNET_TCP_FIN)
		header[13] |= 0x01;
	// window size
	header[14] = (tcp->window_size & 0xff00) >> 8;
	header[15] = (tcp->window_size & 0x00ff) >> 0;
	// checksum placeholder
	header[16] = 0;
	header[17] = 0;
	// urgent pointer
	header[18] = (tcp->urgent_pointer & 0xff00) >> 8;
	header[19] = (tcp->urgent_pointer & 0x00ff) >> 0;
	// TODO : checksum
	return 0;
}
