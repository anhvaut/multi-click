/****************************************************************/
/*																*/
/*  InstallBuilderView.cpp										*/
/*																*/
/*  Implementation of the CInstallBuilderView class.			*/
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

#include "InstallBuilderDoc.h"
#include "InstallBuilderView.h"
#include "GeneralTab.h"
#include "FilesTab.h"
#include "ShortcutTab.h"
#include "OutputTab.h"

#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CInstallBuilderView, CFormView)

BEGIN_MESSAGE_MAP(CInstallBuilderView, CFormView)
	//{{AFX_MSG_MAP(CInstallBuilderView)
	ON_WM_SIZE()
	ON_COMMAND(ID_PROJECT_GENERAL, OnProjectGeneral)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_GENERAL, OnUpdateProjectGeneral)
	ON_COMMAND(ID_PROJECT_OUTPUT, OnProjectOutput)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_OUTPUT, OnUpdateProjectOutput)
	ON_COMMAND(ID_PROJECT_SHORTCUTS, OnProjectShortcuts)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_SHORTCUTS, OnUpdateProjectShortcuts)
	ON_COMMAND(ID_PROJECT_FILES, OnProjectFiles)
	ON_UPDATE_COMMAND_UI(ID_PROJECT_FILES, OnUpdateProjectFiles)
	ON_COMMAND(ID_BUILD_SETUP, OnBuildSetup)
	ON_COMMAND(ID_TESTRUNSETUP, OnTestrunsetup)
	ON_UPDATE_COMMAND_UI(ID_TESTRUNSETUP, OnUpdateTestrunsetup)
	ON_COMMAND(ID_BUILD_ADDREMOVEPROGRAMS, OnBuildAddremoveprograms)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CInstallBuilderView::CInstallBuilderView()
	: CFormView(CInstallBuilderView::IDD)
{
	//{{AFX_DATA_INIT(CInstallBuilderView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bOutputFileExists = FALSE;
}

CInstallBuilderView::~CInstallBuilderView()
{

}

void CInstallBuilderView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInstallBuilderView)
	DDX_Control(pDX, IDC_TABCTRL, m_TabCtrl);
	//}}AFX_DATA_MAP
}

BOOL CInstallBuilderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}


