// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

/// @file stack.h

#ifndef LIBNET_STACK_H
#define LIBNET_STACK_H

#include <libnet/protocol.h>

#ifndef LIBNET_PROTOCOL_MAX
#define LIBNET_PROTOCOL_MAX 8ULL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Contains a type-safe indication
/// of the maximum amount of protocols the stack
/// may have.
extern const unsigned long long libnet_protocol_max;

/// @brief A network stack.
struct libnet_stack
{
	/// @brief An array of protocols that make
	/// up the network stack.
	struct libnet_protocol protocol_array[8];
	/// @brief The number of protocols in the
	/// nework stack.
	unsigned long long int protocol_count;
};

/// @brief Initializes the network stack.
/// The stack will not initially contain any
/// protocols. The protocols have to be added
/// before the stack may be used.
void libnet_stack_init(struct libnet_stack *stack);

/// @brief Pushes the IP protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the number of
/// protocols has already exceeded @ref LIBNET_PROTOCOL_MAX.
int libnet_stack_push_ip(struct libnet_stack *stack);

/// @brief Pushes the TCP protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the number
/// of protocols has already exceeded @ref LIBNET_PROTOCOL_MAX.
int libnet_stack_push_tcp(struct libnet_stack *stack);

/// @brief Removes the protocol that was added last from
/// the network stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the stack
/// is already empty.
int libnet_stack_pop(struct libnet_stack *stack);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_STACK_H
