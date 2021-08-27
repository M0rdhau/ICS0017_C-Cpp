#pragma once
//
// Declarations of ITEM1....ITEM10
// Declarations of TIME, DATE1, DATE2, DATE 3 are in DateTime.h
// The ID is a C string consisting of two words. The words are separated 
// by one (and only one) space. The first characters of both words are 
// uppercase English letters. The other characters (if the are present)
// may be uppercase or lowercase English letters and '-'. The minimal
// number of characters in ID is 3, the maximal number is not specified.
// Examples: "Blood Red", "Blue-violet Crayola", "KSU Purple", "A B"
// To construct an item you must use function GetItem() from ICS0017DataSource.dll
//
typedef struct item1
{ 
	char *pID;
	unsigned long int Code;
	char *pTime; // formatted as hh::mm::ss
	struct item1 *pNext;
} ITEM1;

typedef struct item2
{  
	char *pID;
	unsigned long int Code;
	TIME *pTime; 
	struct item2 *pNext;
} ITEM2;

typedef struct item3
{  
	char *pID;
	unsigned long int Code;
	TIME Time;  
	struct item3 *pNext;
} ITEM3;

typedef struct item4
{  
	char *pID;
	unsigned long int Code;
	char *pDate; // formatted as dd-mm-yyyy
	struct item4 *pNext;
} ITEM4;

typedef struct item5
{  
	char *pID;
	unsigned long int Code;
	DATE1 *pDate; 
	struct item5 *pNext;
} ITEM5;

typedef struct item6
{ 
	char *pID;
	unsigned long int Code;
	DATE1 Date; 
	struct item6 *pNext;
} ITEM6;

typedef struct item7
{  
	char *pID;
	unsigned long int Code;
	DATE2 *pDate; 
	struct item7 *pNext;
} ITEM7;

typedef struct item8
{  
	char *pID;
	unsigned long int Code;
	DATE2 Date; 
	struct item8 *pNext;
} ITEM8;

typedef struct item9
{  
	char *pID;
	unsigned long int Code;
	DATE3 *pDate; 
	struct item9 *pNext;
} ITEM9;

typedef struct item10
{ 
	char *pID;
	unsigned long int Code;
	DATE3 Date; 
	struct item10 *pNext;
} ITEM10;

