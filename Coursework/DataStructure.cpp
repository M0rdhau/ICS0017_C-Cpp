#include "DataStructure.h"

void printItem2(ITEM2* pI, int& n) {
	n++;
	char* id = pI->pID;
	unsigned long int Code = pI->Code;
	int hour = pI->pTime->Hour;
	int minute = pI->pTime->Min;
	int second = pI->pTime->Sec;
	cout << n << " " << id << " " << Code << " " << hour << " " << minute << " " << second << endl;
}

//This nightmare of a code is here because I had to rewrite functions Iterate... to work as constant
//functions. Otherwise overloading operator << was no possible
void DataStructure::PrintDataStructure() const {
	int n = 0;
	HEADER_B* pB = this->EntryP;
	while (pB->pNext != 0) {
		HEADER_A* pA = pB->pHeaderA;
		while (pA->pNext != 0) {
			ITEM2* pI = (ITEM2*)pA->pItems;
			while (pI->pNext != 0) {
				printItem2(pI, n);
				pI = pI->pNext;
			}
			printItem2(pI, n);
			pA = pA->pNext;
		}
		ITEM2* pI = (ITEM2*)pA->pItems;
		while (pI->pNext != 0) {
			printItem2(pI, n);
			pI = pI->pNext;
		}
		printItem2(pI, n);
		pB = pB->pNext;
	}
	HEADER_A* pA = pB->pHeaderA;
	while (pA->pNext != 0) {
		ITEM2* pI = (ITEM2*)pA->pItems;
		while (pI->pNext != 0) {
			printItem2(pI, n);
			pI = pI->pNext;
		}
		printItem2(pI, n);
		pA = pA->pNext;
	}
	ITEM2* pI = (ITEM2*)pA->pItems;
	while (pI->pNext != 0) {
		printItem2(pI, n);
		pI = pI->pNext;
	}
	printItem2(pI, n);
	pB = pB->pNext;
	return;
}

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

	ITEM2* DataStructure::FindItem(char* pItemID, bool deleteItem = false) {
		char first = *pItemID;
		char second = *(strchr(pItemID, ' ') + 1);
		HEADER_B* searchP = this->EntryP;
		HEADER_B* prevB = 0;
		while (searchP->cBegin != first && searchP->pNext != 0) {
			prevB = searchP;
			searchP = searchP->pNext;
		}
		if (searchP->cBegin != first && searchP->pNext == 0) {
			return NULL;
		}
		else {
			HEADER_A* searchA = searchP->pHeaderA;
			HEADER_A* prevA = 0;
			while (searchA->cBegin != second && searchA->pNext != 0) {
				prevA = searchA;
				searchA = searchA->pNext;
			}
			if (searchA->cBegin != second && searchA->pNext == 0) {
				return NULL;
			}
			else {
				ITEM2* searchI = (ITEM2*)searchA->pItems;
				ITEM2* prev = 0;
				while (strcmp(searchI->pID, pItemID) != 0 && searchI->pNext != 0) {
					prev = searchI;
					searchI = searchI->pNext;
				}
				if (strcmp(searchI->pID, pItemID) != 0 && searchI->pNext == 0) {
					return 0;
				}
				else if (deleteItem) {
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
					return NULL;
				}
				else {
					return searchI;
				}
			}
		}
	}

	void DataStructure::IterItem2(item2* pI, IterOperation it, DataStructure* pComp = 0) {
		if (it == IterOperation::Count || it == IterOperation::Print) {
			this->itemAmt++;
			if (it == IterOperation::Print) {
				char* id = pI->pID;
				unsigned long int Code = pI->Code;
				int hour = pI->pTime->Hour;
				int minute = pI->pTime->Min;
				int second = pI->pTime->Sec;
				//printf("%d) %s %u %d:%d:%d \r\n", this->itemAmt, id, Code, hour, minute, second);
				cout << this->itemAmt << " " << id << " " << Code << " " << hour << " " << minute << " " << second << endl;
			}
		}
		else if (it == IterOperation::Delete) {
			delete pI->pID;
			delete pI->pTime;
		}
		else if (it == IterOperation::Compare) {
			ITEM2* pOther = pComp->GetItem(pI->pID);
			if (pOther == 0) {
				return;
			}
		}
		return;
	}

	void DataStructure::IterHeaderA(HEADER_A* pA, IterOperation it, DataStructure* pComp = 0) {
		ITEM2* pI = (ITEM2*)pA->pItems;
		while (pI->pNext != 0) {
			IterItem2(pI, it, pComp);
			if (it == IterOperation::Delete) {
				ITEM2* pPrev = pI;
				delete(pPrev);
			}
			pI = pI->pNext;
		}
		IterItem2(pI, it, pComp);
		if (it == IterOperation::Delete) {
			ITEM2* pPrev = pI;
			delete(pPrev);
		}
		return;
	}

	void DataStructure::IterHeaderB(HEADER_B* p, IterOperation it, DataStructure* pComp = 0) {
		HEADER_A* pA = p->pHeaderA;
		while (pA->pNext != 0) {
			IterHeaderA(pA, it, pComp);
			if (it == IterOperation::Delete) {
				HEADER_A* pPrev = pA;
				delete(pPrev);
			}
			pA = pA->pNext;
		}
		IterHeaderA(pA, it, pComp);
		if (it == IterOperation::Delete) {
			HEADER_A* pPrev = pA;
			delete(pPrev);
		}
		return;
	}


	void DataStructure::Iterate(IterOperation it, DataStructure* pComp = 0) {
		HEADER_B* pB = this->EntryP;
		while (pB->pNext != 0) {
			IterHeaderB(pB, it, pComp);
			if (it == IterOperation::Delete) {
				HEADER_B* pPrev = pB;
				delete(pPrev);
			}
			pB = pB->pNext;
		}
		IterHeaderB(pB, it, pComp);
		if (it == IterOperation::Delete) {
			HEADER_B* pPrev = pB;
			delete(pPrev);
		}
		return;
	}



	int DataStructure::GetItemsNumber() {
		this->itemAmt = 0;
		Iterate(IterOperation::Count);
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
		Iterate(IterOperation::Delete);
	}
	/*DataStructure DataStructure::operator+(ITEM2* p) {
		return DataStructure(this)
		this->InsertItem(p);
	}*/
	//DataStructure DataStructure::operator-(char* c) {

	//	this->FindItem(c, true);
	//	return;
	//}
	//ITEM2* DataStructure::GetItem(char* c) {
	//	this->FindItem(c, false);
	//}