#include "catch.hpp"
#include "encoder.h"

namespace CatchTestset01
{
	TEST_CASE("Test encoding for simple alligned string", "[Encode]")
	{
		REQUIRE(B64::encode(std::string("Man")) == std::string("TWFu"));
	}
	TEST_CASE("Test encoding for simple unalligned string", "[Encode]")
	{
		REQUIRE(B64::encode(std::string("Ma")) == std::string("TWE="));
		REQUIRE(B64::encode(std::string("M")) == std::string("TQ=="));
	}
	TEST_CASE("Test encoding for long string", "[Encode]")
	{
		std::string lon = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
		std::string res = "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmltYWxzLCB3aGljaCBpcyBhIGx1c3Qgb2Yg"
			"dGhlIG1pbmQsIHRoYXQgYnkgYSBwZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBpbmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRzIHRo"
			"ZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=";
		REQUIRE(B64::encode(lon) == res);
	}
}