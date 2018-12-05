#include "catch.hpp"
#include "encoder.h"
#include <fstream>
#include <sstream>
TEST_CASE("Test enoding of a file", "[Decode Raw]")
{
	char buffer[1024 * 3];
	char dest[1024 * 4];
	size_t cnt = 0;
	{
		std::string ifname = "a.bmp";
		std::string ofname = "b.b64";
		std::ifstream input(ifname, std::ios::binary);
		std::ofstream output(ofname,std::ios::binary);
		while (input.good() && output.good())
		{
			input.read(buffer, sizeof(buffer));
			cnt = input.gcount();
			std::string s = B64::encode((uint8_t*)buffer, cnt);
			output << s;
		}
	}
	{
		std::string ifname = "b.b64";
		std::string ofname = "a2.bmp";
		std::ifstream input;
		input.open(ifname, std::ios::binary);
		std::ofstream output(ofname, std::ios::binary);
		while (input.good() && output.good())
		{
			std::stringstream ss;
			input.read(dest, sizeof(dest));
			cnt = input.gcount();
			ss.write(dest, cnt);
			ss.put('/0');
			size_t len = B64::decode(ss.str(), (uint8_t*)buffer,sizeof(buffer));
			output.write(buffer, len);
		}
	}

}