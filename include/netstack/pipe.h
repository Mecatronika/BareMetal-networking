// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file pipe.h

#ifndef NETSTACK_PIPE_H
#define NETSTACK_PIPE_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Used to implement send
/// and receive functions for the
/// network stack.
struct netstack_pipe
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
	            void *buf,
	            unsigned long long int buf_size,
	            unsigned long long int *recv_size);
	/// @brief Function pointer for the send
	/// implementation.
	int (*send)(void *pipe_data,
	            const void *buf,
	            unsigned long long int buf_size,
	            unsigned long long int *send_size);
};

/// @brief Initializes a pipe.
/// The caller still must set the internal callback
/// functions after this. This function is only for
/// pointer safety.
void netstack_pipe_init(struct netstack_pipe *pipe);

/// @brief Releases resources allocated by
/// the pipe.
void netstack_pipe_done(struct netstack_pipe *pipe);

/// @brief Moves the pipe from one structure to
/// another. The contents of the old structure are
/// erased.
void netstack_pipe_move(struct netstack_pipe *dst,
                        struct netstack_pipe *src);

/// @brief Receives data.
int netstack_pipe_recv(struct netstack_pipe *pipe,
                       void *buf,
                       unsigned long long int buf_size,
                       unsigned long long int *recv_size);

/// @brief Sends data.
int netstack_pipe_send(struct netstack_pipe *pipe,
                       const void *buf,
                       unsigned long long int buf_size,
                       unsigned long long int *recv_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_PIPE_H
