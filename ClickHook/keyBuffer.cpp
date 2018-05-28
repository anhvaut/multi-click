#include "KeyBuffer.h"
#include "ClickHook.h"
#include "..\MultiClick\typedef.h"
#include "codetable.h"


UINT VK_BACK_SCAN;
UINT VK_PAUSE_SCAN;
extern	BOOL   isInitOK;
extern  int	typeOfCharset;
extern int  index;
extern	int isVietNamese;
extern	int typing;
extern	int switchKey;
extern	int uClipboard;
extern	int notFreeMarking;

	
int oldCharset=-1;
DWORD indexTable[256];
unsigned char _8bitWovel1[12][6];
unsigned char _8bitDouble1[8];
unsigned char _8bitBreve1[6];
DWORD L_16bit[256];
DWORD H_16bit[256];

unsigned char  States[256],oldChar,oldPrevChar;
CKeyBuffer ckBuffer;
unsigned char VIQRTone[] = {'\'', '`', '?', '~', '.'};
unsigned char telexToneMark[]={'s', 'f', 'r', 'x', 'j'};

unsigned char telexBreveMark[]={'w','W'};
unsigned char telexDoubleMark[]={'d', 'D', 'e', 'E', 'a', 'A', 'o', 'O', 'u', 'U'};
unsigned char telexShortKey[] = {'[', ']','{', '}'};


unsigned char vniToneMark[]={'1', '2', '3', '4', '5'};
unsigned char vniBreveMark[]={'7','8'};
unsigned char vniDoubleMark[]={'6','9'};

unsigned char VIQRToneMark[] = {'\'', '`', '?', '~', '.'};
unsigned char VIQRDoubleMark[] = {'^', '+', '(', 'd'};

void buildTelexTable();
void buildVniTable();
void buildCodeTable(int typing,int index);


void CKeyBuffer::processChar(unsigned char c){
	if(oldCharset!=index){
		buildCodeTable(typing,index);
		oldCharset=index;
	}
	VK_BACK_SCAN = MapVirtualKey(VK_BACK, 0);
	/*
	for(int i=0;i<12;i++)
		for(int j=0;j<6;j++)
	PostMessage(GetFocus(),WM_CHAR,_8bitWovel1[i][j],0);
	*/
	//if(keys==0) MessageBox(NULL,"keys=0","ok",MB_OK);
	//char buffer[128];
	
	oldChar=c;
	c=tolower(c);
	//wsprintf(buffer, "TextHook %d",indexTable[c]);
	//MessageBox(NULL, buffer, "ERROR_CAPTION", MB_OK);
	if(c!=8){
		if(isToneMark(indexTable[c])){
				processToneMark(c);
		}
		else if(typing==TELEX_TYPING&&isDoubleMark(indexTable[c])||
				typing==VNI_TYPING&&isVniDoubleMark(c)){
				processDoubleMark(c);
		}
		else if(typing==TELEX_TYPING&&isBreveMark(indexTable[c])||
			   typing==VNI_TYPING&&isVniBreveMark(c)){
				processBreveMark(c);
		}
		else if(isTelexShortKey(indexTable[c])){
				TelexShortKey(c);
		}
		else{
				KeyBuffer[keys]=c;
				CaseBuffer[keys]=islower(oldChar);
				keys++;
		}
	}
	
	if(keys>BUFFER_SIZE){
		keys=1;
		KeyBuffer[0]='k';
	}
	
	if(oldChar!='w')
	oldPrevChar=oldChar;//oldPrevChar xu li cho w:tra dau
}//end processChar

