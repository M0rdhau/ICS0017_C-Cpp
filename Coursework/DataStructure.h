#pragma once
#include <iostream>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
using namespace std;
enum class IterOperation {Count, Print, Delete, Compare, None};
class DataStructure
{
private:
	HEADER_B* EntryP;
	void InsertItem(ITEM2*);
	void CreateBHeader(char, char, ITEM2*);
	void CreateAHeader(char, HEADER_A*, ITEM2*);
	void RemoveItem(char*);
	void IterItem2(item2*, HEADER_B*);
	void IterHeaderA(HEADER_A*, HEADER_B*);
	void IterHeaderB(HEADER_B*, HEADER_B*);
	void Iterate(HEADER_B*);
	void PrintDataStructure();
	int itemAmt = 0;
	IterOperation op;
public:
	//Empty datastructure
	DataStructure();
	//Read datastructure from file
	DataStructure(char *);
	//Copy from another datastructure
	DataStructure(const DataStructure&);
	~DataStructure();
	int GetItemsNumber();
	ITEM2* GetItem(char*);
	void operator+(ITEM2*);
	void operator-(char *);
	DataStructure operator=(const DataStructure&);
	int operator==(DataStructure&);
	void Write(char*);
	//print everything to console
	friend std::ostream& operator<<(std::ostream&, const DataStructure&);
};


