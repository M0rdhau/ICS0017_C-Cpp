#include "DataStructure.h"
void DataStructure::CreateAHeader(char second, HEADER_A* p, ITEM2* pI) {
	HEADER_A* newHeader;
	newHeader = (HEADER_A*)malloc(sizeof(HEADER_A));
	newHeader->cBegin = second;
	newHeader->pItems = pI;
	newHeader->pNext = 0;
	while (p->pNext != 0 && (int)p->pNext->cBegin < (int)second) { p = p->pNext; }
	if (p->pNext == 0) {
		p->pNext = newHeader;
	}
	else {
		newHeader->pNext = p->pNext;
		p->pNext = newHeader;
	}
	return;
}

void DataStructure::CreateBHeader(char first, char second, ITEM2* pI) {
	HEADER_B* p = EntryP;
	HEADER_A* newHeader;
	newHeader = (HEADER_A*)malloc(sizeof(HEADER_A));
	newHeader->cBegin = second;
	newHeader->pItems = pI;
	newHeader->pNext = 0;
	HEADER_B* newBHeader;
	newBHeader = (HEADER_B*)malloc(sizeof(HEADER_B));
	newBHeader->cBegin = first;
	newBHeader->pHeaderA = newHeader;
	newBHeader->pNext = 0;
	while (p->pNext != 0 && (int)p->pNext->cBegin < (int)first) { p = p->pNext; }
	if (p->pNext == 0) {
		p->pNext = newBHeader;
	}
	else {
		newBHeader->pNext = p->pNext;
		p->pNext = newBHeader;
	}
	return;
}

void DataStructure::InsertItem(ITEM2* pI) {
	printf("\r\n Item name: %s\r\n", pI->pID);
	char first = *pI->pID;
	char second = *(strchr(pI->pID, ' ') + 1);
	HEADER_B* searchP = this->EntryP;
	while (searchP->cBegin != first && searchP->pNext != 0) { searchP = searchP->pNext; }
	if (searchP->cBegin != first && searchP->pNext == 0) {
		CreateBHeader(first, second, pI);
		return;
	}
	else {
		HEADER_A* searchA = searchP->pHeaderA;
		while (searchA->cBegin != second && searchA->pNext != 0) { searchA = searchA->pNext; }
		if (searchA->cBegin != second && searchA->pNext == 0) {
			CreateAHeader(second, searchP->pHeaderA, pI);
			return;
		}
		else {
			ITEM2* searchI = (ITEM2*)searchA->pItems;
			while (strcmp(searchI->pID, pI->pID) != 0 && searchI->pNext != 0) { searchI = searchI->pNext; }
			if (strcmp(searchI->pID, pI->pID) != 0 && searchI->pNext == 0) {
				pI->pNext = (ITEM2*)searchA->pItems;
				searchA->pItems = pI;
				return;
			}
			else {
				throw 1337;
			}
		}
	}
}

void DataStructure::RemoveItem(char* pItemID) {
	char first = *pItemID;
	char second = *(strchr(pItemID, ' ') + 1);
	HEADER_B* searchP = this->EntryP;
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
							this->EntryP = searchP->pNext;
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

void DataStructure::IterItem2(item2* pI, HEADER_B* pComp = 0) {
	if (this->op == IterOperation::Count || this->op == IterOperation::Print) {
		this->itemAmt++;
		if (this->op == IterOperation::Print) {
			char* id = pI->pID;
			unsigned long int Code = pI->Code;
			int hour = pI->pTime->Hour;
			int minute = pI->pTime->Min;
			int second = pI->pTime->Sec;
			printf("%d) %s %u %d:%d:%d \r\n", this->itemAmt, id, Code, hour, minute, second);
		}
	}
	else if (this->op == IterOperation::Delete) {
		delete pI->pID;
		delete pI->pTime;
	}
}

void DataStructure::IterHeaderA(HEADER_A* pA, HEADER_B* pComp = 0) {
	ITEM2* pI = (ITEM2*)pA->pItems;
	while (pI->pNext != 0) {
		IterItem2(pI, pComp);
		if (this->op == IterOperation::Delete) {
			ITEM2* pPrev = pI;
			delete(pPrev);
		}
		pI = pI->pNext;
	}
	IterItem2(pI);
	if (this->op == IterOperation::Delete) {
		ITEM2* pPrev = pI;
		delete(pPrev);
	}
}

void DataStructure::IterHeaderB(HEADER_B* p, HEADER_B* pComp = 0) {
	HEADER_A* pA = p->pHeaderA;
	while (pA->pNext != 0) {
		IterHeaderA(pA, pComp);
		if (this->op == IterOperation::Delete) {
			HEADER_A* pPrev = pA;
			delete(pPrev);
		}
		pA = pA->pNext;
	}
	IterHeaderA(pA, pComp);
	if (this->op == IterOperation::Delete) {
		HEADER_A* pPrev = pA;
		delete(pPrev);
	}
}

void DataStructure::Iterate(HEADER_B* pComp = 0) {
	HEADER_B* pB = this->EntryP;
	while (pB->pNext != 0) {
		IterHeaderB(pB, pComp);
		if (this->op == IterOperation::Delete) {
			HEADER_B* pPrev = pB;
			delete(pPrev);
		}
		pB = pB->pNext;
	}
	IterHeaderB(pB, pComp);
	if (this->op == IterOperation::Delete) {
		HEADER_B* pPrev = pB;
		delete(pPrev);
	}
}

void DataStructure::PrintDataStructure() {
	this->op = IterOperation::Print;
	Iterate();
	this->op = IterOperation::None;
}



int DataStructure::GetItemsNumber() {
	this->itemAmt = 0;
	this->op = IterOperation::Count;
	Iterate();
	this->op = IterOperation::None;
	return this->itemAmt;
}

DataStructure::DataStructure()
{
	this->EntryP = 0;
}
DataStructure::DataStructure(char* pFileName) {
}
DataStructure::DataStructure(const DataStructure& original) {
}
DataStructure::~DataStructure() {
	this->op = IterOperation::Delete;
	Iterate();
	this->op = IterOperation::None;
}
void DataStructure::operator+(ITEM2* p) {
	this->InsertItem(p);
}
void DataStructure::operator-(char* c) {
	this->RemoveItem(c);
}