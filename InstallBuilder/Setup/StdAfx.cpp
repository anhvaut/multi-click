// stdafx.cpp : source file that includes just the standard includes
//	Setup.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


PFNSHGETFOLDERPATHA GetFuncPtr_SHGetFolderPathA()
{
	static HMODULE hMod = NULL;
	PFNSHGETFOLDERPATHA pSHGetFolderPath = NULL;

	// Load SHFolder.dll only once
	if (!hMod)
		hMod = LoadLibrary("SHFolder.dll");

	// Obtain a pointer to the SHGetFolderPathA function
	if (hMod)
		pSHGetFolderPath = (PFNSHGETFOLDERPATHA)GetProcAddress(hMod, "SHGetFolderPathA");

	return pSHGetFolderPath;
} 


/********************************************************************/
/*																	*/
/* Function name : BrowseForFolder									*/		
/* Description   : Browse for folder using SHBrowseForFolder.		*/
/*																	*/
/********************************************************************/
CString BrowseForFolder(HWND hWnd, LPCSTR lpszTitle, UINT nFlags)
{
	// We're going to use the shell to display a 
	// "Choose Directory" dialog box for the user.
	CString strResult = "";
  
	LPMALLOC lpMalloc;
	
	if (::SHGetMalloc(&lpMalloc) != NOERROR)
	{
		// failed to get allocator  
		return strResult; 
	}

	char szBuffer[_MAX_PATH];
	char szDisplayName[_MAX_PATH];

	BROWSEINFO browseInfo;
	browseInfo.hwndOwner = hWnd;
	// set root at Desktop
	browseInfo.pidlRoot = NULL; 
	browseInfo.pszDisplayName = szDisplayName;
	browseInfo.lpszTitle = lpszTitle;
	browseInfo.ulFlags = nFlags;
	browseInfo.lpfn = NULL;
	browseInfo.lParam = 0;
	
	LPITEMIDLIST lpItemIDList;

	if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo)) != NULL)
	{
		// Get the path of the selected folder from the item ID list.
		if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
		{
			// At this point, szBuffer contains the path the user chose.
			if (szBuffer[0] == '\0')
			{
				// SHGetPathFromIDList failed, or SHBrowseForFolder failed.
				AfxMessageBox("Failed to get directory", MB_ICONSTOP|MB_OK);
				return strResult;
			}
     
			// We have a path in szBuffer!
			strResult = szBuffer;
			return strResult;
		}
		else
		{
			// The thing referred to by lpItemIDList 
			// might not have been a file system object.
			// For whatever reason, SHGetPathFromIDList didn't work!
			AfxMessageBox("Failed to get directory", MB_ICONSTOP|MB_OK);
			return strResult; // strResult is empty 
		}
		lpMalloc->Free(lpItemIDList);
		lpMalloc->Release();      
	}
	return strResult;
}


/********************************************************************/
/*																	*/
/* Function name : GetStartMenuFolder								*/		
/* Description   : Get folder of startup menu.						*/
/*																	*/
/********************************************************************/
BOOL GetStartMenuFolder(CString &strFolder)
{
	PFNSHGETFOLDERPATHA pSHGetFolderPath = NULL;
	TCHAR lpszLink[MAX_PATH];
	BOOL bFound = FALSE;

	pSHGetFolderPath = GetFuncPtr_SHGetFolderPathA();

	// Find the current user's Start Menu Programs folder
	if (pSHGetFolderPath)
		bFound = SUCCEEDED(pSHGetFolderPath(NULL, CSIDL_PROGRAMS, NULL, 0, lpszLink));

	if (bFound)
		strFolder = lpszLink;

	return bFound;
}


/********************************************************************/
/*																	*/
/* Function name : CreateStartMenuShortcut							*/		
/* Description   : Create a shortcut using the IShellLink interface.*/
/*																	*/
/********************************************************************/
HRESULT CreateStartMenuShortcut(LPSTR lpszShortcutFile, LPSTR lpszDescription, LPTSTR lpszRelativeFolder)
{
	HRESULT hr;
	PFNSHGETFOLDERPATHA pSHGetFolderPath = NULL;
	TCHAR lpszLink[MAX_PATH];
	BOOL bFound = FALSE;

	pSHGetFolderPath = GetFuncPtr_SHGetFolderPathA();

	// Find the current user's Start Menu Programs folder
	if (pSHGetFolderPath)
		bFound = SUCCEEDED(pSHGetFolderPath(NULL, CSIDL_PROGRAMS, NULL, 0, lpszLink));

	if (bFound)
	{
		// Proceed to create the shortcut
		IShellLink *pIShellLink = NULL;
		IPersistFile *ppf = NULL;
		WCHAR pLinkUnicode[MAX_PATH];

		CoInitialize(NULL);

		// Get a pointer to the IShellLink interface.
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                            IID_IShellLink, (void **)&pIShellLink);

		if (SUCCEEDED(hr))
		{
			// Get a pointer to IPersistFile interface for saving shortcut
			hr = pIShellLink->QueryInterface(IID_IPersistFile, (void **)&ppf);

			if (SUCCEEDED(hr))
			{   
	            hr = pIShellLink->SetPath(lpszShortcutFile);
		        hr = pIShellLink->SetDescription(lpszDescription);

				if (SUCCEEDED(hr))
				{
					// Add the target folder to the Start Menu Programs path
					lstrcat(lpszLink, "\\");
					lstrcat(lpszLink, lpszRelativeFolder);
					lstrcat(lpszLink, "\\");
	
					// Create the directory if it does not exist
					CreateDirectory(lpszLink,NULL);

					// Add the file name for the shortcut
					lstrcat(lpszLink, lpszDescription);
					lstrcat(lpszLink, ".lnk");

					// Convert string to Unicode, and call IPersistFile::Save()
					MultiByteToWideChar(CP_ACP, 0, lpszLink, -1, pLinkUnicode, MAX_PATH);
					hr = ppf->Save(pLinkUnicode, TRUE);
				}
				ppf->Release();
			}
			pIShellLink->Release();
		}
		CoUninitialize();
	}
	return hr;
} 



/********************************************************************/
/*																	*/
/* Function name : CreateDirectories								*/
/* Description   : Create directory tree.							*/
/*																	*/
/********************************************************************/
BOOL CreateDirectories(LPCTSTR lpszDirectory)
{
	CString strResult = lpszDirectory;

	if (strResult.Right(1) != '\\')
		strResult += '\\';
	
	CString strDir;
	BOOL bResult;
	// create directory structure one part at a time
	while (strResult != "")
	{
		strDir += strResult.Left(strResult.Find("\\")+1);
		strResult = strResult.Mid(strResult.Find("\\")+1);
		bResult = CreateDirectory(strDir, 0);
	}
	return bResult;
}