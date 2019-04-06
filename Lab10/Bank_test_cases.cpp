#include "catch.hpp"
#include "Bank.h"

TEST_CASE("Testing non-random CustomerGenerator implementation") {
	SECTION("Testing .......") {
		BankTest test;
		test.simulate();
		REQUIRE(test.totalCustom() == 3);
		REQUIRE(test.endTime() == 12);
		REQUIRE(test.maxWaiting() == 6);
		REQUIRE(test.maxLine() == 1);
	}
}