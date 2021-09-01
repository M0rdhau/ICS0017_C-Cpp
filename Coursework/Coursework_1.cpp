#include <iostream> 
#include <iomanip>
#include "stdarg.h"
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h"
#include "DataStructure.h"
using namespace std;
#pragma warning ( disable : 4996 )
// IMPORTANT: follow the given order of *.h files: ICS0017DataSource.h must be 
// the last
void PrintItem2(item2* pI, int* n) {
	char* id = pI->pID;
	unsigned long int Code = pI->Code;
	int hour = pI->pTime->Hour;
	int minute = pI->pTime->Min;
	int second = pI->pTime->Sec;
	printf("%d) %s %u %d:%d:%d \r\n", *n, id, Code, hour, minute, second);
	(*n)++;
}

void PrintHeaderA(HEADER_A* pA, int* n) {
	ITEM2* pI = (ITEM2*)pA->pItems;
	while (pI->pNext != 0) {
		PrintItem2(pI, n);
		pI = pI->pNext;
	}
	PrintItem2(pI, n);
}

void PrintHeaderB(HEADER_B* p, int* n) {
	HEADER_A* pA = p->pHeaderA;
	while (pA->pNext != 0) {
		PrintHeaderA(pA, n);
		pA = pA->pNext;
	}
	PrintHeaderA(pA, n);
}

void PrintDataStructure(HEADER_B* p) {
	int n = 1;
	while (p->pNext != 0) {
		PrintHeaderB(p, &n);
		p = p->pNext;
	}
	PrintHeaderB(p, &n);
}

bool checkWord(char* p, int len) {
	for (int i = 0; i < len; i++) {
		int ascii = (int)*(p + i);
		if (!((ascii >= 65 || ascii <= 90) || (ascii >= 97 || ascii <= 122) || ascii == 45)) return true;
	}
	return false;
}

bool validateIDFormat(char* pNewItemID) {
	if (strlen(pNewItemID) < 3) return false;
	char* spacePos = strchr(pNewItemID, ' ');
	if ( spacePos == 0 || strchr(spacePos + 1, ' ') != 0) return false;
	char first = *pNewItemID;
	char second = *(spacePos + 1);
	if ((int)first < 65 || (int)first > 90 || (int)second < 65 || (int)second > 90) return false;
	int lenFirst = spacePos - pNewItemID;
	int lenSecond = strlen(pNewItemID) - lenFirst - 1;
	if (checkWord(pNewItemID, lenFirst) || checkWord(spacePos + 1, lenSecond)) return false;
	return true;
}

void createBHeader(char first, char second, HEADER_B* p, ITEM2* pI) {
	HEADER_A *newHeader = new HEADER_A;
	newHeader = (HEADER_A *)malloc(sizeof(HEADER_A));
	newHeader->cBegin = second;
	newHeader->pItems = pI;
	newHeader->pNext = 0;
	HEADER_B *newBHeader = new HEADER_B;
	newBHeader = (HEADER_B *)malloc(sizeof(HEADER_B));
	newBHeader->cBegin = first;
	newBHeader->pHeaderA = newHeader;
	newBHeader->pNext = 0;
	while (p->pNext != 0 && (int) p->pNext->cBegin < (int) first) { p = p->pNext; }
	if (p->pNext == 0) {
		p->pNext = newBHeader;
	}
	else {
		newBHeader->pNext = p->pNext;
		p->pNext = newBHeader;
	}
	return;
}

void createAHeader(char second, HEADER_A* p, ITEM2 *pI) {
	HEADER_A* newHeader;
	newHeader = (HEADER_A*)malloc(sizeof(HEADER_A));
	newHeader->cBegin = second;
	newHeader->pItems = pI;
	newHeader->pNext = 0;
	while (p->pNext != 0 && (int) p->pNext->cBegin < (int)second) { p = p->pNext; }
	if (p->pNext == 0) {
		p->pNext = newHeader;
	}
	else {
		newHeader->pNext = p->pNext;
		p->pNext = newHeader;
	}
	return;
}

