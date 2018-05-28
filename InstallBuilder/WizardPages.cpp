/****************************************************************/
/*																*/
/*  WizardPages.cpp												*/
/*																*/
/*  Implementation of the Wizard classes.						*/
/*	This file is part of the Install Builder application.		*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 14 june 2002									*/
/*																*/
/****************************************************************/


#include "stdafx.h"
#include "resource.h"
#include "WizardPages.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CWizardPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CWizardPage2, CPropertyPage)
IMPLEMENT_DYNCREATE(CWizardPage3, CPropertyPage)
IMPLEMENT_DYNCREATE(CWizardPage4, CPropertyPage)


/////////////////////////////////////////////////////////////////////////////
// CWizardPage1 property page

CWizardPage1::CWizardPage1() : CPropertyPage(CWizardPage1::IDD)
{
	//{{AFX_DATA_INIT(CWizardPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CWizardPage1::~CWizardPage1()
{
}

void CWizardPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardPage1)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWizardPage2 property page

CWizardPage2::CWizardPage2() : CPropertyPage(CWizardPage2::IDD)
{
	//{{AFX_DATA_INIT(CWizardPage2)
	m_strCompanyName = AfxGetApp()->GetProfileString("Settings", "CompanyName", "My Company");
	m_strProductName = "My Application";
	m_strProductURL = AfxGetApp()->GetProfileString("Settings", "ProductURL", "www.pablovandermeer.nl");
	m_strProductVersion = "1.0";
	m_strCopyrightNotice = AfxGetApp()->GetProfileString("Settings", "CopyrightNotice", "Copyright (c) 2002");
	m_strProductDescription = "My Application Description";
	//}}AFX_DATA_INIT
}

CWizardPage2::~CWizardPage2()
{
}

void CWizardPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardPage2)
	DDX_Text(pDX, IDC_COMPANYNAME, m_strCompanyName);
	DDX_Text(pDX, IDC_PRODUCTNAME, m_strProductName);
	DDX_Text(pDX, IDC_PRODUCTURL, m_strProductURL);
	DDX_Text(pDX, IDC_PRODUCTVERSION, m_strProductVersion);
	DDX_Text(pDX, IDC_COPYRIGHTNOTICE, m_strCopyrightNotice);
	DDX_Text(pDX, IDC_PRODUCTDESCRIPTION, m_strProductDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardPage2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWizardPage3 property page

CWizardPage3::CWizardPage3() : CPropertyPage(CWizardPage3::IDD)
{
	//{{AFX_DATA_INIT(CWizardPage3)
	m_strFolder = _T("");
	//}}AFX_DATA_INIT
}

CWizardPage3::~CWizardPage3()
{
}

void CWizardPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardPage3)
	DDX_Text(pDX, IDC_FOLDER, m_strFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardPage3)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWizardPage4 property page

CWizardPage4::CWizardPage4() : CPropertyPage(CWizardPage4::IDD)
{
	//{{AFX_DATA_INIT(CWizardPage4)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CWizardPage4::~CWizardPage4()
{
}

void CWizardPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardPage4)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizardPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CWizardPage4)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CWizardPage1::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}

BOOL CWizardPage2::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	
	return CPropertyPage::OnSetActive();
}

BOOL CWizardPage3::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	
	return CPropertyPage::OnSetActive();
}

BOOL CWizardPage4::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_FINISH);	
	return CPropertyPage::OnSetActive();
}

void CWizardPage3::OnBrowse() 
{
	CString strDir = BrowseForFolder(m_hWnd, "Select a folder:", BIF_RETURNONLYFSDIRS);
	if (!strDir.IsEmpty())
	{
		GetDlgItem(IDC_FOLDER)->SetWindowText(strDir);
	}		
}

LRESULT CWizardPage3::OnWizardNext() 
{
	CEdit *editBox = (CEdit *)GetDlgItem(IDC_FOLDER);
	if (editBox->GetWindowTextLength() == 0)
	{
		MessageBox("You must enter a folder.", "Project Wizard",  MB_OK | MB_ICONEXCLAMATION);
		editBox->SetFocus();
		return -1;
	}		
	return CPropertyPage::OnWizardNext();
}
