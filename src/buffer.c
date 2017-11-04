// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/buffer.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void libnet_buffer_init(struct libnet_buffer *buffer)
{
	buffer->data = NULL;
	buffer->size = 0;
	buffer->reserved = 0;
}