HEADER_B* InsertItem(HEADER_B* p, char* pNewItemID = 0) {
	if (pNewItemID == 0 || validateIDFormat(pNewItemID)) {
		ITEM2* pI = (ITEM2*)GetItem(2, pNewItemID);
		printf("\r\n Item name: %s\r\n", pI->pID);
		if (pNewItemID == 0) {
			pNewItemID = pI->pID;
		}
		char first = *pNewItemID;
		char second = *(strchr(pNewItemID, ' ') + 1);
		HEADER_B* searchP = p;
		while (searchP->cBegin != first && searchP->pNext != 0) { searchP = searchP->pNext; }
		if (searchP->cBegin != first && searchP->pNext == 0) {
			createBHeader(first, second, p, pI);
			return p;
		}
		else {
			HEADER_A* searchA = searchP->pHeaderA;
			while (searchA->cBegin != second && searchA->pNext != 0) { searchA = searchA->pNext; }
			if (searchA->cBegin != second && searchA->pNext == 0) {
				createAHeader(second, searchP->pHeaderA, pI);
				return p;
			}
			else {
				ITEM2* searchI =(ITEM2 *) searchA->pItems;
				while (strcmp(searchI->pID, pI->pID) != 0 && searchI->pNext != 0) { searchI = searchI->pNext; }
				if (strcmp(searchI->pID, pI->pID) != 0 && searchI->pNext == 0) {
					pI->pNext = (ITEM2 *) searchA->pItems;
					searchA->pItems = pI;
					return p;
				}
				else {
					throw 1337;
				}
			}
		}
	}
	else {
		throw 1337;
	}
}

void RemoveItem(HEADER_B* p, char* pItemID) {
	if (validateIDFormat(pItemID)) {
		char first = *pItemID;
		char second = *(strchr(pItemID, ' ') + 1);
		HEADER_B* searchP = p;
		HEADER_B* prevB = 0;
		while (searchP->cBegin != first && searchP->pNext != 0) {
			prevB = searchP;
			searchP = searchP->pNext;
		}
		if (searchP->cBegin != first && searchP->pNext == 0) {
			throw 1337;
		}
		else {
			HEADER_A* searchA = searchP->pHeaderA;
			HEADER_A* prevA = 0;
			while (searchA->cBegin != second && searchA->pNext != 0) {
				prevA = searchA;
				searchA = searchA->pNext;
			}
			if (searchA->cBegin != second && searchA->pNext == 0) {
				throw 1337;
			}
			else {
				ITEM2* searchI = (ITEM2*)searchA->pItems;
				ITEM2* prev = 0;
				while (strcmp(searchI->pID, pItemID) != 0 && searchI->pNext != 0) {
					prev = searchI;
					searchI = searchI->pNext;
				}
				if (strcmp(searchI->pID, pItemID) != 0 && searchI->pNext == 0) {
					throw 1337;
				}
				else {
					if (searchI == (ITEM2*)searchA->pItems) {
						delete(searchI->pID);
						delete(searchI->pTime);
						searchA->pItems = searchI->pNext;
						delete(searchI);
					}
					else if (searchI->pNext == 0) {
						delete(searchI->pID);
						delete(searchI->pTime);
						prev->pNext = 0;
						delete(searchI);
					}
					else {
						delete(searchI->pID);
						delete(searchI->pTime);
						prev->pNext = searchI->pNext;
						delete(searchI);
					}
					if (searchA->pItems == 0) {
						if (prevA == 0) {
							searchP->pHeaderA = searchA->pNext;
						}
						else {
							prevA->pNext = searchA->pNext;
						}
						delete(searchA);
						if (searchP->pHeaderA == 0) {
							if (prevB == 0) {
								p = searchP->pNext;
							}
							else {
								prevB->pNext = searchP->pNext;
							}
							delete(searchP);
						}
					}
					return;
				}
			}
		}
	}
	else {
		throw 1337;
	}
}

