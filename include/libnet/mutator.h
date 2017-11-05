// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file mutator.h

#ifndef LIBNET_MUTATOR_H
#define LIBNET_MUTATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

struct libnet_ethernet;
struct libnet_ipv6;
struct libnet_tcp;

/// @brief Used for modifying protocol
/// parameters.
struct libnet_mutator
{
	/// @brief Mutator implementation data goes here.
	const void *data;
	/// @brief Mutate ethernet data.
	int (*mutate_ethernet)(const void *data, struct libnet_ethernet *ethernet);
	/// @brief Mutate IPv6 data.
	int (*mutate_ipv6)(const void *data, struct libnet_ipv6 *ipv6);
	/// @brief Mutate TCP data.
	int (*mutate_tcp)(const void *data, struct libnet_tcp *tcp);
};

/// @brief Initalizes the mutator structure.
void libnet_mutator_init(struct libnet_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_MUTATOR_H
