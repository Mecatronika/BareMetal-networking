// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//==========================================================

/// @file tcp.h

#ifndef LIBNET_TCP_H
#define LIBNET_TCP_H

#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct libnet_buffer;
struct libnet_mutator;

/// @brief TCN-nonce - concealment protection
#define LIBNET_TCP_NS  0x0100

/// @brief Sent by the sending host to indicate
/// that it received a TCP segment with the ECE
/// flag set and had responded in congestion
/// control mechanism.
#define LIBNET_TCP_CWR 0x0080

/// @brief Depending on the SYN flag,
/// it indicates:
/// - If the SYN flag is 1, that the TCP
///   peer is ECN capable.
/// - If the SYN flag is 0, that a packet
///   with Congestion Experienced flag set
///   (ECN=11) in IP header was was received
///   during normal transmission. This serves
///   as an indication of network congestion
///   to the TCP sender.
#define LIBNET_TCP_ECE 0x0040

/// @brief Indicates that the urgent pointer
/// field is significant.
#define LIBNET_TCP_URG 0x0020

/// @brief Indicates that the acknowledgment
/// field is significant.
#define LIBNET_TCP_ACK 0x0010

/// @brief Push function. Asks to push
/// the buffered data to the receiving
/// application.
#define LIBNET_TCP_PSH 0x0008

/// @brief Resets the connection.
#define LIBNET_TCP_RST 0x0004

/// @brief Synchronize sequence numbers.
/// Only the first packet sent from each
/// end should have this flag set. Some
/// other flags and fields change meaning
/// based on this flag, and some are only
/// valid when it is set, and others when
/// it is clear.
#define LIBNET_TCP_SYN 0x0002

/// @brief Indicates that the packet is
/// the last packet from the sender.
#define LIBNET_TCP_FIN 0x0001

struct libnet_tcp
{
	/// @brief Identifies the sending
	/// port. This value may not exceed
	/// 65535.
	unsigned int source;
	/// @brief Identifies the receiving
	/// port. This value may not exceed
	/// 65535.
	unsigned int destination;
	/// @brief Sequence number
	unsigned long int sequence;
	/// @brief Acknowledgement number
	unsigned long int acknowledgment;
	/// @brief The offset from the header
	/// to the actual data. This is also
	/// equal to the size of the TCP header.
	/// The unit of measurement is not bytes,
	/// it is 32-bit words. The minimum value
	/// of this field is 5 and the maximum
	/// value is 15.
	unsigned int data_offset;
	/// @brief TCP control bits.
	unsigned int control_bits;
	/// @brief The size of the receive window,
	/// which specifies the number of window size
	/// units (by default, bytes) that the sender
	/// of this segment is currently willing to
	/// receive.
	unsigned int window_size;
	/// @brief The 16-bit checksum of the TCP header
	/// and the data that follows. This field is set
	/// by the library and does not need to be set by
	/// the caller.
	unsigned int checksum;
	/// @brief If the @ref LIBNET_TCP_URG flag is set,
	/// then this is an offset from the sequence number
	/// indicating the last urgent data byte.
	unsigned int urgent_pointer;
};

void libnet_tcp_init(struct libnet_tcp *tcp);

int libnet_tcp_set_source(struct libnet_tcp *tcp,
                          const char *str,
                          size_t str_size);

int libnet_tcp_set_destination(struct libnet_tcp *tcp,
                               const char *str,
                               size_t str_size);

int libnet_tcp_mutate(struct libnet_tcp *tcp,
                      const struct libnet_mutator *mutator);

int libnet_tcp_pack(struct libnet_tcp *tcp,
                    struct libnet_buffer *buffer);

int libnet_tcp_unpack(struct libnet_tcp *tcp,
                      struct libnet_buffer *buffer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_TCP_H
