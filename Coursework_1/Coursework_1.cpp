#include <iostream> 
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h" 
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
	HEADER_A newHeader;
	newHeader.cBegin = second;
	newHeader.pItems = pI;
	HEADER_B newBHeader;
	newBHeader.cBegin = first;
	newBHeader.pHeaderA = &newHeader;
	while ((int) p->pNext->cBegin < (int) first && p->pNext != 0) { p = p->pNext; }
	if (p->pNext == 0) {
		p->pNext = &newBHeader;
	}
	else {
		newBHeader.pNext = p->pNext;
		p->pNext = &newBHeader;
	}
	return;
}

void createAHeader(char second, HEADER_A* p, ITEM2 *pI) {
	HEADER_A newHeader;
	newHeader.cBegin = second;
	newHeader.pItems = pI;
	while ((int) p->pNext->cBegin < (int)second && p->pNext != 0) { p = p->pNext; }
	if (p->pNext == 0) {
		p->pNext = &newHeader;
	}
	else {
		newHeader.pNext = p->pNext;
		p->pNext = &newHeader;
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
				while (searchI->pID != pI->pID && searchI->pNext != 0) { searchI = searchI->pNext; }
				if (searchI->pID != pI->pID && searchI->pNext == 0) {
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

int main()
{
	HEADER_B* p = GetStruct1(2, 100);	
	PrintDataStructure(p);
	char insert[] = "Light Yellow";
	InsertItem(p, insert);
	PrintDataStructure(p);
	return 0;
}