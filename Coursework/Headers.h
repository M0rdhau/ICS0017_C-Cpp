#pragma once
//
// Declarations of HEADER_A, HEADER_B, HEADER_C, HEADER_D
// Declarations of ITEM1...ITEM10 are in Items.h
//
typedef struct headerA
{
	void *pItems;  // Pointer to the linked list of items. 
				   // Items may be of types ITEM1...ITEM10.
	char cBegin;   // The linked list contains objects in which
				   // the first letter of the second word
	               // of ID cBegin.
	struct headerA *pNext;
} HEADER_A;


typedef struct headerB
{
	HEADER_A *pHeaderA; // Pointer to the linked list of headers type A.
	char cBegin;        // The first letter of ID of objects related to
					    // header is cBegin.
	struct headerB *pNext;
} HEADER_B;


typedef struct headerC
{
	void **ppItems;   // Pointer to the array of pointers to items. 
					  // Items may be of types ITEM1...ITEM10.
	char cBegin;      // The first letter of ID of objects related to
					  // header is cBegin.
	struct headerC *pNext;
} HEADER_C;

typedef struct headerD
{
	HEADER_A *pHeaderA; // Pointer to the linked list of headers type A.
	char cBegin;        // The first letter of ID of objects related to
					    // header is cBegin.
	struct headerD *pNext;
	struct headerD *pPrior;

} HEADER_D;


typedef struct headerE
{
	void **ppItems;   // Pointer to the array of pointers to items. 
					  // Items may be of types ITEM1...ITEM10.
	char cBegin;      // The first letter of ID of objects related to
					  // header is cBegin.
	struct headerE *pNext;
	struct headerE *pPrior;
} HEADER_E;

