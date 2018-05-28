#include "stdAfx.h"
#include "Regedit.h"

#define START_UP_NAME  _T("MultiClick")


int CRegeditInfo::setValue()
{
	long ret;
	HKEY key;
	DWORD state;
	ret=RegCreateKeyEx(
		        HKEY_CURRENT_USER,
		        _TEXT("Software\\Bluerain\\MultiClick"),
				0,
				NULL,
				REG_OPTION_NON_VOLATILE,    
				KEY_QUERY_VALUE | KEY_SET_VALUE,        
				NULL,
				&key,          
				&state);

	if (ret!=ERROR_SUCCESS)
		return 0;
	
	RegSetValueEx(key, 
				_TEXT("autoStart"),
				0,
				REG_DWORD,
				(LPBYTE)&autoStart,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("onAutoLook"),
				0,
				REG_DWORD,
				(LPBYTE)&onAutoLook,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("autoLook"),
				0,
				REG_DWORD,
				(LPBYTE)&autoLook,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("backcolor"),
				0,
				REG_DWORD,
				(LPBYTE)&backcolor,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("titlecolor"),
				0,
				REG_DWORD,
				(LPBYTE)&titlecolor,
				sizeof(DWORD));
	

	//key
	RegSetValueEx(key, 
				_TEXT("charset"),
				0,
				REG_DWORD,
				(LPBYTE)&charset,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("inputMethod"),
				0,
				REG_DWORD,
				(LPBYTE)&inputMethod,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("switchKey"),
				0,
				REG_DWORD,
				(LPBYTE)&switchKey,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("isVietNamese"),
				0,
				REG_DWORD,
				(LPBYTE)&VietNamese,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("notFreeMarking"),
				0,
				REG_DWORD,
				(LPBYTE)&notFreeMarking,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("unicodeClipboard"),
				0,
				REG_DWORD,
				(LPBYTE)&uClipboard,
				sizeof(DWORD));
	RegSetValueEx(key, 
				_TEXT("vietNameseOn"),
				0,
				REG_DWORD,
				(LPBYTE)&vietNameseOn,
				sizeof(DWORD));
	
    RegSetValueEx(key, 
				_TEXT("onlyText"),
				0,
				REG_DWORD,
				(LPBYTE)&onlyText,
				sizeof(DWORD));
	 RegSetValueEx(key, 
				_TEXT("lookupOnAuto"),
				0,
				REG_DWORD,
				(LPBYTE)&lookupOnAuto,
				sizeof(DWORD));

	  
	
		RegSetValueEx(key, 
				_TEXT("guiLanguage"),
				0,
				REG_DWORD,
				(LPBYTE)&guiLanguage,
				sizeof(DWORD));

		RegSetValueEx(key, 
				_TEXT("kindDictionary"),
				0,
				REG_DWORD,
				(LPBYTE)&kindDictionary,
				sizeof(DWORD));

		RegSetValueEx(key, 
				_TEXT("onlineLookup"),
				0,
				REG_DWORD,
				(LPBYTE)&onlineLookup,
				sizeof(DWORD));
	
		RegSetValueEx(key, 
				_TEXT("autoUpdate"),
				0,
				REG_DWORD,
				(LPBYTE)&autoUpdate,
				sizeof(DWORD));
	RegCloseKey(key);
	return 1;
}

int CRegeditInfo::getValue()
{

	long ret;
	HKEY key;
	DWORD nbytes, valType;
	ret = RegOpenKeyEx(
				HKEY_CURRENT_USER,
				_TEXT("Software\\Bluerain\\MultiClick"),
				0,
				KEY_QUERY_VALUE,
				&key);
	if (ret!=ERROR_SUCCESS)
		return 0;
	
	nbytes = sizeof(DWORD);
	
	RegQueryValueEx(key, 
				_TEXT("autoStart"),
				0,
				&valType,
				(LPBYTE)&autoStart,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("onAutoLook"),
				0,
				&valType,
				(LPBYTE)&onAutoLook,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("autoLook"),
				0,
				&valType,
				(LPBYTE)&autoLook,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("backcolor"),
				0,
				&valType,
				(LPBYTE)&backcolor,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("titlecolor"),
				0,
				&valType,
				(LPBYTE)&titlecolor,
				&nbytes);
	//key
	RegQueryValueEx(key, 
				_TEXT("charset"),
				0,
				&valType,
				(LPBYTE)&charset,
				&nbytes);

	RegQueryValueEx(key, 
				_TEXT("inputMethod"),
				0,
				&valType,
				(LPBYTE)&inputMethod,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("switchKey"),
				0,
				&valType,
				(LPBYTE)&switchKey,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("isVietNamese"),
				0,
				&valType,
				(LPBYTE)&VietNamese,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("notFreeMarking"),
				0,
				&valType,
				(LPBYTE)&notFreeMarking,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("unicodeClipboard"),
				0,
				&valType,
				(LPBYTE)&uClipboard,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("vietNameseOn"),
				0,
				&valType,
				(LPBYTE)&vietNameseOn,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("onlyText"),
				0,
				&valType,
				(LPBYTE)&onlyText,
				&nbytes);
	RegQueryValueEx(key, 
				_TEXT("lookupOnAuto"),
				0,
				&valType,
				(LPBYTE)&lookupOnAuto,
				&nbytes);
	
	
	RegQueryValueEx(key, 
				_TEXT("guiLanguage"),
				0,
				&valType,
				(LPBYTE)&guiLanguage,
				&nbytes);

	RegQueryValueEx(key, 
				_TEXT("kindDictionary"),
				0,
				&valType,
				(LPBYTE)&kindDictionary,
				&nbytes);

	RegQueryValueEx(key, 
				_TEXT("onlineLookup"),
				0,
				&valType,
				(LPBYTE)&onlineLookup,
				&nbytes);

	RegQueryValueEx(key, 
				_TEXT("autoUpdate"),
				0,
				&valType,
				(LPBYTE)&autoUpdate,
				&nbytes);



	RegCloseKey(key);
	
	return 1;
}//end getValue()

int CRegeditInfo::enableAutoStart(int enabled){
	long res;
	HKEY key, hRoot;
	TCHAR path[_MAX_PATH];
	int ok;
	OSVERSIONINFO version;
	version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&version);
	if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
		hRoot = HKEY_CURRENT_USER;
	else
		hRoot = HKEY_LOCAL_MACHINE;

	res = RegOpenKeyEx(
				hRoot, 
				_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),
				0, // option, not used
				KEY_SET_VALUE | KEY_QUERY_VALUE, // allow setting values
				&key);
	if (res!=ERROR_SUCCESS)
		return 0;
	if (enabled) {
		GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		res = RegSetValueEx(key,  START_UP_NAME, 0, REG_SZ, (LPBYTE)path, (_tcsclen(path)+1)*sizeof(TCHAR));
		ok = (res == ERROR_SUCCESS);
	}
	else {
		RegDeleteValue(key,  START_UP_NAME);
		res = RegQueryValueEx(key,  START_UP_NAME, 0, NULL, NULL, NULL);
		ok = (res != ERROR_SUCCESS);
	}
	RegCloseKey(key);
	return ok;
}


