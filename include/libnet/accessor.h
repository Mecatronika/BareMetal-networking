// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file accessor.h

#ifndef LIBNET_ACCESSOR_H
#define LIBNET_ACCESSOR_H

#ifdef __cplusplus
extern "C"
{
#endif

struct libnet_ethernet;
struct libnet_ipv6;
struct libnet_tcp;

/// @brief Used for reading
/// protocol parameters.
struct libnet_accessor
{
	/// @brief Accessor implementation data goes here.
	void *data;
	/// @brief Access ethernet data.
	int (*access_ethernet)(void *data, const struct libnet_ethernet *ethernet);
	/// @brief Access IPv6 data.
	int (*access_ipv6)(void *data, const struct libnet_ipv6 *ipv6);
	/// @brief Access TCP data.
	int (*access_tcp)(void *data, const struct libnet_tcp *tcp);
};

/// @brief Initalizes the accessor structure.
void libnet_accessor_init(struct libnet_accessor *accessor);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_ACCESSOR_H