/********************************************************************/
/*																	*/
/* Function name : OnInitialUpdate									*/
/* Description   : Initialize view when document is loaded.			*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// only resize once
	static BOOL bInitialized = FALSE;
	if (!bInitialized)
	{
		GetParentFrame()->RecalcLayout();
		ResizeParentToFit();
		bInitialized = TRUE;
	}

	// initialize General Page
	((CGeneralTab *)m_TabCtrl.m_tabPages[0])->m_strCompanyName = GetDocument()->m_strCompanyName;
	((CGeneralTab *)m_TabCtrl.m_tabPages[0])->m_strCopyrightNotice = GetDocument()->m_strCopyrightNotice;
	((CGeneralTab *)m_TabCtrl.m_tabPages[0])->m_strProductDescription = GetDocument()->m_strProductDescription;
	((CGeneralTab *)m_TabCtrl.m_tabPages[0])->m_strProductName = GetDocument()->m_strProductName;
	((CGeneralTab *)m_TabCtrl.m_tabPages[0])->m_strProductURL = GetDocument()->m_strProductURL;
	((CGeneralTab *)m_TabCtrl.m_tabPages[0])->m_strProductVersion = GetDocument()->m_strProductVersion;
	((CGeneralTab *)m_TabCtrl.m_tabPages[0])->UpdateData(FALSE);

	// initialize Output Page
	((COutputTab *)m_TabCtrl.m_tabPages[3])->m_strOutputFolder = GetDocument()->m_strOutputFolder;
	((COutputTab *)m_TabCtrl.m_tabPages[3])->m_strSetupFileName = GetDocument()->m_strSetupFileName;
	((COutputTab *)m_TabCtrl.m_tabPages[3])->m_strApplicationName = GetDocument()->m_strApplicationName;
	((COutputTab *)m_TabCtrl.m_tabPages[3])->m_bShowCheckbox = GetDocument()->m_bShowRunCheckbox;
	((COutputTab *)m_TabCtrl.m_tabPages[3])->UpdateData(FALSE);
	((COutputTab *)m_TabCtrl.m_tabPages[3])->UpdateDialogControls(((COutputTab *)m_TabCtrl.m_tabPages[3]), FALSE);

	int i;

	// initialize Files Page
	((CFilesTab *)m_TabCtrl.m_tabPages[1])->m_FilesList.DeleteAllItems();
	for (i=0; i < GetDocument()->m_strFiles.GetSize(); i++)
	{
		AddFile(GetDocument()->m_strFiles[i]);
	}
	AutoSizeColumns(&((CFilesTab *)m_TabCtrl.m_tabPages[1])->m_FilesList);

	// initialize Shortcut Page
	((CShortcutTab *)m_TabCtrl.m_tabPages[2])->m_ShortcutList.DeleteAllItems();
	for (i=0; i < GetDocument()->m_ShortcutObjects.GetSize(); i++)
	{
		AddShortcut(GetDocument()->m_ShortcutObjects[i], i);
	}
	AutoSizeColumns(&((CShortcutTab *)m_TabCtrl.m_tabPages[2])->m_ShortcutList);

	CString strOutputFile = GetDocument()->m_strOutputFolder;
	if (strOutputFile.Right(1) != '\\')
		strOutputFile += "\\";
	
	strOutputFile += GetDocument()->m_strSetupFileName;

	// check if output file exists
	DWORD dwAttributes = GetFileAttributes(strOutputFile);
	if (dwAttributes != 0xFFFFFFFF)
	{
		m_bOutputFileExists = TRUE;
	}
}


#ifdef _DEBUG
void CInstallBuilderView::AssertValid() const
{
	CFormView::AssertValid();
}

void CInstallBuilderView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CInstallBuilderDoc* CInstallBuilderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CInstallBuilderDoc)));
	return (CInstallBuilderDoc*)m_pDocument;
}
#endif //_DEBUG


/********************************************************************/
/*																	*/
/* Function name : OnSize											*/
/* Description   : Make tabctrl same size as view.					*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	if (IsWindow(m_TabCtrl.m_hWnd))
	{
		m_TabCtrl.MoveWindow(4, 4, cx - 8, cy - 8);
	}
}


/********************************************************************/
/*																	*/
/* Function name : AddFile											*/
/* Description   : Add file to list in Files Page.					*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::AddFile(LPCTSTR lpszFileName, BOOL bAddToDocument)
{
	int nIcon = GetIconIndex(lpszFileName, FALSE, FALSE);
	CString strSize;
	CFileFind filefind;

	// get file size
	if (filefind.FindFile(lpszFileName))
	{
		filefind.FindNextFile();
		strSize = FormatSize(filefind.GetLength());
	}
	else
		strSize = FormatSize(0);
	
	// split path and filename
	CString strFileName = lpszFileName;
	CString strPath;

	int nPos = strFileName.ReverseFind('\\');
	if (nPos != -1)
	{
		strPath = strFileName.Left(nPos);
		strFileName = strFileName.Mid(nPos + 1);
	}

	// insert to list
	int nItem = ((CFilesTab *)m_TabCtrl.m_tabPages[1])->m_FilesList.GetItemCount();
	((CFilesTab *)m_TabCtrl.m_tabPages[1])->m_FilesList.InsertItem(nItem, strFileName, nIcon);
	((CFilesTab *)m_TabCtrl.m_tabPages[1])->m_FilesList.SetItemText(nItem, 1, strSize);
	((CFilesTab *)m_TabCtrl.m_tabPages[1])->m_FilesList.SetItemText(nItem, 2, GetTypeName(lpszFileName));
	((CFilesTab *)m_TabCtrl.m_tabPages[1])->m_FilesList.SetItemText(nItem, 3, strPath);

	if (bAddToDocument)
	{
		GetDocument()->m_strFiles.Add(lpszFileName);
		GetDocument()->SetModifiedFlag();
	}
}


/********************************************************************/
/*																	*/
/* Function name : RemoveFile										*/
/* Description   : Remove file from filelist.						*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::RemoveFile(LPCTSTR lpszFileName)
{
	for (int i=0; i < GetDocument()->m_strFiles.GetSize(); i++)
	{
		if (GetDocument()->m_strFiles[i].CompareNoCase(lpszFileName) == 0)
		{
			GetDocument()->m_strFiles.RemoveAt(i);
			GetDocument()->SetModifiedFlag();
		}
	}
}

/********************************************************************/
/*																	*/
/* Function name : AddShortcut										*/
/* Description   : Add shortcut to list in Shortcut Page.			*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::AddShortcut(CShortcutObject &shortcutObject, int nIndex)
{
	int nItem = ((CShortcutTab *)m_TabCtrl.m_tabPages[2])->m_ShortcutList.GetItemCount();
	((CShortcutTab *)m_TabCtrl.m_tabPages[2])->m_ShortcutList.InsertItem(nItem, shortcutObject.m_strName, 0);
	((CShortcutTab *)m_TabCtrl.m_tabPages[2])->m_ShortcutList.SetItemText(nItem, 1, "File Shortcut");
	((CShortcutTab *)m_TabCtrl.m_tabPages[2])->m_ShortcutList.SetItemText(nItem, 2, shortcutObject.m_strTarget);

	if (nIndex == -1)
	{
		nIndex = GetDocument()->m_ShortcutObjects.Add(shortcutObject);
		GetDocument()->SetModifiedFlag();
	}
//	((CShortcutTab *)m_TabCtrl.m_tabPages[2])->m_ShortcutList.SetItemData(nItem, nIndex);
}


/********************************************************************/
/*																	*/
/* Function name : OnProjectGeneral									*/
/* Description   : Activate General Page.							*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnProjectGeneral() 
{
	m_TabCtrl.SetCurFocusEx(0);
}


/********************************************************************/
/*																	*/
/* Function name : OnUpdateProjectGeneral							*/
/* Description   : Set check state of Project->General menu.		*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnUpdateProjectGeneral(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TabCtrl.m_nCurrentPage == 0);
}


/********************************************************************/
/*																	*/
/* Function name : OnProjectOutput									*/
/* Description   : Activate Output Page.							*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnProjectOutput() 
{
	m_TabCtrl.SetCurFocusEx(3);
}


/********************************************************************/
/*																	*/
/* Function name : OnInitialUpdate									*/
/* Description   : Set check state of Project->Output menu.			*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnUpdateProjectOutput(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TabCtrl.m_nCurrentPage == 3);
}


/********************************************************************/
/*																	*/
/* Function name : OnProjectShortcuts								*/
/* Description   : Activate Shortcut Page.							*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnProjectShortcuts() 
{
	m_TabCtrl.SetCurFocusEx(2);
}


/********************************************************************/
/*																	*/
/* Function name : OnUpdateProjectShortcuts							*/
/* Description   : Set check state of Project->Shortcut menu.		*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnUpdateProjectShortcuts(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TabCtrl.m_nCurrentPage == 2);	
}


/********************************************************************/
/*																	*/
/* Function name : OnProjectFiles									*/
/* Description   : Activate Files Page.								*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnProjectFiles() 
{
	m_TabCtrl.SetCurFocusEx(1);	
}


/********************************************************************/
/*																	*/
/* Function name : OnUpdateProjectFiles								*/
/* Description   : Set check state of Project->Files menu.			*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnUpdateProjectFiles(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_TabCtrl.m_nCurrentPage == 1);	
}


/********************************************************************/
/*																	*/
/* Function name : OnBuildSetup										*/
/* Description   : Build the setup output file.						*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnBuildSetup() 
{
	CreateDirectories(GetDocument()->m_strOutputFolder);

	// create the output filename
	CString strOutputFile = GetDocument()->m_strOutputFolder;

	if (strOutputFile.Right(1) != '\\')
		strOutputFile += "\\";

	CString strSetupFile = strOutputFile;

	CString strTitle = GetDocument()->GetTitle();	
	int nPos = strTitle.ReverseFind('.');
	if (nPos != -1)
		strTitle = strTitle.Left(nPos);

	strSetupFile += strTitle;
	strSetupFile += ".inf";

	// create 'Microsoft compatible' setup script
	CreateSetupScript(strSetupFile);

	strOutputFile += GetDocument()->m_strSetupFileName;

	CWaitCursor waitCursor;

	if (!CreateStubFile(strOutputFile))
	{
		MessageBox("Could not create output file!", "Extracting Stub", MB_ICONSTOP);
		return;
	}

	// add files to package
	FILE *outputfile;
	if ((outputfile = fopen(strOutputFile, "ab")) != NULL)
	{
		for (int i=0; i<GetDocument()->m_strFiles.GetSize(); i++)
		{
			AppendFile(GetDocument()->m_strFiles[i], outputfile);
		}
		// last file in the package is the setup file
		AppendFile(strSetupFile, outputfile);
		fclose(outputfile);
		m_bOutputFileExists = TRUE;

		MessageBox("Setup program succesfully created!", "Build Setup", MB_OK | MB_ICONINFORMATION);
	}
	// delete temporary setup script
	DeleteFile(strSetupFile);
}


/********************************************************************/
/*																	*/
/* Function name : AppendFile										*/
/* Description   : Append file to setup package.					*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::AppendFile(LPCTSTR lpszFileName, FILE* file)
{
    FILE* inputfile;
    int ch;
    FILETIME filetime[3];
    HANDLE hFile = CreateFile(lpszFileName, GENERIC_READ,
					FILE_SHARE_READ, 0, OPEN_EXISTING,
					FILE_ATTRIBUTE_NORMAL, 0 );
    if (hFile == INVALID_HANDLE_VALUE )
    {
        CString strError;
		strError.Format("File %s not found!", lpszFileName);
		AfxMessageBox(strError);
        return;
    }

    GetFileTime(hFile, &filetime[0], &filetime[1], &filetime[2]);
    CloseHandle(hFile);

	// 'begin of file' marker
	CString strTag = "{58A60076-593E-414e-8152-BD3516480CAA}";
	strTag.MakeReverse();
	// write marker
    fwrite(strTag, strTag.GetLength(), 1, file);
	// write time stamps(used for restoring original time stamps)
    fwrite(filetime, sizeof(FILETIME), 3, file);

	// write filename
	CString strFileName = lpszFileName;
	int nPos = strFileName.ReverseFind('\\');
	if (nPos >= 0)
		strFileName = strFileName.Right(strFileName.GetLength() - nPos - 1);
		
    fwrite(strFileName, strFileName.GetLength() + 1, 1, file);
	// copy all bytes to setup package
    if ((inputfile = fopen(lpszFileName, "rb")) != NULL)
	{
		while ((ch = fgetc(inputfile)) != EOF) 
			fputc(ch, file);
		fclose(inputfile);
	}
}


/********************************************************************/
/*																	*/
/* Function name : CreateSetupScript								*/
/* Description   : Create setup script.								*/
/*																	*/
/********************************************************************/
BOOL CInstallBuilderView::CreateSetupScript(LPCTSTR lpszFileName)
{
	CString strTitle = GetDocument()->GetTitle();
	
	int i;
	char szShortPathName[MAX_PATH];

	int nPos = strTitle.ReverseFind('.');
	if (nPos != -1)
		strTitle = strTitle.Left(nPos);

	CFile myFile(lpszFileName, CFile::modeWrite | CFile::modeCreate);
	CString strLine;

	try
	{
		// Create a storing archive.
		CArchive arStore(&myFile, CArchive::store);

		// get short filename
		GetShortPathName(lpszFileName, szShortPathName, MAX_PATH);
		CString strShortInf = GetFileName(szShortPathName);
		
		arStore.WriteString("[version]\r\n");
		arStore.WriteString("signature = \"$CHICAGO$\"\r\n\r\n");

		// create setup.inf header (win9x)
		arStore.WriteString("[DefaultInstall]\r\n");
		strLine = "CopyFiles = " + strTitle + ".Files1, " + strTitle + ".Copy.Inf\r\n";
		arStore.WriteString(strLine);
		strLine = "UpdateInis = " + strTitle + ".Inis\r\n";
		arStore.WriteString(strLine);
		strLine = "Uninstall = DefaultUninstall\r\n";
		arStore.WriteString(strLine);
		strLine = "AddReg = " + strTitle + ".Add.Reg\r\n\r\n";
		arStore.WriteString(strLine);

		// create setup.inf header (NT)
		arStore.WriteString("[DefaultInstall.NT]\r\n");
		strLine = "CopyFiles = " + strTitle + ".Files1, " + strTitle + ".Copy.Inf\r\n";
		arStore.WriteString(strLine);
		strLine = "UpdateInis = " + strTitle + ".Inis\r\n";
		arStore.WriteString(strLine);
		strLine = "Uninstall = DefaultUninstall\r\n";
		arStore.WriteString(strLine);
		strLine = "AddReg = " + strTitle + ".Add.RegNT\r\n\r\n";
		arStore.WriteString(strLine);

		// [DefaultUninstall]
		arStore.WriteString("[DefaultUninstall]\r\n");
		strLine = "DelFiles = " + strTitle + ".Files1, " + strTitle + ".Copy.Inf\r\n";
		arStore.WriteString(strLine);
		strLine = "UpdateInis = " + strTitle + ".Del.Inis\r\n";
		arStore.WriteString(strLine);
		strLine = "DelReg = " + strTitle + ".Del.Reg\r\n\r\n";
		arStore.WriteString(strLine);

		strLine = "[" + strTitle + ".Inis]\r\n";
		arStore.WriteString(strLine);
		
		// Program Group Name
		strLine = "setup.ini, progman.groups,, \"group321=%AppGroup%\"\r\n";
		arStore.WriteString(strLine);

		for (i=0; i<GetDocument()->m_ShortcutObjects.GetSize(); i++)
		{
			GetShortPathName(GetDocument()->m_ShortcutObjects[i].m_strOriginalPath, szShortPathName, MAX_PATH);
			CString strTarget = GetDocument()->m_ShortcutObjects[i].m_strTarget;
			int nPos = strTarget.ReverseFind('\\');
			if (nPos >= 0)
				strTarget = strTarget.Left(nPos + 1);

			strTarget += GetFileName(szShortPathName);
			strLine = "setup.ini, group321,, \"\"\"" + GetDocument()->m_ShortcutObjects[i].m_strName +
						"\"\", " + strTarget + "\"\r\n";
			arStore.WriteString(strLine);
		}
		arStore.WriteString("\r\n");

		// [App.Del.Inis]
		strLine = "[" + strTitle + ".Del.Inis]\r\n";
		arStore.WriteString(strLine);
		strLine = "setup.ini, progman.groups,, \"group322=%AppGroup%\"\r\n";
		arStore.WriteString(strLine);
		for (i=0; i<GetDocument()->m_ShortcutObjects.GetSize(); i++)
		{
			strLine = "setup.ini, group322,, \"\"\"" + GetDocument()->m_ShortcutObjects[i].m_strName + "\"\"\"\r\n";
			arStore.WriteString(strLine);
		}
		arStore.WriteString("\r\n");

		// [App.Add.Reg]
		strLine = "[" + strTitle + ".Add.Reg]\r\n";
		arStore.WriteString(strLine);
		
		strLine = "HKLM,Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + strTitle + 
					",DisplayName,,\"%AppName%\"\r\n";
		arStore.WriteString(strLine);

		strLine = "HKLM,Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + strTitle + 
					",UninstallString,,\"%10%\\%w95u1% %wu2% %17%\\" + strShortInf + "\"\r\n";
		arStore.WriteString(strLine);
		arStore.WriteString("\r\n");

		// [App.Add.RegNT]
		strLine = "[" + strTitle + ".Add.RegNT]\r\n";
		arStore.WriteString(strLine);

		strLine = "HKLM,Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + strTitle + 
					",DisplayName,,\"%AppName%\"\r\n";
		arStore.WriteString(strLine);
		strLine = "HKLM,Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + strTitle + 
					",UninstallString,,\"%wNTu1% %wu2% %17%\\" + strShortInf + "\"\r\n";
		arStore.WriteString(strLine);
		arStore.WriteString("\r\n");

		// [App.Del.Reg]
		strLine = "[" + strTitle + ".Del.Reg]\r\n";
		arStore.WriteString(strLine);
		strLine = "HKLM,Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\" + strTitle + "\r\n";
		arStore.WriteString(strLine);
		arStore.WriteString("\r\n");

		// [App.Files1]
		strLine = "[" + strTitle + ".Files1]\r\n";
		arStore.WriteString(strLine);
		for (i=0; i<GetDocument()->m_strFiles.GetSize(); i++)
		{
			// make short filename -> setup doesn't understand long file names !!!
			GetShortPathName(GetDocument()->m_strFiles[i], szShortPathName, MAX_PATH);
			strLine = GetFileName(szShortPathName);
//			strLine = GetDocument()->m_strFiles[i];

			arStore.WriteString(strLine);
			arStore.WriteString("\r\n");
		}
		arStore.WriteString("\r\n");

		// [App.Copy.Inf]
		strLine = "[" + strTitle + ".Copy.Inf]\r\n";
		arStore.WriteString(strLine);
		arStore.WriteString(strShortInf + "\r\n");
		arStore.WriteString("\r\n");

		// [SourceDisksNames]
		arStore.WriteString("[SourceDisksNames]\r\n");
		strLine = "55=\"" + strTitle + " Files\",\"\",1\r\n";
		arStore.WriteString(strLine);
		arStore.WriteString("\r\n");

		// [SourceDisksFiles]
		arStore.WriteString("[SourceDisksFiles]\r\n");
		for (i=0; i<GetDocument()->m_strFiles.GetSize(); i++)
		{
			// make short filename -> setup doesn't understand long file names !!!
			GetShortPathName(GetDocument()->m_strFiles[i], szShortPathName, MAX_PATH);
			strLine = GetFileName(szShortPathName);
//			strLine = GetDocument()->m_strFiles[i];
//			nPos = strLine.ReverseFind('\\');
//			if (nPos != -1)
//				strLine = strLine.Mid(nPos + 1);

			strLine = strLine + " = 55\r\n";
			arStore.WriteString(strLine);
		}
		arStore.WriteString(strShortInf + " = 55\r\n");
		arStore.WriteString("\r\n");

		// [DestinationDirs]
		arStore.WriteString("[DestinationDirs]\r\n");
		strLine = strTitle + ".Files1=24,%AppDir%\r\n";
		arStore.WriteString(strLine);
		strLine = strTitle + ".Copy.Inf=17\r\n";
		arStore.WriteString(strLine);
		arStore.WriteString("\r\n");

		// [Strings]
		arStore.WriteString("[Strings]\r\n");
		arStore.WriteString("w95u1=\"rundll.exe setupx.dll,InstallHinfSection\"\r\n");
		arStore.WriteString("wNTu1=\"RunDll32 syssetup.dll,SetupInfObjectInstallAction\"\r\n");
		arStore.WriteString("wu2=\"DefaultUninstall 132\"\r\n");

		// the following two fields will be filled by the setup application and must be SFN
		arStore.WriteString("AppDir=\r\n");
		arStore.WriteString("AppGroup=\r\n");

		// some general stuff
		strLine = "AppName = \"" + GetDocument()->m_strProductName + "\"\r\n";
		arStore.WriteString(strLine);
		strLine = "CopyrightMessage=" + GetDocument()->m_strCopyrightNotice + ". All rights reserved. " +
				GetDocument()->m_strCompanyName + ". " + GetDocument()->m_strProductURL + ".";
		arStore.WriteString(strLine);
		arStore.WriteString("\r\n");
		if (GetDocument()->m_bShowRunCheckbox)
		{
			strLine = "AppExe = \"" + GetDocument()->m_strApplicationName + "\"\r\n";
			arStore.WriteString(strLine);
		}
		arStore.WriteString("\r\n");
		
		// [Rename]
		arStore.WriteString("[Rename]\r\n");
		for (i=0; i<GetDocument()->m_strFiles.GetSize(); i++)
		{
			GetShortPathName(GetDocument()->m_strFiles[i], szShortPathName, MAX_PATH);
			strLine = GetFileName(szShortPathName);

			strLine = strLine + " = " + GetFileName(GetDocument()->m_strFiles[i]) + "\r\n";
			arStore.WriteString(strLine);
		}
	}
	catch(CFileException *e)
	{
		e->Delete();
	}
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : OnTestrunsetup									*/
/* Description   : Execute setup program.							*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnTestrunsetup() 
{
	CString strOutputFile = GetDocument()->m_strOutputFolder;
	if (strOutputFile.Right(1) != '\\')
		strOutputFile += "\\";
	
	strOutputFile += GetDocument()->m_strSetupFileName;

	// check if output file exists
	DWORD dwAttributes = GetFileAttributes(strOutputFile);
	if (dwAttributes != 0xFFFFFFFF)
	{
		ShellExecute(m_hWnd, "open", strOutputFile,	NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		m_bOutputFileExists = FALSE;
	}
}


/********************************************************************/
/*																	*/
/* Function name : OnUpdateTestrunsetup								*/
/* Description   : Check if setup program exists.					*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnUpdateTestrunsetup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bOutputFileExists);
	((COutputTab *)m_TabCtrl.m_tabPages[3])->GetDlgItem(IDC_TESTRUN)->EnableWindow(m_bOutputFileExists);
}


/********************************************************************/
/*																	*/
/* Function name : CreateStubFile									*/
/* Description   : Create stub file, this file contains the 'real'	*/
/*				   setup application.								*/
/*																	*/
/********************************************************************/
BOOL CInstallBuilderView::CreateStubFile(LPCTSTR lpszFileName)
{
	// Get the instance handle - required for loading the resource
    HINSTANCE hInst = AfxGetInstanceHandle();

    // Load the user-defined resource.
    HRSRC hExeFile = ::FindResource(hInst, "STUB.EXE", "EXE_RESOURCE");
    HGLOBAL hRes = ::LoadResource(hInst, hExeFile);
    DWORD dwSize = ::SizeofResource(hInst, hExeFile);

	if (hRes != NULL)
    {
		UINT FAR* lpnRes = (UINT FAR*)::LockResource(hRes);

        TRY
        {
			// Create the .exe file
            CFile file(lpszFileName, CFile::modeCreate | CFile::modeWrite);

            // Write the user-defined resource to the .exe file
            file.Write(lpnRes, dwSize);
			
            file.Flush();
        }
        CATCH(CFileException, e)
        {
		}
        END_CATCH
        ::FreeResource(hRes);
		return TRUE;
	}
	return FALSE;
} 


/********************************************************************/
/*																	*/
/* Function name : GetFileName										*/
/* Description   : Get filename from complete path.					*/
/*																	*/
/********************************************************************/
CString CInstallBuilderView::GetFileName(LPCTSTR lpszPathName)
{
	CString strResult = lpszPathName;

	int nPos = strResult.ReverseFind('\\');
	if (nPos >= 0)
		strResult = strResult.Right(strResult.GetLength() - nPos - 1);

	return strResult;
}


/********************************************************************/
/*																	*/
/* Function name : OnBuildAddremoveprograms							*/
/* Description   : Call Add/Remove Program Control Panel component.	*/
/*																	*/
/********************************************************************/
void CInstallBuilderView::OnBuildAddremoveprograms() 
{
	char szPath[MAX_PATH];
	GetSystemDirectory(szPath, MAX_PATH);
	ShellExecute(m_hWnd, "open", "control.exe", "appwiz.cpl", szPath, SW_SHOW);
}



