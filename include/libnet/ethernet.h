// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file ethernet.h

#ifndef LIBNET_ETHERNET_H
#define LIBNET_ETHERNET_H

#include <libnet/mac.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct libnet_mutator;

/// @brief Used to indicate which
/// protocol is encapsulated in the
/// payload.
enum libnet_ethertype
{
	/// @brief No procotol in the payload.
	LIBNET_ETHERTYPE_NONE,
	/// @brief The protocol is ARP.
	LIBNET_ETHERTYPE_ARP,
	/// @brief The protocol is IPv4.
	LIBNET_ETHERTYPE_IPv4,
	/// @brief The protocol is IPv6.
	LIBNET_ETHERTYPE_IPv6
};

/// @brief Ethernet protocol variables.
struct libnet_ethernet
{
	/// @brief Destination MAC address.
	struct libnet_mac destination;
	/// @brief Source MAC address.
	struct libnet_mac source;
	/// @brief Indicates what protocol,
	/// if any, is in the payload.
	enum libnet_ethertype type;
};

/// @brief Initializes the ethernet protocol.
void libnet_ethernet_init(struct libnet_ethernet *ethernet);

/// @brief Sets the source MAC address for the ethernet headers.
int libnet_ethernet_set_source(struct libnet_ethernet *ethernet,
                               const char *src,
                               unsigned long long int src_size);

/// @brief Sets the destination MAC address for the ethernet headers.
int libnet_ethernet_set_destination(struct libnet_ethernet *ethernet,
                                    const char *dst,
                                    unsigned long long int dst_size);

/// @brief Allow a mutator access to the ethernet parameters.
int libnet_ethernet_mutate(struct libnet_ethernet *ethernet,
                           const struct libnet_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_ETHERNET_H
