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

#ifndef _HASHTABLE_H
#define _HASHTABLE_H



typedef struct KeyValuePair_struct {
    CString key;
    CString value;
    struct KeyValuePair_struct *next;
} KeyValuePair;

typedef struct {
    long numOfBuckets;
    long numOfElements;
    KeyValuePair **bucketArray;
    float idealRatio, lowerRehashThreshold, upperRehashThreshold;
    unsigned long (*hashFunction)(CString key);
    void (*keyDeallocator)(CString key);
    void (*valueDeallocator)(CString value);
} HashTable;

HashTable *HashTableCreate(long numOfBuckets);

void HashTableDestroy(HashTable *hashTable);

int HashTablePut(HashTable *hashTable, CString key, CString value);

CString HashTableGet(const HashTable *hashTable, CString key);

void HashTableRemove(HashTable *hashTable, CString key);
void HashTableRemoveAll(HashTable *hashTable);



int HashTableIsEmpty(const HashTable *hashTable);

long HashTableSize(const HashTable *hashTable);
long HashTableGetNumBuckets(const HashTable *hashTable);
void HashTableRehash(HashTable *hashTable, long numOfBuckets);

void HashTableSetIdealRatio(HashTable *hashTable, float idealRatio,
                            float lowerRehashThreshold,
                            float upperRehashThreshold);



void HashTableSetDeallocationFunctions(HashTable *hashTable,
                                       void (*keyDeallocator)(CString key),
                                       void (*valueDeallocator)(CString value));


unsigned long HashTableStringHashFunction(CString key);

#endif /* _HASHTABLE_H */
