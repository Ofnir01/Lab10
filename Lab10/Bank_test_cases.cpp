#include "catch.hpp"
#include "BankTest.h"

TEST_CASE("Testing non-random CustomerGenerator implementation") {
	SECTION("Testing .......") {
		BankTest test;
		test.simulate();
		REQUIRE(test.totalCustom() == 3);
		REQUIRE(test.endTime() == 21);
		REQUIRE(test.maxWaiting() == 12);
		REQUIRE(test.maxDayLine() == 2);
	}
}