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
	printf("CRC = 0x%02X%02X\n", data[length-2], data[length-1]);
	printf("CRC = 0x%04X\n", crc);
	return crc == 0;
}

int setup() {
  Serial.begin(115200);
  
	if (test(msg, sizeof(msg))) {
		Serial.print("CRC16 Ok!\n");
	} else {
		Serial.print("CRC16 Fail!\n");
	}
}

void loop() {
  ;
}
