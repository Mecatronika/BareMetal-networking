// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file pipe.h

#ifndef LIBNET_PIPE_H
#define LIBNET_PIPE_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Used to implement send
/// and receive functions for the
/// network stack.
struct libnet_pipe
{
	/// @brief Implementation data goes here.
	void *data;
	/// @bief Called when the pipe is no longer
	/// needed. Used to free up resources allocated
	/// by the pipe, if any.
	void (*done)(void *pipe_data);
	/// @brief Function pointer for the receive
	/// implementation.
	int (*recv)(void *pipe_data,
	            struct libnet_pipe *pipe);
	/// @brief Function pointer for the send
	/// implementation.
	int (*send)(void *pipe_data,
	            const struct libnet_pipe *pipe);
};

void libnet_pipe_init(struct libnet_pipe *pipe);

void libnet_pipe_done(struct libnet_pipe *pipe);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_PIPE_H
