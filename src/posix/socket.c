// =========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <netstack/posix/socket.h>

#include <unistd.h>

void netstack_socket_init(struct netstack_socket *socket)
{
	netstack_pipe_init(&socket->base);
	socket->fd = -1;
}

void netstack_socket_done(struct netstack_socket *socket)
{
	if (socket->fd >= 0)
	{
		close(socket->fd);
		socket->fd = -1;
	}
}
