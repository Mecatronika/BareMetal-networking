// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file ipv4.h

#ifndef NETSTACK_IPV4_H
#define NETSTACK_IPV4_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct netstack_buffer;
struct netstack_mutator;

struct netstack_ipv4_address
{
	unsigned char octets[4];
};

void netstack_ipv4_address_init(struct netstack_ipv4_address *address);

int netstack_ipv4_address_parse(struct netstack_ipv4_address *address,
                                const char *str, size_t str_size);

/// @brief The IPv4 protocol.
struct netstack_ipv4
{
	/// @brief The source address.
	struct netstack_ipv4_address source;
	/// @brief The destination address.
	struct netstack_ipv4_address destination;
};

void netstack_ipv4_init(struct netstack_ipv4 *ipv4);

int netstack_ipv4_set_source(struct netstack_ipv4 *ipv4,
                             const char *src, size_t src_size);

int netstack_ipv4_set_destination(struct netstack_ipv4 *ipv4,
                                  const char *dst, size_t dst_size);

int netstack_ipv4_pack(struct netstack_ipv4 *ipv4,
                       struct netstack_buffer *buffer);

int netstack_ipv4_mutate(struct netstack_ipv4 *ipv4,
                         const struct netstack_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_IPV4_H
