// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file ethernet.h

#ifndef NETSTACK_ETHERNET_H
#define NETSTACK_ETHERNET_H

#include <netstack/mac.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct netstack_buffer;
struct netstack_mutator;

/// @brief Used to indicate which
/// protocol is encapsulated in the
/// payload.
enum netstack_ethertype
{
	/// @brief No procotol in the payload.
	NETSTACK_ETHERTYPE_NONE,
	/// @brief The protocol is ARP.
	NETSTACK_ETHERTYPE_ARP,
	/// @brief The protocol is IPv4.
	NETSTACK_ETHERTYPE_IPV4,
	/// @brief The protocol is IPv6.
	NETSTACK_ETHERTYPE_IPV6,
	/// @brief The protocol is unknown
	/// or not supported.
	NETSTACK_ETHERTYPE_UNKNOWN
};

/// @brief Ethernet protocol variables.
struct netstack_ethernet
{
	/// @brief Destination MAC address.
	struct netstack_mac destination;
	/// @brief Source MAC address.
	struct netstack_mac source;
	/// @brief Indicates what protocol,
	/// if any, is in the payload.
	enum netstack_ethertype type;
	/// @brief If @ref NETSTACK_ETHERNET_NONE
	/// is set, then this field will indicate
	/// the length of the payload.
	unsigned int length;
	/// @brief The CRC32 checksum of the
	/// header and payload.
	unsigned long int checksum;
};

/// @brief Initializes the ethernet protocol.
void netstack_ethernet_init(struct netstack_ethernet *ethernet);

/// @brief Sets the source MAC address for the ethernet headers.
int netstack_ethernet_set_source(struct netstack_ethernet *ethernet,
                                 const char *src,
                                 unsigned long long int src_size);

/// @brief Sets the destination MAC address for the ethernet headers.
int netstack_ethernet_set_destination(struct netstack_ethernet *ethernet,
                                      const char *dst,
                                      unsigned long long int dst_size);

int netstack_ethernet_pack(struct netstack_ethernet *ethernet,
                           struct netstack_buffer *buffer);

int netstack_ethernet_unpack(struct netstack_ethernet *ethernet,
                             struct netstack_buffer *buffer);

/// @brief Allow a mutator access to the ethernet parameters.
int netstack_ethernet_mutate(struct netstack_ethernet *ethernet,
                             const struct netstack_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_ETHERNET_H
