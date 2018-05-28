#if !defined(AFX_SHORTCUTTAB_H__1D5D05EE_67E3_478B_9796_A368E335E4BC__INCLUDED_)
#define AFX_SHORTCUTTAB_H__1D5D05EE_67E3_478B_9796_A368E335E4BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShortcutTab.h : header file
//
#include "DialogResize.h"
/////////////////////////////////////////////////////////////////////////////
// CShortcutTab dialog

class CShortcutTab : public CDialogResize
{
// Construction
public:
	CShortcutTab(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShortcutTab)
	enum { IDD = IDD_SHORTCUT_TAB };
	CListCtrl	m_ShortcutList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutTab)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(CShortcutTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnEdit();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDblclkShortcuts(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRemove();
	afx_msg void OnRclickShortcuts(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShortcutAdd();
	afx_msg void OnShortcutEdit();
	afx_msg void OnShortcutRemove();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DECLARE_DLGRESIZE_MAP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTTAB_H__1D5D05EE_67E3_478B_9796_A368E335E4BC__INCLUDED_)
