// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/stack.h>

#include <libnet/ethernet.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

const unsigned long long int libnet_protocol_max = LIBNET_PROTOCOL_MAX;

static int ethernet_pack(void *ethernet_ptr,
                         struct libnet_buffer *buffer)
{
	struct libnet_ethernet *ethernet = (struct libnet_ethernet *) ethernet_ptr;

	return libnet_ethernet_pack(ethernet, buffer);
}

static int ethernet_mutate(void *ethernet_ptr,
                           const struct libnet_mutator *mutator)
{
	struct libnet_ethernet *ethernet = (struct libnet_ethernet *) ethernet_ptr;

	return libnet_ethernet_mutate(ethernet, mutator);
}

static int ipv6_pack(void *ipv6_ptr,
                     struct libnet_buffer *buffer)
{
	struct libnet_ipv6 *ipv6 = (struct libnet_ipv6 *) ipv6_ptr;

	return libnet_ipv6_pack(ipv6, buffer);
}

static int ipv6_mutate(void *ipv6_ptr,
                       const struct libnet_mutator *mutator)
{
	struct libnet_ipv6 *ipv6 = (struct libnet_ipv6 *) ipv6_ptr;

	return libnet_ipv6_mutate(ipv6, mutator);
}

void libnet_stack_init(struct libnet_stack *stack)
{
	libnet_pipe_init(&stack->pipe);

	for (unsigned long long int i = 0; i < LIBNET_PROTOCOL_MAX; i++)
		libnet_protocol_init(&stack->protocol_array[i]);

	stack->protocol_count = 0;
}

void libnet_stack_done(struct libnet_stack *stack)
{
	libnet_pipe_done(&stack->pipe);

	for (unsigned long long int i = 0; i < LIBNET_PROTOCOL_MAX; i++)
		libnet_protocol_done(&stack->protocol_array[i]);
}

int libnet_stack_mutate(struct libnet_stack *stack,
                        const struct libnet_mutator *mutator)
{
	for (unsigned long long int i = 0; i < stack->protocol_count; i++)
	{
		struct libnet_protocol *protocol = &stack->protocol_array[i];

		int err = libnet_protocol_mutate(protocol, mutator);
		if (err != 0)
			return err;
	}

	return 0;
}

int libnet_stack_push_ethernet(struct libnet_stack *stack)
{
	libnet_ethernet_init(&stack->ethernet);

	struct libnet_protocol protocol;
	libnet_protocol_init(&protocol);
	protocol.data = &stack->ethernet;
	protocol.done = NULL;
	protocol.pack = ethernet_pack; //ethernet_write;
	protocol.pack = NULL; //ethernet_read;
	protocol.mutate = ethernet_mutate;
	return libnet_stack_push_protocol(stack, &protocol);
}

int libnet_stack_push_ipv6(struct libnet_stack *stack)
{
	libnet_ipv6_init(&stack->ipv6);

	struct libnet_protocol protocol;
	libnet_protocol_init(&protocol);
	protocol.data = &stack->ipv6;
	protocol.done = NULL;
	protocol.pack = ipv6_pack;
	protocol.mutate = ipv6_mutate;
	return libnet_stack_push_protocol(stack, &protocol);
}

int libnet_stack_push_protocol(struct libnet_stack *stack,
                               struct libnet_protocol *protocol)
{
	if (stack->protocol_count >= libnet_protocol_max)
		return -1;

	libnet_protocol_move(&stack->protocol_array[stack->protocol_count], protocol);

	stack->protocol_count++;

	return 0;
}

int libnet_stack_read(struct libnet_stack *stack,
                      struct libnet_buffer *buffer)
{
	(void) stack;
	(void) buffer;
	return 0;
}

void libnet_stack_set_pipe(struct libnet_stack *stack,
                           struct libnet_pipe *pipe)
{
	libnet_pipe_move(&stack->pipe, pipe);
}
