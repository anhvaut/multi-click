/****************************************************************/
/*																*/
/*  FilesTab.cpp												*/
/*																*/
/*  Implementation of the CFilesTab class.						*/
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
#include "FilesTab.h"

#include "InstallBuilderDoc.h"
#include "InstallBuilderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CFilesTab::CFilesTab(CWnd* pParent /*=NULL*/)
	: CDialogResize(CFilesTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFilesTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFilesTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogResize::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFilesTab)
	DDX_Control(pDX, IDC_FILES, m_FilesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFilesTab, CDialogResize)
	//{{AFX_MSG_MAP(CFilesTab)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_NOTIFY(NM_RCLICK, IDC_FILES, OnRclickFiles)
	ON_COMMAND(ID_FILES_ADD, OnFilesAdd)
	ON_COMMAND(ID_FILES_REMOVE, OnFilesRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DLGRESIZE_MAP(CFilesTab)
	DLGRESIZE_CONTROL(IDC_FILES, DLSZ_SIZE_X | DLSZ_SIZE_Y)
	DLGRESIZE_CONTROL(IDC_ADD, DLSZ_MOVE_X)
	DLGRESIZE_CONTROL(IDC_REMOVE, DLSZ_MOVE_X)
END_DLGRESIZE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CFilesTab::OnInitDialog() 
{
	CDialogResize::OnInitDialog();
	
	// do not take ownership of the imagelist!
	m_FilesList.ModifyStyle(0, LVS_SHAREIMAGELISTS);

	InitListViewImageLists();

	InitResizing(FALSE, TRUE, NULL);	

	DWORD dwStyle = m_FilesList.GetExtendedStyle();
	dwStyle |= (LVS_EX_FULLROWSELECT);
    m_FilesList.SetExtendedStyle(dwStyle);

	m_FilesList.InsertColumn(0, "Name");
	m_FilesList.InsertColumn(1, "Size");
	m_FilesList.InsertColumn(2, "Type");
	m_FilesList.InsertColumn(3, "Link To");

	AutoSizeColumns(&m_FilesList);

	m_FilesList.DragAcceptFiles();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/********************************************************************/
/*																	*/
/* Function name : InitListViewImageLists							*/
/* Description   : Use system imagelist for the file icons			*/
/*																	*/
/********************************************************************/
BOOL CFilesTab::InitListViewImageLists()
{
	HIMAGELIST himlSmall;
	HIMAGELIST himlLarge;
	SHFILEINFO sfi;

	himlSmall = (HIMAGELIST) SHGetFileInfo ((LPCSTR) "C:\\", 
		0, &sfi, sizeof (SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	himlLarge = (HIMAGELIST) SHGetFileInfo ((LPCSTR) "C:\\", 
		0, &sfi, sizeof (SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

	if (himlSmall && himlLarge)
	{
		::SendMessage(m_FilesList.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)himlSmall);
		::SendMessage(m_FilesList.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)himlLarge);
		return TRUE;
	}
	return FALSE;
} 


/********************************************************************/
/*																	*/
/* Function name : OnAdd											*/
/* Description   : Add files to filelist							*/
/*																	*/
/********************************************************************/
void CFilesTab::OnAdd() 
{
	char szFilters[] = "All Files (*.*)|*.*||";
	
	CFileDialog dlg(FALSE, "*", "*.*" , OFN_NOVALIDATE| OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, szFilters, this);
	
	dlg.m_ofn.lpstrTitle = "Select Files";
	
	if (dlg.DoModal() == IDOK)
	{
		POSITION pos = dlg.GetStartPosition();
		while (pos != NULL)
		{
			CString strPath = dlg.GetNextPathName(pos);
			if (strPath.Find(":\\\\") == 1 && strPath.GetLength() > 4)
			{
				// this means we have an invalid path that looks like this:
				// C:\\foo.bmp
				// We need to cut out the extra slash
				CString temp;
				temp = strPath.Left(3);
				temp += strPath.Mid(4);
				strPath = temp;
			}
			CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
			pView->AddFile(strPath, TRUE);
		}
		AutoSizeColumns(&m_FilesList);
	}		
}


/********************************************************************/
/*																	*/
/* Function name : PreTranslateMessage								*/
/* Description   : Catch WM_DROPFILES messages						*/
/*																	*/
/********************************************************************/
BOOL CFilesTab::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_DROPFILES && pMsg->hwnd == m_FilesList.m_hWnd)
	{
		HDROP hDropInfo = (HDROP)pMsg->wParam;
	
		char szFileName[_MAX_PATH];
	
		// determine how many files are dropped
		UINT nCount = DragQueryFile(hDropInfo, -1, NULL, 0);

		for(UINT i=0; i < nCount; i++)
		{
			// get the filename
			DragQueryFile(hDropInfo, i, szFileName, _MAX_PATH);

			CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
			pView->AddFile(szFileName, TRUE);
		}
	}

	// process WM_KEYDOWN for keyboard shortcuts
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)		
		{
			case VK_INSERT:
				OnAdd();	
				return TRUE;
			case VK_DELETE:
				OnRemove();	
				return TRUE;
		}
	}
	return CDialogResize::PreTranslateMessage(pMsg);
}


/********************************************************************/
/*																	*/
/* Function name : OnRemove											*/
/* Description   : Remove selected file(s) from list				*/
/*																	*/
/********************************************************************/
void CFilesTab::OnRemove() 
{
	int nIndex = m_FilesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nIndex == -1)
		return;

	// delete items
	while (nIndex != -1)
	{
		CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
		
		CString strFileName = m_FilesList.GetItemText(nIndex, 3);
		strFileName += "\\";
		strFileName += m_FilesList.GetItemText(nIndex, 0);
		pView->RemoveFile(strFileName);
		m_FilesList.DeleteItem(nIndex);
		nIndex = m_FilesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	}
	
}

void CFilesTab::OnOK() 
{
//	CDialogResize::OnOK();
}

void CFilesTab::OnCancel() 
{
//	CDialogResize::OnCancel();
}


/********************************************************************/
/*																	*/
/* Function name : OnRclickFiles									*/
/* Description   : Handle listview context menu						*/
/*																	*/
/********************************************************************/
void CFilesTab::OnRclickFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu;
	if (menu.LoadMenu(IDR_FILESMENU))
	{
		POINT pt;
		GetCursorPos(&pt);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}		
	*pResult = 0;
}


/********************************************************************/
/*																	*/
/* Function name : OnFilesAdd										*/
/* Description   : Handle Add-command of listview context menu		*/
/*																	*/
/********************************************************************/
void CFilesTab::OnFilesAdd() 
{
	OnAdd();
}


/********************************************************************/
/*																	*/
/* Function name : OnFilesRemove									*/
/* Description   : Handle Remove-command of listview context menu	*/
/*																	*/
/********************************************************************/
void CFilesTab::OnFilesRemove() 
{
	OnRemove();
}
