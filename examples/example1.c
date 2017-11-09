//============================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

#include <netstack/stack.h>

#include <stdlib.h>

int main(void)
{
	struct netstack_stack stack;

	netstack_stack_init(&stack);

	netstack_stack_done(&stack);

	return EXIT_SUCCESS;
}
