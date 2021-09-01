#pragma once
#include <iostream>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
using namespace std;
enum class IterOperation {Count, List};
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
	void IterItem2(item2*, IterOperation, int&, ITEM2**) const;
	void IterHeaderA(HEADER_A*, IterOperation, int&, ITEM2**) const;
	void IterHeaderB(HEADER_B*, IterOperation, int &, ITEM2**) const;
	void Iterate(IterOperation, int&, ITEM2 **) const;
	void PrintItem2(ITEM2*, int) const;
	void PrintDataStructure() const;
	char* SerializeItem2(ITEM2*, int*);
	void InsertItem(ITEM2*);
	ITEM2** GetItems() const;
public:
	//Empty datastructure
	DataStructure();
	//Read datastructure from file
	DataStructure(char *);
	//Copy from another datastructure
	DataStructure(const DataStructure&);
	~DataStructure();
	int GetItemsNumber() const;
	ITEM2* GetItemPointer(char* pID) { return FindItem(pID, false); }
	void operator+=(ITEM2*);
	void operator-=(char *);
	DataStructure &operator=(const DataStructure&);
	int operator==(DataStructure&);
	void Write(char*);
	//print everything to console
	friend std::ostream& operator<<(std::ostream& out, const DataStructure& list) {
		list.PrintDataStructure();
		return out;
	}
};


