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

	//This function will return the total amount of customers that the bank received during the day.
	int totalCustom() const { 
		return totalCust; 
	}

	//THis function will return the total amount of minutes until the last customer left.
	int endTime() const {
		return currTime;
	}

	//This function will return the maximum wait time registered during the day.
	int maxWaiting() const {
		return maxWait;
	}

	//This function will return the maximum wait line registered during the day.
	int maxDayLine() const {
		return maxLine;
	}
};

#endif