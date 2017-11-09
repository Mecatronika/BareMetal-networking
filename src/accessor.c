// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/accessor.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void netstack_accessor_init(struct netstack_accessor *accessor)
{
	accessor->data = NULL;
	accessor->access_ethernet = NULL;
	accessor->access_ipv6 = NULL;
	accessor->access_tcp = NULL;
}
