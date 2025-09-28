//    Arduino PPM Generator
//    Copyright (C) 2015-2019  Alexandr Kolodkin <alexandr.kolodkin@gmail.com>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <SimpleModbusSlave.h>

static uint8_t msg[] = {0x01, 0x03, 0x02, 0x00, 0x10, 0xff, 0x1e};

bool test(uint8_t *data, uint8_t length) {
	add_crc16(data, length - 2);
	uint16_t crc = crc16(data, length);
	Serial.print("CRC = 0x");
	Serial.print(data[length-2], HEX);
	Serial.print(data[length-1], HEX);
	Serial.println();
	Serial.print("CRC = 0x");
	Serial.println(crc, HEX);
	return crc == 0;
}

void setup() {
  Serial.begin(115200);
  
	if (test(msg, sizeof(msg))) {
		Serial.println("CRC16 Ok!");
	} else {
		Serial.println("CRC16 Fail!");
	}
}

void loop() {
  ;
}
