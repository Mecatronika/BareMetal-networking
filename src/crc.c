// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#include <netstack/crc.h>

uint32_t crc32(const void *buf,
               size_t buf_size);

uint32_t netstack_crc32(const void *buf,
                        size_t buf_size)
{
	return crc32(buf, buf_size);
}
