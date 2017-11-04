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

/// @brief Ethernet protocol variables.
struct libnet_ethernet
{
	/// @brief Destination MAC address.
	struct libnet_mac destination;
	/// @brief Source MAC address.
	struct libnet_mac source;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_ETHERNET_H
