#include "stdAfx.h"
#include "Database.h"
#include "Math.h"
#include "StdioFileEx.h"
#include "utf8.h"
#include "common.h"


HashTable *m_hashtableEV;
HashTable *m_hashtableVE;


HashTable *m_hashtableFV;
HashTable *m_hashtableVF;


HashTable *m_hashtableDV;
HashTable *m_hashtableVD;


HashTable *m_hashtableNV;  //nga viet
HashTable *m_hashtableNauyV;
HashTable *m_hashtableVV;

/*
* InitHash
*/
void CDatabase::InitHashEV(){
	//tieng anh viet 110.000 tu
	// chon B=109987
	if(m_hashtableEV==NULL){
		m_hashtableEV=HashTableCreate(109987);
		LoadDict2Hash("anhviet.index",m_hashtableEV);
	}

	//tieng viet anh 30.000 tu 
	//chon B=29989 : so nguyen to
	if(m_hashtableVE==NULL){
		m_hashtableVE=HashTableCreate(29989);
		LoadDict2Hash("vietanh.index",m_hashtableVE);
	}

	
	
	

}

void CDatabase::InitHashFV(){

	//tieng phap viet 48.000 tu 
	//chon B=47981 : so nguyen to
	if(m_hashtableFV==NULL){
		m_hashtableFV=HashTableCreate(47981);
		LoadDict2Hash("phapviet.index",m_hashtableFV);
	}

	//tieng viet phap 39.000 tu 
	//chon B=38993 : so nguyen to
	if(m_hashtableVF==NULL){
		m_hashtableVF=HashTableCreate(38993);
		LoadDict2Hash("vietphap.index",m_hashtableVF);
	}
	
	
	

}

void CDatabase::InitHashNV(){

	//tieng Nga Viet 40.000 tu 
	//chon B=39989 : so nguyen to
	if(m_hashtableNV==NULL){
		m_hashtableNV=HashTableCreate(39989);
		LoadDict2Hash("ngaviet.index",m_hashtableNV);
	}

}

void CDatabase::InitHashNauyV(){

	
	//tieng Nauy Viet 20.000 tu 
	//chon B=19997 : so nguyen to
	if(m_hashtableNauyV==NULL){
		m_hashtableNauyV=HashTableCreate(19997);
		LoadDict2Hash("nauyviet.index",m_hashtableNauyV);
	}

}
void CDatabase::InitHashVV(){

	
	//tieng Nauy Viet 30.000 tu 
	//chon B=19997 : so nguyen to
	if(m_hashtableVV==NULL){
		m_hashtableVV=HashTableCreate(29989);
		LoadDict2Hash("vv.index",m_hashtableVV);
	}

}

void CDatabase::InitHashDV(){

	//tieng ducviet 45.000 tu 
	//chon B=44987 : so nguyen to

	if(m_hashtableDV==NULL){
		m_hashtableDV=HashTableCreate(44987);
		LoadDict2Hash("ducviet.index",m_hashtableDV);
	}

	//tieng vietduc 12.000 tu 
	//chon B=11987 : so nguyen to
	if(m_hashtableVD==NULL){
		m_hashtableVD=HashTableCreate(11987);
		LoadDict2Hash("vietduc.index",m_hashtableVD);
	}
	
	
	

}

