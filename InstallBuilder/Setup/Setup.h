// Setup.h : main header file for the SETUP application
//

#if !defined(AFX_SETUP_H__B5181A2F_0F25_406D_AA05_6AB50E40462B__INCLUDED_)
#define AFX_SETUP_H__B5181A2F_0F25_406D_AA05_6AB50E40462B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSetupApp:
// See Setup.cpp for the implementation of this class
//

class CSetupApp : public CWinApp
{
public:
	CSetupApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	void GetExtractFolder(CString &strFolder) { strFolder = m_strExtractFolder; };
	void GetSetupFileName(CString &strFileName) { strFileName = m_strLastExtractedFile; };
	CString m_strApplicationName;
	CString m_strCopyright;
	CString m_strApplicationExe;

	//{{AFX_MSG(CSetupApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CString m_strExtractFolder;
	CString m_strLastExtractedFile;
	void DeleteTemporaryFolder();
	BOOL ExtractSetupFiles();
	
	BOOL LoadFile(LPCTSTR lpszFileName, char** ppMemoryBlock, char** ppBlockEnd);
	BOOL ExtractFile(LPTSTR lpszStart, LPTSTR lpEnd, LPCTSTR lpszExtractFolder);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUP_H__B5181A2F_0F25_406D_AA05_6AB50E40462B__INCLUDED_)
