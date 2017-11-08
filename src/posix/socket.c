// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/posix/socket.h>

#include <unistd.h>

void libnet_socket_init(struct libnet_socket *socket)
{
	libnet_pipe_init(&socket->base);
	socket->fd = -1;
}

void libnet_socket_done(struct libnet_socket *socket)
{
	if (socket->fd >= 0)
	{
		close(socket->fd);
		socket->fd = -1;
	}
}
