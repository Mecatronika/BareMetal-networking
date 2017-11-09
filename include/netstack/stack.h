// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

/// @file stack.h

#ifndef NETSTACK_STACK_H
#define NETSTACK_STACK_H

#include <netstack/ethernet.h>
#include <netstack/ipv6.h>
#include <netstack/tcp.h>

#include <netstack/pipe.h>
#include <netstack/protocol.h>

#ifndef NETSTACK_PROTOCOL_MAX
#define NETSTACK_PROTOCOL_MAX 8ULL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

struct netstack_buffer;
struct netstack_ethernet;

/// @brief Contains a type-safe indication
/// of the maximum amount of protocols the stack
/// may have.
extern const unsigned long long netstack_protocol_max;

/// @brief A network stack.
struct netstack_stack
{
	/// @brief The pipe used for sending and
	/// receiving data.
	struct netstack_pipe pipe;
	/// @brief An array of protocols that make
	/// up the network stack.
	struct netstack_protocol protocol_array[8];
	/// @brief The number of protocols in the
	/// nework stack.
	unsigned long long int protocol_count;
	/// @brief Ethernet protocol. This member
	/// is used if @ref netstack_stack_push_ethernet
	/// is called.
	struct netstack_ethernet ethernet;
	/// @brief IPv6 protocol. This member is
	/// used if @ref netstack_stack_push_ipv6 is
	/// called.
	struct netstack_ipv6 ipv6;
	/// @brief TCP protocol. This member is
	/// used if @ref netstack_stack_push_tcp is
	/// called.
	struct netstack_tcp tcp;
};

/// @brief Initializes the network stack.
/// The stack will not initially contain any
/// protocols. The protocols have to be added
/// before the stack may be used.
void netstack_stack_init(struct netstack_stack *stack);

/// @brief Called when the stack is no longer going
/// to be used. This function releases all resources
/// allocated by the protocols and pipe.
void netstack_stack_done(struct netstack_stack *stack);

/// @brief Pushes the ethernet protocol to the end of the stack.
/// @returns Zero if the function is successfull, non-zero
/// otherwise. This function will only fail if the number of
/// protocols has already exceed @ref NETSTACK_PROTOCOL_MAX.
int netstack_stack_push_ethernet(struct netstack_stack *stack);

/// @brief Pushes the IP protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the number of
/// protocols has already exceeded @ref NETSTACK_PROTOCOL_MAX.
int netstack_stack_push_ipv6(struct netstack_stack *stack);

/// @brief Pushes the TCP protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the number
/// of protocols has already exceeded @ref NETSTACK_PROTOCOL_MAX.
int netstack_stack_push_tcp(struct netstack_stack *stack);

/// @brief Pushes an arbitrary protocol to the end of the stack.
/// @returns Zero if the function is successful, non-zero otherwise.
/// This function will only fail if the number of protocols have
/// already exceeded @ref NETSTACK_PROTOCOL_MAX.
int netstack_stack_push_protocol(struct netstack_stack *stack,
                                 struct netstack_protocol *protocol);

/// @brief Removes the protocol that was added last from
/// the network stack.
/// @returns Zero if the function is successful, non-zero
/// otherwise. This function will only fail if the stack
/// is already empty.
int netstack_stack_pop(struct netstack_stack *stack);

/// @brief Encapsulate a buffer with headers and footers
/// of the network stack.
int netstack_stack_pack(struct netstack_stack *stack,
                        struct netstack_buffer *buffer);

/// @brief Assigns a pipe to the network stack. This function
/// must be called before @ref netstack_stack_send and @ref netstack_stack_recv
/// may be used.
void netstack_stack_set_pipe(struct netstack_stack *stack,
                             struct netstack_pipe *pipe);

/// @brief Attempts to read from the network.
int netstack_stack_read(struct netstack_stack *stack,
                        struct netstack_buffer *buffer);

/// @brief Attempts to write to the network.
int netstack_stack_write(struct netstack_stack *stack,
                         const struct netstack_buffer *buffer);

/// @brief Modify the network stack data.
int netstack_stack_mutate(struct netstack_stack *stack,
                          const struct netstack_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_STACK_H
