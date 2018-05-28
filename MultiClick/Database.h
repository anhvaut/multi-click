#ifndef __DATABASE_H
#define __DATABASE_H

#include "HashTable.h"

class CDatabase
{

public:
	CDatabase(){
	}
	~CDatabase(){
	}

	void InitHashEV();
	void InitHashFV();
	void InitHashDV();
	void InitHashNV();
	void InitHashNauyV();
	void InitHashVV();
	void LoadDict2Hash(char *dictionaryIndex,HashTable *m_hashtable);
	void DestroyHash();
	int GetDemicalValue (CString str);
	CString ChangeStyle(CString wordmean);
	BOOL GetMeaning (CString dictionary,char *dictionaryIndex,CString wordmean);
	CString GetOffSet_Length(char *dictionaryIndex,CString wordmean);
	//int isWord_InDict(char *dictionaryIndex,CString wordmean);
	void chooseDictionary(int kindDictionary,CString wordmean);
	CString chooseDictionaryOnline(int kindDictionary,CString wordmean,CString &dict);
	
	BOOL GetMeaning2(CString dictionary,CString sOffLen);

	//online

	CString GetOffSet_LengthOnline(char *dictionary,CString wordmean, CString &offset);
	
	
};//end 
#endif
