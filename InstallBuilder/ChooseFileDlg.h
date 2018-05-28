#if !defined(AFX_CHOOSEFILEDLG_H__505A0287_B872_433B_8443_F6996CFD7B7D__INCLUDED_)
#define AFX_CHOOSEFILEDLG_H__505A0287_B872_433B_8443_F6996CFD7B7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChooseFileDlg.h : header file
//
#include "DialogResize.h"
/////////////////////////////////////////////////////////////////////////////
// CChooseFileDlg dialog

class CChooseFileDlg : public CDialogResize
{
// Construction
public:
	CString m_strFileName;
	CString m_strPathName;
	CStringArray m_strFiles;
	CChooseFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChooseFileDlg)
	enum { IDD = IDD_CHOOSE_FILE };
	CListCtrl	m_FilesList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL InitListViewImageLists();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChooseFileDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkFiles(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	DECLARE_DLGRESIZE_MAP;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSEFILEDLG_H__505A0287_B872_433B_8443_F6996CFD7B7D__INCLUDED_)
