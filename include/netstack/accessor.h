// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file accessor.h

#ifndef NETSTACK_ACCESSOR_H
#define NETSTACK_ACCESSOR_H

#ifdef __cplusplus
extern "C"
{
#endif

struct netstack_ethernet;
struct netstack_ipv6;
struct netstack_tcp;

/// @brief Used for reading
/// protocol parameters.
struct netstack_accessor
{
	/// @brief Accessor implementation data goes here.
	void *data;
	/// @brief Access ethernet data.
	int (*access_ethernet)(void *data, const struct netstack_ethernet *ethernet);
	/// @brief Access IPv6 data.
	int (*access_ipv6)(void *data, const struct netstack_ipv6 *ipv6);
	/// @brief Access TCP data.
	int (*access_tcp)(void *data, const struct netstack_tcp *tcp);
};

/// @brief Initalizes the accessor structure.
void netstack_accessor_init(struct netstack_accessor *accessor);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_ACCESSOR_H
