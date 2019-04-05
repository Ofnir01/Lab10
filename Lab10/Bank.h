#ifndef BANK_H_
#define BANK_H_

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
public:
	Bank();
	~Bank();
};

#endif