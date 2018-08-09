#pragma once
#ifndef StockAccount_h
#define StockAccount_h
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Account_QikeYing.h"

using namespace std;

//doubly linked node class
class Node {
	friend class StockAccount;
public:
	Node(string &, int, double);//string symbol,int sharenum,double price
private:
	string symbol;	// stock name
	int sharenum;	//shares to buy/sell
	double price;   //buy/sell price
	double totalValue;  //total money to pay/get
	Node *prev;
	Node *next;
};

//doubly linked list
class StockAccount :public Account{
public:
	StockAccount();
	double getTotalValue(Node *) const;// get the total value already buy  
	double getTotalPortfolioValue() const; //get the total value of poryfolio to buy
	void displayPrice(string &);//diplay total money
	void displayCurrentPortfolio();//display current portfolio
	double findPrice(string &);//find the price of stock randomly in result file
	//actions function
	void buyShare(string &, int, double);//buy shares
	void sellShare(string &, int, double);//sell shares
	void insert(string &, int, double);//insert node
	void remove(Node *);//remove node
	void viewHistory();//view history
	bool isEmpty() const;
	//bubble sort
	void sortlist();
    //matlab
	void viewgraph();
	void savecurrentport();
private:
	double totalPortfolioValue;
	Node *head;
	Node *tail;
	int mySize;
};
#endif 