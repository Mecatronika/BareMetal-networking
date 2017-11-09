// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/stack.h>

#include <netstack/ethernet.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

const unsigned long long int netstack_protocol_max = NETSTACK_PROTOCOL_MAX;

static int ethernet_pack(void *ethernet_ptr,
                         struct netstack_buffer *buffer)
{
	struct netstack_ethernet *ethernet = (struct netstack_ethernet *) ethernet_ptr;

	return netstack_ethernet_pack(ethernet, buffer);
}

static int ethernet_mutate(void *ethernet_ptr,
                           const struct netstack_mutator *mutator)
{
	struct netstack_ethernet *ethernet = (struct netstack_ethernet *) ethernet_ptr;

	return netstack_ethernet_mutate(ethernet, mutator);
}

static int ipv6_pack(void *ipv6_ptr,
                     struct netstack_buffer *buffer)
{
	struct netstack_ipv6 *ipv6 = (struct netstack_ipv6 *) ipv6_ptr;

	return netstack_ipv6_pack(ipv6, buffer);
}

static int ipv6_mutate(void *ipv6_ptr,
                       const struct netstack_mutator *mutator)
{
	struct netstack_ipv6 *ipv6 = (struct netstack_ipv6 *) ipv6_ptr;

	return netstack_ipv6_mutate(ipv6, mutator);
}

static int tcp_pack(void *tcp_ptr,
                     struct netstack_buffer *buffer)
{
	struct netstack_tcp *tcp = (struct netstack_tcp *) tcp_ptr;

	return netstack_tcp_pack(tcp, buffer);
}

static int tcp_mutate(void *tcp_ptr,
                      const struct netstack_mutator *mutator)
{
	struct netstack_tcp *tcp = (struct netstack_tcp *) tcp_ptr;

	return netstack_tcp_mutate(tcp, mutator);
}

void netstack_stack_init(struct netstack_stack *stack)
{
	netstack_pipe_init(&stack->pipe);

	for (unsigned long long int i = 0; i < NETSTACK_PROTOCOL_MAX; i++)
		netstack_protocol_init(&stack->protocol_array[i]);

	stack->protocol_count = 0;
}

void netstack_stack_done(struct netstack_stack *stack)
{
	netstack_pipe_done(&stack->pipe);

	for (unsigned long long int i = 0; i < NETSTACK_PROTOCOL_MAX; i++)
		netstack_protocol_done(&stack->protocol_array[i]);
}

int netstack_stack_mutate(struct netstack_stack *stack,
                          const struct netstack_mutator *mutator)
{
	for (unsigned long long int i = 0; i < stack->protocol_count; i++)
	{
		struct netstack_protocol *protocol = &stack->protocol_array[i];

		int err = netstack_protocol_mutate(protocol, mutator);
		if (err != 0)
			return err;
	}

	return 0;
}

int netstack_stack_push_ethernet(struct netstack_stack *stack)
{
	netstack_ethernet_init(&stack->ethernet);

	struct netstack_protocol protocol;
	netstack_protocol_init(&protocol);
	protocol.data = &stack->ethernet;
	protocol.done = NULL;
	protocol.pack = ethernet_pack;
	protocol.unpack = NULL;
	protocol.mutate = ethernet_mutate;
	return netstack_stack_push_protocol(stack, &protocol);
}

int netstack_stack_push_ipv6(struct netstack_stack *stack)
{
	netstack_ipv6_init(&stack->ipv6);

	struct netstack_protocol protocol;
	netstack_protocol_init(&protocol);
	protocol.data = &stack->ipv6;
	protocol.done = NULL;
	protocol.pack = ipv6_pack;
	protocol.unpack = NULL;
	protocol.mutate = ipv6_mutate;
	return netstack_stack_push_protocol(stack, &protocol);
}

int netstack_stack_push_tcp(struct netstack_stack *stack)
{
	netstack_tcp_init(&stack->tcp);

	struct netstack_protocol protocol;
	netstack_protocol_init(&protocol);
	protocol.data = &stack->tcp;
	protocol.done = NULL;
	protocol.pack = tcp_pack;
	protocol.unpack = NULL;
	protocol.mutate = tcp_mutate;
	return netstack_stack_push_protocol(stack, &protocol);
}

int netstack_stack_push_protocol(struct netstack_stack *stack,
                                 struct netstack_protocol *protocol)
{
	if (stack->protocol_count >= netstack_protocol_max)
		return -1;

	netstack_protocol_move(&stack->protocol_array[stack->protocol_count], protocol);

	stack->protocol_count++;

	return 0;
}

int netstack_stack_pack(struct netstack_stack *stack,
                        struct netstack_buffer *buffer)
{
	for (size_t i = stack->protocol_count; i > 0; i--)
	{
		int err = netstack_protocol_pack(&stack->protocol_array[i - 1], buffer);
		if (err != 0)
			return err;
	}

	return 0;
}

int netstack_stack_read(struct netstack_stack *stack,
                        struct netstack_buffer *buffer)
{
	(void) stack;
	(void) buffer;
	return 0;
}

void netstack_stack_set_pipe(struct netstack_stack *stack,
                             struct netstack_pipe *pipe)
{
	netstack_pipe_move(&stack->pipe, pipe);
}
