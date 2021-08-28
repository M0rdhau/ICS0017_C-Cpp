#pragma once
#include <iostream>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
using namespace std;
enum class IterOperation {Count, Print, Delete, Compare, None};
enum class LastMatch {Match, NoMatch, Nil};
class DataStructure
{
private:
	HEADER_B* EntryP;
	void InsertItem(ITEM2*);
	void CreateBHeader(char, char, ITEM2*);
	void CreateAHeader(char, HEADER_A*, ITEM2*);
	ITEM2* FindItem(char*, bool);
	// Functions for iteration - so that less copy-pasted code occurs
	void IterItem2(item2*, DataStructure*);
	void IterHeaderA(HEADER_A*, DataStructure*);
	void IterHeaderB(HEADER_B*, DataStructure*);
	void Iterate(DataStructure*);
	void PrintDataStructure();
	int itemAmt = 0;
	IterOperation op;
	LastMatch match;
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


