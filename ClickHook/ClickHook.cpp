

#include "windows.h"
#include "comdef.h"
#include "OLEAcc.h"
#include "ClickHook.h"

void getName(char *dest,char *src){
      int lendest=0,lensrc=0,i;
	  while(*(src+lensrc)!='\0') lensrc++;

	   i=lensrc-1;
	   int j=0;
       while (i>0 && *(src+i)!='\\'){
		*(dest + j)=*(src+i);
		i--;
		j++;
       }
       *(dest+j)='\0';
	   strrev(dest);
}

char Work[256];
//////////////////////////////////////////////////////////////////////////////

//SHARED DATA
#pragma data_seg(".SHARDATA")

static HWND hMainWnd= NULL;
static HHOOK hMouseHook= NULL;
CHAR szBuffer[BUFFER_COUNT+1]= {'\0'};
WCHAR szBufferW[BUFFER_COUNT+1]= {'\0'};
int isUnicode= 0;//0: string trong szBuffer; 1: string trong szBufferW
static POINT g_ptCurPos = {-1, -1};
int lookMode=SHIFT_RIGHT_CLICK;
int textMode=0;

#pragma data_seg()
int GetAccStringAtPoint(IAccessible*,VARIANT ,POINT, CHAR *,WCHAR *,int,int= BUFFER_COUNT);
bool CopyToClipboard(POINT);
DWORD CheckMenu(POINT pt, _bstr_t &_bstrInfo);

BOOL fUserSelect= TRUE;//kieu chon tu: manual hay auto (Send Dbl click)

int isOnlyText=0;
unsigned char  KeyState[256];

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
			
			// Only hook the APIs if this is the Everquest proess.
			
			/*
			char *p;
			p=strrchr(Work,'\\');
			
			strcpy(p+1,"");
			*/
			
			
			/*

			GetModuleFileName( GetModuleHandle( NULL ), Work, sizeof(Work) );
			char dest[256];
			getName(dest,Work);
			//char buffer[128];
			//wsprintf(buffer, "TextHook i=%s",dest);
			//MessageBox(NULL, buffer,"ERROR_CAPTION", MB_OK);
			 if(stricmp(dest,"winword.exe")==0||stricmp(dest,"acrord32.exe")==0)
				  
			*/
		//char buffer[128];
		//	wsprintf(buffer, "TextHook i=%d",textMode);
		//	MessageBox(NULL, buffer,"ERROR_CAPTION11", MB_OK);
		break;

	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}
HRESULT lay(POINT pt,IAccessible* pAcc, VARIANT varChild);
void SetHHook(HWND hMWnd, HHOOK hMsHook)
{	hMainWnd= hMWnd;//HWND to send message
	hMouseHook= hMsHook;
}

