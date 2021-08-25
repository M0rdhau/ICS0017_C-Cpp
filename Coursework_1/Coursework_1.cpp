#include <iostream> 
#include "DateTime.h" 
#include "Items.h" 
#include "Headers.h" 
#include "ICS0017DataSource.h" 
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

void InsertItem(HEADER_B* p, char* pNewItemID = 0) {
	if (validateIDFormat(pNewItemID)) {
	
	}
	else {
		throw 1337;
	}
}

int main()
{
	HEADER_B* p = GetStruct1(2, 100);	
	PrintDataStructure(p);
	return 0;
}