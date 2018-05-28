/****************************************************************/
/*																*/
/*  OutputTab.cpp												*/
/*																*/
/*  Implementation of the COutputTab class.						*/
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
#include "OutputTab.h"
#include "ChooseFileDlg.h"
#include "InstallBuilderDoc.h"
#include "InstallBuilderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


COutputTab::COutputTab(CWnd* pParent /*=NULL*/)
	: CDialogResize(COutputTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutputTab)
	m_strOutputFolder = _T("");
	m_strSetupFileName = _T("");
	m_bShowCheckbox = FALSE;
	m_strApplicationName = _T("");
	//}}AFX_DATA_INIT
}


void COutputTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogResize::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputTab)
	DDX_Text(pDX, IDC_OUTPUTFOLDER, m_strOutputFolder);
	DDX_Text(pDX, IDC_SETUP_FILENAME, m_strSetupFileName);
	DDX_Check(pDX, IDC_SHOWCHECKBOX, m_bShowCheckbox);
	DDX_Text(pDX, IDC_APPLICATION, m_strApplicationName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutputTab, CDialogResize)
	//{{AFX_MSG_MAP(COutputTab)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_CHANGE(IDC_OUTPUTFOLDER, OnChangeOutputfolder)
	ON_EN_CHANGE(IDC_SETUP_FILENAME, OnChangeSetupFilename)
	ON_BN_CLICKED(IDC_BUILD, OnBuild)
	ON_BN_CLICKED(IDC_TESTRUN, OnTestrun)
	ON_BN_CLICKED(IDC_SHOWCHECKBOX, OnShowcheckbox)
	ON_EN_CHANGE(IDC_APPLICATION, OnChangeApplication)
	ON_BN_CLICKED(IDC_BROWSEAPP, OnBrowseapp)
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDC_BROWSEAPP, OnUpdateApplication)
	ON_UPDATE_COMMAND_UI(IDC_APPLICATION, OnUpdateApplication)
	ON_UPDATE_COMMAND_UI(IDC_STATIC1, OnUpdateApplication)
END_MESSAGE_MAP()


BEGIN_DLGRESIZE_MAP(COutputTab)
	DLGRESIZE_CONTROL(IDC_BROWSE, DLSZ_MOVE_X)
	DLGRESIZE_CONTROL(IDC_BROWSEAPP, DLSZ_MOVE_X)
	DLGRESIZE_CONTROL(IDC_APPLICATION, DLSZ_SIZE_X)
	DLGRESIZE_CONTROL(IDC_OUTPUTFOLDER, DLSZ_SIZE_X)
	DLGRESIZE_CONTROL(IDC_SETUP_FILENAME, DLSZ_SIZE_X)
	DLGRESIZE_CONTROL(IDC_BUILD, DLSZ_MOVE_X | DLSZ_MOVE_Y)
	DLGRESIZE_CONTROL(IDC_TESTRUN, DLSZ_MOVE_X | DLSZ_MOVE_Y)
END_DLGRESIZE_MAP()


void COutputTab::OnBrowse() 
{
	CString strDir = BrowseForFolder(m_hWnd, "Select a directory:", BIF_RETURNONLYFSDIRS);
	if (!strDir.IsEmpty())
	{
		GetDlgItem(IDC_OUTPUTFOLDER)->SetWindowText(strDir);
	}		
}


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL COutputTab::OnInitDialog() 
{
	CDialogResize::OnInitDialog();
	
	InitResizing(FALSE, TRUE, NULL);	
	
	return TRUE;
}

void COutputTab::OnOK() 
{
//	CDialogResize::OnOK();
}

void COutputTab::OnCancel() 
{
//	CDialogResize::OnCancel();
}

void COutputTab::OnChangeOutputfolder() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strOutputFolder = m_strOutputFolder;
	pDoc->SetModifiedFlag();	
}

void COutputTab::OnChangeSetupFilename() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strSetupFileName = m_strSetupFileName;
	pDoc->SetModifiedFlag();	
}


void COutputTab::OnBuild() 
{
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();	
	pView->SendMessage(WM_COMMAND, ID_BUILD_SETUP);
}

void COutputTab::OnTestrun() 
{
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();	
	pView->SendMessage(WM_COMMAND, ID_TESTRUNSETUP);

}

void COutputTab::OnShowcheckbox() 
{
	UpdateData();	
	UpdateDialogControls(this, FALSE);

	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_bShowRunCheckbox = m_bShowCheckbox;
	pDoc->SetModifiedFlag();
}


void COutputTab::OnUpdateApplication(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bShowCheckbox);	
}

void COutputTab::OnChangeApplication() 
{
	UpdateData();
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();
	pDoc->m_strApplicationName = m_strApplicationName;
	pDoc->SetModifiedFlag();	
}

void COutputTab::OnBrowseapp() 
{
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();

	CChooseFileDlg dlg;

	for (int i=0; i<pDoc->m_strFiles.GetSize(); i++)
		dlg.m_strFiles.Add(pDoc->m_strFiles[i]);

	if (dlg.DoModal() == IDOK)
	{
		m_strApplicationName = "%AppDir%\\" + dlg.m_strFileName;
		UpdateData(FALSE);

		pDoc->m_strApplicationName = m_strApplicationName;
		pDoc->SetModifiedFlag();	
	}	
}
