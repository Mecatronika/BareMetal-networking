// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#ifndef LIBNET_POSIX_PIPE_H
#define LIBNET_POSIX_PIPE_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief A POSIX implementation of
/// a network pipe.
struct libnet_posix_pipe
{
	/// @brief Base functions of the pipe
	struct libnet_pipe base;
	/// @brief Socket file descriptor
	int socket_fd;
	/// @brief Protocol to listen for.
	int protocol;
};

void libnet_posix_pipe_init(struct libnet_posix_pipe *pipe);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_POSIX_PIPE_H */
