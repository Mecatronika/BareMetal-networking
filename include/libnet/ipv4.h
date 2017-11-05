// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file ipv4.h

#ifndef LIBNET_IPV4_H
#define LIBNET_IPV4_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct libnet_buffer;
struct libnet_mutator;

struct libnet_ipv4_address
{
	unsigned char octets[4];
};

void libnet_ipv4_address_init(struct libnet_ipv4_address *address);

int libnet_ipv4_address_parse(struct libnet_ipv4_address *address,
                              const char *str, size_t str_size);

/// @brief The IPv4 protocol.
struct libnet_ipv4
{
	/// @brief The source address.
	struct libnet_ipv4_address source;
	/// @brief The destination address.
	struct libnet_ipv4_address destination;
};

void libnet_ipv4_init(struct libnet_ipv4 *ipv4);

int libnet_ipv4_set_source(struct libnet_ipv4 *ipv4,
                           const char *src, size_t src_size);

int libnet_ipv4_set_destination(struct libnet_ipv4 *ipv4,
                                const char *dst, size_t dst_size);

int libnet_ipv4_pack(struct libnet_ipv4 *ipv4,
                     struct libnet_buffer *buffer);

int libnet_ipv4_mutate(struct libnet_ipv4 *ipv4,
                       const struct libnet_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_IPV4_H
