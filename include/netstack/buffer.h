// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file buffer.h

#ifndef NETSTACK_BUFFER_H
#define NETSTACK_BUFFER_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief A general purpose buffer.
struct netstack_buffer
{
	/// @brief Data associated with the buffer.
	void *data;
	/// @brief The number of bytes containing data.
	size_t size;
	/// @brief The number of bytes reserved for data.
	size_t reserved;
};

/// @brief Initializes a buffer.
void netstack_buffer_init(struct netstack_buffer *buffer);

/// @brief Shifts the buffer right, to make
/// memory available in the beginning of the
/// block.
int netstack_buffer_shift(struct netstack_buffer *buffer,
                          size_t shift_size);

/// @brief Shifts the buffer left, to erase
/// memory in the beginning of the block.
int netstack_buffer_shift_left(struct netstack_buffer *buffer,
                               size_t shift_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_BUFFER_H
