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
//CustomerGenerator class definition.	*
//***************************************

//CustomerGenerator nextMinute definition.
void CustomerGenerator::nextMinute() {
	min_to_new_gen = randInt1To4();
}

//***************************************
//Bank class definition.				*
//***************************************

//Bank nextMinute definition.
void Bank::nextMinute() {

}

//Bank simultation definition.
void Bank::simulate() {

}


