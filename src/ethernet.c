// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/ethernet.h>

#include <libnet/buffer.h>
#include <libnet/crc.h>
#include <libnet/mutator.h>

#include <stdlib.h>

void libnet_ethernet_init(struct libnet_ethernet *ethernet)
{
	libnet_mac_init(&ethernet->source);
	libnet_mac_init(&ethernet->destination);
	ethernet->type = LIBNET_ETHERTYPE_NONE;
	ethernet->length = 0;
	ethernet->checksum = 0;
}

int libnet_ethernet_set_source(struct libnet_ethernet *ethernet,
                               const char *src,
                               unsigned long long int src_size)
{
	return libnet_mac_parse(&ethernet->source, src, src_size);
}

int libnet_ethernet_set_destination(struct libnet_ethernet *ethernet,
                                    const char *dst,
                                    unsigned long long int dst_size)
{
	return libnet_mac_parse(&ethernet->destination, dst, dst_size);
}

int libnet_ethernet_pack(struct libnet_ethernet *ethernet,
                         struct libnet_buffer *buffer)
{
	if (buffer->reserved < buffer->size)
	{
		// this could cause a security bug
		// below, if left unchecked
		return -1;
	}

	size_t available = buffer->reserved - buffer->size;
	if (available < 18)
	{
		// ethernet header requires 18 bytes,
		// the buffer is suppose to fit this.
		return -1;
	}

	// limitations of the ethernet protocol
	if ((buffer->size < 46) || (buffer->size > 1500))
		return -1;

	size_t data_size = buffer->size;

	// MAC dst + MAC src + length/ethertype
	int err = libnet_buffer_shift(buffer, 14);
	if (err != 0)
		return err;

	unsigned char *header = buffer->data;

	for (size_t i = 0; i < 6; i++)
	{
		header[i + 0] = ethernet->destination.octets[i];
		header[i + 6] = ethernet->source.octets[i];
	}

	if (ethernet->type == LIBNET_ETHERTYPE_IPV4)
	{
		header[12] = 0x08;
		header[13] = 0x00;
	}
	else if (ethernet->type == LIBNET_ETHERTYPE_IPV6)
	{
		header[12] = 0x86;
		header[13] = 0xdd;
	}
	else if (ethernet->type == LIBNET_ETHERTYPE_NONE)
	{
		header[12] = (unsigned char) ((data_size & 0xff00) >> 8);
		header[13] = (unsigned char) ((data_size & 0x00ff) >> 0);
	}

	uint32_t crc = libnet_crc32(buffer->data, buffer->size);

	header[14 + data_size + 3] = (0xff000000 & crc) >> 24;
	header[14 + data_size + 2] = (0x00ff0000 & crc) >> 16;
	header[14 + data_size + 1] = (0x0000ff00 & crc) >> 8;
	header[14 + data_size + 0] = (0x000000ff & crc) >> 0;

	buffer->size += 4;

	return 0;
}

int libnet_ethernet_unpack(struct libnet_ethernet *ethernet,
                           struct libnet_buffer *buffer)
{
	// ethernet header should be at
	// least eighteen bytes long
	if (buffer->size < 18)
		return -1;

	unsigned char *header = buffer->data;

	for (size_t i = 0; i < 6; i++)
	{
		ethernet->destination.octets[i] = header[i];
		ethernet->source.octets[i] = header[i + 6];
	}

	unsigned int length = 0;
	length |= ((unsigned int) header[12]) << 8;
	length |= ((unsigned int) header[13]) << 0;
	if (length  < 1500)
	{
		ethernet->type = LIBNET_ETHERTYPE_NONE;
		ethernet->length = length;
	}
	else if (length == 0x0800)
	{
		ethernet->type = LIBNET_ETHERTYPE_IPV4;
		ethernet->length = 0;
	}
	else if (length == 0x0806)
	{
		ethernet->type = LIBNET_ETHERTYPE_ARP;
		ethernet->length = 0;
	}
	else if (length == 0x86dd)
	{
		ethernet->type = LIBNET_ETHERTYPE_IPV6;
		ethernet->length = 0;
	}
	else
	{
		ethernet->type = LIBNET_ETHERTYPE_UNKNOWN;
		ethernet->length = 0;
	}

	int err = libnet_buffer_shift_left(buffer, 14);
	if (err != 0)
		return err;

	// remove checksum
	buffer->size -= 4;

	return 0;
}

int libnet_ethernet_mutate(struct libnet_ethernet *ethernet,
                           const struct libnet_mutator *mutator)
{
	if (mutator->mutate_ethernet == NULL)
		// Not an ethernet mutator
		return 0;

	return mutator->mutate_ethernet(mutator->data, ethernet);
}
