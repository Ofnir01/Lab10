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
	int arriveTime;		//Time (in minutes) since the bank opened.
	int waitTime;		//Time (in minutes) that the customer needs to be helped.
};

//*******************************************************************************************************************
//CustomerGenerator class. This class represents the stream of customers arriving at the front door of the bank.	*
//It will indicate the number of minutes remainding before another customer is generated.							*
//It will decrement the number of minutes left till the next customer.												*
//*******************************************************************************************************************
class CustomerGenerator {
private:
	static int min_to_new_gen;

public:
	//---------------------------------------------------------------------------------------
	//This function decrements the number of minutes left  till the next customer			-
	//---------------------------------------------------------------------------------------
	Customer* nextMinute(Bank&);
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
	int timeOpen;				//Number of minutes since the bank opened.
	int maxQueue;				//Number of the maximum queue length seen during the day.
	int maxWait;				//Number of the maximum waiting time.
	queue<Customer*> line;		//Queue that indicates the line of customers waiting.
	CustomerGenerator* ptr;		//Reference to a CustomerGenerator object.

public:
	//Default constructor.
	Bank();
	
	//---------------------------------------------------------------------------------------
	//nextMinute function. This function will update the followig info:						-
	//Will increment the number of minutes since opening. If there is a customer being		-
	//helped, decrement the amount of help time still required for that customer; if the	-
	//customer has no more minutes required, the customer leaves. If the bank is still open	-
	//use nextMinute() of CustomerGenerator to check for a possible new customer to add		-
	//to the waiting list. Note the current length of the line and check if the maximum		-
	//should be updated. If there are customers in line and no customers being helped,		-
	//begin helping the first customer in line and pop him from the waiting line.			-
	//---------------------------------------------------------------------------------------
	void nextMinute();

	//---------------------------------------------------------------------------------------
	//simulate function. This function should simulate a day at the bank by calling			-
	//nextMinute() for each minute of the work day and then continuing to call it until		-
	//everyone at line in the bank has been helped.											-
	//---------------------------------------------------------------------------------------
	void simulate();

	//Define CustomerGerenator as a frind to have acces to the private member variables.
	friend Customer* CustomerGenerator::nextMinute(Bank&);
};

#endif