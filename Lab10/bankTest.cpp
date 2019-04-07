#include "BankTest.h"
#include <queue>
#include <random>
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
using std::queue;

void BankTest::nextMinute() {
	//If statement that will increment the time even if the bank is already closed but there
	//are still sutomers inside.
	if (currTime <= workDayTest || !line.empty())
		currTime++;

	//Print current time
	cout << "****************" << endl;
	cout << "   Time: " << currTime << endl;
	cout << "****************" << endl;

	//Display a message that signals when the bank closes.
	if (currTime == workDayTest)
		cout << "------------------------------ BANK CLOSES ------------------------------" << endl;

	//If statement tha will check id the bank is still open to check if there is a new customer at the door.
	if (currTime < workDayTest) {
		newCustomer = custGenPtrTest->nextMinute(); //Info stored on this pointer for not calling custGenPtr->nextMinute() multiple times due to the random factor

		//If statement that will check if the new generated customer is not equal to null ptr.
		if (newCustomer != nullptr) {
			totalCust++;							//Becuase the new customer was not null ptr, we increment the total amount of customers that the bank has received during the day.
			line.push(newCustomer);					//store the new customer in the queue
			waitTime += newCustomer->helpTime;		//Add to wait time the amount of help time that the customer needs.
			newCustomer->arriveTime = currTime;		//Set the arrival time for that customer to be equal to the current time.
			currCustomer = line.front();			//Set the front customer of the queue to be the current customer to be helped.

			//Because que in this simulation is people waiting on the line not counting the one being helped
			//we check if the curennt customer is not equal to line.front() increment or not the line counter.
			if (!line.empty())
				waitLine = line.size() - 1;

			//Now we procede to report in real time that a customer just arrived to the bank right now.
			cout << "New customer arrived at minute: " << newCustomer->arriveTime << endl;

			//Display the help time of the customer.
			cout << "Help time needed for this customer: " << newCustomer->helpTime << endl;
		}
	}

	//Display message if bank is empty.
	if (line.empty())
		cout << "Bank is empty." << endl;
	

	//Check if maxLine or maxWait need to be updated. This happens at the very start of the minute.
	if (waitTime > maxWait)
		maxWait = waitTime;

	if (waitLine > maxLine)
		maxLine = waitLine;

	//If statement that will check if the customer being helped is already done, and it will
	//pop him out of the list if his help time is already zero. This is done before decrementing the wait time
	//so we can ensure that we will not get a negative wait time. If the condition is true, we eill pop that customer.
	if (currCustomer != nullptr && currCustomer->helpTime == 0) {
		//pop the customer that already was done being helped.
		line.pop();
		//Now that we popped out a customer, we procede to report that the custumer left
		cout << "Customer left at minute: " << currTime << endl;

		currCustomer = nullptr;

		//Becuase a customer was popped in this step, we need to update the current customer to the next line.front() as long as the line is not empty.
		//Becuase a customer was popped in this step, we update the length of the current waiting line.
		if (!line.empty()) {
			waitLine = line.size() - 1;
			currCustomer = line.front();
			cout << "Customer is being helped." << endl;
		}
	}

	//Report the total amount of wait time and wait line at the start of the current minute.
	cout << "Current wait time minutes at the start of minute " << currTime << ": " << waitTime << endl;
	cout << "Current number of customers in the waiting line after " << currTime << " minutes: " << waitLine << endl << endl;

	//If statement that will check if someone is being helped to decrement his help time.
	if (currCustomer != nullptr) {
		//Becuase the customer arrived to the front desk at the exact start of the minute, by the end of this itereation
		//the customer would have spend one entire minute being helped, so we decrement the his wait time.
		currCustomer->helpTime--;

		//Beacuse we helped a customer here. We decrement by one the amount of waitTime in the queue.
		waitTime--;
	}
}


void BankTest::simulate() {
	do {
		nextMinute();
	} while (currTime < workDayTest || !line.empty());

	//When the bank is already closed and all the customers have left, we procede to show our final results.
	cout << "The total number of customers during the day was: " << totalCust << " customers." << endl;
	cout << "The maximum wait time for the line during the day was: " << maxWait << " minutes." << endl;
	cout << "The maximum line length during the day was: " << maxLine << " customers in line" << endl;
}

//***************************************
//CustomerGenerator class definition.	*
//***************************************
//CustomerGenerator nextMinute definition.
Customer* CustomerGeneratorTest::nextMinute() {

	static Customer* newCust;
	static int min_to_new_gen = 2;

	if (min_to_new_gen-- == 0) {
		newCust = new Customer;
		//Set total time for that customer to be helped.
		newCust->helpTime = 6;
		min_to_new_gen = 2;
		return newCust;
	}
	else
		return nullptr;
}
