// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file buffer.h

#ifndef LIBNET_BUFFER_H
#define LIBNET_BUFFER_H

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
	unsigned long long int size;
	/// @brief The number of bytes reserved for data.
	unsigned long long int reserved;
};

/// @brief Initializes a buffer.
void libnet_buffer_init(struct libnet_buffer *buffer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_BUFFER_H
