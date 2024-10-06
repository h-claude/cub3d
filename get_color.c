#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[31m"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define MAGENTA "\033[95m"
#define CYAN "\033[96m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

void print_bits(int n);
void print_color_bits(int n);
typedef unsigned char uint8_t;
typedef unsigned int uint32_t;


int main(int ac, char **av)
{
	// RGB are 0-255, so 8 bits, so a single color channel is uint8_t
	// We want to store 4 channels, so we need
	//		> (4_channels * 8_bits_per_channel) = 32 bits, so we use uint32_t

	const int size_of_uint8_t = 8;

	uint32_t red   = 0xFC << (size_of_uint8_t * 3);
	uint32_t green = 0xD9 << (size_of_uint8_t * 2);
	uint32_t blue  = 0x17 << (size_of_uint8_t * 1);
	uint32_t alpha = 0xff << (size_of_uint8_t * 0);

	// Same as above, written in decimal form
	// uint32_t red   = 252 << (size_of_uint8_t * 3);
	// uint32_t green = 217 << (size_of_uint8_t * 2);
	// uint32_t blue  = 23 << (size_of_uint8_t * 1);
	// uint32_t alpha = 255 << (size_of_uint8_t * 0);

	// [red     ][green   ][blue     ][alpha  ]
	// [255     ][255     ][255      ][255    ]
	// [11111111][11111111][11111111][11111111]


	printf(RED"R %sDecimal: %010u, hex: %08x, Binary: ", RESET,red,red); print_bits(red); printf("\n");
	printf(GREEN"G %sDecimal: %010u, hex: %08x, Binary: ", RESET,green,green); print_bits(green); printf("\n");
	printf(BLUE"B %sDecimal: %010u, hex: %08x, Binary: ", RESET,blue,blue); print_bits(blue); printf("\n");
	printf(YELLOW"A %sDecimal: %010u, hex: %08x, Binary: ", RESET,alpha,alpha); print_bits(alpha); printf("\n");

	printf("\n");
	// Same result
	// uint32_t color = red | green | blue | alpha;
	uint32_t color = red + green + blue + alpha;
	print_color_bits(color);
}

void print_bits(int n) {
	int i;
	for (i = 31; i >= 0; i--) {
		short bit = (n >> i) & 1;
		if (bit) {
			printf(CYAN "%d" RESET, bit);
		} else {
			printf(MAGENTA "%d"RESET, bit);
		}
	}
}

void print_color_bits(int n) {
	int i;
	printf("\033[4mFinal uint32_t Value:%s\n\n", RESET);
	printf("\tAs Decimal: %u\n\n", n);
	printf("\tAs Hex:    ");
	{
		int red = n >> 24 & 0xFF;
		int green = (n >> 16) & 0xFF;
		int blue = (n >> 8) & 0xFF;
		int alpha = n & 0xFF;
		printf(RED "%02X" RESET, red);
		printf(GREEN "%02X" RESET, green);
		printf(BLUE "%02X" RESET, blue);
		printf(YELLOW "%02X" RESET, alpha);
	}
	printf("\n\n");
	printf("\tAs Binary: ");
	for (i = 31; i >= 0; i--)
	{
		short bit = (n >> i) & 1;
		if (i >= 24)
			printf(RED "%d" RESET, bit);
		else if (i >= 16)
			printf(GREEN "%d" RESET, bit);
		else if (i >= 8)
			printf(BLUE "%d" RESET, bit);
		else
			printf(YELLOW "%d" RESET, bit);
	}
	printf("\n\n");
}