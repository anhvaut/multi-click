/*--------------------------------------------------------------------------*\
 *                   -----===== HashTable =====-----
 *
 * Author: Tran The Vu & Huynh Thi Le Thanh
 * Date Create:   30/9/2005
 * IT Faculty - DaNang University of Technology .
 *
 *--------------------------------------------------------------------------
 * $Id: HashTable.c
\*--------------------------------------------------------------------------*/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hashtable.h"


static int isProbablePrime(long number);
static long calculateIdealNumOfBuckets(HashTable *hashTable);

HashTable *HashTableCreate(long numOfBuckets) {
    HashTable *hashTable;
    int i;

    assert(numOfBuckets > 0);

    hashTable = (HashTable *) malloc(sizeof(HashTable));
    if (hashTable == NULL)
        return NULL;

    hashTable->bucketArray = (KeyValuePair **)
                        malloc(numOfBuckets * sizeof(KeyValuePair *));
    if (hashTable->bucketArray == NULL) {
        free(hashTable);
        return NULL;
    }
    
    hashTable->numOfBuckets = numOfBuckets;
    hashTable->numOfElements = 0;

    for (i=0; i<numOfBuckets; i++)
        hashTable->bucketArray[i] = NULL;

    hashTable->idealRatio = 3.0;
    hashTable->lowerRehashThreshold = 0.0;
    hashTable->upperRehashThreshold = 15.0;

  //  hashTable->keycmp = pointercmp;
//    hashTable->valuecmp = pointercmp;
    hashTable->hashFunction = HashTableStringHashFunction;
    hashTable->keyDeallocator = NULL;
    hashTable->valueDeallocator = NULL;

    return hashTable;
}

void HashTableDestroy(HashTable *hashTable) {
    int i;

    for (i=0; i<hashTable->numOfBuckets; i++) {
        KeyValuePair *pair = hashTable->bucketArray[i];
        while (pair != NULL) {
            KeyValuePair *nextPair = pair->next;
//            if (hashTable->keyDeallocator != NULL)
//                hashTable->keyDeallocator((void *) pair->key);
 //           if (hashTable->valueDeallocator != NULL)
 //               hashTable->valueDeallocator(pair->value);
            free(pair);
            pair = nextPair;
        }
    }

    free(hashTable->bucketArray);
    free(hashTable);
}

int HashTablePut(HashTable *hashTable, CString key, CString value) {
    long hashValue;
    KeyValuePair *pair;

//    assert(key != NULL);
//    assert(value != NULL);

    hashValue = hashTable->hashFunction(key) % hashTable->numOfBuckets;
    pair = hashTable->bucketArray[hashValue];

    while (pair != NULL && key.Trim().CompareNoCase( pair->key) != 0)
        pair = pair->next;

    if (pair) {
        if (pair->key != key) {
           // if (hashTable->keyDeallocator != NULL)
            //    hashTable->keyDeallocator((void *) pair->key);
            pair->key = key;
        }
        if (pair->value != value) {
            //if (hashTable->valueDeallocator != NULL)
            //    hashTable->valueDeallocator(pair->value);
            pair->value = value;
        }
    }
    else {
        KeyValuePair *newPair = new KeyValuePair;
        if (newPair == NULL) {
            return -1;
        }
        else {
            newPair->key = key;
            newPair->value = value;
            newPair->next = hashTable->bucketArray[hashValue];
            hashTable->bucketArray[hashValue] = newPair;
            hashTable->numOfElements++;

            if (hashTable->upperRehashThreshold > hashTable->idealRatio) {
                float elementToBucketRatio = (float) hashTable->numOfElements /
                                             (float) hashTable->numOfBuckets;
                if (elementToBucketRatio > hashTable->upperRehashThreshold)
                    HashTableRehash(hashTable, 0);
            }
        }
    }

    return 0;
}

