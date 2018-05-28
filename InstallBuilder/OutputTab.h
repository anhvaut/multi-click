#if !defined(AFX_OUTPUTTAB_H__0DE58E02_2BF3_4E36_9884_BCF1F9EE987C__INCLUDED_)
#define AFX_OUTPUTTAB_H__0DE58E02_2BF3_4E36_9884_BCF1F9EE987C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputTab.h : header file
//

#include "DialogResize.h"

class COutputTab : public CDialogResize
{
// Construction
public:
	COutputTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COutputTab)
	enum { IDD = IDD_OUTPUT_TAB };
	CString	m_strOutputFolder;
	CString	m_strSetupFileName;
	BOOL	m_bShowCheckbox;
	CString	m_strApplicationName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutputTab)
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeOutputfolder();
	afx_msg void OnChangeSetupFilename();
	afx_msg void OnBuild();
	afx_msg void OnTestrun();
	afx_msg void OnShowcheckbox();
	afx_msg void OnChangeApplication();
	afx_msg void OnBrowseapp();
	//}}AFX_MSG
	afx_msg void OnUpdateApplication(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	DECLARE_DLGRESIZE_MAP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTTAB_H__0DE58E02_2BF3_4E36_9884_BCF1F9EE987C__INCLUDED_)