void CDatabase::DestroyHash(){
	if(m_hashtableEV!=NULL)
		HashTableDestroy(m_hashtableEV);
	if(m_hashtableVE!=NULL)
		HashTableDestroy(m_hashtableVE);

	if(m_hashtableFV!=NULL)
		HashTableDestroy(m_hashtableFV);
	if(m_hashtableVF!=NULL)
		HashTableDestroy(m_hashtableVF);

	
	if(m_hashtableDV!=NULL)
		HashTableDestroy(m_hashtableDV);
	if(m_hashtableVD!=NULL)
		HashTableDestroy(m_hashtableVD);

	if(m_hashtableNV!=NULL)
		HashTableDestroy(m_hashtableNV);
	if(m_hashtableNauyV!=NULL)
		HashTableDestroy(m_hashtableNauyV);

	if(m_hashtableVV!=NULL)
		HashTableDestroy(m_hashtableVV);

}
/*
*  LoadDict2Hash
*/
void CDatabase::LoadDict2Hash(char *dictionaryIndex,HashTable *m_hashtable){

	char FullPath[256];
	GetModuleFileNameA( GetModuleHandle( NULL ), FullPath, sizeof(FullPath) );
	char *p;
	p=strrchr(FullPath,'\\');
	
	strcpy(p+1,dictionaryIndex);

		CString sOffLen("");
		FILE *inFile;
		
	inFile = fopen (FullPath,"r");
	

	if (inFile == NULL){

		MessageBox(NULL,_TEXT("File .index not Found! wrong path or name1???"),_TEXT("Error!"),MB_OK);
	}else {

		char * line;

		char lineBuf[100];

		line = (char *) lineBuf;

		CString word = "";

		CString sWord = "";

		CString sData = "";

		while (!feof(inFile)){

			fgets(line,99,inFile);
			
		

			if (strlen(line)>=2){

					word = line;

					int pos = word.Find(_TEXT("\t"),0);

					sWord = word.Left(pos);

					sData = word.Mid(pos+1,word.GetLength()-pos-1);

					if (sData.Find(_TEXT("\n"),0) > 0){

						sData = sData.Left(sData.GetLength()-1); 
					}

					//strHtml+=sWord+"<br>";
					//wchar_t unicode_string[256];
					//sWord=Convert_String(sWord,unicode_string);
					
					  char destination[256];
					  wchar_t unicode_string[256];
					
					   int i=indexOf(destination,'\t');
					   strncpy1(destination, line,pos);
					  Utf8_Unicode((BYTE*)destination,unicode_string);
					   CString myWord;
					   myWord.Format(unicode_string);
				
					   HashTablePut(m_hashtable,myWord,sData);

			} //end if strlen(line)>=2

		} //end else
		
	}//end else

	fclose(inFile);


}

/*
* chuyen sang co so 10
*/

extern CString currentDict;//luu loai tu dien chua tu can tra
CString saveWord;

int CDatabase::GetDemicalValue (CString str){
	  CString base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

			int decValue = 0;

			int len = str.GetLength();

			for (int i = 0; i<len; i++){

				int pos = base64.Find(str.GetAt(i),0);

				decValue += (int)pow(64,len-i-1)*pos;

		}

		return decValue;

}

