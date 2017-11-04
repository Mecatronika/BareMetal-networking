// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file protocol.h

#ifndef LIBNET_PROTOCOL_H
#define LIBNET_PROTOCOL_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Identifies which protocol
/// is contained by the protocol structure.
enum libnet_protocol_id
{
	/// @brief The protocol is not
	/// specified.
	LIBNET_PROTOCOL_NONE,
	/// @brief The protocol is ethernet.
	LIBNET_PROTOCOL_ETHERNET,
	/// @brief The protocol is TCP.
	LIBNET_PROTOCOL_TCP,
	/// @brief The protocol is IP.
	LIBNET_PROTOCOL_IP,
	/// $brief The protocol is HTTP.
	LIBNET_PROTOCOL_HTTP
};

/// @brief The base structure for a protocol.
/// It contains all the callbacks required to
/// integrate with the network stack.
struct libnet_protocol
{
	/// @brief Identifies type information
	/// about the protocol.
	enum libnet_protocol_id id;
	/// @brief Protocol specific data.
	void *data;
};

/// @brief Initializes the protocol. This initializes
/// all of thei fields of the structure to prevent segmentation
/// fauls. It does not assign a real protocol to the structure.
void libnet_protocol_init(struct libnet_protocol *protocol);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_PROTOCOL_H
