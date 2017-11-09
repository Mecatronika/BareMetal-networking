// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

/// @file ip.h

#ifndef NETSTACK_IP_H
#define NETSTACK_IP_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief IP protocols
enum netstack_ip
{
	/// @brief No protocol specified
	NETSTACK_IP_NONE,
	/// @brief Internet Control Message Protocol
	NETSTACK_IP_ICMP,
	/// @brief Internet Group Management Protocol
	NETSTACK_IP_IGMP,
	/// @brief Transmission Control Protocol
	NETSTACK_IP_TCP,
	/// @brief User Datagram Protocol
	NETSTACK_IP_UDP,
	/// @brief IPv6 Encapsulation
	NETSTACK_IP_ENCAP,
	/// @brief Open Shortest Path First
	NETSTACK_IP_OSPF,
	/// @brief Stream Control Transmission Control
	NETSTACK_IP_SCTP,
	/// @brief Unknown protocol
	NETSTACK_IP_UNKNOWN,
	/// @brief References the first protocol in
	/// the enumeration. Used for iteration.
	NETSTACK_IP_FIRST = NETSTACK_IP_ICMP,
	/// @brief References the last protocol in
	/// the enumeration. Used for iteration.
	NETSTACK_IP_LAST = NETSTACK_IP_SCTP
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_IP_H
