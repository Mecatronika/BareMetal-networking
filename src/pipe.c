// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/pipe.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void libnet_pipe_init(struct libnet_pipe *pipe)
{
	pipe->data = NULL;
	pipe->done = NULL;
	pipe->send = NULL;
	pipe->recv = NULL;
}

void libnet_pipe_done(struct libnet_pipe *pipe)
{
	if (pipe->done != NULL)
		pipe->done(pipe->data);
}
