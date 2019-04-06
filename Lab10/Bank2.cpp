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

//Constructor.
Bank::Bank() {
	currTime = 0;
	currLine = 0;
	currWait = 0;
	maxQueue = 0;
	totalCust = 0;
	currCustomer = nullptr;
}

//Bank nextMinute definition.
void Bank::nextMinute() {
	//If statement that will increment the time even if the bank is already closed but there
	//are still sutomers inside.
	if (currTime <= workDay || !line.empty())
		currTime++;

	//If statement tha will check id the bank is still open to check if there is a new customer at the door.
	if (currTime <= workDay) {
		newCustomer = custGenPtr->nextMinute(); //Info stored on this pointer for not calling custGenPtr->nextMinute() multiple times due to the random factor

		//If statement that will check if the new generated customer is not equal to null ptr.
		if (newCustomer != nullptr) {
			totalCust++;							//Becuase the new customer was not null ptr, we increment the total amount of customers that the bank has received during the day.
			line.push(newCustomer);					//store the new customer in the queue
			newCustomer->arriveTime = currTime;		//Set the arrival time for that customer to be equal to the current time.
			currCustomer = line.front();			//Set the front customer of the queue to be the current customer to be helped.
			
			//Because que in this simulation is people waiting on the line not counting the one being helped
			//we check if the curennt customer is not equal to line.front() increment or not the line counter.
			if (!line.empty())
				currLine = line.size() - 1;

			//Now we procede to report in real time that a customer just arrived to the bank right now.
			cout << "New customer arrived at minute: " << newCustomer->arriveTime << endl;
			
			//We reoprt what is the total wait time at that moment (also counting the amount of time needed by the new arrived one).
			//COMMENTED OUT BECAUSE IS STILL NOT IMPLEMENTED
			//cout << "Current wait time in the line: " << currWait << endl;

			//We report how many people are in the line when this customer arrived (also counting the new arrived one).
			cout << "Current number of customers in the line: " << currLine << endl << endl;
		}
	}

	//If statement that will check if the customer being helped is already done, and it will
	//pop him out of the list if his help time is already zero. This is done before decrementing the wait time
	//so we can ensure that we will not get a negative wait time. If the condition is true, we eill pop that customer.
	if (currCustomer->helpTime == 0) {
		//pop the customer that already was done being helped.
		line.pop();

		//Becuase a customer was popped in this step, we need to update the current customer to the next line.front()
		currCustomer = line.front();

		//Now that we popped out a customer, we procede to report that the custumer left
		cout << "Customer left at minute: " << currTime << endl;


		//currQueue--; QUEUE SHALL NOT BE DECREMENTED, BECUASE THIS CUSTOMER WAS BEING HELPED AND WAS NOT PART OF THE LINE.
	}

	//If statement that will check if someone is being helped to decrement his help time.
	if (currCustomer != nullptr)
		//Becuase the customer arrived to the front desk at the exact start of the minute, by the end of this itereation
		//the customer would have spend one entire minute being helped, so we decrement the his wait time.
		currCustomer->helpTime--;
}

//Bank simultation definition.
void Bank::simulate() {
	do {
		nextMinute();
	} while (currTime <= workDay || !line.empty());

	//When the bank is already closed and all the customers have left, we procede to show our final results.
	/* STILL UNDER CUNSTRUCTION.
	cout << "The total number of customers during the day was: " << totalCust << " customers." << endl;
	cout << "The maximum wait time for the line during the day was: " << maxWait << " minutes." << endl;
	cout << "The maximum line length during the day was: " << maxQueue << " customers in line" << endl;
	*/
}