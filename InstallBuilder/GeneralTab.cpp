/****************************************************************/
/*																*/
/*  GeneralTab.cpp												*/
/*																*/
/*  Implementation of the CGeneralTab class.					*/
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
#include "InstallBuilder.h"
#include "GeneralTab.h"

#include "InstallBuilderDoc.h"
#include "InstallBuilderView.h"

#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CGeneralTab::CGeneralTab(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneralTab)
	m_strCompanyName = _T("");
	m_strProductName = _T("");
	m_strProductURL = _T("");
	m_strProductVersion = _T("");
	m_strCopyrightNotice = _T("");
	m_strProductDescription = _T("");
	//}}AFX_DATA_INIT
}


void CGeneralTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralTab)
	DDX_Text(pDX, IDC_COMPANYNAME, m_strCompanyName);
	DDX_Text(pDX, IDC_PRODUCTNAME, m_strProductName);
	DDX_Text(pDX, IDC_PRODUCTURL, m_strProductURL);
	DDX_Text(pDX, IDC_PRODUCTVERSION, m_strProductVersion);
	DDX_Text(pDX, IDC_COPYRIGHTNOTICE, m_strCopyrightNotice);
	DDX_Text(pDX, IDC_PRODUCTDESCRIPTION, m_strProductDescription);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralTab, CDialog)
	//{{AFX_MSG_MAP(CGeneralTab)
	ON_EN_CHANGE(IDC_COMPANYNAME, OnChangeCompanyname)
	ON_EN_CHANGE(IDC_PRODUCTNAME, OnChangeProductname)
	ON_EN_CHANGE(IDC_PRODUCTVERSION, OnChangeProductversion)
	ON_EN_CHANGE(IDC_PRODUCTDESCRIPTION, OnChangeProductdescription)
	ON_EN_CHANGE(IDC_PRODUCTURL, OnChangeProducturl)
	ON_EN_CHANGE(IDC_COPYRIGHTNOTICE, OnChangeCopyrightnotice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CGeneralTab::OnChangeCompanyname() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strCompanyName = m_strCompanyName;
	pDoc->SetModifiedFlag();
}

void CGeneralTab::OnChangeProductname() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strProductName = m_strProductName;	
	pDoc->SetModifiedFlag();
}

void CGeneralTab::OnChangeProductversion() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strProductVersion = m_strProductVersion;	
	pDoc->SetModifiedFlag();
}

void CGeneralTab::OnChangeProductdescription() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strProductDescription = m_strProductDescription;	
	pDoc->SetModifiedFlag();
}

void CGeneralTab::OnChangeProducturl() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strProductURL = m_strProductURL;	
	pDoc->SetModifiedFlag();
}

void CGeneralTab::OnChangeCopyrightnotice() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strCopyrightNotice = m_strCopyrightNotice;	
	pDoc->SetModifiedFlag();
}

void CGeneralTab::OnOK() 
{
//	CDialog::OnOK();
}

void CGeneralTab::OnCancel() 
{
//	CDialog::OnCancel();
}



