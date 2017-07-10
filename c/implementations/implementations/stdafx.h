// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>


// Reference additional headers your program requires here
#include <stdexcept>
//#include <ctime>    
#include <string>
#include <vector>		// for hashing without rewriting Vector() to have generic types
//#include <functional> // this is "hash": for testing purposes
//#include <iostream>	// cout
#include <queue>        // Level-Order Traversal of Binary Tree
#include <list>         // Level-Order Traversal of Binary Tree
#include <algorithm>>   // bst.ccp: max()
#include <iostream>     // cout <<


typedef int8_t i8;		// BYTE
typedef int16_t i16;	// WORD
typedef int32_t i32;	// DWORD
typedef int64_t i64;	// QWORD


typedef uint8_t u8;		// BYTE
typedef uint16_t u16;	// WORD
typedef uint32_t u32;	// DWORD
typedef uint64_t u64;	// QWORD (4 16-bit WORDS)
