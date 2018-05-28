// InstallBuilderView.h : interface of the CInstallBuilderView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INSTALLBUILDERVIEW_H__9A70C0B2_4C1A_455B_849E_0BDC510A20BF__INCLUDED_)
#define AFX_INSTALLBUILDERVIEW_H__9A70C0B2_4C1A_455B_849E_0BDC510A20BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TabCtrlEx.h"

class CInstallBuilderView : public CFormView
{
protected: // create from serialization only
	CInstallBuilderView();
	DECLARE_DYNCREATE(CInstallBuilderView)

public:
	//{{AFX_DATA(CInstallBuilderView)
	enum { IDD = IDD_INSTALLBUILDER_FORM };
	CTabCtrlEx	m_TabCtrl;
	//}}AFX_DATA

// Attributes
public:
	CInstallBuilderDoc* GetDocument();

// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallBuilderView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bOutputFileExists;
	void RemoveFile(LPCTSTR lpszFileName);
	void AddFile(LPCTSTR lpszFileName, BOOL bAddToDocument = FALSE);
	void AddShortcut(CShortcutObject &shortcutObject, int nIndex = -1);
	virtual ~CInstallBuilderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void AppendFile(LPCTSTR lpszFileName, FILE* f);
	HACCEL m_hAccel;

// Generated message map functions
protected:
	CString GetFileName(LPCTSTR lpszPathName);
	BOOL CreateStubFile(LPCTSTR lpszFileName);
	BOOL CreateSetupScript(LPCTSTR lpszFileName);
	//{{AFX_MSG(CInstallBuilderView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnProjectGeneral();
	afx_msg void OnUpdateProjectGeneral(CCmdUI* pCmdUI);
	afx_msg void OnProjectOutput();
	afx_msg void OnUpdateProjectOutput(CCmdUI* pCmdUI);
	afx_msg void OnProjectShortcuts();
	afx_msg void OnUpdateProjectShortcuts(CCmdUI* pCmdUI);
	afx_msg void OnProjectFiles();
	afx_msg void OnUpdateProjectFiles(CCmdUI* pCmdUI);
	afx_msg void OnBuildSetup();
	afx_msg void OnTestrunsetup();
	afx_msg void OnUpdateTestrunsetup(CCmdUI* pCmdUI);
	afx_msg void OnBuildAddremoveprograms();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in InstallBuilderView.cpp
inline CInstallBuilderDoc* CInstallBuilderView::GetDocument()
   { return (CInstallBuilderDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLBUILDERVIEW_H__9A70C0B2_4C1A_455B_849E_0BDC510A20BF__INCLUDED_)
