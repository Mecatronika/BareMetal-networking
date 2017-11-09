// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file ipv6.h

#ifndef NETSTACK_IPV6_H
#define NETSTACK_IPV6_H

#include <netstack/ip.h>

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct netstack_buffer;
struct netstack_mutator;

struct netstack_ipv6_address
{
	unsigned char octets[16];
};

void netstack_ipv6_address_init(struct netstack_ipv6_address *address);

int netstack_ipv6_address_parse(struct netstack_ipv6_address *address,
                                const char *str, size_t str_size);

/// @brief The IPv6 protocol.
struct netstack_ipv6
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
	enum netstack_ip protocol;
	/// @brief The source address.
	struct netstack_ipv6_address source;
	/// @brief The destination address.
	struct netstack_ipv6_address destination;
};

void netstack_ipv6_init(struct netstack_ipv6 *ipv6);

int netstack_ipv6_set_source(struct netstack_ipv6 *ipv6,
                             const char *src, size_t src_size);

int netstack_ipv6_set_destination(struct netstack_ipv6 *ipv6,
                                  const char *dst, size_t dst_size);

int netstack_ipv6_pack(struct netstack_ipv6 *ipv6,
                       struct netstack_buffer *buffer);

int netstack_ipv6_unpack(struct netstack_ipv6 *ipv6,
                         struct netstack_buffer *buffer);

int netstack_ipv6_mutate(struct netstack_ipv6 *ipv6,
                         const struct netstack_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_IPV6_H
