//#define _CRT_SECURE_NO_WARNINGS
#include "StockAccount_QikeYing.h"
#include "Account_QikeYing.h"
#include <string>
//#pragma comment( lib, "libmx.lib")
//#pragma comment( lib, "libmex.lib")
//#pragma comment( lib, "libeng.lib")
//#include <yvals.h>
//#if (_MSC_VER >= 1600)
//#define __STDC_UTF_16__
//#endif
//#include "mex.h"
//#include <engine.h>

using namespace std;

//constructor
//create a Node for a stock
//the data info is totalValue to store the value of stocks that already buy
Node::Node(string &symbol, int n, double price)
	:symbol(symbol), sharenum(n), price(price)
{
	this->next = NULL;
	this->prev = NULL;
	totalValue = price*sharenum;//data info
}

//constructor
//create the linked list of stocks
//add a size for sort convenience
StockAccount::StockAccount()
{
	Node *head = NULL;
	Node *tail = NULL;
	int mySize = 0;
}

//return the total value of stocks already buy to the data info
double StockAccount::getTotalValue(Node *stock) const
{
	return stock->totalValue;
}

//calculate the total value of stocks already buy
double StockAccount::getTotalPortfolioValue() const
{
	double total = 0.0;
	Node *current = head;
	while (current != NULL)//travesal the linked list
	{
		total += current->totalValue;
		current = current->next;//move to the next node
	}
	return total;
}

// Return the price of the stock
// if the stock is not found, return -1.0
double StockAccount::findPrice(string &symbol)
{
	string line;
	//choose one file to open randomly
	srand(time(0));
	int flag = rand() % 2 + 1;//the flag could only be 1 or 2
	ifstream infile;//make file could write in
	if (flag == 1)
		infile.open("Result1.txt");
	else if (flag == 2)
		infile.open("Result2.txt");
	if (infile.is_open())//open the file to write in
	{
		//get line into the file
		while (getline(infile, line)) {
			stringstream ss(line);//create a string line to store information
			double price;
			string a;
			if (ss >> a >> price) //read from each line
			{
				if (a == symbol && !infile.eof())//if the sybol could match,and it didn't get to the end of file
				{
					return price;
				}
			}
		}
	}
	else
		cout << "Unable to open file." << endl;
	return -1.0;	// stock symbol not found
}


//dispaly the price
//call the find price function then display it in order of symbol and price
void StockAccount::displayPrice(string &symbol)
{
	double price = findPrice(symbol);//get the price of stock
	if (price == -1.0)	//if the stock is not found
		cout << "The symbol cannot be found" << endl;
	else
	{
		cout << "Company Symbol " << "Price per share" << endl;
		cout << "      " << symbol << "       " << price << endl;
	}
}

void StockAccount::savecurrentport()
{
	Node* current = head;
	while (current != NULL)
	{
		double price = findPrice(current->symbol);
		double totalValue = price*(current->sharenum);
		ofstream myfile;
		myfile.open("current_portfolio.txt",ios::app);
		if (myfile.is_open())
		{
			myfile << current->symbol << setw(16) << current->sharenum << "  $" << price << setw(16) << "$" << totalValue << endl;

		}
		myfile.close();
		current = current->next;//move to the next node
	}
	
}
//display current portfolio already buy
//use the linked list function
void StockAccount::displayCurrentPortfolio()
{
	Node* current = head;
	//first cout the current cash balance
	cout << "Cash balance=$" << getCashBalance() << endl;
	//get the price randomly from two result.txt,and calculate it

	cout << "CompanySymbol " << "Number " << "PricePerShare " << "TotalValue" << endl;
	while (current != NULL)
	{
		double price = findPrice(current->symbol);
		double totalValue = price*(current->sharenum);
		cout << current->symbol << setw(16) << current->sharenum << "  $" << price << setw(16) << "$" << totalValue << endl;
		current = current->next;//move to the next node
	}
	cout << "Total portfolio value: $" << getTotalPortfolioValue() << endl;

}


