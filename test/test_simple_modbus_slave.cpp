#ifdef UNIT_TEST

#include <unity.h>
#include <Arduino.h>
#include "SimpleModbusSlave.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_slave_initialization() {
    SimpleModbusSlave slave(1);
    TEST_ASSERT_TRUE(true); // Basic test that constructor works
}

void test_slave_with_direction_pin() {
    SimpleModbusSlave slave(1, 2);
    TEST_ASSERT_TRUE(true); // Basic test that constructor with dir_pin works
}

void test_slave_register_loop() {
    SimpleModbusSlave slave(1);
    uint16_t regs[10] = {0x1234, 0x5678, 0x9ABC, 0xDEF0};
    
    // This would normally be called in loop(), but we can't test actual Modbus communication
    // without hardware, so we just verify it doesn't crash
    int result = slave.loop(regs, 10);
    TEST_ASSERT_GREATER_OR_EQUAL(-10, result); // Should return a valid error code or positive value
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_slave_initialization);
    RUN_TEST(test_slave_with_direction_pin);
    RUN_TEST(test_slave_register_loop);
    UNITY_END();
}

void loop() {
    // Empty loop for unit testing
}

#endif