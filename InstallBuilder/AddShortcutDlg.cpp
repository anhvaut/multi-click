/****************************************************************/
/*																*/
/*  AddShortcutDlg.cpp											*/
/*																*/
/*  Implementation of the CAddShortcutDlg class.				*/
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
#include "AddShortcutDlg.h"
#include "ChooseFileDlg.h"

#include "InstallBuilderDoc.h"
#include "InstallBuilderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CAddShortcutDlg::CAddShortcutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddShortcutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddShortcutDlg)
	m_strName = _T("");
	m_strTarget = _T("");
	m_strWorkingDir = _T("");
	m_strIconPath = _T("");
	m_strCmdLine = _T("");
	m_nIconIndex = 0;
	//}}AFX_DATA_INIT
}


void CAddShortcutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddShortcutDlg)
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_TARGET, m_strTarget);
	DDX_Text(pDX, IDC_WORKINGDIR, m_strWorkingDir);
	DDX_Text(pDX, IDC_ICONPATH, m_strIconPath);
	DDX_Text(pDX, IDC_CMDLINE, m_strCmdLine);
	DDX_Text(pDX, IDC_ICONINDEX, m_nIconIndex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddShortcutDlg, CDialog)
	//{{AFX_MSG_MAP(CAddShortcutDlg)
	ON_BN_CLICKED(IDC_BROWSE_TARGET, OnBrowseTarget)
	ON_BN_CLICKED(IDC_BROWSE_ICON, OnBrowseIcon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CAddShortcutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (!m_strTitle.IsEmpty())
		SetWindowText(m_strTitle);
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : OnBrowseTarget									*/
/* Description   : Browse for target file							*/
/*																	*/
/********************************************************************/
void CAddShortcutDlg::OnBrowseTarget() 
{
	UpdateData();

	CChooseFileDlg dlg;

	for (int i=0; i<m_strFiles.GetSize(); i++)
		dlg.m_strFiles.Add(m_strFiles[i]);

	if (dlg.DoModal() == IDOK)
	{
		m_strTarget = "%AppDir%\\" + dlg.m_strFileName;
		m_strOriginalPath = dlg.m_strPathName;
		UpdateData(FALSE);
	}
}


/********************************************************************/
/*																	*/
/* Function name : OnBrowseIcon										*/
/* Description   : Browse for icon.									*/
/*																	*/
/********************************************************************/
void CAddShortcutDlg::OnBrowseIcon() 
{
	UpdateData();

	CChooseFileDlg dlg;

	for (int i=0; i<m_strFiles.GetSize(); i++)
		dlg.m_strFiles.Add(m_strFiles[i]);

	if (dlg.DoModal() == IDOK)
	{
		m_strIconPath = "%AppDir%\\" + dlg.m_strFileName;
		UpdateData(FALSE);
	}	
}
