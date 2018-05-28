/****************************************************************/
/*																*/
/*  SetupSheet.cpp												*/
/*																*/
/*  Implementation of the CSetupSheet class.					*/
/*	This file is part of the Setup application.					*/
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
#include "SetupSheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CSetupSheet, CPropertySheet)

CSetupSheet::CSetupSheet(CWnd* pWndParent)
	 : CPropertySheet(IDS_PROPSHT_CAPTION, pWndParent)
{
	// Add all of the property pages here.  Note that
	// the order that they appear in here will be
	// the order they appear in on screen.  By default,
	// the first page of the set is the active one.
	// One way to make a different property page the 
	// active one is to call SetActivePage().

	AddPage(&m_Page1);
	AddPage(&m_Page2);
	AddPage(&m_Page3);
	AddPage(&m_Page4);
	AddPage(&m_Page5);

	SetWizardMode();
}

CSetupSheet::~CSetupSheet()
{
}


BEGIN_MESSAGE_MAP(CSetupSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CSetupSheet)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CSetupSheet::OnDestroy() 
{
	AfxGetMainWnd()->PostMessage(WM_QUIT);
	CPropertySheet::OnDestroy();
}
