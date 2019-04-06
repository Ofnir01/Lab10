#include "Bank.h"
#include <queue>
#include <random>
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
using std::queue;

//***********************************************************
// Returns an integer 1, 2, 3, or 4 uniformly at random		*
//***********************************************************
int randInt1To4() {
	// shared random number generator (seeded with clock time)
	static std::default_random_engine randEngine(std::time(0));
	
	// shared uniform distribution
	static std::uniform_int_distribution<int> dist1To4(1, 4);
	
	// return a sample
	return dist1To4(randEngine);
}



//***************************************
//Bank class definition.				*
//***************************************
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Constructor.
Bank::Bank() {
	currTime = 0;
	waitLine = 0;
	waitTime = 0;
	maxQueue = 0;
	totalCust = 0;
	currCustomer = nullptr;
}

//Bank nextMinute definition.
void Bank::nextMinute() {
	//Increment the time that the bank has been open.
	if(currTime <= workDay || !line.empty())
		currTime++;

	//If statement that checks if the bank is still open tu use nextMinute() of CustomerGenerator
	//to check for a possible new customer to add to the waiting line.
	if (currTime <= workDay) {
		newCustomer = custGenPtr->nextMinute();
			
		if (newCustomer != nullptr) {
			line.push(newCustomer);
			waitTime += newCustomer->helpTime;
			newCustomer->arriveTime = currTime;
			currCustomer = line.front();

			if (newCustomer != line.front())
				waitLine++;
			
			totalCust++;

			if (line.size() > maxQueue)
				maxQueue = line.size() - 1;
				
			if (waitTime > maxWait)
				maxWait = waitTime;

			cout << "New customer arrived at minute: " << currCustomer->arriveTime << endl;
			cout << "Current wait time in line: " << waitTime << endl;
			cout << "Current number of customers in the line: " << waitLine << endl << endl;
				
		}
	}

	//If statement that check if someone is being helped to decrement the amount of help
	//time for the customer.
	if (currCustomer != nullptr) {
		currCustomer->helpTime--;
		
	}
		
	//If statement that checks if there is not a current client being helped to pop the currendt one
	//(if necesarry) 
	if (!line.empty() && currCustomer->helpTime <= 0) {
		line.pop();
		waitLine--;
		cout << "Customer left at minute: " << currTime << endl;
		cout << "Current wait time in line: " << waitTime << endl ;
		cout << "Current number of customers in the line: " << waitLine << endl << endl;
	}
	
	//Check if maxWait neeeds to be updated and then decrement the amount of currWait.
	
	//Always update maxQueue to the current number of line.
	waitLine = line.size() - 1;
	
	if (waitTime >= 1)
		waitTime--;
}

//Bank simultation definition.
void Bank::simulate() {
	do {
		nextMinute();
	} while (currTime <= workDay || !line.empty());

	cout << "The total number of customers during the day was: " << totalCust << " customers."<< endl;
	cout << "The maximum wait time for the line during the day was: " << maxWait << " minutes." << endl;
	cout << "The maximum line length during the day was: " << maxQueue << " customers in line" << endl;
}


//***************************************
//BankTest class definition.			*
//***************************************
void BankTest::nextMinute() {
	//Increment the time that the bank has been open.
	if (currTime <= workDayTest || !line.empty())	
		currTime++;

	//If statement that checks if the bank is still open tu use nextMinute() of CustomerGenerator
	//to check for a possible new customer to add to the waiting line.
	if (currTime <= workDayTest) {
		newCustomer = custGenTestPtr->nextMinute();

		if (newCustomer != nullptr) {
			line.push(newCustomer);
			newCustomer->arriveTime = currTime;
			waitTime += newCustomer->helpTime;
			currCustomer = line.front();

			if (newCustomer != line.front())
				waitLine++;
			
			totalCust++;
			if (line.size() - 1 > maxQueue)
				maxQueue = line.size() - 1;

			if (waitTime > maxWait)
				maxWait = waitTime;

			cout << "New customer arrived at minute: " << currTime << endl;
			cout << "Current wait time in line: " << waitTime << endl;
			cout << "Current number of customers in the line: " << waitLine << endl << endl;

		}
	}

	//If statement that check if someone is being helped to decrement the amount of help
	//time for the customer.
	if (currCustomer != nullptr) {
		currCustomer->helpTime--;
	}

	//If statement that checks if there is not a current client being helped to pop the currendt one
	//(if necesarry) 
	if (!line.empty() && currCustomer->helpTime <= 0) {
		line.pop();
		
		waitLine--;
		
		cout << "Customer left at minute: " << currTime << endl;
		cout << "Current number of customers in the line: " << waitLine << endl;

		waitLine = line.size() - 1;
	}

	if (waitTime >= 1)
		waitTime--;
	cout << "Current wait time in line: " << waitTime << endl << endl;
}

//Banktest simulation definition	*
void BankTest::simulate() {
	do {
		nextMinute();
	} while (currTime <= workDayTest || !line.empty());
}


//***************************************
//CustomerGenerator class definition.	*
//***************************************
//CustomerGenerator nextMinute definition.
Customer* CustomerGenerator::nextMinute() {
	static Customer* newCust;
	newCust = new Customer;
	static int min_to_new_gen = randInt1To4();
	
	if (min_to_new_gen-- == 0) {
		//Set total time for that customer to be helped.
		newCust->helpTime = randInt1To4();
		min_to_new_gen = randInt1To4();
		return newCust;
	}
	else
		return nullptr;
}

//*******************************************
//CustomerGeneratorTest class definition.	*
//*******************************************
Customer* CustomerGeneratorTest::nextMinute() {
	static Customer* newCust;
	newCust = new Customer;
	static int min_to_new_gen = 2;

	if (min_to_new_gen-- == 0) {
		//Set total time for that customer to be helped.
		newCust->helpTime = 4;
		min_to_new_gen = 2;
		return newCust;
	}
	else
		return nullptr;
}
