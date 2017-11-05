// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file buffer.h

#ifndef LIBNET_BUFFER_H
#define LIBNET_BUFFER_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief A general purpose buffer.
struct libnet_buffer
{
	/// @brief Data associated with the buffer.
	void *data;
	/// @brief The number of bytes containing data.
	size_t size;
	/// @brief The number of bytes reserved for data.
	size_t reserved;
};

/// @brief Initializes a buffer.
void libnet_buffer_init(struct libnet_buffer *buffer);

/// @brief Shifts the buffer right, to make
/// memory available in the beginning of the
/// block.
int libnet_buffer_shift(struct libnet_buffer *buffer,
                        size_t shift_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_BUFFER_H
