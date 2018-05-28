/****************************************************************/
/*																*/
/*  SetupPages.cpp												*/
/*																*/
/*  Implementation of the CSetup wizard classes.				*/
/*	This file is part of the Setup application.					*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 22 July 2002									*/
/*																*/
/****************************************************************/

#include "stdafx.h"
#include "Setup.h"
#include "resource.h"
#include "SetupPages.h"
#include "RegKey.h"
#include "SetupSheet.h"
#include "FileOperations.h"
#include ".\setuppages.h"
#include "FolderUtils.h"
#include "Shortcut.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSetupPage1, CPropertyPage)
IMPLEMENT_DYNCREATE(CSetupPage2, CPropertyPage)
IMPLEMENT_DYNCREATE(CSetupPage3, CPropertyPage)
IMPLEMENT_DYNCREATE(CSetupPage4, CPropertyPage)
IMPLEMENT_DYNCREATE(CSetupPage5, CPropertyPage)


CSetupPage1::CSetupPage1() : CPropertyPage(CSetupPage1::IDD)
{
	//{{AFX_DATA_INIT(CSetupPage1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CSetupPage1::~CSetupPage1()
{
}

void CSetupPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupPage1)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CSetupPage1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CSetupPage1::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString strText, strFormat;
	GetDlgItemText(IDC_TEXT1, strFormat);
	strText.Format(strFormat, ((CSetupApp *)AfxGetApp())->m_strApplicationName, ((CSetupApp *)AfxGetApp())->m_strApplicationName);
	SetDlgItemText(IDC_TEXT1, strText);
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : OnSetActive										*/
/* Description   : Called when this becomes the active page.		*/
/*																	*/
/********************************************************************/
BOOL CSetupPage1::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons(PSWIZB_NEXT);
	return CPropertyPage::OnSetActive();
}


CSetupPage2::CSetupPage2() : CPropertyPage(CSetupPage2::IDD)
{
	//{{AFX_DATA_INIT(CSetupPage2)
	m_strDestinationPath = _T("");
	//}}AFX_DATA_INIT

	CRegKey regKey;
	if (regKey.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion") == ERROR_SUCCESS)
	{
		char szProgramFiles[MAX_PATH];
		DWORD dwSize = MAX_PATH;

		if (regKey.QueryValue(szProgramFiles, "ProgramFilesDir", &dwSize) == ERROR_SUCCESS)
		{
			m_strDestinationPath.Format("%s\\%s", szProgramFiles, ((CSetupApp *)AfxGetApp())->m_strApplicationName);
		}
		regKey.Close();

	}
}

CSetupPage2::~CSetupPage2()
{
}

void CSetupPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupPage2)
	DDX_Text(pDX, IDC_DESTINATION_PATH, m_strDestinationPath);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CSetupPage2)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	//}}AFX_MSG_MAP
	ON_STN_CLICKED(IDC_TEXT1, OnStnClickedText1)
	ON_STN_CLICKED(IDC_TEXT2, OnStnClickedText2)
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnSetActive										*/
/* Description   : Called when this becomes the active page.		*/
/*																	*/
/********************************************************************/
BOOL CSetupPage2::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	
	return CPropertyPage::OnSetActive();
}


/********************************************************************/
/*																	*/
/* Function name : OnBrowse											*/
/* Description   : Browse for folder.								*/
/*																	*/
/********************************************************************/
void CSetupPage2::OnBrowse() 
{
	CString strDir = BrowseForFolder(m_hWnd, "Select a directory:", BIF_RETURNONLYFSDIRS);
	if (!strDir.IsEmpty())
	{
		GetDlgItem(IDC_DESTINATION_PATH)->SetWindowText(strDir);
	}		


}


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CSetupPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	CString strText, strFormat;
	GetDlgItemText(IDC_TEXT1, strFormat);
	strText.Format(strFormat, ((CSetupApp *)AfxGetApp())->m_strApplicationName);
	SetDlgItemText(IDC_TEXT1, strText);
	
	GetDlgItemText(IDC_TEXT2, strFormat);
	strText.Format(strFormat, ((CSetupApp *)AfxGetApp())->m_strApplicationName);
	SetDlgItemText(IDC_TEXT2, strText);
	
	

	///Copy MFC file vao windos System32

	CFileOperation fo;
	//fo.SetAskIfReadOnly(1);
	fo.SetOverwriteMode(1);
	char windowsPath[256];
	
	
	GetWindowsDirectory(windowsPath,sizeof(windowsPath));
	

	OSVERSIONINFO version;
	version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&version);
	if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
		strcat(windowsPath,"\\system32");
	else
		strcat(windowsPath,"\\system");
	
	
	if (!fo.Copy("./System32",windowsPath)) fo.ShowError();	

	
	

	////////////////////////////////////////////////////////////


	return TRUE;
}


