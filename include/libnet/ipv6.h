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

struct libnet_ipv6_address
{
	unsigned char octets[16];
};

void libnet_ipv6_address_init(struct libnet_ipv6_address *address);

int libnet_ipv6_address_parse(struct libnet_ipv6_address *address,
                              const char *str, size_t str_size);

struct libnet_ipv6
{
	struct libnet_ipv6_address source;
	struct libnet_ipv6_address destination;
};

void libnet_ipv6_init(struct libnet_ipv6 *ipv6);

int libnet_ipv6_set_source(struct libnet_ipv6 *ipv6,
                           const char *src, size_t src_size);

int libnet_ipv6_set_destination(struct libnet_ipv6 *ipv6,
                                const char *dst, size_t dst_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_IPV6_H
