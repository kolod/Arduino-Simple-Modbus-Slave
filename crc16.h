/*
 * Copyright © 2015 Alexandr Kolodkin <alexandr.kolodkin@gmail.com>
 *
 * License ISC, see LICENSE for more details.
 *
 * This library implements the Modbus protocol.
 * http://libmodbus.org/
 *
 */

#ifndef CRC16_h
#define CRC16_h

#include <stddef.h>
#include <stdint.h>

extern uint16_t crc16(uint8_t *data, uint8_t length);
extern void add_crc16(uint8_t *data, uint8_t length);

#endif /* CRC16_h */
