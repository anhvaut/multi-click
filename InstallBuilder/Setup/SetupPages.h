// SetupPages.h : header file
//

#ifndef __SETUPPAGES_H__
#define __SETUPPAGES_H__

/////////////////////////////////////////////////////////////////////////////
// CSetupPage1 dialog

class CSetupPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetupPage1)

// Construction
public:
	CSetupPage1();
	~CSetupPage1();

// Dialog Data
	//{{AFX_DATA(CSetupPage1)
	enum { IDD = IDD_PROPPAGE1 };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetupPage1)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetupPage1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSetupPage2 dialog

class CSetupPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetupPage2)

// Construction
public:
	CSetupPage2();
	~CSetupPage2();

// Dialog Data
	//{{AFX_DATA(CSetupPage2)
	enum { IDD = IDD_PROPPAGE2 };
	CString	m_strDestinationPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetupPage2)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetupPage2)
	afx_msg void OnBrowse();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnStnClickedText1();
	afx_msg void OnStnClickedText2();
};


/////////////////////////////////////////////////////////////////////////////
// CSetupPage3 dialog

class CSetupPage3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetupPage3)

// Construction
public:
	CSetupPage3();
	~CSetupPage3();

// Dialog Data
	//{{AFX_DATA(CSetupPage3)
	enum { IDD = IDD_PROPPAGE3 };
	CListBox	m_ExistingFolders;
	CString	m_strProgramFolder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetupPage3)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetupPage3)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeExistingfolders();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSetupPage4 dialog

class CSetupPage4 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetupPage4)

// Construction
public:
	CSetupPage4();
	~CSetupPage4();

// Dialog Data
	//{{AFX_DATA(CSetupPage4)
	enum { IDD = IDD_PROPPAGE4 };
	CEdit	m_EditCtrl;
	CString	m_strCurrentSettings;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetupPage4)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void RenameFiles(LPCTSTR lpszSetupFile, LPCTSTR lpszDestination);
	// Generated message map functions
	//{{AFX_MSG(CSetupPage4)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CSetupPage5 dialog

class CSetupPage5 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetupPage5)

// Construction
public:
	CSetupPage5();
	~CSetupPage5();

// Dialog Data
	//{{AFX_DATA(CSetupPage5)
	enum { IDD = IDD_PROPPAGE5 };
	BOOL	m_bRunNow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSetupPage5)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSetupPage5)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __SETUPPAGES_H__