CString CDatabase::ChangeStyle(CString wordmean){
  
   CString meaning = wordmean;
   CString t (" ");
   CString tt =_T("-")+t;
   CString pn=_T("#")+t;
   meaning = meaning.Right(meaning.GetLength()-1);

   int pos = meaning.Find(_T("\n"),1);

   meaning.Insert(pos,_T("</b>"));

   //meaning = _T("<b>") + meaning;

   meaning.Replace(_T("\n"),_T("</b><br>"));

  
   meaning.Replace(_T("="),_T("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src='"+ImagesPath()+"ball.xgt' width='6' height='6'><font color=\'#0000ff\'>&nbsp;"));
   meaning.Replace(_T("\n"),_T("</font>"));
	 
  
   meaning.Replace(pn,_T("<img src='"+ImagesPath()+"biztecht.xgt' width='10' height='10'><font color=\"#cc00hh\"><b>&nbsp;"));
   meaning.Replace(_T("\n"),_T("</b></font>"));



   meaning.Replace(_T("+"),_T("<font color=\'#ff00hh\'><br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"));
   meaning.Replace(_T("\n"),_T("</font>"));

   meaning.Replace(_T("\n"),_T("</font>"));
   
   meaning.Replace(_T("*"),_T("<img src='"+ImagesPath()+"biztecht.xgt' width='10' height='10'><font color=\"#cc00hh\"><b>"));
   meaning.Replace(_T("\n"),_T("</b></font>"));
	
  
   meaning.Replace(tt,_T("&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src='"+ImagesPath()+"narrowedgediamond.xgt' width='9' height='9'><font color=\'#666666\'>&nbsp;"));
   meaning.Replace(_T("\n"),_T("</font>"));


   return meaning;

}
/*
* La^'y nghi~a cu?a tu+` trong file .dict
* dictionary truye^`n o+? dda^y co' pha^`n dduo^i
* vi du : GetMeaning("anhviet.dict","anhviet.index","wonderful")
*/
BOOL CDatabase::GetMeaning(CString dictionary,char *dictionaryIndex,CString wordmean){ 

	
	CFile f;
		
	CString meaning="";

		
		
		if (f.Open(DatabasesPath()+dictionary,CFile::modeRead) == FALSE) {

				MessageBox(NULL,_TEXT("File .dict not Found! wrong path or name???"),_TEXT("Error!"),MB_OK);	 

		} else {

		     CString sOffLen;

		     sOffLen=GetOffSet_Length(dictionaryIndex,wordmean);

			 if(sOffLen.Compare(_T(""))){//new sOffLen ko bang ""
			  

				int pos = sOffLen.Find(_TEXT("\t"),0);

				CString sOff = sOffLen.Left(pos);
				CString sLen = sOffLen.Right(sOffLen.GetLength()-pos-1);

				int iOff = GetDemicalValue(sOff);
				int iLength = GetDemicalValue(sLen);
				int temp = f.Seek(iOff,CFile::begin);

				char buff[64];

					DWORD dwRead;

					do {

						if (iLength>=64)  dwRead = f.Read(buff,64);
						else  dwRead = f.Read(buff,iLength);
						

						iLength -= dwRead;

						CString stemp = buff;

						stemp = stemp.Left(dwRead);

						meaning += stemp;

					}while (iLength>0);

				f.Close();
				}

		}//end else

		if(meaning.Compare(_T(""))==0){
			meaning="<b><font color='red'>Not found in dictionary</font></b> ";
		}else{
			meaning = ChangeStyle(meaning);
		}
		

		CString strHtml("");
	

		strHtml += "<html>\n<head>\n";

		strHtml +="<meta http-equiv=\"Content-Type\" content=\"TEXT/html; charset=utf-8\">\n";
		strHtml+="<style type=\"text/css\">\n";
		strHtml+="BODY { MARGIN: 0px; SCROLLBAR-BASE-COLOR:#d2e4fc; }\n";
			/*
			A{ FONT-WEIGHT: bold }
			A { FONT-SIZE: 11px; COLOR: #304c6c; FONT-FAMILY: Verdana; TEXT-DECORATION: none 
			}
			A:link { FONT-SIZE: 11px; COLOR: blue; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			none } 
			A:visited { FONT-SIZE: 11px; COLOR: #304c6c; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			none }
			A:active { FONT-SIZE: 11px; COLOR: #304c6c; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			none } 
			A:hover { FONT-SIZE: 11px; COLOR: #e9800f; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			underline }
			*/
		strHtml+="</style>";

		strHtml +="</head>\n<body leftmargin='10' topmargin='0' background='"+ImagesPath()+"mainbackground.gif'>\n";

		//strHtml +="<font color='red'><b>"+wordmean+ "</b></font><br>";
		//char* st=CurrentDirectory1();
		//char st[256];
		//CurrentDirectory2(st);
		//CString vu("");
	//	vu.Format(_T("%s"),st);
	//	strHtml+="abc"+vu+"abcd <br>";
		strHtml += meaning + "\n</body>\n</html>";
	
	

		CStdioFileEx f2;

			if (f2.Open(CurrentDirectory()+"temp.htm",CFile::modeCreate | CFile::modeWrite) == FALSE){

				MessageBox(NULL,_TEXT("Cannot write meaning file!"),_TEXT("Error!"),MB_OK);

				return 0;
		}

	    f2.WriteString(strHtml);
		f2.Close();
		


		return 1;

}


