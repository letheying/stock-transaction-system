#include <iostream>
#include <fstream>
#include <sstream>
#include "Account_QikeYing.h"
using namespace std;

double Account::setCashBalance(double balance) 
{
	ofstream myfile;
	myfile.open("Cash_Balance.txt");
	if (myfile.is_open()) {
		while (myfile << balance) {
			return balance;
		}
	}
	myfile.close();
	return 0;
}

//get cash balance from txt file
double Account::getCashBalance() const
{
	double balance;
	ifstream myfile;
	myfile.open("Cash_Balance.txt");
	if (myfile.is_open()) {
		while (myfile >> balance) {
			return balance;
		}
	}
	myfile.close();
	return 0;
}


//write in cash balance
double Account::addCashBalance(double cash)
{
	balance=getCashBalance();
	balance += cash;
	ofstream myfile;
	myfile.open("Cash_Balance.txt");
	if (myfile.is_open())
	{
		myfile << balance;
	}
	myfile.close();
	return 0;
}

void Account::deletefile()
{
	ofstream file1;
	file1.open("Cash_Balance.txt",ios::trunc);
	file1.close();

	ofstream file2;
	file2.open("bank_transaction_history.txt", ios::trunc);
	file2.close();

	ofstream file3;
	file3.open("stock_transaction_history.txt", ios::trunc);
	file3.close();

	ofstream file4;
	file4.open("current_portfolio.txt", ios::trunc);
	file4.close();
}