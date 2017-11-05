// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

/// @file stack.h

#ifndef LIBNET_STACK_H
#define LIBNET_STACK_H

#include <libnet/ethernet.h>
#include <libnet/ipv6.h>

#include <libnet/pipe.h>
#include <libnet/protocol.h>

#ifndef LIBNET_PROTOCOL_MAX
#define LIBNET_PROTOCOL_MAX 8ULL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

struct libnet_buffer;
struct libnet_ethernet;

/// @brief Contains a type-safe indication
/// of the maximum amount of protocols the stack
/// may have.
extern const unsigned long long libnet_protocol_max;

/// @brief A network stack.
struct libnet_stack
{
	/// @brief The pipe used for sending and
	/// receiving data.
	struct libnet_pipe pipe;
	/// @brief An array of protocols that make
	/// up the network stack.
	struct libnet_protocol protocol_array[8];
	/// @brief The number of protocols in the
	/// nework stack.
	unsigned long long int protocol_count;
	/// @brief Ethernet protocol. This member
	/// is used if @ref libnet_stack_push_ethernet
	/// is called.
	struct libnet_ethernet ethernet;
	/// @brief IPv6 protocol. This member is
	/// used if @ref libnet_stack_push_ipv6 is
	/// called.
	struct libnet_ipv6 ipv6;
};

/// @brief Initializes the network stack.
/// The stack will not initially contain any
/// protocols. The protocols have to be added
/// before the stack may be used.
void libnet_stack_init(struct libnet_stack *stack);

/// @brief Called when the stack is no longer going
/// to be used. This function releases all resources
/// allocated by the protocols and pipe.
void libnet_stack_done(struct libnet_stack *stack);

/// @brief Pushes the ethernet protocol to the end of the stack.
/// @returns Zero if the function is successfull, non-zero
/// otherwise. This function will only fail if the number of
/// protocols has already exceed @ref LIBNET_PROTOCOL_MAX.
int libnet_stack_push_ethernet(struct libnet_stack *stack);

/// @brief Pushes the IP protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the number of
/// protocols has already exceeded @ref LIBNET_PROTOCOL_MAX.
int libnet_stack_push_ipv6(struct libnet_stack *stack);

/// @brief Pushes the TCP protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the number
/// of protocols has already exceeded @ref LIBNET_PROTOCOL_MAX.
int libnet_stack_push_tcp(struct libnet_stack *stack);

/// @brief Pushes an arbitrary protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero otherwise.
/// This function will only fail if the number of protocols have
/// already exceeded @ref LIBNET_PROTOCOL_MAX.
int libnet_stack_push_protocol(struct libnet_stack *stack,
                               struct libnet_protocol *protocol);

/// @brief Removes the protocol that was added last from
/// the network stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the stack
/// is already empty.
int libnet_stack_pop(struct libnet_stack *stack);

/// @brief Assigns a pipe to the network stack. This function
/// must be called before @ref libnet_stack_send and @ref libnet_stack_recv
/// may be used.
void libnet_stack_set_pipe(struct libnet_stack *stack,
                           struct libnet_pipe *pipe);

/// @brief Attempts to read from the network.
int libnet_stack_read(struct libnet_stack *stack,
                      struct libnet_buffer *buffer);

/// @brief Attempts to write to the network.
int libnet_stack_write(struct libnet_stack *stack,
                       const struct libnet_buffer *buffer);

/// @brief Modify the network stack data.
int libnet_stack_mutate(struct libnet_stack *stack,
                        const struct libnet_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_STACK_H