LRESULT CALLBACK MyMouseProc(int code, WPARAM wParam, LPARAM lParam)
{	
	if(hMainWnd && hMouseHook && code== HC_ACTION)
	{
		
		MOUSEHOOKSTRUCT *pMouseHook= (MOUSEHOOKSTRUCT *)lParam;

		GetKeyboardState(KeyState);
		if(wParam== WM_RBUTTONDOWN&& (KeyState[VK_RCONTROL] & 0x80)){
			

			CopyToClipboard(pMouseHook->pt);
			SendNotifyMessage(hMainWnd,WM_APP+MOUSE_PROC,9,
					MAKELPARAM(pMouseHook->pt.x,pMouseHook->pt.y));
			return 1;
		}
		else if(GetLookMode(wParam))
		{	
				
		
		//AA Service
			IAccessible* pAcc = NULL;
			HRESULT      hResult;
			VARIANT      varChild;
			VariantInit(&varChild);

			/* iCode: Ma gui thong bao lai cho hMainWnd:
				iCode= -1: khong gui thong bao
				iCode= 0: get string= clipboard
				iCode> 0: get string= AA Service, string nam trong shared data of DLL
				iCode= 1: string trong DLL la ANSI
				iCode= 2: string trong DLL la UNICODE
			*/
			
			int iCode= -1;

			GetModuleFileName( GetModuleHandle( NULL ), Work, sizeof(Work) );
			char dest[256];
			getName(dest,Work);
			
			_bstr_t _bstrInfo;
			
			if(CheckMenu(pMouseHook->pt,_bstrInfo))

			if((stricmp(dest,"winword.exe")==0||stricmp(dest,"acrord32.exe")==0)&&stricmp(_bstrInfo,"menu item")!=0){
					if(CopyToClipboard(pMouseHook->pt))
							iCode= 0;
					//else
					//		iCode= -1;
			}
			else{
						//This function retrieves the lowest-level accessible object in the object hierarchy at a given point
						hResult= AccessibleObjectFromPoint(pMouseHook->pt,&pAcc,&varChild);
					
						//if can not get string = AA Service, get string = Clipboard
						if(hResult!= S_OK)
						{	if(CopyToClipboard(pMouseHook->pt))
								iCode= 0;
							else
								iCode= -1;
						}
						//else, get string by AA Service
						else
						{	//if pAcc =  accessible object
							if(varChild.lVal== CHILDID_SELF)
							{	iCode= GetAccStringAtPoint(pAcc,varChild,pMouseHook->pt,szBuffer,szBufferW,TH1);
								//MessageBox(NULL,"ok1","ok",MB_OK);
								
							}
							//else pAcc = parent, varChild.lVal contains child_ID
							else
							{	
								//MessageBox(NULL,"ok2","ok",MB_OK);
								//Get child
								IDispatch* pDis = NULL;
								hResult= pAcc->get_accChild(varChild,&pDis);
								//verify returned value
								switch(hResult)
								{	case S_OK:
									//child is an accessible object, query for its IAccessible interface
										hResult= pDis->QueryInterface(&pAcc);
										if(hResult!= S_OK)
										{	strcpy(szBuffer,"QueryInterface fail!");
											break;
										}
										varChild.lVal= CHILDID_SELF;
										iCode= GetAccStringAtPoint(pAcc,varChild,pMouseHook->pt,szBuffer,szBufferW,TH2);
										//MessageBox(NULL,"ok2","ok",MB_OK);
										pDis->Release();
										break;

									case S_FALSE:
									//child is not an accessible object, but an element, varChild.lVal= child_ID
									//parent will provide information for this child
										iCode= GetAccStringAtPoint(pAcc,varChild,pMouseHook->pt,szBuffer,szBufferW,TH3);
										//MessageBox(NULL,"ok3","ok",MB_OK);
										break;
									//Error codes
									case DISP_E_MEMBERNOTFOUND:
										strcpy(szBuffer,"MEMBERNOTFOUND");
										break;
									case E_NOTIMPL :
										strcpy(szBuffer,"E_NOTIMPL ");
										break;
									case E_FAIL  :
										strcpy(szBuffer,"E_FAIL  ");
										break;
									case E_OUTOFMEMORY   :
										strcpy(szBuffer,"E_OUTOFMEMORY   ");
										break;
									case E_INVALIDARG    :
										strcpy(szBuffer,"E_INVALIDARG    ");
										break;
									default: 
									//other errors,	This is IE
										iCode= GetAccStringAtPoint(pAcc,varChild,pMouseHook->pt,szBuffer,szBufferW,TH4);
										//MessageBox(NULL,"ok4","ok",MB_OK);
										break;
								}//eo SWITCH
							}//eo if varChild.lVal== CHILDID_SELF
						}//eo HRESULT

			}//end else
			VariantClear(&varChild);
			
		//Get string complete, Send mess to MainWnd
			if(iCode>= 0)
			{	//wParam= iCode
				//LOWORD(lParam): cx mouse
				//HIWORD(lParam): cy mouse

				SendNotifyMessage(hMainWnd,WM_APP+MOUSE_PROC,iCode,
					MAKELPARAM(pMouseHook->pt.x,pMouseHook->pt.y));
			}

		//not pass control to next hook.
			
			return 1;
		}
	
		
	}
	//pass control to next hook.
	return ( CallNextHookEx(hMouseHook,code,wParam,lParam) );
}

