// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file protocol.h

#ifndef NETSTACK_PROTOCOL_H
#define NETSTACK_PROTOCOL_H

#ifdef __cplusplus
extern "C"
{
#endif

struct netstack_buffer;
struct netstack_mutator;

/// @brief Identifies which protocol
/// is contained by the protocol structure.
enum netstack_protocol_id
{
	/// @brief The protocol is not
	/// specified.
	NETSTACK_PROTOCOL_NONE,
	/// @brief The protocol is ethernet.
	NETSTACK_PROTOCOL_ETHERNET,
	/// @brief The protocol is TCP.
	NETSTACK_PROTOCOL_TCP,
	/// @brief The protocol is IP.
	NETSTACK_PROTOCOL_IP,
	/// $brief The protocol is HTTP.
	NETSTACK_PROTOCOL_HTTP
};

/// @brief The base structure for a protocol.
/// It contains all the callbacks required to
/// integrate with the network stack.
struct netstack_protocol
{
	/// @brief Identifies type information
	/// about the protocol.
	enum netstack_protocol_id id;
	/// @brief Protocol specific data.
	void *data;
	/// @brief Called when the protocol
	/// is no longer going to be used.
	void (*done)(void *protocol_data);
	/// @brief Attempts to read data from
	/// the protocol.
	int (*pack)(void *protocol_data,
	            struct netstack_buffer *buffer);
	/// @brief Attempts to write data to
	/// the protocol.
	int (*unpack)(void *protocol_data,
	              struct netstack_buffer *buffer);
	/// @brief Modify protocol data.
	int (*mutate)(void *protocol_data,
	              const struct netstack_mutator *mutator);
};

/// @brief Initializes the protocol. This initializes
/// all of the fields of the structure to prevent segmentation
/// fauls. It does not assign a real protocol to the structure.
void netstack_protocol_init(struct netstack_protocol *protocol);

/// @brief Releases resources allocated by the protocol.
void netstack_protocol_done(struct netstack_protocol *protocol);

/// @brief Moves the contents of one protocol structure
/// to another, erasing the old protocol.
/// @param dst The structure to move the protocol to.
/// @param src The structure to move the contents from.
void netstack_protocol_move(struct netstack_protocol *dst,
                            struct netstack_protocol *src);

int netstack_protocol_pack(struct netstack_protocol *protocol,
                           struct netstack_buffer *buffer);

int netstack_protocol_unpack(struct netstack_protocol *protocol,
                             struct netstack_buffer *buffer);

/// @brief Modify the protocol data.
int netstack_protocol_mutate(struct netstack_protocol *protocol,
                             const struct netstack_mutator *mutator);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_PROTOCOL_H
