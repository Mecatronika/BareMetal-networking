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
	pipe->recv = NULL;
	pipe->send = NULL;
}

void libnet_pipe_done(struct libnet_pipe *pipe)
{
	if (pipe->done != NULL)
		pipe->done(pipe->data);
}

int libnet_pipe_recv(struct libnet_pipe *pipe,
                     void *buf,
                     unsigned long long int buf_size,
                     unsigned long long int *recv_size)
{
	if (pipe->recv == NULL)
		return -1;

	return pipe->recv(pipe->data, buf, buf_size, recv_size);
}

int libnet_pipe_send(struct libnet_pipe *pipe,
                     const void *buf,
                     unsigned long long int buf_size,
                     unsigned long long int *recv_size)
{
	if (pipe->recv == NULL)
		return -1;

	return pipe->send(pipe->data, buf, buf_size, recv_size);
}
