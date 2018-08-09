#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<time.h>  
#include<fstream>  
#include<string>
#include<stdlib.h>
#include<vector>
#include<sstream>

#include "BankAccount_QikeYing.h"

using namespace std;

//constructor
BankAccount::BankAccount()
{
	//empty body
}

//view bank account balance
void BankAccount::ViewBalance() 
{
	cout << "You have: $" << getCashBalance() << " in your bank account." << endl;
}

//deposit money
void BankAccount::deposit(double money)
{
	addCashBalance(money);//change the cash balance first
	double balance = getCashBalance();
	// add to history
	ofstream ofile;
	ofile.open("bank_transaction_history.txt",ios::app);
	if (ofile.is_open())
	{
		// get local time
		struct tm *local;
		time_t t = time(0);
		local = localtime(&t);
		ofile << "Deposit" << "      $" << money << "     " << local->tm_mon << "/" << local->tm_mday << "/" << local->tm_year << "      $" << balance << "\n";
	}
	else
		cout << "Unable to open bank_transaction_history.txt" << endl;
}

//withdraw money
void BankAccount::withdraw(double money)
{
	//if money is not enough,reaturn false
	if (money>getCashBalance())
		cout << "Error: the balance of the account is not sufficient to withdraw." << endl;
	else
	{
		addCashBalance(-money);//update cash balance
		double balance = getCashBalance();
		// add to history
		ofstream ofile;
		ofile.open("bank_transaction_history.txt",ios::app);
		if (ofile.is_open())
		{
			// get local time
			struct tm *local;
			time_t t = time(0);
			local = localtime(&t);

			ofile << "Withdraw" << "    $" << money << "     " << local->tm_mon << "/" << local->tm_mday << "/" << local->tm_year << "      $"<<balance<<"\n";
		}
		else
			cout << "Unable to open bank_transaction_history.txt" << endl;
	}
}

//open file to print history function
void BankAccount::printHistory()
{
	ifstream infile;
	infile.open("bank_transaction_history.txt",ios::out);
	if (infile.is_open())
	{
		cout << "Event" << "     " << "Amount" << "    " << "Date" << "                "<<"Balance"<<endl;
		string line;
		while (!infile.eof())
		{
			while (getline(infile, line))
				cout << line << endl;		
		}
	}
	else
		cout << "Unable to print out history." << endl;
}

