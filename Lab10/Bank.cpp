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
}

//Bank nextMinute definition.
void Bank::nextMinute() {
	do {
		timeOpen++;			//Increment the time that the bank has been open.

		//If statement that check if the line is not empty to decrement the amount of help
		//time for the customer, and the overall maxWait.
		if (!line.empty()) {
			do {
				line.front()->waitTime--;
				timeOpen++;
				maxWait--;
			} while (line.front()->waitTime >= 0);
			line.pop();
			maxQueue--;
		}
		
		//If statement that checks if the bank is still open tu use nextMinute() of CustomerGenerator
		//to check for a possible new customer to add to the waiting line.
		if (timeOpen <= workDay) {
			line.push(ptr->nextMinute()); //FIGURE OUT HOW TO SEND THE BANK REFERNECE TO THE FUNCTION.
			maxQueue++;
		}
		
		//Always update maxQueue to the current number of line.
		maxQueue = line.size();

		//FIGURE OUT HOW TO WORK STEP 5 OF THE LAB.
		if (!line.empty() && line.front()->waitTime == ) {
			;
		}

	} while (maxQueue == 0);
}

//Bank simultation definition.
void Bank::simulate() {
	do {
		line.push(ptr->nextMinute()); //FIGURE OUT HOW TO SEND THE BANK REFERNECE TO THE FUNCTION.
		if (ptr->nextMinute() != nullptr) {
			maxQueue++;
			maxWait += ptr->nextMinute()->waitTime;
		}
		timeOpen++;
	} while (timeOpen <= workDay);
}


//***************************************
//CustomerGenerator class definition.	*
//***************************************
//CustomerGenerator nextMinute definition.
Customer* CustomerGenerator::nextMinute(Bank& bank) {
	Customer* newCust;
	min_to_new_gen = randInt1To4();
	//Do something to decrement time

	do {
		min_to_new_gen--;
		bank.timeOpen++;
		if (min_to_new_gen == 0) {
			
			//Set arriving time for the customer.
			newCust->arriveTime = bank.timeOpen;

			//Set total time for that customer to be helped.
			newCust->waitTime = randInt1To4();

			return newCust;
		}

		else
			return nullptr;
	} while (min_to_new_gen >= 0);
}