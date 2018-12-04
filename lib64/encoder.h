#pragma once
#include <string>
#define MBYTES 3
#define BITS_PER_BYTE 8
#define BASE_64_BITS 6
#define BUF_LEN 4
#define PADDING '='
namespace B64 {
	std::string encode(std::string c);
	std::string decode(std::string c);
}