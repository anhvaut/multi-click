#if !defined(AFX_ADDSHORTCUTDLG_H__478B79E4_D074_419D_AE81_F4D8F0CCA3F2__INCLUDED_)
#define AFX_ADDSHORTCUTDLG_H__478B79E4_D074_419D_AE81_F4D8F0CCA3F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddShortcutDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddShortcutDlg dialog

class CAddShortcutDlg : public CDialog
{
// Construction
public:
	CString m_strOriginalPath;
	CStringArray m_strFiles;
	CString m_strTitle;
	CAddShortcutDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddShortcutDlg)
	enum { IDD = IDD_ADD_SHORTCUT };
	CString	m_strName;
	CString	m_strTarget;
	CString	m_strWorkingDir;
	CString	m_strIconPath;
	CString	m_strCmdLine;
	int		m_nIconIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddShortcutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddShortcutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowseTarget();
	afx_msg void OnBrowseIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDSHORTCUTDLG_H__478B79E4_D074_419D_AE81_F4D8F0CCA3F2__INCLUDED_)
