#pragma once
#ifndef CashBalance_h
#define CashBalance_h

class Account {
public:
	void deletefile();
	double setCashBalance(double);//set cash balance
	double getCashBalance() const;//get balance
	double addCashBalance(double);//update cash balance

private:
	double balance;
};

#endif