// insert a new node for stock account
void StockAccount::insert(string &name, int n, double price)
{
	Node *newNode = new Node(name, n, price);
	if (mySize == 0)	//linked list is empty
	{
		//insert it as the first node
		head = newNode;
		tail = newNode;
	}
	else
	{
		//create a new node,insert it at the back
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
		tail->next = NULL;
	}
	mySize++;//record size
}


//buy shares
void StockAccount::buyShare(string &name, int n, double max)
{
	double price = findPrice(name);//get the price of symbol to buy
	if (price == -1.0)	// The symbol of stock is not found
		cout << "The stock is not available." << endl;
	else if (price>max)//if the price is lower than the mark price
		cout << "Transaction is failed, because the current price of the stock is higher than the maximum amount you are willing to pay." << endl;
	else
	{
		double total = price*n;
		if (total>getCashBalance())//if money is not enough
			cout << "Transaction is faied, because your stock purchase amount is more than your cash balance." << endl;
		else
		{
			addCashBalance(-total);//record the to the cash balance txt
								   //add new node to the linked list
			Node *current = head;
			//check if user already buy the portfolio
			while (current != NULL && current->symbol != name)
				current = current->next;
			// if the user already has that stock in the porfolio
			//add money to the total value and share num
			if (current != NULL)
			{
				current->sharenum += n;
				current->price = price;
				current->totalValue += total;
			}
			//otherwise use the insert function
			else
				insert(name, n, price);
			cout << "You have purchased " << n << " shares of " << name << " at $" << price << " each for a total of $" << total << endl;

			// add to history
			//open file to write in
			ofstream ofile;
			ofile.open("stock_transaction_history.txt", ios::app);
			if (ofile.is_open())
			{
				// get local time
				time_t t;
				struct tm * timeinfo;
				time(&t);
				timeinfo = localtime(&t);
				ofile << "Buy" << setw(11) << name << "     " << n << "       $" << price << "     $" << total << "   " << asctime(timeinfo);
				ofile.close();
			}
			else
				cout << "Unable to open stock_transaction_history.txt" << endl;
		}
	}
}

// remove node p from the list
void StockAccount::remove(Node *p)
{
	Node *temp = p;
	// delete the first item
	if (p == head)
	{
		p->next->prev = NULL;//set the next ptr's prev link to NULL
		head = p->next;//make the next to be the first
	}
	// delete the last item
	else if (p == tail)
	{
		p->prev->next = NULL;//set the prev ptr's next link to NULL
		tail = p->prev;//make the prev to be the last
	}
	//rule as doubly linked list
	else
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	delete temp;//release temp
	mySize--;//record size
}

//sell shares
void StockAccount::sellShare(string &name, int n, double min)
{
	double price = findPrice(name);//get the price of symbol to sell
								   //travesal  the linked list to find the symbol
	Node *current = head;
	while (current != NULL && current->symbol != name)
	{
		current = current->next;
	}
	//if the symbol's price is not found
	if (price == -1.0)
		cout << "The stock is not available." << endl;
	//if the stock name is not fount
	else if (current == NULL)
		cout << "The stock is not in your portfolio." << endl;
	//if sell num is more than user have
	else if (current->sharenum<n)
		cout << "Transaction is failed, because there is no sufficient shares in the portfolio to sell." << endl;
	//if the user sell it higher than the mark price
	else if (price<min)
		cout << "Transaction is failed, because the price of the stock is lower than the minimum amount you are willing to sell for." << endl;
	//judge whether the user sell the stock all
	else
	{
		double total = price*n;
		addCashBalance(total);//update the cash balance txt
		current->sharenum -= n;
		current->totalValue -= total;
		current->price = price;
		//if the user sell all of the stock 
		if (current->sharenum == 0)
			remove(current);
		cout << "You have sold " << n << " shares of " << name << " at $" << price << " each for a total of $" << total << endl;
		// add to history
		ofstream ofile;
		ofile.open("stock_transaction_history.txt", ios::app);
		if (ofile.is_open())
		{
			// get local time
			time_t t;
			struct tm * timeinfo;
			time(&t);
			timeinfo = localtime(&t);
			ofile << "Sell" << setw(11) << name << "     " << n << "       $" << price << "     $" << total << "   " << asctime(timeinfo);
			ofile.close();
		}
		else
			cout << "Unable to open stock_transaction_history.txt" << endl;
	}
}


