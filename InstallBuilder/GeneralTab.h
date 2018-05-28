#if !defined(AFX_GENERALTAB_H__0A43D28D_FA73_4CC9_8135_833C23368276__INCLUDED_)
#define AFX_GENERALTAB_H__0A43D28D_FA73_4CC9_8135_833C23368276__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GeneralTab.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGeneralTab dialog

class CGeneralTab : public CDialog
{
// Construction
public:
	CGeneralTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGeneralTab)
	enum { IDD = IDD_GENERAL_TAB };
	CString	m_strCompanyName;
	CString	m_strProductName;
	CString	m_strProductURL;
	CString	m_strProductVersion;
	CString	m_strCopyrightNotice;
	CString	m_strProductDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGeneralTab)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGeneralTab)
	afx_msg void OnChangeCompanyname();
	afx_msg void OnChangeProductname();
	afx_msg void OnChangeProductversion();
	afx_msg void OnChangeProductdescription();
	afx_msg void OnChangeProducturl();
	afx_msg void OnChangeCopyrightnotice();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENERALTAB_H__0A43D28D_FA73_4CC9_8135_833C23368276__INCLUDED_)
