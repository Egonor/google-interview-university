#include "stdafx.h"
#include "dictionary.h"

// Used to convert a <string> key to a u32 (to be hashed)
u32 Dictionary::Hash1(string key) {
	// DJB2 Hashing Algorithm
	u32 hash = 5381;
	int c;
	for (int i = 0; i < key.length(); ++i) {
		c = (int)key[i];
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

// TODO: Is this Hash function a placeholder?
u32 Dictionary::Hash2(u32 hashedKey) {
	return (31 - (hashedKey % 31) + 1); // random prime (31) + 1 (can't return 0 or infinite loop @ hash1)

	// http://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-23.html
	//return (1 + ((hashedKey / max) % (max - 1)));
}

vector<Pair> Dictionary::Resize(float scale) {
	vector<Pair> temp;
	tableSize = (u32)(tableSize * scale);
	temp.resize(tableSize);

	// tableSize * 3 so we loop over every slot in the old table
	// everything else uses the new tableSize for calculation

	// divided by scale so we only loop over original table's size
	for (u32 i = 0; i < (u32)(tableSize / scale); ++i) {
		if (!table[i].key.empty() || !table[i].key.compare(deleted)) 
		{
			u32 toCopy = Hash1(table[i].key) % tableSize;

			// Loop (inside new table) until we find a non-duplicate space
			// same function as below but we don't need to check deleted
			// Collision detection (Double hashing)
			while (!temp[toCopy].key.empty()) {
				toCopy = Hash2(toCopy) % tableSize;
			}
			// Copy newly hashed of current value into the safe hash
			temp[toCopy].key = table[i].key;
			temp[toCopy].value = table[i].value;
		}
	}
	return temp;
}

Dictionary::Dictionary(u32 initialSize) {
	size = 0;
	tableSize = initialSize;  // Should be power of two for speed.
	//tableSize = (int)pow(2, 4);
	table.resize(tableSize);	// sets the initial values of each key to null

	//linearProbePrime = 7;
}

u32 Dictionary::Size() {
	return size;
}


// Searches for a key in the dictionary.
// With hash chaining/double hashing, this is O(n * hash())
bool Dictionary::Exists(string key) {
	u32 hashedKey = Hash1(key) % tableSize;

	for (u32 i = 0; i < (tableSize - 1); ++i) {
		if (table[hashedKey].key.empty())
			return false;
		else if (table[hashedKey].key.compare(key))
			return true;
		else
			hashedKey = ((hashedKey + (i * Hash2(hashedKey))) % tableSize);
	}
    return false;
}

// Return the value of a given key, if it exists.
int Dictionary::GetValue(string key) {
	u32 hashedKey = Hash1(key) % tableSize;	

	for (u32 i = 0; i < (tableSize - 1); ++i) {
		if (table[hashedKey].key.empty()) {
			printf("'%s' doesn't exist in Dictionary!\n", key.c_str());
            return -1; // Key doesn't exist
		}
		else if (table[hashedKey].key.compare(key) == 0)
			return table[hashedKey].value;
		else
			hashedKey = ((hashedKey + (i * Hash2(hashedKey))) % tableSize);
	}
    return -1;
}

// Add a Hashed {key, value} pair to the dictionary.
u32 Dictionary::Insert(string key, int value) {
	// GROW if Load Factor(a) is >= 0.5
	if (((float)size / (float)tableSize) >= 0.5f)
		table = Resize(2.0f);

	/*********************** INSERT *************************/
	u32 hashedKey = (Hash1(key) % tableSize);
	//u32 hashedKey = FindSlot(key);
	// Loop until we find a safe hash to write (Double Hashing)	

	for (u32 i = 0; i < (tableSize - 1); ++i) {
		if (!table[hashedKey].key.empty() ||				// Rehash if slot isn't empty
			table[hashedKey].key.compare(deleted) == 0)		// Rehash if slot isn't rewritable("deleted")
															//  * compare returns 0 if strings are equal
			hashedKey = ((hashedKey + (i * Hash2(hashedKey))) % tableSize);
		else
			break;
	}

	if (!table[hashedKey].key.compare(key))					// Check if Key already exists
	{		
		printf("'%s' already exists, updating value...\n", key.c_str());
		table[hashedKey].value = value;						// WARN: Extraneous functionality, should error out.
		return hashedKey;
	}
	else {													// Write into the safe hash
		table[hashedKey].key = key;
		table[hashedKey].value = value;
		size++;		
		return hashedKey;									// Return the successful hash
	}

}


u32 Dictionary::Delete(string key) {
	/* WARN: This doubles the hashing required if key not invalid
	if (!Exists(key)) {
		printf("Key: '%s' not found! Cannot delete.\n", key.c_str());
		return -1;
	} */

	// SHRINK (when 1/4 full)
	if ((tableSize > 16) && ((float)size <= ((float)tableSize / 4.0f))) {
		table = Resize(0.3f);	// shrink by thirds min size is 16
	}

	u32 hashedKey = Hash1(key) % tableSize;

	for (u32 i = 0; i < (tableSize - 1); ++i) {
		// This doesn't actually compare hashes, just compares strings within the hash table.
		// Is this a given with Pair based hash tables (*non-direct addressed)?
		if (table[hashedKey].key.empty()) {
			printf("'%s' does not exist in Dictionary!\n", key.c_str());
			return -1;	// WILL THIS ERROR?!
		}
		else if (table[hashedKey].key.compare(key) == 0) {
			table[hashedKey].key = deleted;
			table[hashedKey].value = NULL;
			size--;
			printf("Sucessfully deleted '%s'.\n", key.c_str());
			return hashedKey;
		}
		else {
			hashedKey = ((hashedKey + (i * Hash2(hashedKey))) % tableSize);
		}
	}
    return -1;
}
