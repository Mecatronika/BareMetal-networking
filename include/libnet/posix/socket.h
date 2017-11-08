// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#ifndef LIBNET_POSIX_SOCKET_H
#define LIBNET_POSIX_SOCKET_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief A POSIX implementation of
/// a network pipe.
struct libnet_socket
{
	/// @brief Base functions of the pipe
	struct libnet_pipe base;
	/// @brief Socket file descriptor
	int fd;
	/// @brief Protocol to listen for.
	int protocol;
};

void libnet_socket_init(struct libnet_socket *socket);

void libnet_socket_done(struct libnet_socket *socket);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_POSIX_SOCKET_H */
