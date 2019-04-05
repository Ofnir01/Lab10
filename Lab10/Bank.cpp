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

//Constructor.
Bank::Bank() {
	timeOpen = 0;
	maxQueue = 0;
	maxWait = 0;
}

//Bank nextMinute definition.
void Bank::nextMinute() {

}

//Bank simultation definition.
void Bank::simulate() {

}

//***************************************
//CustomerGenerator class definition.	*
//***************************************

//CustomerGenerator nextMinute definition.
Customer CustomerGenerator::nextMinute() {
	Customer* newCust;
	min_to_new_gen = randInt1To4();
	//Do something to decrement time

	while (min_to_new_gen >= 0) {
		min_to_new_gen--;
		//timePast++;		//DO SOMTHING TO ESTABLISH A FRIEND RELATIONSHIP.
	}

	if (min_to_new_gen == 0) {
		newCust = new Customer;
	}

	//DO SOMTHING TO ESTSBLIDH A FRIEND RELATIONSHIP.
	//Set arriving time for the customer.
	newCust->arriveTime = timeOpen;

	//Set waiting time for that customer.
	newCust->waitTime = maxWait;

	return *newCust; //CHECK CORRECTNES OF THIS STATEMENT.
}