// Copyright © 2011-2019 Stéphane Raimbault <stephane.raimbault@gmail.com>
// Copyright © 2015-2019 Alexandr Kolodkin <alexandr.kolodkin@gmail.com>
// License ISC, see LICENSE for more details.


#include <SimpleModbusSlave.h>

SimpleModbusSlave slave(1);   // Initialize the slave with the ID 1
uint16_t regs[10];            // Allocate a mapping of 10 values

void setup() {
    // Initialize the first register to have a value to read
    regs[0] = 0x1234;

    // The transfer speed is set to 115200 bauds
    slave.setup(115200);
}

void loop() {
    // Launch Modbus slave loop with:
    // - pointer to the mapping
    // - max values of mapping
    slave.loop(regs, sizeof(regs) / sizeof(regs[0]));
}
