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

static inline char CharDecode(const char &tmp)
{
	if (tmp >= 'A' && tmp <= 'Z')
	{
		return tmp - 'A';
	}
	else if (tmp >= 'a' && tmp <= 'z')
	{
		return tmp - 71;
	}
	else if (tmp >= '0' && tmp <= '9')
	{
		return tmp + 4;
	}
	else if (tmp == '+')
	{
		return 62;
	}
	else if (tmp == '/')
	{
		return 63;
	}
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
		unsigned char t[4];
		for (size_t i = 0; i < c.length(); ++i)
		{
			char tmp = c[i];
			tmp = CharDecode(tmp);
			t[sexesRead] = tmp;
			++sexesRead;
			if (!(sexesRead % 4)) {
				buff[0] = ((t[0] << 2)&0xfc) | ((t[1] & 0x30)>>4);
				buff[1] = ((t[1] & 0xf)<<4) | ((t[2]&0x3c)>>2);
				buff[2] = ((t[2] & 0x3) << 6) | t[3] & 0x3f;
				buffer << buff[0] << buff[1] << buff[2];
				sexesRead = 0;
			}

		}
		return buffer.str();
	}
}