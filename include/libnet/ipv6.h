// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file ipv6.h

#ifndef LIBNET_IPV6_H
#define LIBNET_IPV6_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct libnet_buffer;
struct libnet_mutator;

/// @brief Indicates the data protocol of
/// the content following the IPv6 header.
enum libnet_ipv6_protocol
{
	/// @brief Transmission Control Protocol.
	/// This is the default.
	LIBNET_IPV6_PROTOCOL_TCP,
	/// @brief User Datagram Protocol.
	LIBNET_IPV6_PROTOCOL_UDP
};

struct libnet_ipv6_address
{
	unsigned char octets[16];
};

void libnet_ipv6_address_init(struct libnet_ipv6_address *address);

int libnet_ipv6_address_parse(struct libnet_ipv6_address *address,
                              const char *str, size_t str_size);

/// @brief The IPv6 protocol.
struct libnet_ipv6
{
	/// @brief The length of the data following
	/// the IPv6 header.
	unsigned int length;
	/// @brief The number of times this packet
	/// may be forwarded until it's discarded.
	/// This value cannot exceed 255, and is set
	/// to 255 by default.
	unsigned int hop_limit;
	/// @brief Indicates the protocol following
	/// the IPv6 header.
	enum libnet_ipv6_protocol protocol;
	/// @brief The source address.
	struct libnet_ipv6_address source;
	/// @brief The destination address.
	struct libnet_ipv6_address destination;
};

void libnet_ipv6_init(struct libnet_ipv6 *ipv6);

int libnet_ipv6_set_source(struct libnet_ipv6 *ipv6,
                           const char *src, size_t src_size);

int libnet_ipv6_set_destination(struct libnet_ipv6 *ipv6,
                                const char *dst, size_t dst_size);

int libnet_ipv6_pack(struct libnet_ipv6 *ipv6,
                     struct libnet_buffer *buffer);

int libnet_ipv6_unpack(struct libnet_ipv6 *ipv6,
                       struct libnet_buffer *buffer);

int libnet_ipv6_mutate(struct libnet_ipv6 *ipv6,
                       const struct libnet_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_IPV6_H
