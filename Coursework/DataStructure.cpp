#include "DataStructure.h"

ITEM2* DataStructure::CopyItem2(ITEM2* p) {
	ITEM2* it = new ITEM2;
	it->pNext = 0;
	int n;
	char* pNewID = new char[n = strlen(p->pID) + 1];
	strcpy_s(pNewID, n, p->pID);
	TIME* time = new TIME;
	time->Hour = p->pTime->Hour;
	time->Min = p->pTime->Min;
	time->Sec = p->pTime->Sec;
	it->Code = p->Code;
	it->pID = pNewID;
	it->pTime = time;
	return it;
}

void DataStructure::PrintItem2(ITEM2* pI, int n) const{
	char* id = pI->pID;
	unsigned long int Code = pI->Code;
	int hour = pI->pTime->Hour;
	int minute = pI->pTime->Min;
	int second = pI->pTime->Sec;
	cout << n << " " << id << " " << Code << " " << hour << " " << minute << " " << second << endl;
}

	void DataStructure::CreateAHeader(char second, HEADER_A* p, ITEM2* pI) {
		HEADER_A* newHeader = new HEADER_A;
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
		HEADER_B* p = this->EntryP;
		HEADER_A* newHeader = new HEADER_A;
		newHeader->cBegin = second;
		newHeader->pItems = pI;
		newHeader->pNext = 0;
		HEADER_B* newBHeader = new HEADER_B;
		newBHeader->cBegin = first;
		newBHeader->pHeaderA = newHeader;
		newBHeader->pNext = 0;
		if (p == 0) {
			this->EntryP = newBHeader;
		}
		else {
			while (p->pNext != 0 && (int)p->pNext->cBegin < (int)first) { p = p->pNext; }
			if (p->pNext == 0) {
				p->pNext = newBHeader;
			}
			else {
				newBHeader->pNext = p->pNext;
				p->pNext = newBHeader;
			}
		}
		return;
	}

	void DataStructure::InsertItem(ITEM2* pI) {
		printf("\r\n Item name: %s\r\n", pI->pID);
		char first = *pI->pID;
		char second = *(strchr(pI->pID, ' ') + 1);
		HEADER_B* searchP = this->EntryP;

		if (this->EntryP == 0) {
			CreateBHeader(first, second, pI);
			return;
		}
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

	void DataStructure::IterItem2(item2* pI, IterOperation it, int& amt, ITEM2** arr) const {
		if (it == IterOperation::List) {
			arr[amt] = pI;
		}
		amt++;
		return;
	}

	void DataStructure::IterHeaderA(HEADER_A* pA, IterOperation it, int& amt, ITEM2** arr) const {
		ITEM2* pI = (ITEM2*)pA->pItems;
		while (pI->pNext != 0) {
			IterItem2(pI, it, amt, arr);
			pI = pI->pNext;
		}
		IterItem2(pI, it, amt, arr);
		return;
	}

	void DataStructure::IterHeaderB(HEADER_B* p, IterOperation it, int& amt, ITEM2** arr) const {
		HEADER_A* pA = p->pHeaderA;
		while (pA->pNext != 0) {
			IterHeaderA(pA, it, amt, arr);
			pA = pA->pNext;
		}
		IterHeaderA(pA, it, amt, arr);
		return;
	}


	void DataStructure::Iterate(IterOperation it, int &amt, ITEM2** arr) const{
		HEADER_B* pB = this->EntryP;
		if (pB == 0) {
			return;
		}
		while (pB->pNext != 0) {
			IterHeaderB(pB, it, amt, arr);
			pB = pB->pNext;
		}
		IterHeaderB(pB, it, amt, arr);
		return;
	}



	int DataStructure::GetItemsNumber() const{
		int itemAmt = 0;
		Iterate(IterOperation::Count, itemAmt, 0);
		return itemAmt;
	}

	ITEM2** DataStructure::GetItems() const{
		int amt = this->GetItemsNumber();
		ITEM2** items = (ITEM2**)malloc(amt * sizeof(ITEM2*));
		int zero = 0;
		Iterate(IterOperation::List, zero, items);
		return items;
	}

	void DataStructure::PrintDataStructure() const {
		int amt = this->GetItemsNumber();
		ITEM2** items = this->GetItems();
		if (amt == 0) return;
		for (int i = 0; i < amt; i++) {
			int printNum = i + 1;
			PrintItem2(items[i], printNum);
		}
		return;
	}

	char* DataStructure::SerializeItem2(ITEM2* pI)
	{
		short int n = strlen(pI->pID) + 1;
		char* itemSer, * r;
		//itemSer = (char *)malloc(n += sizeof(ITEM2) + 3*sizeof(int) + sizeof(unsigned long int) - sizeof(ITEM2 *) - sizeof(TIME *) )
	}



	DataStructure::DataStructure()
	{
		this->EntryP = 0;
	}
	DataStructure::DataStructure(char* pFileName) {
	}
	DataStructure::DataStructure(const DataStructure& original) {
		ITEM2** originalItems = original.GetItems();
		int itemNum = original.GetItemsNumber();
		for (int i = 0; i < itemNum; i++) {
			this->InsertItem(this->CopyItem2(originalItems[i]));
		}
	}
	DataStructure::~DataStructure() {
		ITEM2** items = this->GetItems();
		int itemNum = this->GetItemsNumber();
		for (int i = 0; i < itemNum; i++) {
			this->FindItem(items[i]->pID, true);
		}
		delete this->EntryP;
	}
	void DataStructure::operator+=(ITEM2* p) {
		this->InsertItem(p);
		return;
	}
	void DataStructure::operator-=(char* c) {
		this->FindItem(c, true);
		return;
	}

	DataStructure& DataStructure::operator=(const DataStructure& s)
	{
		ITEM2** items = this->GetItems();
		int itemNum = this->GetItemsNumber();
		for (int i = 0; i < itemNum; i++) {
			this->FindItem(items[i]->pID, true);
		}
		this->EntryP = 0;
		ITEM2** originalItems = s.GetItems();
		int otherItems = s.GetItemsNumber();
		for (int i = 0; i < otherItems; i++) {
			this->InsertItem(this->CopyItem2(originalItems[i]));
		}
		return *this;
	}


	int DataStructure::operator==(DataStructure& other)
	{
		int thisNum = this->GetItemsNumber();
		int otherNum = other.GetItemsNumber();
		if (thisNum == otherNum) {
			ITEM2** thisList = this->GetItems();
			for (int i = 0; i < thisNum; i++) {
				ITEM2* fromThis = thisList[i];
				ITEM2* fromOther = other.FindItem(thisList[i]->pID, false);
				if (!(
					strcmp(fromThis->pID, fromOther->pID)==0 &&
					fromThis->Code == fromOther->Code &&
					fromThis->pTime->Hour == fromOther->pTime->Hour &&
					fromThis->pTime->Min == fromOther->pTime->Min &&
					fromThis->pTime->Sec == fromOther->pTime->Sec
					)) {
					return 0;
				}
					
			}
		}
		return 1;
	}

	void DataStructure::Write(char*)
	{
	}

	

