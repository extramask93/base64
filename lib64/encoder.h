#pragma once
#include <string>
#include <vector>


namespace B64 {
	std::string encode(std::string c);
	std::string decode(std::string c);
	std::string encode(uint8_t *src, const size_t len);
	size_t decode(const std::string src, uint8_t *out, size_t out_len);

}