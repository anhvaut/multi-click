// WizardPages.h : header file
//

#ifndef __WIZARDPAGES_H__
#define __WIZARDPAGES_H__

/////////////////////////////////////////////////////////////////////////////
// CWizardPage1 dialog

class CWizardPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardPage1)

// Construction
public:
	CWizardPage1();
	~CWizardPage1();

// Dialog Data
	//{{AFX_DATA(CWizardPage1)
	enum { IDD = IDD_WIZARDPAGE1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardPage1)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardPage1)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CWizardPage2 dialog

class CWizardPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardPage2)

// Construction
public:
	CWizardPage2();
	~CWizardPage2();

// Dialog Data
	//{{AFX_DATA(CWizardPage2)
	enum { IDD = IDD_WIZARDPAGE2 };
	CString	m_strCompanyName;
	CString	m_strProductName;
	CString	m_strProductURL;
	CString	m_strProductVersion;
	CString	m_strCopyrightNotice;
	CString	m_strProductDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardPage2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardPage2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CWizardPage3 dialog

class CWizardPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardPage3)

// Construction
public:
	CWizardPage3();
	~CWizardPage3();

// Dialog Data
	//{{AFX_DATA(CWizardPage3)
	enum { IDD = IDD_WIZARDPAGE3 };
	CString	m_strFolder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardPage3)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardPage3)
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CWizardPage4 dialog

class CWizardPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CWizardPage4)

// Construction
public:
	CWizardPage4();
	~CWizardPage4();

// Dialog Data
	//{{AFX_DATA(CWizardPage4)
	enum { IDD = IDD_WIZARDPAGE4 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CWizardPage4)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CWizardPage4)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __WIZARDPAGES_H__
