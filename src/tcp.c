// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/tcp.h>

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
	(void) tcp;
	(void) str;
	(void) str_size;
	return -1;
}

int libnet_tcp_set_destination(struct libnet_tcp *tcp,
                               const char *str,
                               size_t str_size)
{
	(void) tcp;
	(void) str;
	(void) str_size;
	return -1;
}
