// MultiClick.h : main header file for the MultiClick application
//

#if !defined(AFX_MultiClick_H__3916B44E_FB76_11D4_868C_00E02930B0CE__INCLUDED_)
#define AFX_MultiClick_H__3916B44E_FB76_11D4_868C_00E02930B0CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMultiClickApp:
// See MultiClick.cpp for the implementation of this class
//

class CMultiClickApp : public CWinApp
{
public:
	CMultiClickApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiClickApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMultiClickApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MultiClick_H__3916B44E_FB76_11D4_868C_00E02930B0CE__INCLUDED_)
