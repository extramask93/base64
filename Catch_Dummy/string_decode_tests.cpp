#include "catch.hpp"
#include "encoder.h"

TEST_CASE("Decode simple alligned string","[Decode]")
{
	std::string in = "TWFu";
	std::string res = "Man";
	REQUIRE(res == B64::decode(in));
}
TEST_CASE("Decode simple unalligned string", "[Decode]")
{
	std::string in = "TWE=";
	std::string res = "Ma";
	REQUIRE(res == B64::decode(in));
}
TEST_CASE("Decode simple unalligned string 2", "[Decode]")
{
	std::string in = "TQ==";
	std::string res = "M";
	REQUIRE(res == B64::decode(in));
}
TEST_CASE("Decode long string", "[Decode]")
{
	std::string in = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
		"dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
		"ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
	std::string lon = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
	REQUIRE(lon == B64::decode(in));
}