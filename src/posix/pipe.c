// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/posix/pipe.h>

void libnet_posix_pipe_init(struct libnet_posix_pipe *pipe)
{
	libnet_pipe_init(&pipe->base);
}

