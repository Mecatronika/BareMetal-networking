// ===========================================================
// netstack -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// ===========================================================

#ifndef NETSTACK_CRC_H
#define NETSTACK_CRC_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Calculates the 16-bit CRC for a block of memory.
uint16_t netstack_crc16(const void *buf,
                        size_t buf_size);

/// @brief Calculates the 32-bit CRC for a block of memory.
uint32_t netstack_crc32(const void *buf,
                        size_t buf_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // NETSTACK_CRC_H
