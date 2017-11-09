// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

/// @file mac.h

#ifndef NETSTACK_MAC_H
#define NETSTACK_MAC_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief A MAC address. MAC stands for
/// media access control. It is used in
/// ethernet headers to specify source and
/// destinations.
struct netstack_mac
{
	/// @brief The six octets that make
	/// up the address.
	unsigned char octets[6];
};

/// @brief Initializes the MAC address to zero.
void netstack_mac_init(struct netstack_mac *mac);

/// @brief Parses a string containing a MAC address.
/// @param mac A MAC address structure.
/// @param str A string containing the MAC address
/// string. The numbers must be given in hexidecimal.
/// Each octet may be separated by a colon, dash or neither.
/// @param len The maximum number of characters that
/// may be contained by @p str.
/// @returns Zero if the function is successful, non-zero
/// otherwise.
int netstack_mac_parse(struct netstack_mac *mac,
                       const char *str,
                       unsigned long long int len);

/// @brief Writes the MAC address to a string.
/// The MAC address will be separated by dashes.
/// The string will be null-terminated.
/// @param mac An initialized MAC address.
/// @param str The string to write the MAC address to.
/// @param len The maximum number of characters that
/// may be stored by @p str. This should be greater than
/// or equal to eighteen.
/// @returns Zero on success, non-zero otherwise.
int netstack_mac_write(const struct netstack_mac *mac,
                       char *str,
                       unsigned long long int len);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_MAC_H
