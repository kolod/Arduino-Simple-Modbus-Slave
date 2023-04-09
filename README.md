[![Stand With Ukraine](https://raw.githubusercontent.com/vshymanskyy/StandWithUkraine/main/banner2-direct.svg)](https://vshymanskyy.github.io/StandWithUkraine/)

Simple Modbus Slave
=========

Introduction
------------

Arduino Simple Modbus Slave is an ISC licensed library to handle Modbus requests on Arduino (slave).


Features
--------

To keep it simple and to reduce memory consumption, only the two following
Modbus functions are supported:

* read holding registers (0x03)
* write multiple registers (0x10)

Example
-------

```c
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
```

Contribute
----------

I want to keep this library very basic and small so if you want to contribute:

1. Check for open issues or open a fresh issue to start a discussion around a feature idea or a bug.
2. Fork the [repository](https://github.com/kolod/Arduino-Simple-Modbus-Slave/) on Github to start making your changes on another
   branch.
3. Send a pull request (of your small and atomic changes).
4. Bug the maintainer if he's too busy to answer :)