BOOL CDatabase::GetMeaning2(CString dictionary,CString sOffLen){ 

	
	CFile f;
		
	CString meaning="";

		
		
		if (f.Open(DatabasesPath()+dictionary,CFile::modeRead) == FALSE) {

				MessageBox(NULL,_TEXT("File .dict not Found! wrong path or name???"),_TEXT("Error!"),MB_OK);	 

		} else {

		

		    
			 if(sOffLen.Compare(_T(""))){//new sOffLen ko bang ""
			  

				int pos = sOffLen.Find(_TEXT("\t"),0);

				CString sOff = sOffLen.Left(pos);
				CString sLen = sOffLen.Right(sOffLen.GetLength()-pos-1);

				int iOff = GetDemicalValue(sOff);
				int iLength = GetDemicalValue(sLen);
				int temp = f.Seek(iOff,CFile::begin);

				char buff[64];

					DWORD dwRead;

					do {

						if (iLength>=64)  dwRead = f.Read(buff,64);
						else  dwRead = f.Read(buff,iLength);
						

						iLength -= dwRead;

						CString stemp = buff;

						stemp = stemp.Left(dwRead);

						meaning += stemp;

					}while (iLength>0);

				f.Close();
				}

		}//end else

		if(meaning.Compare(_T(""))==0){
			if(currentDict==_T("anhviet"))
				meaning=saveWord +":<b><font color='red'>Not found in dictionary</font></b> ";
			else 
				meaning="<b><font color='red'>Not found in dictionary</font></b> ";
		}else{
			meaning = ChangeStyle(meaning);
		}
		

		CString strHtml("");
	

		strHtml += "<html>\n<head>\n";

		strHtml +="<meta http-equiv=\"Content-Type\" content=\"TEXT/html; charset=utf-8\">\n";
		strHtml+="<style type=\"text/css\">\n";
		strHtml+="BODY { MARGIN: 0px; SCROLLBAR-BASE-COLOR:#d2e4fc; }\n";
			/*
			A{ FONT-WEIGHT: bold }
			A { FONT-SIZE: 11px; COLOR: #304c6c; FONT-FAMILY: Verdana; TEXT-DECORATION: none 
			}
			A:link { FONT-SIZE: 11px; COLOR: blue; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			none } 
			A:visited { FONT-SIZE: 11px; COLOR: #304c6c; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			none }
			A:active { FONT-SIZE: 11px; COLOR: #304c6c; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			none } 
			A:hover { FONT-SIZE: 11px; COLOR: #e9800f; FONT-FAMILY: Verdana; TEXT-DECORATION: 
			underline }
			*/
		strHtml+="</style>";

		strHtml +="</head>\n<body leftmargin='10' topmargin='0' background='"+ImagesPath()+"mainbackground.gif'>\n";

		//strHtml +="<font color='red'><b>"+wordmean+ "</b></font><br>";
		//char* st=CurrentDirectory1();
		//char st[256];
		//CurrentDirectory2(st);
		//CString vu("");
	//	vu.Format(_T("%s"),st);
	//	strHtml+="abc"+vu+"abcd <br>";
		strHtml += meaning + "\n</body>\n</html>";
	
	

		CStdioFileEx f2;

			if (f2.Open(CurrentDirectory()+"temp.htm",CFile::modeCreate | CFile::modeWrite) == FALSE){

				MessageBox(NULL,_TEXT("Cannot write meaning file!"),_TEXT("Error!"),MB_OK);

				return 0;
		}

	    f2.WriteString(strHtml);
		f2.Close();
		


		return 1;

}

