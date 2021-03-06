// Converter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "encoder.h"
#include <fstream>
#include <sstream>

char buffer[1024 * 3];
char dest[1024 * 4];
void print_usage()
{
	std::cerr << "Usage:\nConverter.exe -d|-e inputfile outputfile\n" <<
		"\t-d\tdecode inputfile from base64 format\n" <<
		"\t-e\tencode inputfile to base64 format\n";
}
int main(int argc, char **argv)
{
	if (argc < 4)
	{
		print_usage();
		return 1;
	}
	const std::string ifname(argv[2]);
	const std::string ofname(argv[3]);
	std::ifstream input(ifname, std::ios::binary);
	std::ofstream output(ofname,std::ios::binary);
	if (strcmp("-d", argv[1])==0)
	{
		while (input.good() && output.good())
		{
			std::stringstream ss;
			input.read(dest, sizeof(dest));
			auto cnt = input.gcount();
			ss.write(dest, cnt);
			ss.put(char('/0'));
			const size_t len = B64::decode(ss.str(), reinterpret_cast<uint8_t*>(buffer), 
				sizeof(buffer));
			output.write(buffer, len);
		}
	}
	else if (strcmp("-e", argv[1]) == 0)
	{
		while (input.good() && output.good())
		{
			input.read(buffer, sizeof(buffer));
			auto cnt = input.gcount();
			std::string s = B64::encode(reinterpret_cast<uint8_t*>(buffer),static_cast<size_t>(cnt));
			output << s;
		}
	}
	else {
		print_usage();
		return 2;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
