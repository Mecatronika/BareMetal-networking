// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/mutator.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void libnet_mutator_init(struct libnet_mutator *mutator)
{
	mutator->data = NULL;
	mutator->mutate_ethernet = NULL;
}
