// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

/// @file error.h

#ifndef LIBNET_ERROR_H
#define LIBNET_ERROR_H

#ifdef __cplusplus
extern "C"
{
#endif

enum {
	/// @brief No error has occured
	LIBNET_ERROR_NONE = 0,
	/// @brief A protocol handler found a
	/// bad field.
	LIBNET_ERROR_BAD_FIELD,
	/// @brief A protocol handler needs more
	/// data to parse a header (or footer)
	LIBNET_ERROR_MISSING_DATA,
	/// @brief Unknown error has occured
	LIBNET_ERROR_UNKNOWN
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_ERROR_H