void CKeyBuffer::processDoubleMark(unsigned char ch){
unsigned char c,returnKey;

//dd  DD    ee   EE   aa  AA   oo    OO
		if(keys>0){
			prevChar=KeyBuffer[keys-1];

		
			if(prevChar==_8bitDouble1[0]){//d
				returnKey='d';
				if(typing==TELEX_TYPING&&returnKey==ch||
				   typing==VNI_TYPING){
					KeyBuffer[keys-1]=returnKey;
					KeyBuffer[keys]=ch;
					CaseBuffer[keys]=islower(oldChar);
					keys++;
					PostChar(1,prevChar,1);
				return;
				}
			}
			else if(prevChar==_8bitDouble1[2]){//e
				returnKey='e';
				if(typing==TELEX_TYPING&&returnKey==ch){
					KeyBuffer[keys-1]=returnKey;
					KeyBuffer[keys]=ch;
					CaseBuffer[keys]=islower(oldChar);
					keys++;
					PostChar(1,prevChar,1);
				return;
				}
			}
			else if(prevChar==_8bitDouble1[4]){//a
				returnKey='a';
				if(typing==TELEX_TYPING&&returnKey==ch){
					KeyBuffer[keys-1]=returnKey;
					KeyBuffer[keys]=ch;
					CaseBuffer[keys]=islower(oldChar);
					keys++;
					PostChar(1,prevChar,1);
				return;
				}
			}
			else if(prevChar==_8bitDouble1[6]){//o
				returnKey='o';
				if(typing==TELEX_TYPING&&returnKey==ch){
					KeyBuffer[keys-1]=returnKey;
					KeyBuffer[keys]=ch;
					CaseBuffer[keys]=islower(oldChar);
					keys++;
					PostChar(1,prevChar,1);
				return;
				}
			}

			if(typing==TELEX_TYPING&&prevChar==ch||
			   typing==VNI_TYPING){
				c=_8bitDouble1[indexTable[prevChar]-DOUBLE_MARK];	
				KeyBuffer[keys-1]=c;
				PostChar(1,prevChar,0);
				return;
				
			}
			
			KeyBuffer[keys]=ch;
			CaseBuffer[keys]=islower(oldChar);
			keys++;
		}
	
		//if(keys>BUFFER_SIZE) keys=0;
		if(keys>8){
			keys=1;
			KeyBuffer[0]='k';
		}
	
}

void CKeyBuffer::processBreveMark(unsigned char ch){
unsigned char c,returnKey;
int i=-1;
		
		if(keys>0){
			prevChar=KeyBuffer[keys-1];
			switch(indexTable[prevChar]){
					case 2+WOVEL:// a(
						returnKey='a';
						KeyBuffer[keys-1]=returnKey;
						KeyBuffer[keys]=ch;
						CaseBuffer[keys]=islower(oldChar);
						keys++;
						PostChar(1,prevChar,1);
						return;
					case 8+WOVEL://o+
						returnKey='o';
						KeyBuffer[keys-1]=returnKey;
						KeyBuffer[keys]=ch;
						CaseBuffer[keys]=islower(oldChar);
						keys++;
						PostChar(1,prevChar,1);
						return;
					case 10+WOVEL://u+
						if(oldPrevChar=='u'){
							returnKey='u';
							KeyBuffer[keys-1]=returnKey;
							KeyBuffer[keys]=ch;
							CaseBuffer[keys]=islower(oldChar);
							keys++;
							
							PostChar(1,prevChar,1);
						}else{
								//MessageBox(NULL,"ok","ok",MB_OK);
								KeyBuffer[keys-1]=ch;
								PostChar(1,prevChar,0);
						
						}
						return;
			}//end switch

				switch(prevChar){
					case 'a':i=0;break;
					case 'o':i=2;break;
					case 'u':i=4;break;

				}
				if(i!=-1){
					c=_8bitBreve1[i];
						KeyBuffer[keys-1]=c;
						PostChar(1,prevChar,0);
						return;
					
				}
				
				else if(ch=='w'){
					c=_8bitBreve1[4];
					KeyBuffer[keys]=c;
					CaseBuffer[keys]=islower(prevChar);
					keys++;
					PostChar(0,prevChar,1);
					return;
				}
				

				KeyBuffer[keys]=ch;
				CaseBuffer[keys]=islower(oldChar);
				keys++;
			
		}

}