CSetupPage3::CSetupPage3() : CPropertyPage(CSetupPage3::IDD)
{
	//{{AFX_DATA_INIT(CSetupPage3)
	m_strProgramFolder = ((CSetupApp *)AfxGetApp())->m_strApplicationName;
	//}}AFX_DATA_INIT
}

CSetupPage3::~CSetupPage3()
{
}

void CSetupPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupPage3)
	DDX_Control(pDX, IDC_EXISTINGFOLDERS, m_ExistingFolders);
	DDX_Text(pDX, IDC_PROGRAMFOLDER, m_strProgramFolder);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupPage3, CPropertyPage)
	//{{AFX_MSG_MAP(CSetupPage3)
	ON_LBN_SELCHANGE(IDC_EXISTINGFOLDERS, OnSelchangeExistingfolders)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/********************************************************************/
/*																	*/
/* Function name : OnSetActive										*/
/* Description   : Called when this becomes the active page.		*/
/*																	*/
/********************************************************************/
BOOL CSetupPage3::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);	
	return CPropertyPage::OnSetActive();
}

/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CSetupPage3::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString strFolder;
	if (GetStartMenuFolder(strFolder))
	{
		CFileFind fileFind;
		
		strFolder += "\\*.*";

		BOOL bContinue = fileFind.FindFile(strFolder);
		while (bContinue)
		{
			bContinue = fileFind.FindNextFile();
			if (fileFind.IsDots() || !fileFind.IsDirectory())
				continue;

			m_ExistingFolders.AddString(fileFind.GetFileName());
		}
	}





	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE


	
	

}


/********************************************************************/
/*																	*/
/* Function name : OnSelchangeExistingfolders						*/
/* Description   : Another folder has been selected.				*/
/*																	*/
/********************************************************************/
void CSetupPage3::OnSelchangeExistingfolders() 
{
	int nIndex = m_ExistingFolders.GetCurSel();
	if (nIndex != -1)
	{
		m_ExistingFolders.GetText(nIndex, m_strProgramFolder);
		UpdateData(FALSE);
	}
}



CSetupPage4::CSetupPage4() : CPropertyPage(CSetupPage4::IDD)
{
	//{{AFX_DATA_INIT(CSetupPage4)
	m_strCurrentSettings = _T("");
	//}}AFX_DATA_INIT
}

CSetupPage4::~CSetupPage4()
{
}

void CSetupPage4::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupPage4)
	DDX_Control(pDX, IDC_CURRENT_SETTINGS, m_EditCtrl);
	DDX_Text(pDX, IDC_CURRENT_SETTINGS, m_strCurrentSettings);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupPage4, CPropertyPage)
	//{{AFX_MSG_MAP(CSetupPage4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnSetActive										*/
/* Description   : Called when this becomes the active page.		*/
/*																	*/
/********************************************************************/
BOOL CSetupPage4::OnSetActive() 
{
	CSetupSheet* parent = (CSetupSheet*)GetParent();
	parent->SetWizardButtons(PSWIZB_NEXT | PSWIZB_BACK);

	m_strCurrentSettings = "Target Directory:\r\n " + parent->m_Page2.m_strDestinationPath +
							"\r\n\r\nProgram Manager Group:\r\n " + parent->m_Page3.m_strProgramFolder;
	UpdateData(FALSE);
	m_EditCtrl.SetSel(-1, 0);
	return CPropertyPage::OnSetActive();
}


