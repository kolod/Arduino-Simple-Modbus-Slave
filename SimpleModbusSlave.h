/*
 * Copyright © 2011-2012 Stéphane Raimbault <stephane.raimbault@gmail.com>
 * Copyright © 2015-2025 Oleksandr Kolodkin <oleksandr.kolodkin@ukr.net>
 *
 * License ISC, see LICENSE for more details.
 *
 * This library implements the Modbus protocol.
 * http://libmodbus.org/
 *
 */

#ifndef SimpleModbusSlave_h
#define SimpleModbusSlave_h

#include <inttypes.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
  #include <pins_arduino.h>
#endif

#include "crc16.h"

#define MODBUS_BROADCAST_ADDRESS 0

/* Protocol exceptions */
#define MODBUS_EXCEPTION_ILLEGAL_FUNCTION     1
#define MODBUS_EXCEPTION_ILLEGAL_DATA_ADDRESS 2
#define MODBUS_EXCEPTION_ILLEGAL_DATA_VALUE   3
#define MODBUS_INFORMATIVE_NOT_FOR_US   4
#define MODBUS_INFORMATIVE_RX_TIMEOUT   5

class SimpleModbusSlave {
public:
    SimpleModbusSlave(const uint8_t slave, const uint8_t dir_pin = 0xFF);
    void setup(const long baud);
    int loop(uint16_t *tab_reg, uint16_t nb_reg);
private:
    uint8_t _slave;
    uint8_t _dir_pin;
    
    int receive(uint8_t *req);
    void reply(uint16_t *tab_reg, uint16_t nb_reg, uint8_t *req, uint8_t req_length);
    int check_integrity(uint8_t *msg, const uint8_t msg_length);
    int build_response_basis(const uint8_t function, uint8_t* rsp);
    void send_msg(uint8_t *msg, const uint8_t msg_length);
    uint8_t response_exception(const uint8_t function, const uint8_t exception_code, uint8_t *rsp);
    void flush(void);
};

#endif /* SimpleModbusSlave_h */
