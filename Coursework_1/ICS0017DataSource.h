#pragma once
#ifdef ICS0017DATASOURCE_EXPORTS
#define LIBSPEC extern "C" _declspec(dllexport)
#else
#define LIBSPEC extern "C" _declspec(dllimport)
#endif
LIBSPEC HEADER_B *GetStruct1(int iItem, int nItems);
LIBSPEC HEADER_C *GetStruct2(int iItem, int nItems);
LIBSPEC HEADER_A **GetStruct3(int iItem, int nItems);
LIBSPEC HEADER_D *GetStruct4(int iItem, int nItems);
LIBSPEC HEADER_E *GetStruct5(int iItem, int nItems);
LIBSPEC void *GetItem(int iItem, char *pID = nullptr);
#ifdef INSTRUCTOR
LIBSPEC void SetInstructorMode(); // asks password
#endif
// iItem - index of item(s) to generate (1...10) and insert into data structure
// nItem - number of items to insert into data structure
// Functions CreateStructn() (n = 1...5) construct nItem items of type iItem and insert
// them into data structure. Their return value is the pointer allowing to access
// the data. In each item the member "code" as well as members presenting time or date
// are calculated by C++ pseudo-random data generators. The ID is randomly selected from
// list Colors.txt.
// Function GetItem() generates a stand-alone item of type iItem and returns the pointer
// to it. Its member member "code" as well as members presenting time or date are 
// set as presented above. If the second parameter of this function is zero pointer,
// the pID is selected from list Colors.txt. If not, the string presented by the second
// parameter is used.
// Examples:
// HEADER_B *ps1 = GetStruct1(3, 30);
// Creates data structure of type 1 consisting of 30 items of type 3
// HEADER_A **pps3 = GetStruct3(10, 100);
// Creates data structure of type 3 consisting of 100 items of type 10
// ITEM5 *pit5 = (ITEM5 *)GetItem(5, (char *)"A B");
// Constructs item of type 5, ID will set to "A B" (do not forget that "A B" is of type const string *)
// ITEM8 *pit8 = (ITEM8 *)GetItem(8);
// Constructs item of type 8, ID will set by program
// In case of failure all the listed here functions return zero pointer and in command prompt 
// window print the error message.