/********************************************************************/
/*																	*/
/* Function name : OnWizardNext										*/
/* Description   : Called when Next button has been pressed.		*/
/*																	*/
/********************************************************************/
LRESULT CSetupPage4::OnWizardNext() 
{
	CString strSetupFile, strExtractFolder;

	CSetupSheet* parent = (CSetupSheet*)GetParent();

	CSetupApp *pApp = (CSetupApp *)AfxGetApp();
	pApp->GetSetupFileName(strSetupFile);
	pApp->GetExtractFolder(strExtractFolder);

	CString strDestinationPath = "Progra~1\\MyApp";
	

	// create directory to be able to get short pathname
	CreateDirectories(parent->m_Page2.m_strDestinationPath);

	if (::GetShortPathName(parent->m_Page2.m_strDestinationPath, strDestinationPath.GetBuffer(MAX_PATH), MAX_PATH) == 0)
	{
		// rare failure case (especially on not-so-modern file systems)
		strDestinationPath = parent->m_Page2.m_strDestinationPath;
	}

	


	strDestinationPath.ReleaseBuffer();

	
	/////// Tu viet : Copy file tu dien vao trong thu muc cai dat
	CFileOperation fo1;
	//fo.SetAskIfReadOnly(1);
	fo1.SetOverwriteMode(1);

	//if(!fo1.Copy("data",strDestinationPath))  fo1.ShowError();	
	CString imagesPath=strDestinationPath+"\\Images";
	CFolderUtils::CreateFolder(imagesPath);
	CString DatabasesPath=strDestinationPath+"\\Databases";
	CFolderUtils::CreateFolder(DatabasesPath);
	if(!fo1.Copy("data",DatabasesPath))  fo1.ShowError();	
	if(!fo1.Copy("image",imagesPath))  fo1.ShowError();	
	//Cfile f;
	//CFile f;
	
	
	//if(!fo1.Copy("./image",imagesPath))  fo1.ShowError();	
	
	////////


	int nPos = strDestinationPath.Find(':');
	if (nPos >= 0)
		strDestinationPath = "\"" + strDestinationPath.Right(strDestinationPath.GetLength() - nPos - 2) + "\"";

	WritePrivateProfileString("Strings", "AppDir", strDestinationPath, strSetupFile);
	WritePrivateProfileString("Strings", "AppGroup", "\"" + parent->m_Page3.m_strProgramFolder + "\"", strSetupFile);
	
	

	// execute setup.inf (and let Windows do the rest!)
    SHELLEXECUTEINFO si;

    si.cbSize		= sizeof(si); 
    si.fMask		= SEE_MASK_NOCLOSEPROCESS;
    si.hwnd			= 0; 
    si.lpVerb		= "Install";
    si.lpFile		= strSetupFile; 
    si.lpParameters = 0; 
    si.lpDirectory	= strExtractFolder;
    si.nShow		= SW_SHOWNORMAL; 
    
	if (ShellExecuteEx(&si) == 0)
    {
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL);
		// Display the string.
		MessageBox((LPCTSTR)lpMsgBuf, "Error while executing setup script", MB_OK | MB_ICONSTOP);
		// Free the buffer.
		LocalFree(lpMsgBuf);

		return CPropertyPage::OnWizardNext();
    }
    // wait for execution to complete
	WaitForSingleObject(si.hProcess, INFINITE);

	// give files their original name
	RenameFiles(strSetupFile, parent->m_Page2.m_strDestinationPath);

	
	/////////////// Copy tu dien vao thu muc cai dat

	


	
	return CPropertyPage::OnWizardNext();
}


CSetupPage5::CSetupPage5() : CPropertyPage(CSetupPage5::IDD)
{
	//{{AFX_DATA_INIT(CSetupPage5)
	m_bRunNow = TRUE;
	//}}AFX_DATA_INIT
}

CSetupPage5::~CSetupPage5()
{
}

void CSetupPage5::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupPage5)
	DDX_Check(pDX, IDC_RUN_NOW, m_bRunNow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupPage5, CPropertyPage)
	//{{AFX_MSG_MAP(CSetupPage5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/********************************************************************/
