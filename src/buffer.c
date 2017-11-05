// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/buffer.h>

void libnet_buffer_init(struct libnet_buffer *buffer)
{
	buffer->data = NULL;
	buffer->size = 0;
	buffer->reserved = 0;
}

int libnet_buffer_shift(struct libnet_buffer *buffer,
                        size_t shift_size)
{
	if (buffer->reserved < buffer->size)
		// caller error
		return -1;
	else if ((buffer->reserved - buffer->size) < shift_size)
		// not enough room
		return -1;

	unsigned char *src = (unsigned char *) buffer->data;
	unsigned char *dst = &src[shift_size];

	size_t buffer_size = buffer->size;

	for (size_t i = 0; i < buffer_size; i++)
		dst[(buffer_size - 1) - i] = src[(buffer_size - 1) - i];

	buffer->size += shift_size;

	return 0;
}
