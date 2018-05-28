#include "stdafx.h"
#include "common.h"
/*
* La^'y ddu+o+`ng da^~n cu?a thu+ mu.c hie^.n ha`nh
* Tra? ve^` kie^?u String
*/
CString CurrentDirectory(){
	   CString currentDirectory("");
		TCHAR path[MAX_PATH];
		GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
		//tra? ve^` te^n va` du+o+`ng da^~n lu+u trong bie^'n path
		// vi' du. : D:\multiclick\multiclick.exe

		TCHAR *p = _tcsrchr(path, _TEXT('\\'));
		_tcscpy(p+1, _TEXT(""));						
		//loai bo? ten u+'ng du.ng
		// co`n la.i : D:\multiclick\ 
		
		currentDirectory.Format(path);
		return currentDirectory;
}

CString ImagesPath(){
	   CString ImageP("");
		TCHAR path[MAX_PATH];
		GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	

		TCHAR *p = _tcsrchr(path, _TEXT('\\'));
		_tcscpy(p+1, _TEXT("Images\\"));						
	
		
		ImageP.Format(path);
		return ImageP;
}
CString DatabasesPath(){
	   CString DatabaseP("");
		TCHAR path[MAX_PATH];
		GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	

		TCHAR *p = _tcsrchr(path, _TEXT('\\'));
		_tcscpy(p+1, _TEXT("Databases\\"));						
	
		
		DatabaseP.Format(path);
		return DatabaseP;
}
/*
* Duong dan cua file index
*/
/*
char* IndexPath(char *dictionaryIndex){
	char IndexP[256];
	GetModuleFileNameA( GetModuleHandle( NULL ), IndexP, sizeof(IndexP) );
	char *p;
	p=strrchr(IndexP,'\\');		
	strcpy(p+1,dictionaryIndex);
	return IndexP;
}
*/