void oldCoursework2() {
	DataStructure* dS = new DataStructure();
	cout << "print empty" << endl;
	cout << *dS << endl;
	cout << "printed" << endl;
	char name[] = "Phtahlo Blue";
	ITEM2* it = (ITEM2*)GetItem(2, name);
	*dS += it;
	*dS += (ITEM2*)GetItem(2);
	cout << *dS << endl;
	cout << dS->GetItemPointer(name) << endl;
	DataStructure* newS = new DataStructure(*dS);
	cout << *newS << endl;
	cout << "newS and dS are equal: " << (*newS == *dS) << endl;
	*newS += (ITEM2*)GetItem(2);
	*newS += (ITEM2*)GetItem(2);
	cout << *newS << endl;
	cout << *dS << endl;
	DataStructure dSS;
	dSS = *newS;
	cout << "dSS is now equal to newS" << endl;
	cout << dSS << endl;
	dSS += (ITEM2*)GetItem(2);
	cout << *newS << endl;
	cout << dSS << endl;
	char dest[] = "C:\\temp\\data.txt";
	newS->Write(dest);
	cout << "Wrote a file" << endl;
	DataStructure evenNewerS = DataStructure(dest);
	cout << "From file" << endl;
	cout << evenNewerS << endl;
	//delete dS;
	//cout << *dS << endl;
}

void coursework1() {
	HEADER_B* p = GetStruct1(2, 30);
	PrintDataStructure(p);
	char insert[][5] = {
		"Z A",
		"Z Z",
		"Z K",
		"A Z",
		"A A",
		"A K",
		"G Z",
		"G A",
		"G K",
		"M A",
		"M Ba",
		"M Bb",
		"M Z"
	};
	for (int i = 0; i < 13; i++) {
		InsertItem(p, insert[i]);
	}
	try {
		char insertNew[] = "M";
		InsertItem(p, insertNew);
	}
	catch (...) {
		printf("invalid operation\n\r");
	}
	try {
		char insertNew[] = "Ba";
		InsertItem(p, insertNew);
	}
	catch (...) {
		printf("invalid operation\n\r");
	}
	try {
		char insertNew[] = "Mba";
		InsertItem(p, insertNew);
	}
	catch (...) {
		printf("invalid operation\n\r");
	}
	PrintDataStructure(p);
	for (int i = 0; i < 13; i++) {
		RemoveItem(p, insert[i]);
	}
	try {
		char insertNew[] = "M";
		RemoveItem(p, insertNew);
	}
	catch (...) {
		printf("invalid operation\n\r");
	}
	try {
		char insertNew[] = "Ba";
		RemoveItem(p, insertNew);
	}
	catch (...) {
		printf("invalid operation\n\r");
	}
	try {
		char insertNew[] = "Mba";
		RemoveItem(p, insertNew);
	}
	catch (...) {
		printf("invalid operation\n\r");
	}
	PrintDataStructure(p);
	return;
}

void coursework2() {
	DataStructure *dataStructure = new DataStructure();
	for (int i = 0; i < 10; i++) {
		*dataStructure += (ITEM2*)GetItem(2);
	}
	cout << *dataStructure << endl;
	cout << "Number of items: " << dataStructure->GetItemsNumber() << endl;
	cout << dataStructure->GetItemPointer((char *)"Light Cyan") << endl;
	cout << dataStructure->GetItemPointer((char*)"X X") << endl;
	DataStructure *newDS = new DataStructure(*dataStructure);
	*dataStructure -= (char*)"Banana Mania";
	*dataStructure -= (char*)"Vegas Gold";
	*dataStructure -= (char*)"Persian Green";
	cout << "Old data structure and new are equal? " << (*newDS == *dataStructure) << endl;
	dataStructure->Write((char*)"C:\\temp\\data.txt");
	DataStructure fromFile = DataStructure((char*)"C:\\temp\\data.txt");
	cout << "Old data structure and one created from file are equal? " << (fromFile == *dataStructure) << endl;
	fromFile = *newDS;
	cout << "Assigned 10 item data structure to one created from file " << endl;
	cout << fromFile << endl;
	return;
}

int main()
{
	coursework2();
	coursework1();
	return 0;
}