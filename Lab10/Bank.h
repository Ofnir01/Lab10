#ifndef BANK_H_
#define BANK_H_
#include <queue>
using std::queue;
//*******************************************************************************************************************
//Customer structure. This structure will keep track of the following:												*
//Record the time when the customer arrived in line [as an integer number of minutes from the time bank opened]		*
//Keep track of how many more minutes of help that customer will require.											*
//*******************************************************************************************************************
struct Customer {
	int timeRecord;
	int waitTime;
};

//*******************************************************************************************************************
//CustomerGenerator class. This class represents the stream of customers arriving at the front door of the bank.	*
//It will indicate the number of minutes remainding before another customer is generated.							*
//It will decrement the number of minutes left till the next customer.												*
//*******************************************************************************************************************
class CustomerGenerator {
private:
	int min_to_new_gen;

public:
	//---------------------------------------------------------------------------------------
	//This function decrements the number of minutes left  till the next customer			-
	//---------------------------------------------------------------------------------------
	void nextMinute();
};

//******************************************************************************************************************
//Bank class. This class will simulate the bank itself. It will have a constant length of a work day. It will		*
//keep record of the number of minutes since the bank opened. It will have a pointer to the Current customer being	*
//helped. It will keep track of the line of customers waiting to be helped, a reference to a CustomerGenerator		*
//object, an integer tracking the maximum queue length seen during the day, and an integer traking the maximum		*
//wait time.																										*
//*******************************************************************************************************************
class Bank
{
private:
	const int workDay = 480;	//Number of minutes open.
	int timePast;				//Number of minutes since the bank opened.
	int maxQueue;				//Number of the maximum queue length seen during the day.
	int maxWait;				//Number of the maximum waiting time.
	queue<Customer*> line;		//Queue that indicates the line of customers waiting.

public:
	Bank();
	~Bank();
};

#endif