/*
*  Lay vi tri va do dai cua tu o dang chuoi trong file .index
*  Dict: dict o+? dda^y truye^`n co' pha^`n dduo^i
*  vi' du.: GetOffSet_Length("anhviet.index","ok")
*/
CString CDatabase::GetOffSet_Length(char *dictionaryIndex,CString wordmean){
	saveWord=wordmean;
	char FullPath[256];
	GetModuleFileNameA( GetModuleHandle( NULL ), FullPath, sizeof(FullPath) );
	char *p;
	p=strrchr(FullPath,'\\');
	
	strcpy(p+1,dictionaryIndex);

		CString sOffLen("");
		FILE *inFile;
		
	inFile = fopen (FullPath,"r");
	

	if (inFile == NULL){

		MessageBox(NULL,_TEXT("File .index not Found! wrong path or name1???"),_TEXT("Error!"),MB_OK);
	}else {

		char * line;

		char lineBuf[100];

		line = (char *) lineBuf;

		CString word = "";

		CString sWord = "";

		CString sData = "";

		while (!feof(inFile)){

			fgets(line,99,inFile);
			
		

			if (strlen(line)>=2){

					word = line;

					int pos = word.Find(_TEXT("\t"),0);

					sWord = word.Left(pos);

					sData = word.Mid(pos+1,word.GetLength()-pos-1);

					if (sData.Find(_TEXT("\n"),0) > 0){

						sData = sData.Left(sData.GetLength()-1); 
					}

					//strHtml+=sWord+"<br>";
					//wchar_t unicode_string[256];
					//sWord=Convert_String(sWord,unicode_string);
					
					  char destination[256];
					  wchar_t unicode_string[256];
					
					   int i=indexOf(destination,'\t');
					   strncpy1(destination, line,pos);
					  Utf8_Unicode((BYTE*)destination,unicode_string);
					   CString myWord;
					   myWord.Format(unicode_string);
					  
					//if(sWord.CompareNoCase(wordmean.Trim())==0) ;
					if(myWord.CompareNoCase(wordmean.Trim())==0){
						//MessageBox(NULL,_T("ok"),_T("ok"),MB_OK);
						sOffLen=sData;
						break;
					}
					//if(myWord.GetAt(0)>wordmean.GetAt(0)) break;
				

			} //end if strlen(line)>=2

		} //end else
		
	}//end else

	fclose(inFile);

	
	

	return sOffLen;
}

/*
* Coi thu 1 tu co thuoc tu dien khong
  */
int isWord_InDict(char *dictionaryIndex,CString wordmean){
	char FullPath[256];
	GetModuleFileNameA( GetModuleHandle( NULL ), FullPath, sizeof(FullPath) );
	char *p;
	p=strrchr(FullPath,'\\');		
	strcpy(p+1,dictionaryIndex);

	FILE *inFile;

	inFile = fopen (FullPath,"r");
	

	if (inFile == NULL){

		MessageBox(NULL,_TEXT("File .index not Found! wrong path or name???"),_TEXT("Error!"),MB_OK);
	}else {

		char * line;

		char lineBuf[100];

		line = (char *) lineBuf;

		CString word = "";
		CString sWord = "";



		while (!feof(inFile)){

			fgets(line,99,inFile);
		

			if (strlen(line)>=2){

					word = line;

					int pos = word.Find(_TEXT("\t"),0);

					sWord = word.Left(pos);

				

				
					   char destination[256];
					   wchar_t unicode_string[256];
					
					   int i=indexOf(destination,'\t');
					   strncpy1(destination, line,pos);
					  Utf8_Unicode((BYTE*)destination,unicode_string);
					   CString myWord;
					   myWord.Format(unicode_string);
					
					 if(myWord.CompareNoCase(wordmean.Trim())==0){
						return 1;
					}

			} //end if strlen(line)>=2

		} //end else
		
	}//end else

	fclose(inFile);

	return 0;
}


///*****************
	//kindDictionary=0 : bo^. tu+. ddie^?n lie^n quan dde^'n tie^'ng vie^.t va` english
	//			    =1 : tie^'ng vie^.t va` tie^'ng pha'p
	//			    =2 : tie^'ng vie^.t va` tie^'ng ddu+'c
	//			    =3 : tie^'ng vie^.t va` tie^'ng tie^'ng vie^.t
	//				=4 : tie^'ng vie^.t va` tie^'ng Nga
	//				=5 : tie^'ng vie^.t va` tie^'ng Na uy
	///*****************

