// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

/// @file ip.h

#ifndef LIBNET_IP_H
#define LIBNET_IP_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief IP protocols
enum libnet_ip
{
	/// @brief No protocol specified
	LIBNET_IP_NONE,
	/// @brief Internet Control Message Protocol
	LIBNET_IP_ICMP,
	/// @brief Internet Group Management Protocol
	LIBNET_IP_IGMP,
	/// @brief Transmission Control Protocol
	LIBNET_IP_TCP,
	/// @brief User Datagram Protocol
	LIBNET_IP_UDP,
	/// @brief IPv6 Encapsulation
	LIBNET_IP_ENCAP,
	/// @brief Open Shortest Path First
	LIBNET_IP_OSPF,
	/// @brief Stream Control Transmission Control
	LIBNET_IP_SCTP,
	/// @brief Unknown protocol
	LIBNET_IP_UNKNOWN,
	/// @brief References the first protocol in
	/// the enumeration. Used for iteration.
	LIBNET_IP_FIRST = LIBNET_IP_ICMP,
	/// @brief References the last protocol in
	/// the enumeration. Used for iteration.
	LIBNET_IP_LAST = LIBNET_IP_SCTP
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_IP_H
