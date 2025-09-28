# Testing Setup

This document describes the testing infrastructure for the SimpleModbusSlave library.

## GitHub Actions CI/CD

The project includes comprehensive GitHub Actions workflows that automatically test the library on multiple platforms and configurations.

### Test Matrix

#### Arduino CLI Tests
- **Platforms**: Ubuntu Latest, Windows Latest  
- **Boards**:
  - Arduino Uno (`arduino:avr:uno`)
  - Arduino Mega (`arduino:avr:mega`)
  - ESP32 (`esp32:esp32:esp32`)

#### PlatformIO Tests  
- **Platforms**: Ubuntu Latest, Windows Latest
- **Environments**:
  - Arduino Uno
  - Arduino Mega 2560
  - ESP32 Dev Board
  - ESP8266 NodeMCU

### Test Types

1. **Compilation Tests**: Verify that examples compile successfully
2. **Library Validation**: Check library structure and properties
3. **Unit Tests**: Basic functionality testing
4. **Documentation**: Verify README and examples exist and are valid
5. **Release Readiness**: Version consistency and release preparation

## Running Tests Locally

### Arduino CLI

```bash
# Install Arduino CLI
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

# Install platforms
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli core install esp32:esp32 --additional-urls "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json"

# Create library symlink
mkdir -p ~/Arduino/libraries
ln -s $(pwd) ~/Arduino/libraries/SimpleModbusSlave

# Compile examples
arduino-cli compile --fqbn arduino:avr:uno examples/SimpleModbusSlave/SimpleModbusSlave.ino
arduino-cli compile --fqbn arduino:avr:uno examples/TestCRC16/TestCRC16.ino
```

### PlatformIO

For PlatformIO library testing, create a test project:

```bash
# Install PlatformIO
pip install platformio

# Create test project
mkdir pio-test
cd pio-test
pio project init --board uno

# Copy library to project (local development method)
mkdir -p lib/SimpleModbusSlave
cp ../*.h ../*.cpp ../library.json lib/SimpleModbusSlave/

# Create test main.cpp
cat > src/main.cpp << 'EOF'
#include <Arduino.h>
#include <SimpleModbusSlave.h>

SimpleModbusSlave slave(1, 2);
uint16_t regs[10];

void setup() {
    regs[0] = 0x1234;
    slave.setup(115200);
}

void loop() {
    slave.loop(regs, sizeof(regs) / sizeof(regs[0]));
}
EOF

# Build the project
pio run

# For unit testing, create a separate test project
mkdir ../unit-test-project
cd ../unit-test-project
pio project init --board uno

# Copy library to test project
mkdir -p lib/SimpleModbusSlave
cp ../*.h ../*.cpp ../library.json lib/SimpleModbusSlave/

# Run unit tests (if test directory exists)
pio test
```

### Unit Tests

Unit tests are located in the `test/` directory and use the Unity testing framework.

```bash
# Run unit tests
pio test -e test_uno
```

## Adding New Tests

### Arduino Examples
Add new example sketches to the `examples/` directory. They will be automatically tested by the CI.

### Unit Tests
Add new test files to the `test/` directory following the Unity framework conventions:

```cpp
#ifdef UNIT_TEST
#include <unity.h>

void test_your_feature() {
    TEST_ASSERT_TRUE(condition);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_your_feature);
    UNITY_END();
}

void loop() {}
#endif
```

### PlatformIO Environments
For testing new boards, update the GitHub Actions workflow matrix in `.github/workflows/test.yml`:

```yaml
matrix:
  board:
    - "uno"
    - "megaatmega2560" 
    - "esp32dev"
    - "your_new_board"
```

## Continuous Integration

The CI pipeline runs on:
- Every push to `main`, `develop`, and `add_dir_pin` branches
- Every pull request to `main` and `develop` branches  
- Manual workflow dispatch

### Status Badges

You can add these badges to your README:

```markdown
[![Test Library](https://github.com/kolod/Arduino-Simple-Modbus-Slave/actions/workflows/test.yml/badge.svg)](https://github.com/kolod/Arduino-Simple-Modbus-Slave/actions/workflows/test.yml)
```

## Troubleshooting

### Common Issues

1. **Library not found**: Ensure the library is properly symlinked or installed
2. **Platform not installed**: Install required platforms with Arduino CLI or PlatformIO  
3. **Permission issues**: On Windows, run as administrator for symlink creation
4. **Path issues**: Use absolute paths and proper shell commands for cross-platform compatibility

### Debug Mode

Enable verbose output in CI by adding debug flags:

```yaml
- name: Compile with debug
  run: |
    arduino-cli compile --fqbn arduino:avr:uno --verbose examples/SimpleModbusSlave/SimpleModbusSlave.ino
```