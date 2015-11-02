/*
 * Copyright © 2011-2012 Stéphane Raimbault <stephane.raimbault@gmail.com>
 * Copyright © 2015 Alexandr Kolodkin <alexandr.kolodkin@gmail.com>
 * License ISC, see LICENSE for more details.
 */

#include <SimpleModbusSlave.h>

/* Initialize the slave with the ID 1 */
SimpleModbusSlave slave(1);
/* Allocate a mapping of 10 values */
uint16_t regs[10];

void setup() {
    /* The transfer speed is set to 115200 bauds */
    slave.setup(115200);
}

void loop() {
    /* Initialize the first register to have a value to read */
    regs[0] = 0x1234;
    /* Launch Modbus slave loop with:
       - pointer to the mapping
       - max values of mapping */
    slave.loop(regs, 10);
}
