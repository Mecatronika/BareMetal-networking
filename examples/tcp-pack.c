//============================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
//============================================================

#include <netstack/buffer.h>
#include <netstack/mutator.h>
#include <netstack/stack.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int mutate_ethernet(const void *mutator_data,
                           struct netstack_ethernet *ethernet)
{
	(void) mutator_data;

	ethernet->type = NETSTACK_ETHERTYPE_IPV6;

	int err = 0;
	err |= netstack_ethernet_set_source(ethernet, "00:11:22:33:44:55", 17);
	err |= netstack_ethernet_set_destination(ethernet, "33:44:55:66:77:88", 17);
	return err;
}

const char ipv6_source[] = "2001:0000:3238:DFE1:0063:0000:0000:FEFB";

const char ipv6_destination[] = "2001:0db8:85a3:0000:0000:8a2e:0370:7334";

static int mutate_ipv6(const void *mutator_data,
                       struct netstack_ipv6 *ipv6)
{
	(void) mutator_data;

	int err = 0;
	err |= netstack_ipv6_set_source(ipv6, ipv6_source, sizeof(ipv6_source) - 1);
	err |= netstack_ipv6_set_destination(ipv6, ipv6_destination, sizeof(ipv6_destination) - 1);
	return err;
}

static int mutate_tcp(const void *mutator_data,
                      struct netstack_tcp *tcp)
{
	(void) mutator_data;

	int err = 0;
	err |= netstack_tcp_set_source(tcp, "80", 2);
	err |= netstack_tcp_set_destination(tcp, "80", 2);
	return err;
}

static int export_buffer(const struct netstack_buffer *buffer)
{
	FILE *file = fopen("tcp-packet.pcap", "wb");
	if (file == NULL)
		return -1;

	// export PCAP global header

	// magic number
	fwrite("\xa1\xb2\xc3\xd4", 4, 1, file);
	// version major
	fwrite("\x00\x02", 2, 1, file);
	// version minor
	fwrite("\x00\x04", 2, 1, file);
	// GMT
	fwrite("\x00\x00\x00\x00", 4, 1, file);
	// accuracy of timestamps
	fwrite("\x00\x00\x00\x00", 4, 1, file);
	// max length of captured packets
	fwrite("\x00\x00\x00\x80", 4, 1, file);
	// data link type
	fwrite("\x00\x00\x00\x01", 4, 1, file);

	// export PCAP packet header

	// timestamp seconds
	fwrite("\x00\x00\x00\x00", 4, 1, file);
	// timestamp in microseconds
	fwrite("\x00\x00\x00\x00", 4, 1, file);
	// packet size in file (267)
	fwrite("\x00\x00\x01\x0b", 4, 1, file);
	// actual size of packet (267)
	fwrite("\x00\x00\x01\x0b", 4, 1, file);

	fwrite(buffer->data, 1, buffer->size, file);

	fclose(file);

	return 0;
}

const char http_response[] = "HTTP/1.1 200 OK\n"
                             "Date: Mon, 27 Jul 2009 12:28:53 GMT\n"
                             "Server: Apache/2.2.14 (Win32)\n"
                             "Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n"
                             "Content-Length: 0\n"
                             "Content-Type: text/html\n"
                             "Connection: Closed\n";

int main(void)
{
	struct netstack_stack stack;

	netstack_stack_init(&stack);

	int err = 0;
	err |= netstack_stack_push_ethernet(&stack);
	err |= netstack_stack_push_ipv6(&stack);
	err |= netstack_stack_push_tcp(&stack);
	if (err != 0)
	{
		fprintf(stderr, "Failed to construct network stack.\n");
		netstack_stack_done(&stack);
		return EXIT_FAILURE;
	}

	struct netstack_mutator mutator;
	netstack_mutator_init(&mutator);
	mutator.mutate_ethernet = mutate_ethernet;
	mutator.mutate_ipv6 = mutate_ipv6;
	mutator.mutate_tcp = mutate_tcp;

	err = netstack_stack_mutate(&stack, &mutator);
	if (err != 0)
	{
		fprintf(stderr, "Failed to mutate network stack.\n");
		netstack_stack_done(&stack);
		return EXIT_FAILURE;
	}

	char msgbuf[512];
	memset(msgbuf, 0, sizeof(msgbuf));
	strcat(msgbuf, http_response);

	struct netstack_buffer buffer;
	buffer.data = msgbuf;
	buffer.size = sizeof(http_response);
	buffer.reserved = sizeof(msgbuf);

	err = netstack_stack_pack(&stack, &buffer);
	if (err != 0)
	{
		fprintf(stderr, "Failed to pack message.\n");
		netstack_stack_done(&stack);
		return EXIT_FAILURE;
	}

	export_buffer(&buffer);

	netstack_stack_done(&stack);

	return EXIT_SUCCESS;
}
