#if !defined(AFX_FILESTAB_H__7AE72603_A853_4F27_86BD_26E38A60763A__INCLUDED_)
#define AFX_FILESTAB_H__7AE72603_A853_4F27_86BD_26E38A60763A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilesTab.h : header file
//
#include "DialogResize.h"
/////////////////////////////////////////////////////////////////////////////
// CFilesTab dialog

class CFilesTab : public CDialogResize
{
// Construction
public:
	CFilesTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFilesTab)
	enum { IDD = IDD_FILES_TAB };
	CListCtrl	m_FilesList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFilesTab)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitListViewImageLists();

	// Generated message map functions
	//{{AFX_MSG(CFilesTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnRemove();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRclickFiles(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFilesAdd();
	afx_msg void OnFilesRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DECLARE_DLGRESIZE_MAP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESTAB_H__7AE72603_A853_4F27_86BD_26E38A60763A__INCLUDED_)
