//============================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/http.h>

void netstack_http_init(struct netstack_http *http)
{
	netstack_protocol_init(&http->base);
}

void netstack_http_done(struct netstack_http *http)
{
	netstack_protocol_done(&http->base);
}
