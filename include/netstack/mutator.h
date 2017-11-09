// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file mutator.h

#ifndef NETSTACK_MUTATOR_H
#define NETSTACK_MUTATOR_H

#ifdef __cplusplus
extern "C"
{
#endif

struct netstack_ethernet;
struct netstack_ipv6;
struct netstack_tcp;

/// @brief Used for modifying protocol
/// parameters.
struct netstack_mutator
{
	/// @brief Mutator implementation data goes here.
	const void *data;
	/// @brief Mutate ethernet data.
	int (*mutate_ethernet)(const void *data, struct netstack_ethernet *ethernet);
	/// @brief Mutate IPv6 data.
	int (*mutate_ipv6)(const void *data, struct netstack_ipv6 *ipv6);
	/// @brief Mutate TCP data.
	int (*mutate_tcp)(const void *data, struct netstack_tcp *tcp);
};

/// @brief Initalizes the mutator structure.
void netstack_mutator_init(struct netstack_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_MUTATOR_H
