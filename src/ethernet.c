// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/ethernet.h>

void libnet_ethernet_init(struct libnet_ethernet *ethernet)
{
	ethernet->type = LIBNET_ETHERTYPE_NONE;
	libnet_mac_init(&ethernet->source);
	libnet_mac_init(&ethernet->destination);
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
