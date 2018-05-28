// WizardSheet.h : header file
//
// This class defines custom modal property sheet 
// CWizardSheet.
 
#ifndef __WIZARDSHEET_H__
#define __WIZARDSHEET_H__

#include "WizardPages.h"

/////////////////////////////////////////////////////////////////////////////
// CWizardSheet

class CWizardSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CWizardSheet)

// Construction
public:
	CWizardSheet(CWnd* pWndParent = NULL);

// Attributes
public:
	CWizardPage1 m_Page1;
	CWizardPage2 m_Page2;
	CWizardPage3 m_Page3;
	CWizardPage4 m_Page4;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizardSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizardSheet();

// Generated message map functions
protected:
	//{{AFX_MSG(CWizardSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

#endif	// __WIZARDSHEET_H__
