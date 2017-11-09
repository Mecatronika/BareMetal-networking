// =========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#ifndef NETSTACK_POSIX_SOCKET_H
#define NETSTACK_POSIX_SOCKET_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief A POSIX implementation of
/// a network pipe.
struct netstack_socket
{
	/// @brief Base functions of the pipe
	struct netstack_pipe base;
	/// @brief Socket file descriptor
	int fd;
	/// @brief Protocol to listen for.
	int protocol;
};

void netstack_socket_init(struct netstack_socket *socket);

void netstack_socket_done(struct netstack_socket *socket);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_POSIX_SOCKET_H */