void CDatabase::chooseDictionary(int kindDictionary,CString wordmean){

	if(kindDictionary==0){
		CString sOffLen=HashTableGet(m_hashtableVE,wordmean);
		if(sOffLen!=_T("")){
			currentDict="vietanh";
			GetMeaning2("vietanh.dict",sOffLen);
		}
		else{ 
			//wordmean=wordmean.MakeLower();
			sOffLen=HashTableGet(m_hashtableEV,wordmean);
			currentDict="anhviet";
			GetMeaning2("anhviet.dict",sOffLen);
			
			
		}
	}
	else if(kindDictionary==1){
		CString sOffLen=HashTableGet(m_hashtableVF,wordmean);
		if(sOffLen!=_T("")){
			currentDict="vietphap";
			GetMeaning2("vietphap.dict",sOffLen);
			
		}
		else{ 

			sOffLen=HashTableGet(m_hashtableFV,wordmean);
			currentDict="phapviet";
			GetMeaning2("phapviet.dict",sOffLen);
			
			
		}
	}
	else if(kindDictionary==2){
		CString sOffLen=HashTableGet(m_hashtableVD,wordmean);
		if(sOffLen!=_T("")){
			currentDict="vietduc";
			GetMeaning2("vietduc.dict",sOffLen);
		
		}
		else{ 
			sOffLen=HashTableGet(m_hashtableDV,wordmean);
			currentDict="ducviet";
			GetMeaning2("ducviet.dict",sOffLen);
			
			
		}
		
	}
	else if(kindDictionary==3){
		//if(isWord_InDict("vv.index",wordmean))
			CString sOffLen=HashTableGet(m_hashtableVV,wordmean);
			GetMeaning2("vv.dict",sOffLen);
			currentDict="vietviet";
		//else 
		//	GetMeaning("anhviet68K.dict","anhviet68K.index",wordmean);
	}
	else if(kindDictionary==4){
		//if(isWord_InDict("ngaviet.index",wordmean))
			CString sOffLen=HashTableGet(m_hashtableNV,wordmean);
			GetMeaning2("ngaviet.dict",sOffLen);
			currentDict="ngaviet";
		//else 
		//	GetMeaning("anhviet68K.dict","anhviet68K.index",wordmean);
	}
	else if(kindDictionary==5){
		//if(isWord_InDict("nv.index",wordmean))
			CString sOffLen=HashTableGet(m_hashtableNauyV,wordmean);
			GetMeaning2("nv.dict",sOffLen);
			currentDict="nauyviet";
		//else 
		//	GetMeaning("anhviet68K.dict","anhviet68K.index",wordmean);
	}
}

/*
*  Cho ti`nh huo^'ng online
*  
*/
CString GetW(char *dictionaryIndex,CString wordmean){
	char FullPath[256];
	GetModuleFileNameA( GetModuleHandle( NULL ), FullPath, sizeof(FullPath) );
	char *p;
	p=strrchr(FullPath,'\\');		
	strcpy(p+1,dictionaryIndex);

		CString sW("");
		FILE *inFile;
		
	inFile = fopen (FullPath,"r");
	

	if (inFile == NULL){

		MessageBox(NULL,_TEXT("File .index not Found! wrong path or name1???"),_TEXT("Error!"),MB_OK);
	}else {

		char * line;

		char lineBuf[100];

		line = (char *) lineBuf;

		CString word = "";

		CString sWord = "";


		while (!feof(inFile)){

			fgets(line,99,inFile);
			
		

			if (strlen(line)>=2){

					word = line;

					int pos = word.Find(_TEXT("\t"),0);

					sWord = word.Left(pos);

				

					

					
					  char destination[256];
					  wchar_t unicode_string[256];
					
					   int i=indexOf(destination,'\t');
					   strncpy1(destination, line,pos);
					  Utf8_Unicode((BYTE*)destination,unicode_string);
					   CString myWord;
					   myWord.Format(unicode_string);
					  
					//if(sWord.CompareNoCase(wordmean.Trim())==0) ;
					if(myWord.CompareNoCase(wordmean.Trim())==0){
						//MessageBox(NULL,_T("ok"),_T("ok"),MB_OK);
						sW=sWord;
						break;
					}

			} //end if strlen(line)>=2

		} //end else
		
	}//end else

	fclose(inFile);

	
	

	return sW;
}