void CKeyBuffer::processToneMark(unsigned char ch){
unsigned char prevChar,c;
int i=-1,indexTone=0,numOfVowel=0;
		
	if(keys>0){
		
			//the first vowel
		for(int k=keys-1;k>=0;k--){
			if(KeyBuffer[k]=='a'||KeyBuffer[k]=='o'||KeyBuffer[k]=='e'||KeyBuffer[k]=='u'
			 ||isWovel(indexTable[KeyBuffer[k]])
			   ){
					indexTone=keys-k;
					numOfVowel++;
					if(numOfVowel>0){
						if(isWovel(indexTable[KeyBuffer[k]])&&KeyBuffer[k]!='y'&&KeyBuffer[k]!='i'){
							numOfVowel=1;
							break;
						}
						if(KeyBuffer[k]!='a'&&KeyBuffer[k]!='o'&&KeyBuffer[k]!='e'&&KeyBuffer[k]!='u'
						&&!isWovel(indexTable[KeyBuffer[k]]))
						break;
					}
			}
		}

		if(numOfVowel==3){
			if(KeyBuffer[keys-indexTone+2]==_8bitWovel1[4][5]&&
				KeyBuffer[keys-indexTone+1]=='y'&&KeyBuffer[keys-indexTone]=='u'){
				indexTone=indexTone-2;
				
			}
			else
			indexTone=indexTone-1;
		}
		else if(numOfVowel==2){
			
			if(keys>indexTone&&(KeyBuffer[keys-indexTone-1]=='q'||
				KeyBuffer[keys-indexTone-1]=='g'&&KeyBuffer[keys-indexTone]=='i')){
				indexTone=indexTone-1;
			}else if(indexTone-numOfVowel){//co phu am di cung
				indexTone=indexTone-1;
			}
		}
		
		if(notFreeMarking) indexTone=1;
		if(indexTone>0){
	
			prevChar=KeyBuffer[keys-indexTone];
			
			if(isWovel(indexTable[prevChar])||
				prevChar=='a'||
				prevChar=='e'||
				prevChar=='o'||
				prevChar=='u'){	
				switch(prevChar){
						case 'a':i=0;break;
						case 'e':i=3;break;
						case 'o':i=6;break;
						case 'u':i=9;break;
						default :
							i=indexTable[prevChar]-WOVEL;
							break;
				}
				
				c=_8bitWovel1[i][indexTable[ch]-TONE_MARK];
				
				if(prevChar==c){
					unsigned char returnKey=_8bitWovel1[i][5];
					KeyBuffer[keys-indexTone]=returnKey;
					KeyBuffer[keys]=ch;
					CaseBuffer[keys]=islower(oldChar);
					keys++;
					PostChar(indexTone,prevChar,1);

					return;
				}
				else{
					KeyBuffer[keys-indexTone]=c;
					PostChar(indexTone,prevChar,0);
					return;
				}
			}
		}//end indexTone>0
		
		
		KeyBuffer[keys]=ch;
		CaseBuffer[keys]=islower(oldChar);
		keys++;
	}
	
	
		
}//end processToneMark

void CKeyBuffer::TelexShortKey(unsigned char ch){

	switch(ch){
		case '[':
			KeyBuffer[keys]=_8bitBreve1[2];
			CaseBuffer[keys]=1;
			keys++;
			PostChar(0,ch,1);
			return;
		case ']':
			KeyBuffer[keys]=_8bitBreve1[4];
			CaseBuffer[keys]=1;
			keys++;
			PostChar(0,ch,1);
			return;
		case '{':
			KeyBuffer[keys]=_8bitBreve1[3];
			CaseBuffer[keys]=0;
			keys++;
			PostChar(0,ch,1);
			return;
		case '}':
			KeyBuffer[keys]=_8bitBreve1[5];
			CaseBuffer[keys]=0;
			keys++;
			PostChar(0,ch,1);
			return;
		default:
			break;
	}

	

}//end TelexShortKey

