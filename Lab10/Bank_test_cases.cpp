#include "catch.hpp"
#include "Bank.h"

TEST_CASE("Testing non-random CustomerGenerator implementation") {
	SECTION("Testing .......") {
		BankTest test;
		test.simulate();
		REQUIRE(test.totalCustom() == 6);
		REQUIRE(test.endTime() == 27);
		REQUIRE(test.maxWaiting() == 9);
		REQUIRE(test.maxLine() == 3);
	}
}