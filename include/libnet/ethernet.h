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

struct libnet_buffer;
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
	LIBNET_ETHERTYPE_IPV4,
	/// @brief The protocol is IPv6.
	LIBNET_ETHERTYPE_IPV6,
	/// @brief The protocol is unknown
	/// or not supported.
	LIBNET_ETHERTYPE_UNKNOWN
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
	/// @brief If @ref LIBNET_ETHERNET_NONE
	/// is set, then this field will indicate
	/// the length of the payload.
	unsigned int length;
	/// @brief The CRC32 checksum of the
	/// header and payload.
	unsigned long int checksum;
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

int libnet_ethernet_pack(struct libnet_ethernet *ethernet,
                         struct libnet_buffer *buffer);

int libnet_ethernet_unpack(struct libnet_ethernet *ethernet,
                           struct libnet_buffer *buffer);

/// @brief Allow a mutator access to the ethernet parameters.
int libnet_ethernet_mutate(struct libnet_ethernet *ethernet,
                           const struct libnet_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_ETHERNET_H
