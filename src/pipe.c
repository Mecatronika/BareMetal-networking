// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/pipe.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif

void netstack_pipe_init(struct netstack_pipe *pipe)
{
	pipe->data = NULL;
	pipe->done = NULL;
	pipe->recv = NULL;
	pipe->send = NULL;
}

void netstack_pipe_done(struct netstack_pipe *pipe)
{
	if (pipe->done != NULL)
		pipe->done(pipe->data);
}

void netstack_pipe_move(struct netstack_pipe *dst,
                        struct netstack_pipe *src)
{
	// copy the structure
	*dst = *src;
	// zero the old structure
	netstack_pipe_init(src);
}

int netstack_pipe_recv(struct netstack_pipe *pipe,
                       void *buf,
                       unsigned long long int buf_size,
                       unsigned long long int *recv_size)
{
	if (pipe->recv == NULL)
		return -1;

	return pipe->recv(pipe->data, buf, buf_size, recv_size);
}

int netstack_pipe_send(struct netstack_pipe *pipe,
                       const void *buf,
                       unsigned long long int buf_size,
                       unsigned long long int *recv_size)
{
	if (pipe->recv == NULL)
		return -1;

	return pipe->send(pipe->data, buf, buf_size, recv_size);
}
