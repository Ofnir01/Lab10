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
	currQueue = 0;
	currWait = 0;
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
			currWait += newCustomer->helpTime;
			currCustomer = line.front();
			currQueue++;
			totalCust++;
			if (line.size() > maxQueue)
				maxQueue = line.size() - 1;
				
			if (currWait > maxWait)
				maxWait = currWait;

			cout << "New customer arrived at minute: " << currTime << endl;
			cout << "Current wait time in line: " << currWait << endl;
			cout << "Current number of customers in the line: " << currQueue - 1 << endl << endl;
				
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
		currQueue--;
		cout << "Customer left at minute: " << currTime << endl;
		cout << "Current wait time in line: " << currWait << endl ;
		cout << "Current number of customers in the line: " << currQueue << endl << endl;
	}
	
	//Check if maxWait neeeds to be updated and then decrement the amount of currWait.
	
	//Always update maxQueue to the current number of line.
	currQueue = line.size();
	
	if (currWait >= 1)
		currWait--;
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
//CustomerGenerator class definition.	*
//***************************************
//CustomerGenerator nextMinute definition.
Customer* CustomerGenerator::nextMinute() {
	static Customer* newCust;
	newCust = new Customer;
	static int min_to_new_gen = 1; //randInt1To4();
	
	if (min_to_new_gen-- == 0) {
		//Set total time for that customer to be helped.
		newCust->helpTime = 8;//randInt1To4();
		min_to_new_gen = 1; //randInt1To4();
		return newCust;
	}
	else
		return nullptr;
}