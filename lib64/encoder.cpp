#include "stdafx.h"
#include "encoder.h"
#include <stdint.h>
#include <sstream>
#include <exception>
namespace B64
{
	const size_t MBYTES = 3;
	const size_t BITS_PER_BYTE = 8;
	const size_t BASE_64_BITS = 6;
	const size_t BUF_LEN = 4;
	const char PADDING = '=';

	const std::string base64Table =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";
	uint8_t buff[BUF_LEN];

	inline void eightBitToTableVal(const uint32_t &hold24, uint8_t *buffz) {
		buffz[0] = base64Table[(hold24 >> 18) & 0x3f];
		buffz[1] = base64Table[(hold24 >> 12) & 0x3f];
		buffz[2] = base64Table[(hold24 >> 6) & 0x3f];
		buffz[3] = base64Table[hold24 & 0x3f];
	}

	inline uint8_t CharDecode(const uint8_t &tmp)
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
		else
			return 255;
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
		uint32_t eqTyp = 0;
		uint8_t t[4];
		for (size_t i = 0; i < c.length(); ++i)
		{
			char tmp = c[i];
			if (tmp == '=')
				eqTyp++;
			tmp = CharDecode(tmp);
			t[sexesRead] = tmp;
			++sexesRead;
			if (!(sexesRead % 4)) {
				if (eqTyp == 1)
				{
					buff[0] = ((t[0] << 2) & 0xfc) | ((t[1] & 0x30) >> 4);
					buff[1] = ((t[1] & 0xf) << 4) | ((t[2] & 0x3c) >> 2);
					buffer << buff[0] << buff[1];
				}
				else if (eqTyp == 2)
				{
					buff[0] = ((t[0] << 2) & 0xfc) | ((t[1] & 0x30) >> 4);
					buffer << buff[0];
				}
				else {
					buff[0] = ((t[0] << 2) & 0xfc) | ((t[1] & 0x30) >> 4);
					buff[1] = ((t[1] & 0xf) << 4) | ((t[2] & 0x3c) >> 2);
					buff[2] = ((t[2] & 0x3) << 6) | t[3] & 0x3f;
					buffer << buff[0] << buff[1] << buff[2];
				}
				sexesRead = 0;
			}
		}
		return buffer.str();
	}
}

namespace B64 {
	std::string encode(uint8_t *src, const size_t len)
	{
		uint32_t hold24 = 0;
		uint8_t bytesRead = 0;
		std::stringstream buffer;
		for (size_t i = 0; i < len; ++i)
		{
			hold24 <<= BITS_PER_BYTE;
			hold24 |= src[i];
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
	size_t decode(const std::string src, uint8_t *out, size_t out_len)
	{
		uint32_t hold24 = 0;
		uint8_t sexesRead = 0;
		size_t cnt = 0;
		uint32_t eqTyp = 0;
		uint8_t t[4];
		int z = src.length();
		for (size_t i = 0; i < src.length(); ++i)
		{
			uint8_t tmp = src[i];
			if (tmp == '=')
				eqTyp++;
			tmp = CharDecode(tmp);
			t[sexesRead] = tmp;
			++sexesRead;
			if (!(sexesRead % 4)) {
				if (eqTyp == 1)
				{
					buff[0] = ((t[0] << 2) & 0xfc) | ((t[1] & 0x30) >> 4);
					buff[1] = ((t[1] & 0xf) << 4) | ((t[2] & 0x3c) >> 2);
					out[cnt++] = buff[0];
					out[cnt++] = buff[1];
				}
				else if (eqTyp == 2)
				{
					buff[0] = ((t[0] << 2) & 0xfc) | ((t[1] & 0x30) >> 4);
					out[cnt++] =  buff[0];
				}
				else {
					buff[0] = ((t[0] << 2) & 0xfc) | ((t[1] & 0x30) >> 4);
					buff[1] = ((t[1] & 0xf) << 4) | ((t[2] & 0x3c) >> 2);
					buff[2] = ((t[2] & 0x3) << 6) | t[3] & 0x3f;
					out[cnt++] = buff[0];
					out[cnt++] = buff[1];
					out[cnt++] = buff[2];
				}
				sexesRead = 0;
			}
		}
		return cnt;
	}
}