CString HashTableGet(const HashTable *hashTable, CString key) {
    long hashValue = hashTable->hashFunction(key) % hashTable->numOfBuckets;
    KeyValuePair *pair = hashTable->bucketArray[hashValue];
	//MessageBox(NULL,(LPCWSTR)pair->key,_T("ok"),MB_OK);

    while (pair != NULL && key.Trim().CompareNoCase( pair->key) != 0)
        pair = pair->next;

    return (pair == NULL)? _T("") : pair->value;
}


int HashTableIsEmpty(const HashTable *hashTable) {
    return (hashTable->numOfElements == 0);
}



long HashTableSize(const HashTable *hashTable) {
    return hashTable->numOfElements;
}


long HashTableGetNumBuckets(const HashTable *hashTable) {
    return hashTable->numOfBuckets;
}

void HashTableRehash(HashTable *hashTable, long numOfBuckets) {
    KeyValuePair **newBucketArray;
    int i;

    assert(numOfBuckets >= 0);
    if (numOfBuckets == 0)
        numOfBuckets = calculateIdealNumOfBuckets(hashTable);

    if (numOfBuckets == hashTable->numOfBuckets)
        return; /* already the right size! */

    newBucketArray = (KeyValuePair **)
                                malloc(numOfBuckets * sizeof(KeyValuePair *));
    if (newBucketArray == NULL) {
        /* Couldn't allocate memory for the new array.  This isn't a fatal
         * error; we just can't perform the rehash. */
        return;
    }

    for (i=0; i<numOfBuckets; i++)
        newBucketArray[i] = NULL;

    for (i=0; i<hashTable->numOfBuckets; i++) {
        KeyValuePair *pair = hashTable->bucketArray[i];
        while (pair != NULL) {
            KeyValuePair *nextPair = pair->next;
            long hashValue = hashTable->hashFunction(pair->key) % numOfBuckets;
            pair->next = newBucketArray[hashValue];
            newBucketArray[hashValue] = pair;
            pair = nextPair;
        }
    }

    free(hashTable->bucketArray);
    hashTable->bucketArray = newBucketArray;
    hashTable->numOfBuckets = numOfBuckets;
}



void HashTableSetIdealRatio(HashTable *hashTable, float idealRatio,
        float lowerRehashThreshold, float upperRehashThreshold) {
    assert(idealRatio > 0.0);
    assert(lowerRehashThreshold < idealRatio);
    assert(upperRehashThreshold == 0.0 || upperRehashThreshold > idealRatio);

    hashTable->idealRatio = idealRatio;
    hashTable->lowerRehashThreshold = lowerRehashThreshold;
    hashTable->upperRehashThreshold = upperRehashThreshold;
}

void HashTableSetDeallocationFunctions(HashTable *hashTable,
        void (*keyDeallocator)(void *key),
        void (*valueDeallocator)(CString value)) {
//    hashTable->keyDeallocator = keyDeallocator;
 //   hashTable->valueDeallocator = valueDeallocator;
}



unsigned long HashTableStringHashFunction(CString key) {
  
	key=key.Trim();
	key=key.MakeLower();

    unsigned long hashValue = 0;
    int i;

		for (i=0; i<key.GetLength(); i++)
			hashValue = hashValue * 37 + key[i];

    return hashValue;
}



static int isProbablePrime(long oddNumber) {
    long i;

    for (i=3; i<51; i+=2)
        if (oddNumber == i)
            return 1;
        else if (oddNumber%i == 0)
            return 0;

    return 1; /* maybe */
}

static long calculateIdealNumOfBuckets(HashTable *hashTable) {
    long idealNumOfBuckets = hashTable->numOfElements / hashTable->idealRatio;
    if (idealNumOfBuckets < 5)
        idealNumOfBuckets = 5;
    else
        idealNumOfBuckets |= 0x01; /* make it an odd number */
    while (!isProbablePrime(idealNumOfBuckets))
        idealNumOfBuckets += 2;

    return idealNumOfBuckets;
}

