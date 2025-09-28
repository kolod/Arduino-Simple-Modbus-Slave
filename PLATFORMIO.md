# PlatformIO Library Structure

This is a PlatformIO library project. The structure follows PlatformIO library conventions:

## Library Files
- `SimpleModbusSlave.h` - Main header file
- `SimpleModbusSlave.cpp` - Implementation file  
- `crc16.h` / `crc16.cpp` - CRC calculation utilities
- `library.json` - PlatformIO library manifest
- `library.properties` - Arduino IDE library properties
- `keywords.txt` - Arduino IDE syntax highlighting

## Examples
- `examples/SimpleModbusSlave/SimpleModbusSlave.ino` - Basic usage example
- `examples/TestCRC16/TestCRC16.ino` - CRC testing example

## Testing
- `test/` - Unit tests (Unity framework)
- `.github/workflows/test.yml` - CI/CD pipeline

## Installation

### Arduino IDE
1. Download the library
2. Install via Library Manager or copy to `libraries/` folder

### PlatformIO
```bash
# Install from PlatformIO Registry (when published)
pio lib install "SimpleModbusSlave"

# Install from Git repository
pio lib install "https://github.com/kolod/Arduino-Simple-Modbus-Slave.git"

# Install from local directory
pio lib install "file:///path/to/Arduino-Simple-Modbus-Slave"
```

## Usage in platformio.ini
```ini
[env:myboard]
platform = atmelavr
board = uno
framework = arduino
lib_deps = 
    SimpleModbusSlave
    # or
    https://github.com/kolod/Arduino-Simple-Modbus-Slave.git
```

## Note
This library does NOT use `platformio.ini` in the root directory as it's a library project, not an application project. The CI/CD system creates test projects dynamically to verify the library works across different platforms and boards.