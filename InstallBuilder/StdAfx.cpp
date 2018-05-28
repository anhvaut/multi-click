// stdafx.cpp : source file that includes just the standard includes
//	InstallBuilder.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"


/********************************************************************/
/*																	*/
/* Function name : AutoSizeColumns									*/
/* Description   : 													*/
/*																	*/
/********************************************************************/
void AutoSizeColumns(CListCtrl *pListCtrl) 
{
	// Call this after your the control is filled
	pListCtrl->SetRedraw(FALSE);
	int mincol = 0;
    int maxcol = pListCtrl->GetHeaderCtrl()->GetItemCount()-1;
    for (int col = mincol; col <= maxcol; col++) 
	{
		pListCtrl->SetColumnWidth(col, LVSCW_AUTOSIZE);
        int wc1 = pListCtrl->GetColumnWidth(col);
        pListCtrl->SetColumnWidth(col, LVSCW_AUTOSIZE_USEHEADER);
        int wc2 = pListCtrl->GetColumnWidth(col);
        // 10 is minumim column width
		int wc = max(10, max(wc1,wc2));
        pListCtrl->SetColumnWidth(col,wc);
     }
     pListCtrl->SetRedraw(TRUE);
}


/********************************************************************/
/*																	*/
/* Function name : GetIconIndex										*/
/* Description   : 													*/
/*																	*/
/********************************************************************/
int GetIconIndex(LPCTSTR lpszPath, BOOL bIsDir, BOOL bSelected)
{
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	if (bIsDir)
	{
		SHGetFileInfo(lpszPath, 
				FILE_ATTRIBUTE_DIRECTORY, 
				&sfi, 
				sizeof(sfi), 
				SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES | (bSelected ? SHGFI_OPENICON : 0)
		);

		return sfi.iIcon;
	}
	else
	{
		SHGetFileInfo (lpszPath, 
			FILE_ATTRIBUTE_NORMAL, 
			&sfi, 
			sizeof(sfi), 
			SHGFI_SMALLICON | SHGFI_SYSICONINDEX | SHGFI_USEFILEATTRIBUTES | (bSelected ? SHGFI_OPENICON : 0)
		);
		return sfi.iIcon;
	}
	return -1;
}




/********************************************************************/
/*																	*/
/* Function name : GetTypeName										*/
/* Description   : 													*/
/*																	*/
/********************************************************************/
char* GetTypeName(CString strPath)
{
	SHFILEINFO sfi;
	memset(&sfi, 0, sizeof(sfi));

	static char lpBuff[MAX_PATH];
	lpBuff[0] = char ('\0');

	SHGetFileInfo(strPath, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);

	lstrcpy(lpBuff, sfi.szTypeName);
	if (lpBuff[0] == char('\0'))
	{
		int nDotIdx = strPath.ReverseFind('.');
		int nBSIdx = strPath.ReverseFind('\\');
		if (nDotIdx > nBSIdx)
		{
			strPath = strPath.Mid(nDotIdx+1);
			strPath.MakeUpper();
			lstrcpy (lpBuff, strPath + ' ');
		}

		lstrcat (lpBuff, _T("File"));
	}
	return lpBuff;
}




/********************************************************************/
/*																	*/
/* Function name : FormatSize										*/
/* Description   : Format size, the way explorer diplays it			*/
/*																	*/
/********************************************************************/
char* FormatSize(DWORD dwSizeLow, DWORD dwSizeHigh)
{
	static char szBuff[100];

	unsigned __int64 nFileSize = ((unsigned __int64)(((DWORD)(dwSizeLow)) | 
								 ((unsigned __int64)((DWORD)(dwSizeHigh))) << 32));
	unsigned __int64 kb = 1;

	if (nFileSize > 1024)
	{
		kb = nFileSize / 1024;
		if (nFileSize % 1024)
			kb++;
	}

	// make it a string
	_ui64tot(kb, szBuff, 10);

	// add thousand seperators
	int nLength = lstrlen(szBuff);
	if (nLength > 3)
	{
		LPCTSTR ptr = szBuff;
		ptr += (nLength-1);

		char szTemp[100];

		LPTSTR ptrTemp = szTemp;
		for(int i=0; i<nLength; i++)
		{
			if (i && ((i % 3) == 0)) 
			{
				if (*ptrTemp != ',')
				{
					*ptrTemp = ',';
					ptrTemp = _tcsinc(ptrTemp);
				}
			}
			*ptrTemp = *ptr;
			ptrTemp = _tcsinc(ptrTemp);
			ptr = _tcsdec(szBuff, ptr);
		}
		// terminate string
		*ptrTemp = '\0';
		// reverse string
		_tcsrev(szTemp);
		lstrcpy(szBuff, szTemp);
	}
	// add 'KB' to it
	lstrcat(szBuff, " KB");
	return szBuff;
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