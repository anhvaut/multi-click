#ifndef _AUTO_UPDATE_H
#define _AUTO_UPDATE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Wininet.h>

#define LOCATION_UPDATE_FILE_CHECK _T("version.ini")

class CAutoUpdate  
{
public:

	CAutoUpdate();
	virtual ~CAutoUpdate();
	bool InternetOkay();
	HINTERNET GetSession(CString &URL);
	bool DownloadConfig(HINTERNET hSession, BYTE *pBuf, DWORD bufSize);
	bool DownloadFile(HINTERNET hSession, LPCTSTR localFile);
	CString GetExecutable();
	CString GetFileVersion(LPCTSTR file);
/*		
	
	enum ErrorType { Success, InternetConnectFailure, InternetSessionFailure, 
						ConfigDownloadFailure, FileDownloadFailure, NoExecutableVersion,
						UpdateNotRequired, UpdateNotComplete };

	ErrorType CheckForUpdate(LPCTSTR UpdateServerURL);	
	

	
	

	
	int		CompareVersions(CString ver1, CString ver2);
	bool	IsDigits(CString text);
	
	bool	Switch(CString executable, CString update, bool WaitForReboot);
	*/

private:
	HINTERNET hInternet;
};

#endif 
