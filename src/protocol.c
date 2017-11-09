// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/protocol.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void netstack_protocol_init(struct netstack_protocol *protocol)
{
	protocol->id = NETSTACK_PROTOCOL_NONE;
	protocol->data = NULL;
	protocol->done = NULL;
	protocol->pack = NULL;
	protocol->unpack = NULL;
	protocol->mutate = NULL;
}

void netstack_protocol_done(struct netstack_protocol *protocol)
{
	if (protocol->done)
		protocol->done(protocol->data);
}

void netstack_protocol_move(struct netstack_protocol *dst,
                            struct netstack_protocol *src)
{
	// copy the content
	*dst = *src;
	// reinitialize the old structure
	// with zeroes and null-pointers.
	netstack_protocol_init(src);
}

int netstack_protocol_pack(struct netstack_protocol *protocol,
                           struct netstack_buffer *buffer)
{
	if (protocol->pack == NULL)
		return -1;

	return protocol->pack(protocol->data, buffer);
}

int netstack_protocol_unpack(struct netstack_protocol *protocol,
                             struct netstack_buffer *buffer)
{
	if (protocol->unpack == NULL)
		return -1;

	return protocol->unpack(protocol->data, buffer);
}

int netstack_protocol_mutate(struct netstack_protocol *protocol,
                             const struct netstack_mutator *mutator)
{
	if (protocol->mutate == NULL)
		return -1;

	return protocol->mutate(protocol->data, mutator);
}
