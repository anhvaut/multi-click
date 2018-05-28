/****************************************************************/
/*																*/
/*  Setup.cpp													*/
/*																*/
/*  Implementation of the CSetupApp class.						*/
/*	This file is part of the Setup application.					*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 22 July 2002									*/
/*																*/
/****************************************************************/

#include "stdafx.h"
#include "Setup.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BEGIN_MESSAGE_MAP(CSetupApp, CWinApp)
	//{{AFX_MSG_MAP(CSetupApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CSetupApp::CSetupApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CSetupApp object
CSetupApp theApp;


/********************************************************************/
/*																	*/
/* Function name : InitInstance										*/
/* Description   : CSetupApp initialization.						*/
/*																	*/
/********************************************************************/
BOOL CSetupApp::InitInstance()
{
	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("MultiClick"));

	if (!ExtractSetupFiles())
	{
		AfxMessageBox("Failed to extract setup files!");
		return FALSE;
	}

	char szBuff[255];
	GetPrivateProfileString("Strings", "AppName", "Setup MultiClick  version 1.0", szBuff, sizeof(szBuff), m_strLastExtractedFile);
	m_strApplicationName = szBuff;

	GetPrivateProfileString("Strings", "CopyrightMessage", "Copyright (c) 2005. Khoa Cong Nghe Thong Tin - Dai Hoc Da Nang", szBuff, sizeof(szBuff), m_strLastExtractedFile);
	m_strCopyright = szBuff;

	GetPrivateProfileString("Strings", "AppExe", "", szBuff, sizeof(szBuff), m_strLastExtractedFile);
	m_strApplicationExe = szBuff;
	m_strApplicationExe.TrimLeft();
	m_strApplicationExe.TrimRight();

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.
	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources
	pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL, NULL);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : ExitInstance										*/
/* Description   : CSetupApp cleanup.								*/
/*																	*/
/********************************************************************/
int CSetupApp::ExitInstance() 
{
	DeleteTemporaryFolder();

	CMainFrame* pFrame = (CMainFrame *)m_pMainWnd;
	if (pFrame)
		delete pFrame;

	return CWinApp::ExitInstance();
}


/********************************************************************/
/*																	*/
/* Function name : ExtractSetupFiles								*/
/* Description   : Extract files from setup package.				*/
/*																	*/
/********************************************************************/
BOOL CSetupApp::ExtractSetupFiles()
{
	// get temporary files directory
	char szTempPath[MAX_PATH];
	::GetTempPath(MAX_PATH, szTempPath);

	m_strExtractFolder = szTempPath;

	if (m_strExtractFolder.Right(1) != '\\')
		m_strExtractFolder += "\\";

	m_strExtractFolder += "~instdir\\";

	// create the extract directory
	CreateDirectories(m_strExtractFolder);

	// this is where the real extracting takes place...
	char szModuleName[MAX_PATH];
    char *ppMemoryBlock, *ppBlockEnd, *ptr;
    char *pStartPos = 0;
    
	// string to search for (unique GUID)
	CString strTag = "{58A60076-593E-414e-8152-BD3516480CAA}";
	// reverse it to prevent detecting it in this executable
	strTag.MakeReverse();

    int nLength = strTag.GetLength();

	// get our own name
    GetModuleFileName(NULL, szModuleName, sizeof(szModuleName));

    LoadFile(szModuleName, &ppMemoryBlock, &ppBlockEnd);

    if (!ppMemoryBlock) 
		return FALSE;

    ptr = ppMemoryBlock;
    
	int nCounter = 0;

	// search in memory block for string
    for ( ; ptr < ppBlockEnd; ptr++)
    {
        if (nCounter < nLength)
        {
			// compare part of string
            if (*ptr == strTag.GetAt(nCounter))
			{
                // this part is OK
				nCounter++;
			}
            else
			{
                // not good -> reset counter
				nCounter = 0;
			}
        }
        else
        {
			// found string !

			// rewind pointer (do not include marker tag)
			for (int i=0; i < nLength; i++)
				ptr--;

			ExtractFile(pStartPos, ptr, m_strExtractFolder);

			// skip marker
			for (int j=0; j < nLength; j++)
				ptr++;

            pStartPos = ptr;
            nCounter = 0;
        }
    }
	// last file is setup.inf !
    ExtractFile(pStartPos, ptr + 1, m_strExtractFolder);
    
	// release memory
	GlobalFree((HGLOBAL)ppMemoryBlock);

	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : LoadFile											*/
/* Description   : Load whole file into memory.						*/
/*																	*/
/********************************************************************/
BOOL CSetupApp::LoadFile(LPCTSTR lpszFileName, char** ppMemoryBlock, char** ppBlockEnd)
{
    HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ,
                   FILE_SHARE_READ, 0, OPEN_EXISTING,
                   FILE_ATTRIBUTE_NORMAL, 0 );
    
	*ppMemoryBlock = NULL;
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;

	// get file size
    DWORD dwBytes = GetFileSize(hFile, 0);
    if (dwBytes == -1 )
        return FALSE;

	// allocate memory for file contents
    *ppMemoryBlock = (char*)GlobalAlloc(GMEM_ZEROINIT | GMEM_FIXED, dwBytes);
    *ppBlockEnd = *ppMemoryBlock + dwBytes;

    DWORD dwRead;
    if (ReadFile(hFile, *ppMemoryBlock, dwBytes, &dwRead, 0 ) == 0 || dwRead == 0)
        *ppMemoryBlock = NULL; 

    CloseHandle(hFile);
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : ExtractFile										*/
/* Description   : Extract one file from package -> write memory	*/
/*				   contents to file.								*/
/*																	*/
/********************************************************************/
BOOL CSetupApp::ExtractFile(LPTSTR lpszStart, LPTSTR lpszEnd, LPCTSTR lpszExtractFolder)
{
	if (lpszStart == NULL)
        return FALSE;

    if (lpszEnd - lpszStart == 0)
        return FALSE;

    FILETIME filetime[3];
	// get creation time, last access Time, lastwrite time
	memcpy(filetime, (LPCTSTR)lpszStart, sizeof(FILETIME) * 3);

	// move pointer to filename
	int nSize = sizeof(FILETIME) * 3;
	while (nSize--)
		*lpszStart++;
   
	int nLength = lstrlen(lpszStart);

	// save filename
	CString strFileName = lpszExtractFolder;
	strFileName += lpszStart;

	// move start position
    lpszStart = lpszStart + nLength + 1;
	
	// save file contents
    HANDLE hFile = CreateFile(strFileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    if (hFile == INVALID_HANDLE_VALUE )
        return FALSE;
    
	DWORD dwWritten;
	WriteFile(hFile, (LPCVOID)lpszStart, lpszEnd - lpszStart, &dwWritten, 0);
	// restore original time stamp
	SetFileTime(hFile, &filetime[0], &filetime[1], &filetime[2]);
    CloseHandle(hFile);

	// remember last extracted filename
	m_strLastExtractedFile = strFileName;
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : DeleteTemporaryFolder							*/
/* Description   : Delete Temporary Folder and its contents.		*/
/*																	*/
/********************************************************************/
void CSetupApp::DeleteTemporaryFolder()
{
	// remove all files
	CFileFind finder;
	BOOL bContinue = finder.FindFile(m_strExtractFolder + "*.*");
	while (bContinue)
	{
		bContinue = finder.FindNextFile();
		if (finder.IsDots() || finder.IsDirectory())
			continue;

		DeleteFile(finder.GetFilePath());
	}
	finder.Close();

	// and finally remove the folder
	RemoveDirectory(m_strExtractFolder);
}


