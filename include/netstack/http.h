// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#ifndef NETSTACK_HTTP_H
#define NETSTACK_HTTP_H

#ifndef __cplusplus
extern "C"
{
#endif

/// @brief Indicates whether or not
/// the caller is a HTTP client.
enum netstack_http_mode
{
	/// @brief The caller is a HTTP client.
	NETSTACK_HTTP_MODE_CLIENT,
	/// @brief The caller is a HTTP server.
	NETSTACK_HTTP_MODE_SERVER
};

enum netstack_http_version
{
	NETSTACK_HTTP_VERSION_1_1
};

enum netstack_http_status
{
	NETSTACK_HTTP_STATUS_OK
};

enum netstack_http_content
{
	NETSTACK_HTTP_CONTENT_TEXT_HTML
};

struct netstack_http_response
{
	enum netstack_http_status status;
};

enum netstack_http_command
{
	NETSTACK_HTTP_COMMAND_NONE,
	NETSTACK_HTTP_COMMAND_GET,
	NETSTACK_HTTP_COMMAND_HEAD,
	NETSTACK_HTTP_COMMAND_POST,
	NETSTACK_HTTP_COMMAND_PUT,
	NETSTACK_HTTP_COMMAND_DELETE,
	NETSTACK_HTTP_COMMAND_CONNECT,
	NETSTACK_HTTP_COMMAND_OPTIONS,
	NETSTACK_HTTP_COMMAND_TRACE,
	NETSTACK_HTTP_COMMAND_UNKNOWN
};

struct netstack_http_request
{
	enum netstack_http_command command;
};

struct netstack_http
{
	/// @brief Indicates whether responses or
	/// requests should be sent.
	struct netstack_http_mode mode;
	/// @brief Contains the contents of a response
	/// that was either received or sent.
	struct netstack_http_response response;
	/// @brief Contains the contents of a request
	/// that was either received or sent.
	struct netstack_http_request request;
};

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_HTTP_H