void CKeyBuffer::PostChar(int index,unsigned  char ch,int returnK){
int keyP;
	
	if(typeOfCharset==UNICODE_CHARSET){
		
		keyP=keys;
		
		int key=0;
		
		for(int i=keys-(index+returnK);i<keys;i++){
		if(CaseBuffer[i])
			UnicodeBuffer[key++]=L_16bit[KeyBuffer[i]];
		else
			UnicodeBuffer[key++]=H_16bit[KeyBuffer[i]];

		AnsiBuffer[i-(keys-(index+returnK))]=KeyBuffer[i];
		}
		

		if(uClipboard){

		UnicodeBuffer[key]=0;
		OpenClipboard(GetFocus());  
		EmptyClipboard();

		
		UnicodeBuffer[key] = 0; // null-terminated
		
		HGLOBAL hBuf = GlobalAlloc(GMEM_MOVEABLE, sizeof(WORD) * keys);
		

		LPVOID pBuf = GlobalLock(hBuf);
		
		memcpy(pBuf, UnicodeBuffer, sizeof(WORD) * keys);
		GlobalUnlock(hBuf);

		keybd_event(VK_BACK, VK_BACK_SCAN, 0, 0);
		myBack=index;
		for(i=0;i<index;i++)
			PostMessage(GetFocus(),WM_CHAR,8,0);

		keys=keyP-(index+returnK);
		for(i=0;i<index+returnK;i++){
			KeyBuffer[keys++]=AnsiBuffer[i];
		}
		
		keys++;

		SetClipboardData(CF_UNICODETEXT, hBuf);

		CloseClipboard();
		
		GetKeyboardState(States);
		keybd_event(VK_SHIFT, 0, 0, 0);
		keybd_event(VK_INSERT, 0, KEYEVENTF_EXTENDEDKEY, 0);
		keybd_event(VK_INSERT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
		
		if ((States[VK_SHIFT] & 0x80) == 0 || (States[VK_RSHIFT] & 0x80) != 0)
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
		//ClipboardIsEmpty = 0;
		
		}
		
		else{

			keybd_event(VK_BACK, VK_BACK_SCAN, 0, 0);
			myBack=index+1;
			for(i=0;i<index+1;i++)
				PostMessage(GetFocus(),WM_IME_CHAR,8,0);
			

			keys=keyP-(index+returnK);
			for(i=0;i<index+returnK;i++){
				if(i==0&&(index+returnK==1||!isToneMark(indexTable[tolower(oldChar)]))){
				PostMessage(GetFocus(),WM_IME_CHAR,UnicodeBuffer[i],0);
				PostMessage(GetFocus(),WM_IME_CHAR,UnicodeBuffer[i],0);
				}
				else
				PostMessage(GetFocus(),WM_IME_CHAR,UnicodeBuffer[i],0);
				KeyBuffer[keys++]=AnsiBuffer[i];
			}
			
			if(index+returnK>1&&i!=0){
			PostMessage(GetFocus(),WM_IME_CHAR,UnicodeBuffer[index+returnK-1],0);
			}

			keys++;
		}
		
	}
	else if(typeOfCharset==_16BIT_CHARSET){

	 keyP=keys;
		for(int i=keys-(index+returnK);i<keys;i++)
			AnsiBuffer[i-(keys-(index+returnK))]=KeyBuffer[i];

	 int back=index;
	 //if(isWovel(indexTable[ch])&&
	//	 ch!=_8bitWovel1[10][5]&&
	//	 ch!=_8bitWovel1[7][5])back=index+1;
	 if(HIBYTE(L_16bit[ch]))
		 back=index+1;
	 
	 
	 keybd_event(VK_BACK, VK_BACK_SCAN, 0, 0);
	 myBack=back;
	 for(i=0;i<back;i++)
			PostMessage(GetFocus(),WM_CHAR,8,0);


		keys=keyP-(index+returnK);
	 	for(i=0;i<index+returnK;i++){
		 if(CaseBuffer[i+(keyP-index)]){
			if(HIBYTE(L_16bit[AnsiBuffer[i]])&&
			   LOBYTE(L_16bit[AnsiBuffer[i]])){
				
				PostMessage(GetFocus(),WM_CHAR,LOBYTE(L_16bit[AnsiBuffer[i]]),0);
				PostMessage(GetFocus(),WM_CHAR,HIBYTE(L_16bit[AnsiBuffer[i]]),0);
				
			}else{
				
				PostMessage(GetFocus(),WM_CHAR,L_16bit[AnsiBuffer[i]],0);
			}
		 }else{
			 if(HIBYTE(H_16bit[AnsiBuffer[i]])&&
			   LOBYTE(H_16bit[AnsiBuffer[i]])){
				
				PostMessage(GetFocus(),WM_CHAR,LOBYTE(H_16bit[AnsiBuffer[i]]),0);
				PostMessage(GetFocus(),WM_CHAR,HIBYTE(H_16bit[AnsiBuffer[i]]),0);
				
			}else{
				
				PostMessage(GetFocus(),WM_CHAR,H_16bit[AnsiBuffer[i]],0);
			}

		 }

		 KeyBuffer[keys++]=AnsiBuffer[i];
		
		 
	 }//end for
		
		keys++;
	}//VIETWAREX, VNI...
	else if(typeOfCharset==VIQR_CHARSET){
		char mark;
		keyP=keys;
		for(int i=keys-(index+returnK);i<keys;i++)
			AnsiBuffer[i-(keys-(index+returnK))]=KeyBuffer[i];


	 int back=index;
	 

	 keybd_event(VK_BACK, VK_BACK_SCAN, 0, 0);
	 myBack=back;
	 for(i=0;i<back;i++)
			PostMessage(GetFocus(),WM_CHAR,8,0);


		keys=keyP-(index+returnK);
	 	for(i=0;i<index+returnK;i++){
		 if(CaseBuffer[i+(keyP-index)]){
			if(HIBYTE(L_16bit[AnsiBuffer[i]])&&
			   LOBYTE(L_16bit[AnsiBuffer[i]])){
			
				if(HIBYTE(L_16bit[ch])=='^'||
				   HIBYTE(L_16bit[ch])=='(')
					L_16bit[AnsiBuffer[0]]=MAKEWORD('^',VIQRTone[indexTable[oldChar]-TONE_MARK]);

				if(HIBYTE(L_16bit[ch])=='+')
					L_16bit[AnsiBuffer[0]]=MAKEWORD('+',VIQRTone[indexTable[oldChar]-TONE_MARK]);

				PostMessage(GetFocus(),WM_CHAR,LOBYTE(L_16bit[AnsiBuffer[i]]),0);
				PostMessage(GetFocus(),WM_CHAR,HIBYTE(L_16bit[AnsiBuffer[i]]),0);
				
			}else{
				
				PostMessage(GetFocus(),WM_CHAR,L_16bit[AnsiBuffer[i]],0);
			}
		 }else{
			 if(HIBYTE(H_16bit[AnsiBuffer[i]])&&
			   LOBYTE(H_16bit[AnsiBuffer[i]])){
				
				 	if(HIBYTE(L_16bit[ch])=='^'||
				   HIBYTE(L_16bit[ch])=='(')
					H_16bit[AnsiBuffer[0]]=MAKEWORD('^',VIQRTone[indexTable[oldChar]-TONE_MARK]);

				if(HIBYTE(L_16bit[ch])=='+')
					H_16bit[AnsiBuffer[0]]=MAKEWORD('+',VIQRTone[indexTable[oldChar]-TONE_MARK]);

				PostMessage(GetFocus(),WM_CHAR,LOBYTE(H_16bit[AnsiBuffer[i]]),0);
				PostMessage(GetFocus(),WM_CHAR,HIBYTE(H_16bit[AnsiBuffer[i]]),0);
				
			}else{
				
				PostMessage(GetFocus(),WM_CHAR,H_16bit[AnsiBuffer[i]],0);
			}

		 }

		 KeyBuffer[keys++]=AnsiBuffer[i];
		
		 
	 }//end for 
		
		keys++;
	}//VIQR
	else{
		
		keyP=keys;
		for(int i=keys-(index+returnK);i<keys;i++)
			AnsiBuffer[i-(keys-(index+returnK))]=KeyBuffer[i];


		keybd_event(VK_BACK, VK_BACK_SCAN, 0, 0);
		 myBack=index;
		for(i=0;i<index;i++)
		PostMessage(GetFocus(),WM_CHAR,8,0);
		//keybd_event(VK_BACK, VK_BACK_SCAN, 0, 0);
		
		keys=keyP-(index+returnK);
		for(i=0;i<index+returnK;i++){
			PostMessage(GetFocus(),WM_CHAR,AnsiBuffer[i],0);
			KeyBuffer[keys++]=AnsiBuffer[i];
		}
		
		keys++;
		
	}//TCVN3 , VIETWAREF
}


void buildTelexTable(){

	for(int i=0;i<256;i++)
		indexTable[i]=0;
	//build wovel
	for(i=0;i<12;i++)
		for(int j=0;j<6;j++)
			indexTable[_8bitWovel1[i][j]]=WOVEL+i;

	
	for(i=0;i<sizeof(telexToneMark);i++)
			indexTable[telexToneMark[i]]=TONE_MARK+i;

	//build double mark
	for(i=0;i<sizeof(telexDoubleMark);i++)
			indexTable[telexDoubleMark[i]]=DOUBLE_MARK+i;

	//build breve mark
	for(i=0;i<sizeof(telexBreveMark);i++)
			indexTable[telexBreveMark[i]]=BREVE_MARK+i;

	//build  mark
	for(i=0;i<sizeof(telexShortKey);i++)
			indexTable[telexShortKey[i]]=TELEX_SHORTKEY+i;
	
}

void buildVniTable(){
	
	for(int i=0;i<256;i++)
		indexTable[i]=0;
	//build wovel
	for(i=0;i<12;i++)
		for(int j=0;j<6;j++)
			indexTable[_8bitWovel1[i][j]]=WOVEL+i;

	
	for(i=0;i<sizeof(vniToneMark);i++)
			indexTable[vniToneMark[i]]=TONE_MARK+i;

	//build double mark
	for(i=0;i<sizeof(telexDoubleMark);i++)
			indexTable[telexDoubleMark[i]]=DOUBLE_MARK+i;
	//build double mark
	
	//build breve mark
	for(i=0;i<sizeof(telexBreveMark);i++)
			indexTable[telexBreveMark[i]]=BREVE_MARK+i;
	
}

void buildCodeTable(int typing,int index){
	//char buffer[128];
	//wsprintf(buffer, "TextHook typing=%d|index=%d",typing,index);
	//MessageBox(NULL, buffer, "ERROR_CAPTION", MB_OK);
	if(index<NUM_8bit)
		typeOfCharset=_8BIT_CHARSET;
	else if(index==UNICODE)
		typeOfCharset=UNICODE_CHARSET;
	else if(index==VIQR_CHARSET)
		typeOfCharset=VIQR_CHARSET;
	else typeOfCharset=_16BIT_CHARSET;

	//char buffer[128];
	 //wsprintf(buffer, "TextHook %d|%d",typing,index);
	 //MessageBox(NULL, buffer, "ERROR_CAPTION", MB_OK);
	
	if(index<NUM_8bit){
		memcpy(_8bitWovel1,_8bitWovel[index], sizeof(_8bitWovel1));
		memcpy(_8bitBreve1,_8bitBreve[index], sizeof(_8bitBreve1));
		memcpy(_8bitDouble1,_8bitDouble[index], sizeof(_8bitDouble1));
	}
	else{
		index=index-NUM_8bit-1;
		memcpy(_8bitWovel1,_8bitWovel[0], sizeof(_8bitWovel1));
		memcpy(_8bitBreve1,_8bitBreve[0], sizeof(_8bitBreve1));
		memcpy(_8bitDouble1,_8bitDouble[0], sizeof(_8bitDouble1));
	}

	if(typing==TELEX_TYPING)
		buildTelexTable();
	else buildVniTable();

	if(typeOfCharset>=0){
		
		if(typeOfCharset==VIQR_CHARSET){
			
				for(int i=0;i<256;i++){
				L_16bit[i]=0;
				H_16bit[i]=0;
				}

				for(char lo='a',up='A';lo<='z';lo++,up++){
				L_16bit[lo]=lo;
				H_16bit[lo]=up;
				}

				for (i=0; i<12; i++) { 
					for (int j=0; j<6; j++) {
						L_16bit[_8bitWovel1[i][j]]=MAKEWORD(_8bitWovel1[i][5], VIQRToneMark[j]);
						H_16bit[_8bitWovel1[i][j]]=MAKEWORD(toupper(_8bitWovel1[i][5]),VIQRToneMark[j]);
					}
				}
				

				for (i=0; i<sizeof(_8bitDouble1); i++) {
						L_16bit[_8bitDouble1[i]]=MAKEWORD(telexDoubleMark[i],'^');
						H_16bit[_8bitDouble1[i]]=MAKEWORD(toupper(telexDoubleMark[i]),'^');
				}
				L_16bit[_8bitDouble1[0]]=MAKEWORD('d','d');
				H_16bit[_8bitDouble1[0]]=MAKEWORD('D','D');

				//breve
				L_16bit[_8bitBreve1[0]]=MAKEWORD('a','(');
				H_16bit[_8bitBreve1[0]]=MAKEWORD('A','(');

				L_16bit[_8bitBreve1[2]]=MAKEWORD('o','+');
				H_16bit[_8bitBreve1[2]]=MAKEWORD('O','+');

				L_16bit[_8bitBreve1[4]]=MAKEWORD('u','+');
				H_16bit[_8bitBreve1[4]]=MAKEWORD('U','+');
		}
		else{//16bit,Unicode
			
			for(int i=0;i<256;i++){
				L_16bit[i]=0;
				H_16bit[i]=0;
			}

			for(char lo='a',up='A';lo<='z';lo++,up++){
				L_16bit[lo]=lo;
				H_16bit[lo]=up;
			}

			
				

			unsigned char *p = (unsigned char *)_8bitWovel1;
			for(i=0;i<72;i++){
				L_16bit[*p]=L_16bitWovel[index][i];
				H_16bit[*p]=H_16bitWovel[index][i];
				p++;
			}
			
			L_16bit[_8bitDouble1[0]]=_16bitdd[index];
			H_16bit[_8bitDouble1[0]]=_16bitDD[index];
			
		}
		
	}//end 
	
}//end buildCodeTable

