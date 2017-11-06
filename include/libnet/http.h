// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#ifndef LIBNET_HTTP_H
#define LIBNET_HTTP_H

#ifndef __cplusplus
extern "C"
{
#endif

/// @brief Indicates whether or not
/// the caller is a HTTP client.
enum libnet_http_mode
{
	/// @brief The caller is a HTTP client.
	LIBNET_HTTP_MODE_CLIENT,
	/// @brief The caller is a HTTP server.
	LIBNET_HTTP_MODE_SERVER
};

enum libnet_http_version
{
	LIBNET_HTTP_VERSION_1_1
};

enum libnet_http_status
{
	LIBNET_HTTP_STATUS_OK
};

enum libnet_http_content
{
	LIBNET_HTTP_CONTENT_TEXT_HTML
};

struct libnet_http_response
{
	enum libnet_http_status status;
};

enum libnet_http_command
{
	LIBNET_HTTP_COMMAND_NONE,
	LIBNET_HTTP_COMMAND_GET,
	LIBNET_HTTP_COMMAND_HEAD,
	LIBNET_HTTP_COMMAND_POST,
	LIBNET_HTTP_COMMAND_PUT,
	LIBNET_HTTP_COMMAND_DELETE,
	LIBNET_HTTP_COMMAND_CONNECT,
	LIBNET_HTTP_COMMAND_OPTIONS,
	LIBNET_HTTP_COMMAND_TRACE,
	LIBNET_HTTP_COMMAND_UNKNOWN
};

struct libnet_http_request
{
	enum libnet_http_command command;
};

struct libnet_http
{
	/// @brief Indicates whether responses or
	/// requests should be sent.
	struct libnet_http_mode mode;
	/// @brief Contains the contents of a response
	/// that was either received or sent.
	struct libnet_http_response response;
	/// @brief Contains the contents of a request
	/// that was either received or sent.
	struct libnet_http_request request;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_HTTP_H
