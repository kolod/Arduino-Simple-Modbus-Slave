#include <stdio.h>
#include <stdlib.h>

#include "../CRC16.cpp"

static uint8_t msg[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0x74, 0x45};

int main(int argc, char const *argv[]) {
	if (crc16(msg, sizeof(msg) / sizeof(msg[0]))) {
		puts("CRC16 Fail!");
		return -1;
	} else {
		puts("CRC16 Ok!");
		return 0;
	}
}
