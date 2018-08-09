#include <iostream>
#include "Account_QikeYing.h"
#include "StockAccount_QikeYing.h"
#include "BankAccount_QikeYing.h"

using namespace std;

int main() {
    
	int menu = 0;//level 1 menu choice
	int choice=0;//level 2 menu choice
	string symbol;//stock name
	int sharenum;//number of stock to buy/sell
	double max;//max money per stock to buy
	double min;//min money per stock to sell
	double money;//money to deposite and withdraw

	double balance;

	BankAccount bank;
	StockAccount stock;

	while (1) 
	{
	FirstMenu:
		cout<< "Welcome to the Account Management System. Please select an account to access:" << endl
			<< "1. Stock Portfolio Account" << endl
			<< "2. Bank Account" << endl
			<< "3. Exit" << endl
			<< "Option:";
		    cin >> menu;
		    switch (menu) {
		    case 1:
		    {
		    	while (1) {
		    		cout << "\nMENU\n";
		    		cout << "1.  Display price for stock\n";
		    		cout << "2.  Display current portfolio\n";
		    		cout << "3.  Buy Shares\n";
		    		cout << "4.  Sell Shares\n";
		    		cout << "5.  View Portfolio History in Graph\n"; // MATLAB
		    		cout << "6.  View Transaction History\n";
		    		cout << "7.  Return to previous Menu\n";
		    		cout << "Please Enter your choice:";
		    		cin >> choice;
		    		switch (choice) {
		    		case 1:
		    			cout << "Please enter a stock symbol:";
		    			cin >> symbol;
		    			stock.displayPrice(symbol);
		    			break;
		    
		    		case 2:
						stock.sortlist();
		    			stock.displayCurrentPortfolio();
		    			break;
		    
		    		case 3:
		    			cout << "Please enter the stock symbol you wish to purchase: ";
		    			cin >> symbol;
		    			cout << "Please enter the number of shares: ";
		    			cin >> sharenum;
		    			cout << "Please enter the maximum price you are willing to pay per share: ";
		    			cin >> max;
		    			stock.buyShare(symbol,sharenum, max);
		    			break;
		    
		    		case 4:
		    			cout << "Please enter the stock symbol you wish to sell: ";
		    			cin >> symbol;
		    			cout << "Please enter the number of shares: ";
		    			cin >> sharenum;
		    			cout << "Please enter the minimun price you are willing to pay per share: " << endl;
		    			cin >> min;
		    			stock.sellShare(symbol, sharenum, min);
		    			break;
					case 5:
						stock.viewgraph();
						break;
		    		case 6:
		    			stock.viewHistory();
		    			break;
		    
		    		case 7:
		    			goto FirstMenu;
		    
		    		default:
		    			cout << "Invalid input." << endl;
		    			break;
		    		}
		    	}
		    }
		    
		    case 2:
		    {
		    	while (1) {
		    		cout << "\nMENU\n";
		    		cout << "1.  View Account Balance\n";
		    		cout << "2.  Deposit Money\n";
		    		cout << "3.  Withdraw Money\n";
		    		cout << "4.  print out history\n";
		    		cout << "5.  Return to previous menu\n";
					cout << "6.  set cash balance,delete all the history\n";
		    		cout << "Please Enter your choice\n ";
		    		cin >> choice;
		    		switch (choice) {
		    
		    		case 1:
		    			bank.ViewBalance();
		    			break;
		    		case 2:
		    			cout << "Please enter the amount you wish to deposit: ";
		    			cin >> money;
						bank.deposit(money);
		    			break;
		    		case 3:
		    			cout << "Please enter the amount you wish to withdraw: ";
		    			cin >> money;
		    			bank.withdraw(money);
		    			break;
		    		case 4:
		    			bank.printHistory();
		    			break;
		    
		    		case 5:
		    			goto FirstMenu;

					case 6:
						bank.deletefile();
						cout << "initialized cash balance,and delete the history" << endl;
						cin >> balance;
						bank.setCashBalance(balance);
		    		}
		    	}
		    case 3:
				stock.savecurrentport();
		    	exit(0);
		    }
	   }
  }
return 0;
}
