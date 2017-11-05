// =========================================================
// libnet -- A network stack implementation for BareMetal OS
//
// Copyright (C) 2017 Return Infinity -- see LICENSE
// =========================================================

#include <stdint.h>
#include <stdlib.h>

#ifndef LIBNET_CRC_H
#define LIBNET_CRC_H

#ifdef __cplusplus
extern "C"
{
#endif

/// @brief Calculates the 16-bit CRC for a block of memory.
uint16_t libnet_crc16(const void *buf,
                      size_t buf_size);

/// @brief Calculates the 32-bit CRC for a block of memory.
uint32_t libnet_crc32(const void *buf,
                      size_t buf_size);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // LIBNET_CRC_H
