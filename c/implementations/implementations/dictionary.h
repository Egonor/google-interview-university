// Implement Dictionary with Hash-Chaining and 
//	Open Addressing (Linear Probing & *Double Hashing)
// Hash Algorithm Analysis:
// https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed

#pragma once

#ifndef DICTIONARY_H
#define DICTIONARY_H
#endif

// HashTable w/ LinkedLists REQUIRES a Node with Key:Value pairs to exists/delete
// TODO: Fix Weird implementation (Using my LinkedList but std::vector) by making Vector() generic
// #include "linkedlist.h"

using namespace std;
// TODO: Should I be using u32? or u8/u16/etc...? Find out which & why.

struct Pair {
	string key; // WARN: store initial hash as key, not plaintext "key" for crypto
	int value;
	//node *next; For LinkedList Implementation
};

class Dictionary {
private:
	const string deleted = "DELETED";		// the string to use when a key is "overwritable"
	u32 size;								// n
	u32 tableSize;							// m	
	
	vector<Pair> table;

	u32 Hash1(string key);		
	u32 Hash2(u32 hashedKey);
	vector<Pair> Resize(float scale);		// 2.0f to grow, 0.3f to shrink by thirds

	//u32 FindIndex(u32 key);
	// TODO: Pull Grow/Shrink out into a single function (a lot of repeat code) as an exercise.

public:
	Dictionary(u32 initialSize);

	u32 Size();										// Returns the size of the Dictionary.
	bool Exists(string key);						// Returns true if {key} exists in Dictionary.

	int GetValue(string key);							// Returns the {Value} of a given {Key}.

	u32 Insert(string key, int value);				// Returns {Key}'s Hash when successfully inserted.	
	u32 Delete(string key);							// Returns {Key}'s Hash when successfully deleted.
};

	

/* NOTES NOTES NOTES NOTES NOTES NOTES NOTES NOTES */
// Good Hash Funcitons are:
// - Deterministic
// - Uniform distribution of keys
// - Fast to compute
// - Few Collisions

// m should be a power of 2
// Amortization = Spread out high cost operations so it's cheaper on average
//				* operation takes "T(n) amortized", if k operations take <= k * T(n) time
//				* operation takes "T(n) on average" where average over all operations.

// Growth: Table Doubling 0(n) because it's a geometric series 0(1 + 2 + 4...+ n). 
// 0(1) amortized: k inserts & deletes take 0(k) time

// *********Chaining********
// c - length of the longest chain
// O(n + m) memory used
// Alpha = (n / m) or Load Factor (% of table filled)
// Operations run in O(c + 1) time.

/* TEMP for Linear Probing (Later?)
class LinearDict {
private:
	int size;
	int tableSize;
	unsigned int *table;

public:
	LinearDict();

	bool ExistsL(string key);
	int Size();

	void Insert(string key, int value);
	int GetValue(string key);			// Search using Linear Probing (bad)
	void Delete(string key);
};
*/