/*																	*/
/* Function name : OnSetActive										*/
/* Description   : Called when this becomes the active page.		*/
/*																	*/
/********************************************************************/
BOOL CSetupPage5::OnSetActive() 
{
	CPropertySheet* parent = (CPropertySheet*)GetParent();
	parent->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT | PSWIZB_FINISH);	
	return CPropertyPage::OnSetActive();
}


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CSetupPage5::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CString strText, strFormat;
	GetDlgItemText(IDC_TEXT1, strFormat);
	strText.Format(strFormat, ((CSetupApp *)AfxGetApp())->m_strApplicationName);
	SetDlgItemText(IDC_TEXT1, strText);	

	if (((CSetupApp *)AfxGetApp())->m_strApplicationExe.IsEmpty())
	{
		m_bRunNow = FALSE;
		UpdateData(FALSE);
		GetDlgItem(IDC_RUN_NOW)->ShowWindow(SW_HIDE);
	}



	return TRUE;
}


BOOL CSetupPage5::OnWizardFinish() 
{
	UpdateData();

	if (m_bRunNow)
	{
		CSetupSheet* parent = (CSetupSheet*)GetParent();
		parent->m_Page2.m_strDestinationPath.TrimRight('\\');
		
		CString strApplication = ((CSetupApp *)AfxGetApp())->m_strApplicationExe;
		strApplication.Replace("%AppDir%", parent->m_Page2.m_strDestinationPath);

		ShellExecute(m_hWnd, "open", strApplication, NULL, NULL, SW_SHOWNORMAL);
		
	}
/*
	//Create Shortcut
	CSetupSheet* parent1 = (CSetupSheet*)GetParent();
	CString thu=parent1->m_Page2.m_strDestinationPath.TrimRight('\\')+"\\MultiClick.exe";
	
	CString sBuf;
	CHAR *buf = sBuf.GetBuffer(MAX_PATH);
	GetSystemDirectory(buf, 256);
	lstrcat(buf,"\\shell32.dll");   
		sBuf.ReleaseBuffer();

	m_pShortcut->CreateShortCut("_this",
									"Test Link",
									CSIDL_DESKTOP,
									"Desktop ShellLink",
									sBuf,
									NULL))
									*/


	return CPropertyPage::OnWizardFinish();
}


/****************************************************************/
/*																*/
/* During setup all file name where short filenames				*/
/* We have to restore them to their original names				*/
/*																*/
/****************************************************************/
void CSetupPage4::RenameFiles(LPCTSTR lpszSetupFile, LPCTSTR lpszDestination)
{
	CFile myFile(lpszSetupFile, CFile::modeRead);
	CString strLine;

	CString strDestination = lpszDestination;
	if (strDestination.Right(1) != '\\')
		strDestination += "\\";

	BOOL bFlag = FALSE;

	myFile.SeekToBegin();
	
	// Create a loading archive.
	CArchive arLoad(&myFile, CArchive::load);

	// read one line at a time
	while(arLoad.ReadString(strLine) != NULL)
	{
		// trim leading and trailing spaces
		strLine.TrimLeft();
		strLine.TrimRight();
		if (strLine.IsEmpty())
		{
			// skip empty lines
			continue;
		}
		else
		// is this the data section ?
		if (strLine.CompareNoCase("[Rename]") == 0)
		{
			// from now on we're in the [Rename] section
			bFlag = TRUE;
			continue;
		}
		else
		if ((strLine.Find("[") != -1) && (strLine.Find("]") != -1))
		{
			// we're NOT in the [Rename] section
			bFlag = FALSE;
			continue;
		}
		// if this is a line in the [Rename] section -> rename file
		if (bFlag)
		{
			CString strShortName, strFullName;
			AfxExtractSubString(strShortName, strLine, 0, '=');
			strShortName.TrimLeft();
			strShortName.TrimRight();
			AfxExtractSubString(strFullName, strLine, 1, '=');
			strFullName.TrimLeft();
			strFullName.TrimRight();

			if (!strShortName.IsEmpty() && !strFullName.IsEmpty())
			{
				if (!MoveFile(strDestination + strShortName, strDestination + strFullName))
				{
					MessageBox("Failed to rename filename!", strDestination + strShortName, MB_OK | MB_ICONSTOP);
				}
			}
		}
	}
}

void CSetupPage2::OnStnClickedText1()
{
	// TODO: Add your control notification handler code here
}

void CSetupPage2::OnStnClickedText2()
{
	// TODO: Add your control notification handler code here
}
