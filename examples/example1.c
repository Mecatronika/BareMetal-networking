// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/stack.h>

#include <stdlib.h>

int main(void)
{
	struct libnet_stack stack;

	libnet_stack_init(&stack);

	libnet_stack_done(&stack);

	return EXIT_SUCCESS;
}