//view history funxtion
void StockAccount::viewHistory()
{
	ifstream infile("stock_transaction_history.txt");//open file to read
	if (infile.is_open())
	{
		cout << "Event  " << "CompSymbol  " << "Number  " << "PricePerShare  " << "TotalValue  " << "Time" << endl;
		string line;//string line to store information
		while (!infile.eof())
		{
			while (getline(infile, line))
				cout << line << endl;
		}
	}
	else
		cout << "Unable to open the stock history." << endl;
}

//is empty function
bool StockAccount::isEmpty()const
{
	return mySize == 0;
}


//bubble sort function to sort the  portfolio table
void StockAccount::sortlist()
{
	//if the list is not empty
	if (mySize != 0)
	{
		//start from the first node
		Node* current = head;
		Node* prev = 0;
		Node* tempNode = 0;
		int Flag = 0;//flag to judge whether it need sort,0->don't need sort,1->need sort
		for (int i = 0; i < mySize; i++)
		{
			while (current->next != 0)//while there are more than one node							
			{
				tempNode = current->next;//judge with next node
				double price1 = (current->sharenum)*(current->price);
				double price2 = (tempNode->sharenum)*(tempNode->price);
				//judge if next is greater than the prev
				//if is, swap the two node
				if (price1<price2)
				{
					//change the two node
					Flag = 1;
					current->next = tempNode->next;
					tempNode->next = current;
					//if current is not the first,link temp with current prev
					if (prev != 0)
						prev->next = tempNode;
					prev = tempNode;
					//if current is the first
					if (head == current)
						head = tempNode;
					//if temp is the last
					if (current->next == 0)
						tail = current;
				}
				else//else move the the next node
				{
					prev = current;
					current = current->next;
				}
			}
			//break while loop
			if (Flag == 0)
				break;
			else
			{
				prev = 0;
				current = head;
				Flag = 0;
			}
		}
	}
}

//function call matlab
/*void StockAccount::viewgraph()
{
	Engine *ep;
	size_t size;
	ep = engOpen(NULL);
	if (ep == NULL) {
		cout << "Error: Not Found" << endl;
		exit(1);
	}
	int portSize = 0;
	double portHisValue[100];
	double portHisTime[100][6];
	ifstream portHistory("stock_transaction_history.txt", ios::in);
	if (!portHistory.is_open()) {//if portfolio is empty
		cout << "You do not have any portfolio history. " << endl;
	}
	ifstream PortHistory("stock_transaction_history.txt", ios::in);
	while (!PortHistory.eof()) { //import the file to memory
		PortHistory >> portHisValue[portSize] >> portHisTime[portSize][1] >> portHisTime[portSize][2]
			>> portHisTime[portSize][0] >> portHisTime[portSize][3] >> portHisTime[portSize][4]
			>> portHisTime[portSize][5];
		portSize++;
	}
	mxArray *Value;
	mxArray *Time;
	portSize--;
	Value = mxCreateDoubleMatrix(1, portSize, mxREAL);
	memcpy((void *)mxGetPr(Value), (void *)portHisValue, sizeof(double)*portSize);
	engPutVariable(ep, "v", Value);
	Time = mxCreateDoubleMatrix(6, portSize, mxREAL);
	memcpy((void *)mxGetPr(Time), (void *)portHisTime, sizeof(double) * 6 * portSize);
	engPutVariable(ep, "t", Time);
	engEvalString(ep, "t=t'");
	engEvalString(ep, "x=datenum(t);");
	engEvalString(ep, "plot(x,v,'k*',x,v,'r-');");
	engEvalString(ep, "datetick('x',31,'keepticks','keeplimits');");
	engEvalString(ep, "axis auto;");
}*/