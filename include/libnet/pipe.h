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
void libnet_pipe_init(struct libnet_pipe *pipe);

/// @brief Releases resources allocated by
/// the pipe.
void libnet_pipe_done(struct libnet_pipe *pipe);

/// @brief Receives data.
int libnet_pipe_recv(struct libnet_pipe *pipe,
                     void *buf,
                     unsigned long long int buf_size,
                     unsigned long long int *recv_size);

/// @brief Sends data.
int libnet_pipe_send(struct libnet_pipe *pipe,
                     const void *buf,
                     unsigned long long int buf_size,
                     unsigned long long int *recv_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_PIPE_H