//Getstring= AA Service or = clipboard, return value will be iCode
int GetAccStringAtPoint(IAccessible* pAcc, VARIANT varChild, POINT pt, CHAR *pChar,WCHAR *pCharW,int style,int nCharCount)
{	HRESULT      hResult;
	VARIANT      varRole;
	HWND hWnd= NULL;
	BSTR bstrName= NULL;
	int buffer32[128];

	
	//Init...
	VariantInit(&varRole);
	//Get object's location
	long lTop,lLeft,lWidth,lHeight;
	pAcc->accLocation(&lLeft,&lTop,&lWidth,&lHeight,varChild);
	
	
	//Get object's role
	hResult= pAcc->get_accRole(varChild, &varRole);
	//if(pt.y>lTop+lHeight||pt.y<lTop) return -1;
	if(hResult!= S_OK)
	{	strcpy(pChar,"Unknown error #1!");
		VariantClear(&varRole);
		return -1;
	}
	//verify object's role
	switch(varRole.iVal)
	{	//if role= edit, richedit, IE, goto "get string= clipboard"
		case ROLE_SYSTEM_TEXT:	
			break;
		default:
		//Query on the object's name.
			hResult= pAcc->get_accName(varChild, &bstrName);
			break;
	}
	//if bstrName== NULL, Get string= clipboard
	if(bstrName== NULL)
	{	
		VariantClear(&varRole);
	//Get string into clipboard
		if(CopyToClipboard(pt))
			return 0;
		else
			return -1;
	}
	//else if bstrName!= NULL, get string into shared data
	else
	{
		//Convert BSTR bstrName to CHAR *bChar
		LPCWSTR pNameStr= (LPCWSTR)bstrName;
		
		//calculate string len, and avoid buffer overflow
		int nRequestCount= SysStringLen(bstrName);
		int nMin= min( nCharCount,nRequestCount );
		int iIndex=0;

		HDC hdc=GetDC(GetFocus()); 
		SIZE size;
		TEXTMETRIC tm;
		GetTextExtentPointW(hdc,pNameStr,nMin,&size);
		GetTextMetrics(hdc,&tm);
		
		int bSize=0;
		for(int i=0;i<nMin;i++)
			if((CHAR)pNameStr[i]==' '){
				buffer32[bSize++]=i;
			}
		/*
		int startWord=0;
		int endWord=nMin;
		
		int charWidth=(int)lWidth/nMin;
		int tam=pt.x;
		if(style!=TH3){
			if(bSize<=2)
				tam=pt.x-10;
			else if(bSize>2)
				tam=pt.x-15;
		}
		int charMouseIndex=(int)(abs(tam-lLeft)/charWidth+1/2);
		
		if(bSize>0){//co 2 tu tro len
			//wsprintf(buffer, "bSize=%d|%d|%d",bSize,buffer32[0],charMouseIndex);
			//MessageBox(NULL, buffer, "ERROR_CAPTION", MB_OK);
			for(i=0;i<bSize;i++){
				if(buffer32[i]<charMouseIndex){
					startWord=buffer32[i]+1;
				}
				else if(buffer32[i]>charMouseIndex){
					endWord=buffer32[i];
					break;
				}
			}//end for
		}
		if(charMouseIndex>nMin){
			int startWord=0;
			int endWord=nMin;
		}
		*/
		//Unicode
		if( (int)(pNameStr[0]) >=256 )
		{	
				do
				{
					pCharW[iIndex]= pNameStr[iIndex];
					GetTextExtentPointW(hdc,pCharW,iIndex,&size);
					if(pt.x<=lLeft+size.cx) break;
					iIndex++;
					
				}
				while( iIndex< nMin);

				if(style!=TH3){
					if(bSize>0)
					iIndex-=3/bSize;
				}
				else if(style==TH3){
					iIndex+=(int)(iIndex/3+1/2);
					
				}
				int m=0;
				int n=nMin;
				if((CHAR)(pNameStr[iIndex])!=' '){
					for(m=iIndex;m>0;m--) 
						if((CHAR)(pNameStr[m])==' ') break;
					for(n=iIndex+1;n<nMin;n++)
						if((CHAR)(pNameStr[n])==' ') break;
				}
				
				for(int l=m;l<n;l++)
				pCharW[l-m]=pNameStr[l];
				
				pCharW[l-m]=(WCHAR)0;
		}//end UNICODE

		//ANSI (maybe)
		else
		{	
				isUnicode= 0; 
				do
				{
					pChar[iIndex]= (CHAR)(pNameStr[iIndex]);
					GetTextExtentPoint(hdc,pChar,iIndex,&size);
					if(pt.x<=lLeft+size.cx) break;
					iIndex++;
					
				}
				while( iIndex< nMin);

				if(style!=TH3){
					if(bSize>0)
					iIndex-=3/bSize;
				}
				else if(style==TH3){
					iIndex+=(int)(iIndex/3+1/2);
					
				}
				
				
				int m=0;
				int n=nMin;
				if((CHAR)(pNameStr[iIndex])!=' '){
					for(m=iIndex;m>0;m--) 
						if((CHAR)(pNameStr[m])==' ') break;
					for(n=iIndex+1;n<nMin;n++)
						if((CHAR)(pNameStr[n])==' ') break;
				}
				
				for(int l=m;l<n;l++)
				pChar[l-m]=(CHAR)(pNameStr[l]);
				
				pChar[l-m]=(CHAR)0;
			
		}//end else ANSI

	// Free the string:
		::SysFreeString( bstrName );
	//Special: if it's Adobe Acrobat, goto "get string= clipboard"

			
		if(strcmp(pChar,"AVDocToolView")== 0)
		{	VariantClear(&varRole);
			if(CopyToClipboard(pt))
				return 0;
			else
				return -1;
		}
	}

	VariantClear(&varRole);
	return isUnicode+1;
}

