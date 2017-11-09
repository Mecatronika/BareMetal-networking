// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/mutator.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void netstack_mutator_init(struct netstack_mutator *mutator)
{
	mutator->data = NULL;
	mutator->mutate_ethernet = NULL;
	mutator->mutate_ipv6 = NULL;
	mutator->mutate_tcp = NULL;
}
