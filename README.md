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

Direction Pin Support
--------------------

This library supports RS485 transceivers that require a direction control pin to switch between transmit and receive modes. The direction pin is automatically controlled during communication:

* **LOW (receive mode)**: Default state, allows the slave to receive data
* **HIGH (transmit mode)**: Activated when sending response data

To use a direction pin, specify the pin number when creating the slave instance:

```c
SimpleModbusSlave slave(1, 2);   // Slave ID 1, direction pin 2
```

If no direction pin is needed (e.g., for direct serial communication), omit the parameter or use `0xFF`:

```c
SimpleModbusSlave slave(1);      // No direction pin control
SimpleModbusSlave slave(1, 0xFF); // Explicitly disable direction pin
```

Examples
--------

### Basic Example (No Direction Pin)

```c
#include <SimpleModbusSlave.h>

SimpleModbusSlave slave(1);   // Initialize the slave with ID 1
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

### RS485 Example (With Direction Pin)

```c
#include <SimpleModbusSlave.h>

SimpleModbusSlave slave(1, 2); // Slave ID 1, direction pin 2
uint16_t regs[10];              // Allocate a mapping of 10 values

void setup() {
    // Initialize the first register to have a value to read
    regs[0] = 0x1234;

    // The transfer speed is set to 115200 bauds
    slave.setup(115200);

    // Direction pin is automatically configured as OUTPUT
    // and set to LOW (receive mode) by the library
}

void loop() {
    // Launch Modbus slave loop
    // Direction pin will be automatically controlled:
    // - LOW when receiving data
    // - HIGH when transmitting responses
    slave.loop(regs, sizeof(regs) / sizeof(regs[0]));
}
```

Contribute
----------

I want to keep this library very basic and small so if you want to contribute:

1. Check for open issues or open a fresh issue to start a discussion around a feature idea or a bug.
2. Fork the [repository](https://github.com/kolod/Arduino-Simple-Modbus-Slave/) on Github to start making your changes on another branch.
3. Send a pull request (of your small and atomic changes).
4. Bug the maintainer if he's too busy to answer :)
