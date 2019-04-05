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
	timeOpen = 0;
	currQueue = 0;
	maxWait = 0;
	maxQueue = 0;
	currCustomer = nullptr;
}

//Bank nextMinute definition.
void Bank::nextMinute() {
		//Increment the time that the bank has been open.
		timeOpen++;

		//If statement that checks if the bank is still open tu use nextMinute() of CustomerGenerator
		//to check for a possible new customer to add to the waiting line.
		if (timeOpen <= workDay) {
			newCustomer = custGenPtr->nextMinute();
			if (newCustomer != nullptr) {
				line.push(newCustomer);
				currCustomer = line.front();
				currQueue++;
				if (line.size() > maxQueue) {
					maxQueue = line.size();
				}
			}
		}

		//If statement that check if someone is being helped to decrement the amount of help
		//time for the customer.
		if (currCustomer != nullptr) {
			currCustomer->helpTime--;
		}
		
		//If statement that checks if there is not a current client being helped to pop the currendt one
		//(if necesarry) 
		if (!line.empty() && currCustomer->helpTime == 0) {
			line.pop();
			currQueue--;
		}
		
		//Decrement the amount of currWait.
		if (currWait >= 1)
			currWait--;

		//Always update maxQueue to the current number of line and check if maxQueue needs to be updated.
		currQueue = line.size();
		if (line.size() > maxQueue) {
			maxQueue = line.size();
		}
}

//Bank simultation definition.
void Bank::simulate() {
	do {
		nextMinute();
		cout << "Number of customers in line after " << timeOpen << " minutes open: " << currQueue << endl;
		cout << "Current maximum wait time for the last customer in the line: " << maxWait << endl << endl;
	} while (timeOpen <= workDay || currQueue <= 0);

	//cout << "";
}


//***************************************
//CustomerGenerator class definition.	*
//***************************************
//CustomerGenerator nextMinute definition.
Customer* CustomerGenerator::nextMinute() {
	static Customer* newCust;
	newCust = new Customer;
	static int min_to_new_gen = randInt1To4();
	//min_to_new_gen--;
	if (min_to_new_gen-- == 0) {
		//Set total time for that customer to be helped.
		newCust->helpTime = randInt1To4();
		min_to_new_gen = randInt1To4();
		return newCust;
	}
	else
		return nullptr;
}