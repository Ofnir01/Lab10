#include "Bank.h"
#include <queue>
#include <random>
#include <ctime>
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
	maxQueue = 0;
	maxWait = 0;
	currCustomer = nullptr;
}

//Bank nextMinute definition.
void Bank::nextMinute() {
		//Increment the time that the bank has been open.
		timeOpen++;

		//If statement that checks if the bank is still open tu use nextMinute() of CustomerGenerator
		//to check for a possible new customer to add to the waiting line.
		if (timeOpen <= workDay) {
			if (custGenPtr->nextMinute() != nullptr) {
				line.push(custGenPtr->nextMinute());
				currCustomer = line.front();
				maxQueue++;
			}
		}

		//If statement that check if the line is not empty to decrement the amount of help
		//time for the customer, and the overall maxWait.
		if (!line.empty()) {
			currCustomer->waitTime--;
			timeOpen++;
			maxWait--;
		}
		
		//If statement that checks if there is not a current client being helped to pop the currendt one
		//(if necesarry) 
		if (!line.empty() && currCustomer->waitTime == 0) {
			line.pop();
			//maxWait -= ;
			maxQueue--;
		}
		
		//Always update maxQueue to the current number of line.
		maxQueue = line.size();
}

//Bank simultation definition.
void Bank::simulate() {
	do {
		line.push(custGenPtr->nextMinute());
		if (custGenPtr->nextMinute() != nullptr) {
			maxQueue++;
			maxWait += custGenPtr->nextMinute()->waitTime;
		}
		timeOpen++;
	} while (timeOpen <= workDay || maxQueue != 0);
}


//***************************************
//CustomerGenerator class definition.	*
//***************************************
//CustomerGenerator nextMinute definition.
Customer* CustomerGenerator::nextMinute() {
	static Customer* newCust;
	static int min_to_new_gen = randInt1To4();
	min_to_new_gen--;
	if (min_to_new_gen == 0) {
		//Set total time for that customer to be helped.
		newCust->waitTime = randInt1To4();
		min_to_new_gen = randInt1To4();
		return newCust;
	}
	else
		return nullptr;
}