#include "stdafx.h"
#include "encoder.h"
#include <stdint.h>
#include <sstream>

static const std::string base64Table =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
static char buff[BUF_LEN];

static inline void eightBitToTableVal(const uint32_t &hold24, char *buffz) {
	buffz[0] = base64Table[(hold24 >> 18) & 0x3f];
	buffz[1] = base64Table[(hold24 >> 12) & 0x3f];
	buffz[2] = base64Table[(hold24 >> 6) & 0x3f];
	buffz[3] = base64Table[hold24 & 0x3f];
}
static inline void TableValToEightBit(const uint32_t &hold24, char *buffz) {
	buffz[0] = (hold24 >> 16) & 0xff;
	buffz[1] = (hold24 >> 8) & 0xff;
	buffz[2] = hold24 & 0xff;
}
namespace B64 {
	std::string encode(std::string c)
	{
		std::stringstream buffer;
		uint32_t hold24 = 0;
		uint8_t bytesRead = 0;
		for (size_t i = 0; i < c.length(); ++i)
		{
			hold24 <<= BITS_PER_BYTE;
			hold24 |= c[i];
			++bytesRead;
			if (!(bytesRead % MBYTES)) {
				eightBitToTableVal(hold24, buff);
				buffer << buff[0] << buff[1] << buff[2] << buff[3];
				bytesRead = 0;
			}
		}
		if (bytesRead) {
			hold24 <<= BITS_PER_BYTE * (MBYTES - bytesRead);
			eightBitToTableVal(hold24, buff);
			for (int i = ((bytesRead*BITS_PER_BYTE) / BASE_64_BITS) + 1; i < BUF_LEN; ++i) {
				buff[i] = PADDING;
			}
			buffer << buff[0] << buff[1] << buff[2] << buff[3];
		}
		return buffer.str();
	}
	std::string decode(std::string c)
	{
		std::stringstream buffer;
		uint32_t hold24 = 0;
		uint8_t sexesRead = 0;
		for (size_t i = 0; i < c.length(); ++i)
		{
			hold24 <<= 6;
			char tmp = c[i] & 0x3f;
			if (tmp >= 'A' && tmp <= 'Z')
			{
				tmp = tmp - 'A';
			}
			else if (tmp >='a' && tmp <'z')
			{
				tmp = tmp - 71;
			}
			else if (tmp >= '0' && tmp <= '9')
			{
				tmp = tmp + 4;
			}
			else if (tmp == '+')
			{
				tmp = 62;
			}
			else if (tmp == '/')
			{
				tmp = 63;
			}
			++sexesRead;
			if (!(sexesRead % 4)) {
				TableValToEightBit(hold24, buff);
				buffer << buff[0] << buff[1] << buff[2];
				sexesRead = 0;
			}

		}
		return buffer.str();
	}
}