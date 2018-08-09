#pragma once
#ifndef BankAccount_h
#define BankAccount_h
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Account_QikeYing.h"
using namespace std;

class BankAccount :public Account{
public:
	BankAccount();
	void ViewBalance();	    // view account balance
	void deposit(double);	// deposit money
	void withdraw(double);	// withdraw money
	void printHistory();	// print out history
};

#endif