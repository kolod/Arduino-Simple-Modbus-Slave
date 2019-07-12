#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../crc16.cpp"

#define UNUSED(x) (void)x
#define SIZE(x)   (sizeof(x) / sizeof(x[0]))

static uint8_t msg[] = {0x01, 0x03, 0x02, 0x00, 0x10, 0xff, 0x1e};

bool test(uint8_t *data, uint8_t length) {
	add_crc16(data, length - 2);
	uint16_t crc = crc16(data, length);
	printf("CRC = 0x%02X%02X\n", data[length-2], data[length-1]);
	printf("CRC = 0x%04X\n", crc);
	return crc == 0;
}

int main(int argc, char const *argv[]) {
	UNUSED(argc);
	UNUSED(argv);

	if (test(msg, SIZE(msg))) {
		puts("CRC16 Ok!");
	} else {
		puts("CRC16 Fail!");
	}
}
