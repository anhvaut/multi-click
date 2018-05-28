// InstallBuilder.h : main header file for the InstallBuilder application
//

#if !defined(AFX_INSTALLBUILDER_H__A730C440_F2ED_40AE_9CF9_1126E81F190F__INCLUDED_)
#define AFX_INSTALLBUILDER_H__A730C440_F2ED_40AE_9CF9_1126E81F190F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CInstallBuilderApp:
// See InstallBuilder.cpp for the implementation of this class
//

class CInstallBuilderApp : public CWinApp
{
public:
	CInstallBuilderApp();
	CSingleDocTemplate* m_pDocTemplate;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallBuilderApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CInstallBuilderApp)
	afx_msg void OnAppAbout();
	afx_msg void OnProjectWizard();
	afx_msg void OnHelpIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLBUILDER_H__A730C440_F2ED_40AE_9CF9_1126E81F190F__INCLUDED_)