//get selected string into clipboard = simulate "Ctrl + C"
bool CopyToClipboard(POINT pt)
{	
	
	//open & empty clipboard
	if( !OpenClipboard(NULL) )
	{	strcpy(szBuffer,"Unknown error!");
		return false;
	}
	EmptyClipboard();
	//close Clipboard
	CloseClipboard();

	BYTE keyState[256];
	GetKeyboardState((LPBYTE)&keyState);
	/*
		if( (keyState[VK_CONTROL] & 1) )
		{// Simulate release VK_CONTROL
			keybd_event( VK_CONTROL,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
			
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);
			GetDoubleClickTime();
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);

			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,pt.x,pt.y,0,NULL);

			

		//	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,pt.x,pt.y,0,NULL);
		//	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,pt.x,pt.y,0,NULL);

		}
		else
		{	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);
			GetDoubleClickTime();
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);

			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP,pt.x,pt.y,0,NULL);
		}
	*/
	
	//Simulate double click
	/*if(fUserSelect== FALSE)
	{	//if pressed Ctrl
		if( (keyState[VK_CONTROL] & 1) )
		{// Simulate release VK_CONTROL
			keybd_event( VK_CONTROL,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
			
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);

		}
		else
		{	mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN,pt.x,pt.y,0,NULL);
			mouse_event(MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP,pt.x,pt.y,0,NULL);
		}
	}*/

	//if didnot press Ctrl
	if( !(keyState[VK_CONTROL] & 1) )
	{	//Simulate key press 'Ctrl' & 'C'
		keybd_event( VK_CONTROL,0x45,KEYEVENTF_EXTENDEDKEY | 0,0 );//CTRL
		keybd_event( 0x43,0x45,KEYEVENTF_EXTENDEDKEY | 0,0 );//C
		//Simulate key release 'Ctrl' & 'C'
		keybd_event( 0x43,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
		keybd_event( VK_CONTROL,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
	}
	//else if pressed Ctrl
	else
	{	//Simulate key press 'C'
		keybd_event( 0x43,0x45,KEYEVENTF_EXTENDEDKEY | 0,0 );//C
		//Simulate key release 'C'
		keybd_event( 0x43,0x45,KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0);
	}	



	return true;
}

CHAR *CALLBACK GetSharedString()
{	return szBuffer;
}
WCHAR *CALLBACK GetSharedStringW()
{	return szBufferW;
}


void SetLookMode(int i){
	lookMode=i;
}
void SetTextMode(int i){
	textMode=i;
}

int GetLookMode(WPARAM wParam){
UINT key1;
UINT key2;
	GetKeyboardState(KeyState);
	if(lookMode==CTRL_RIGHT_CLICK){
		key1=WM_RBUTTONDOWN;
		key2=VK_CONTROL;
		
	}else if(lookMode==SHIFT_RIGHT_CLICK){
		key1=WM_RBUTTONDOWN;
		key2=VK_SHIFT;
		
	}else if(lookMode==RIGHT_CLICK){
		key1=WM_RBUTTONDOWN;
		key2=0;
	}
	if(key1&&key2){
		if(wParam== key1&& (KeyState[key2] & 0x80)) return 1;
	}else if(key1&&!key2){
		if(wParam== key1) return 1;
	}

	return 0;
}


/*
* Check if area to lookup is menu in word, acrobat
*/
DWORD CheckMenu(POINT pt, _bstr_t &_bstrInfo)
{
	IAccessible *paccObj = NULL;
	VARIANT varChild;
	VariantInit(&varChild);
	if(AccessibleObjectFromPoint(pt, &paccObj, &varChild) == S_OK)
	{
		VARIANT var;
		VariantInit(&var);
		UINT nRoleLeng;
		WCHAR *lpszRoleStr = NULL;
		BSTR bstrName = NULL;
		if(paccObj->get_accRole(varChild, &var) == S_OK)
		{			
			nRoleLeng = GetRoleTextW(var.lVal, (WCHAR*)NULL, 0);			
			lpszRoleStr = new WCHAR[nRoleLeng + 1];
			GetRoleTextW(var.lVal, lpszRoleStr, nRoleLeng + 1);
		}
		
			
		_bstrInfo = lpszRoleStr;
		//_bstrInfo = (wchar_t*)_bstrInfo;		
		
		VariantClear(&var);
		paccObj->Release();
		delete [] lpszRoleStr;
	}
	VariantClear(&varChild);

	return 1;
}