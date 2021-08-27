#pragma once
#include <iostream>
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h" 
using namespace std;
class DataStructure
{
private:
	HEADER_B* EntryP;
	void InsertItem(ITEM2*);
	void CreateBHeader(char, char, ITEM2*);
	void CreateAHeader(char, HEADER_A*, ITEM2*);
	void RemoveItem(char* pItemID);
	void PrintItem2(item2* pI, int* n);
	void PrintHeaderA(HEADER_A* pA, int* n);
	void PrintHeaderB(HEADER_B* p, int* n);
	void PrintDataStructure();
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


