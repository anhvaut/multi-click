// SetupSheet.h : header file
//
// This class defines custom modal property sheet 
// CSetupSheet.
 
#ifndef __SETUPSHEET_H__
#define __SETUPSHEET_H__

#include "SetupPages.h"

/////////////////////////////////////////////////////////////////////////////
// CSetupSheet

class CSetupSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSetupSheet)

// Construction
public:
	CSetupSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	CSetupPage1 m_Page1;
	CSetupPage2 m_Page2;
	CSetupPage3 m_Page3;
	CSetupPage4 m_Page4;
	CSetupPage5 m_Page5;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSetupSheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CSetupSheet)
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __SETUPSHEET_H__
