#pragma once
typedef struct
{
	int Hour; // 0...23
	int Min;  // 0...59
	int Sec;  // 0...59
} TIME;

typedef struct
{
	int Day;
	int Month; // from 1 to 12
	int Year;  // AD, for example 2019
} DATE1;

typedef struct
{
	int Day;
	char Month[4]; // "Jan", "Feb", ...
	int Year;      // AD, for example 2019
} DATE2;

typedef struct
{
	int Day;
	char *pMonth; // pointer to full name "January", "February", ...
	int Year;     // AD, for example 2019
} DATE3;