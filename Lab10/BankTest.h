#ifndef BANKTEST_H_
#define BANKTEST_H_
#include "Bank2.h"

class CustomerGeneratorTest : public CustomerGenerator {
public:
	Customer* nextMinute();
};

class BankTest : public Bank {
private:
	const int workDayTest = 10;
	CustomerGeneratorTest *custGenPtrTest;
public:
	void nextMinute();
	void simulate();
};

#endif