//////////////////////

CString CDatabase::GetOffSet_LengthOnline(char *dictionaryIndex,CString wordmean,CString &offset){
	char FullPath[256];
	GetModuleFileNameA( GetModuleHandle( NULL ), FullPath, sizeof(FullPath) );
	char *p;
	p=strrchr(FullPath,'\\');		
	strcpy(p+1,dictionaryIndex);

		CString sOffLen("");
		FILE *inFile;
		
	inFile = fopen (FullPath,"r");
	

	if (inFile == NULL){

		MessageBox(NULL,_TEXT("File .index not Found! wrong path or name1???"),_TEXT("Error!"),MB_OK);
	}else {

		char * line;

		char lineBuf[100];

		line = (char *) lineBuf;

		CString word = "";

		CString sWord = "";

		CString sData = "";

		while (!feof(inFile)){

			fgets(line,99,inFile);
			
		

			if (strlen(line)>=2){

					word = line;

					int pos = word.Find(_TEXT("\t"),0);

					sWord = word.Left(pos);

					sData = word.Mid(pos+1,word.GetLength()-pos-1);

					if (sData.Find(_TEXT("\n"),0) > 0){

						sData = sData.Left(sData.GetLength()-1); 
					}

					//strHtml+=sWord+"<br>";
					//wchar_t unicode_string[256];
					//sWord=Convert_String(sWord,unicode_string);
					
					  char destination[256];
					  wchar_t unicode_string[256];
					
					   int i=indexOf(destination,'\t');
					   strncpy1(destination, line,pos);
					  Utf8_Unicode((BYTE*)destination,unicode_string);
					   CString myWord;
					   myWord.Format(unicode_string);
					  
					//if(sWord.CompareNoCase(wordmean.Trim())==0) ;
					if(myWord.CompareNoCase(wordmean.Trim())==0){
						//MessageBox(NULL,_T("ok"),_T("ok"),MB_OK);
						sOffLen=sData;
						break;
					}

			} //end if strlen(line)>=2

		} //end else
		
	}//end else

	fclose(inFile);

	
	int pos = sOffLen.Find(_TEXT("\t"),0);

	offset= sOffLen.Left(pos);
	CString sLen = sOffLen.Right(sOffLen.GetLength()-pos-1);

	return sLen;
}


CString CDatabase::chooseDictionaryOnline(int kindDictionary,CString wordmean,CString &dict){



	CString sLen("");
	CString sOff("");

	if(kindDictionary==0){
		sLen=GetOffSet_LengthOnline("vietanh.index",wordmean,sOff);
		if(!sLen.Compare(_T(""))){
			sLen=GetOffSet_LengthOnline("anhviet.index",wordmean,sOff);
			dict="anhviet";
		}else{
			dict="vietanh";
		}
	}
	else if(kindDictionary==1){
		sLen=GetOffSet_LengthOnline("phapviet.index",wordmean,sOff);
		if(!sLen.Compare(_T(""))){
			sLen=GetOffSet_LengthOnline("vietphap.index",wordmean,sOff);
			dict="vietphap";
		}else{
			dict="phapviet";
		}
	}
	else if(kindDictionary==2){
	
		sLen=GetOffSet_LengthOnline("vietduc.index",wordmean,sOff);
		if(!sLen.Compare(_T(""))){
			sLen=GetOffSet_LengthOnline("ducviet.index",wordmean,sOff);
			dict="ducviet";
		}else{
			dict="vietduc";
		}
	}
	else if(kindDictionary==3){
			sLen=GetOffSet_LengthOnline("vv.index",wordmean,sOff);
			dict="vv";
		
	}
	else if(kindDictionary==4){
		sLen=GetOffSet_LengthOnline("ngaviet.index",wordmean,sOff);
		dict="ngaviet";
	}
	else if(kindDictionary==5){
		sLen=GetOffSet_LengthOnline("nv.index",wordmean,sOff);
		dict="nv";
		
	}
	CString arg="leng="+sLen+"&dict="+dict+"&off="+sOff;
	return arg;
}

//////

