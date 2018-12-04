#include "catch.hpp"
#include "encoder.h"

TEST_CASE("Decode simple alligned string","[Decode]")
{
	std::string in = "TWFu";
	std::string res = "Man";
	REQUIRE(res == B64::decode(in));
}