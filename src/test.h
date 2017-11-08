// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#ifndef LIBNET_TEST_H
#define LIBNET_TEST_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief The structure used for testing the
/// network stack.
struct libnet_test
{
	/// @brief The file containing the binary
	/// contents of a packet.
	const char *packetfile;
	/// @brief The stack containing the protocols
	/// under test.
	struct libnet_stack stack;
};

void libnet_test_init(struct libnet_test *test,
                      const char *packetfile);

void libnet_test_done(struct libnet_test *test);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_TEST_H
