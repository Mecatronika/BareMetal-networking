// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/protocol.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void libnet_protocol_init(struct libnet_protocol *protocol)
{
	protocol->id = LIBNET_PROTOCOL_NONE;
	protocol->data = NULL;
	protocol->done = NULL;
	protocol->pack = NULL;
	protocol->unpack = NULL;
	protocol->mutate = NULL;
}

void libnet_protocol_done(struct libnet_protocol *protocol)
{
	if (protocol->done)
		protocol->done(protocol->data);
}

void libnet_protocol_move(struct libnet_protocol *dst,
                          struct libnet_protocol *src)
{
	// copy the content
	*dst = *src;
	// reinitialize the old structure
	// with zeroes and null-pointers.
	libnet_protocol_init(src);
}

int libnet_protocol_pack(struct libnet_protocol *protocol,
                         struct libnet_buffer *buffer)
{
	if (protocol->pack == NULL)
		return -1;

	return protocol->pack(protocol->data, buffer);
}

int libnet_protocol_unpack(struct libnet_protocol *protocol,
                           struct libnet_buffer *buffer)
{
	if (protocol->unpack == NULL)
		return -1;

	return protocol->unpack(protocol->data, buffer);
}

int libnet_protocol_mutate(struct libnet_protocol *protocol,
                           const struct libnet_mutator *mutator)
{
	if (protocol->mutate == NULL)
		return -1;

	return protocol->mutate(protocol->data, mutator);
}
