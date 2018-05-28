/****************************************************************/
/*																*/
/*  InstallBuilder.cpp											*/
/*																*/
/*  Defines the class behaviors for the application.			*/
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

#include "MainFrm.h"
#include "InstallBuilderDoc.h"
#include "InstallBuilderView.h"
#include "WizardSheet.h"
#include "AboutDlg.h"

#include <afxpriv.h> // for WM_INITIALUPDATE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInstallBuilderApp

BEGIN_MESSAGE_MAP(CInstallBuilderApp, CWinApp)
	//{{AFX_MSG_MAP(CInstallBuilderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEWPROJECTWIZARD, OnProjectWizard)
	ON_COMMAND(ID_HELP_INDEX, OnHelpIndex)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInstallBuilderApp construction

CInstallBuilderApp::CInstallBuilderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CInstallBuilderApp object

CInstallBuilderApp theApp;


/********************************************************************/
/*																	*/
/* Function name : InitInstance										*/
/* Description   : CInstallBuilderApp initialization				*/
/*																	*/
/********************************************************************/
BOOL CInstallBuilderApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Pablo Software Solutions"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CInstallBuilderDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CInstallBuilderView));
	AddDocTemplate(m_pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : OnAppAbout										*/
/* Description   : Command to run the dialog.						*/
/*																	*/
/********************************************************************/
void CInstallBuilderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


/********************************************************************/
/*																	*/
/* Function name : OnProjectWizard									*/
/* Description   : Start new project wizard.						*/
/*																	*/
/********************************************************************/
void CInstallBuilderApp::OnProjectWizard() 
{
	CWizardSheet propSheet;
	if (propSheet.DoModal() == ID_WIZFINISH)
	{
		// create new document
		CDocument *pDoc = m_pDocTemplate->OpenDocumentFile(NULL);
		CInstallBuilderDoc *pSetupDoc = static_cast<CInstallBuilderDoc *>(pDoc);
		ASSERT_VALID(pSetupDoc);
		ASSERT_KINDOF(CInstallBuilderDoc, pSetupDoc);

		pSetupDoc->m_strCompanyName = propSheet.m_Page2.m_strCompanyName;
		pSetupDoc->m_strProductName = propSheet.m_Page2.m_strProductName;
		pSetupDoc->m_strProductURL = propSheet.m_Page2.m_strProductURL;
		pSetupDoc->m_strProductVersion = propSheet.m_Page2.m_strProductVersion;
		pSetupDoc->m_strCopyrightNotice = propSheet.m_Page2.m_strCopyrightNotice;
		pSetupDoc->m_strProductDescription = propSheet.m_Page2.m_strProductDescription;

		if (propSheet.m_Page3.m_strFolder.Right(1) != '\\')
		{
			propSheet.m_Page3.m_strFolder += "\\";
		}

		propSheet.m_Page3.m_strFolder += "*.*";

		// add files to document
		CFileFind finder;
		BOOL bContinue = finder.FindFile(propSheet.m_Page3.m_strFolder);
		while (bContinue)
		{
			bContinue = finder.FindNextFile();
			if (finder.IsDots() || finder.IsDirectory())
				continue;

			pSetupDoc->m_strFiles.Add(finder.GetFilePath());
		}

		pSetupDoc->SetModifiedFlag();

		// force initial update to all views (and other controls) in the frame
		m_pMainWnd->SendMessageToDescendants(WM_INITIALUPDATE, 0, 0, TRUE, TRUE);
	}
}


/********************************************************************/
/*																	*/
/* Function name : OnHelpIndex										*/
/* Description   : Command to show help file.						*/
/*																	*/
/********************************************************************/
void CInstallBuilderApp::OnHelpIndex() 
{
	// launch help
	::WinHelp(AfxGetMainWnd()->m_hWnd, AfxGetApp()->m_pszHelpFilePath, HELP_CONTENTS, 0L);
}


/********************************************************************/
/*																	*/
/* Function name : PreTranslateMessage								*/
/* Description   : Workaround to fix accelerators problem			*/
/*																	*/
/********************************************************************/
BOOL CInstallBuilderApp::PreTranslateMessage(MSG* pMsg) 
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
    HACCEL hAccel = pFrame->m_hAccelTable;

    if (hAccel && TranslateAccelerator(pFrame->m_hWnd, hAccel, pMsg))
		return TRUE;
	
	return CWinApp::PreTranslateMessage(pMsg);
}
