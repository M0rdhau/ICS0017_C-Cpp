#pragma once
#include <iostream>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
using namespace std;
enum class IterOperation {Count, Copy, Delete, Compare, None};
enum class LastMatch {Match, NoMatch, Nil};
class DataStructure
{
private:
	HEADER_B* EntryP;
	void CreateBHeader(char, char, ITEM2*);
	void CreateAHeader(char, HEADER_A*, ITEM2*);
	ITEM2* FindItem(char*, bool);
	ITEM2* CopyItem2(ITEM2*);
	// Functions for iteration - so that less copy-pasted code occurs
	void IterItem2(item2*, IterOperation, DataStructure*);
	void IterHeaderA(HEADER_A*, IterOperation, DataStructure*);
	void IterHeaderB(HEADER_B*, IterOperation, DataStructure*);
	void Iterate(IterOperation, DataStructure*);
	void PrintItem2(ITEM2*, int&) const;
	void PrintDataStructure() const;
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
	void InsertItem(ITEM2*);
	int GetItemsNumber();
	ITEM2* GetItem(char* pID) { return FindItem(pID, false); }
	//DataStructure operator+(ITEM2*);
	//DataStructure operator-(char *);
	//DataStructure operator=(const DataStructure&);
	//int operator==(DataStructure&);
	//void Write(char*);
	//print everything to console
	friend std::ostream& operator<<(std::ostream& out, const DataStructure& list) {
		list.PrintDataStructure();
		return out;
	}
};


