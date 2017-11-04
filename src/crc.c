// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <libnet/crc.h>

unsigned long int libnet_crc32(const void *buf,
                               unsigned long long int buf_size)
{
	(void) buf;
	(void) buf_size;
	return 0;
}
