// InstallBuilderDoc.h : interface of the CInstallBuilderDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INSTALLBUILDERDOC_H__B68B2B4A_A0BC_41A5_A669_550426B2347F__INCLUDED_)
#define AFX_INSTALLBUILDERDOC_H__B68B2B4A_A0BC_41A5_A669_550426B2347F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ShortcutObject.h"

class CInstallBuilderDoc : public CDocument
{
protected: // create from serialization only
	CInstallBuilderDoc();
	DECLARE_DYNCREATE(CInstallBuilderDoc)

// Attributes
public:
	CString	m_strCompanyName;
	CString	m_strProductName;
	CString	m_strProductURL;
	CString	m_strProductVersion;
	CString	m_strCopyrightNotice;
	CString	m_strProductDescription;

	CString m_strOutputFolder;
	CString m_strSetupFileName;

	BOOL m_bShowRunCheckbox;
	CString m_strApplicationName;

	CStringArray m_strFiles;

	CArray <CShortcutObject, CShortcutObject&> m_ShortcutObjects;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInstallBuilderDoc)
	public:
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInstallBuilderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInstallBuilderDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSTALLBUILDERDOC_H__B68B2B4A_A0BC_41A5_A669_550426B2347F__INCLUDED_)
