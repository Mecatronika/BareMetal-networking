// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/buffer.h>

void netstack_buffer_init(struct netstack_buffer *buffer)
{
	buffer->data = NULL;
	buffer->size = 0;
	buffer->reserved = 0;
}

int netstack_buffer_shift(struct netstack_buffer *buffer,
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

int netstack_buffer_shift_left(struct netstack_buffer *buffer,
                               size_t shift_size)
{
	if (buffer->size < shift_size)
		return -1;

	unsigned char *dst = (unsigned char *) buffer->data;
	unsigned char *src = &dst[shift_size];

	size_t buffer_size = 0;
	buffer_size += buffer->size;
	buffer_size -= shift_size;

	for (size_t i = 0; i < buffer_size; i++)
		dst[i] = src[i];

	buffer->size -= shift_size;

	return 0;
}
