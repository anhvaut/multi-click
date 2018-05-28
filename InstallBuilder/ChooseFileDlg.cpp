/****************************************************************/
/*																*/
/*  ChooseFileDlg.cpp											*/
/*																*/
/*  Implementation of the CChooseFileDlg class.					*/
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
#include "ChooseFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CChooseFileDlg::CChooseFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogResize(CChooseFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChooseFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CChooseFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogResize::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChooseFileDlg)
	DDX_Control(pDX, IDC_FILES, m_FilesList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChooseFileDlg, CDialogResize)
	//{{AFX_MSG_MAP(CChooseFileDlg)
	ON_NOTIFY(NM_DBLCLK, IDC_FILES, OnDblclkFiles)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DLGRESIZE_MAP(CChooseFileDlg)
	DLGRESIZE_CONTROL(IDC_FILES, DLSZ_SIZE_X | DLSZ_SIZE_Y)
	DLGRESIZE_CONTROL(IDOK, DLSZ_MOVE_Y)
	DLGRESIZE_CONTROL(IDCANCEL, DLSZ_MOVE_X | DLSZ_MOVE_Y)
END_DLGRESIZE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CChooseFileDlg::OnInitDialog() 
{
	CDialogResize::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);
	DWORD dwStyle = m_FilesList.GetExtendedStyle();
	dwStyle |= (LVS_EX_FULLROWSELECT);
    m_FilesList.SetExtendedStyle(dwStyle);

	InitResizing();	

	m_FilesList.InsertColumn(0, "Name");
	m_FilesList.InsertColumn(1, "Size");
	m_FilesList.InsertColumn(2, "Type");
	m_FilesList.InsertColumn(3, "Link To");

	// do not take ownership of the imagelist!
	m_FilesList.ModifyStyle(0, LVS_SHAREIMAGELISTS);

	InitListViewImageLists();

	for (int i=0; i < m_strFiles.GetSize(); i++)
	{
		int nIcon = GetIconIndex(m_strFiles[i], FALSE, FALSE);
		CString strSize;
		CFileFind filefind;

		if (filefind.FindFile(m_strFiles[i]))
		{
			filefind.FindNextFile();
			strSize = FormatSize(filefind.GetLength());
		}
		else
			strSize = FormatSize(0);
		
		CString strFileName = m_strFiles[i];
		CString strPath;

		int nPos = strFileName.ReverseFind('\\');
		if (nPos != -1)
		{
			strPath = strFileName.Left(nPos);
			strFileName = strFileName.Mid(nPos + 1);
		}

		m_FilesList.InsertItem(i, strFileName, nIcon);
		m_FilesList.SetItemText(i, 1, strSize);
		m_FilesList.SetItemText(i, 2, GetTypeName(m_strFiles[i]));
		m_FilesList.SetItemText(i, 3, strPath);
	}
	AutoSizeColumns(&m_FilesList);	

	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/********************************************************************/
/*																	*/
/* Function name : InitListViewImageLists							*/
/* Description   : Use system imagelist for the file icons			*/
/*																	*/
/********************************************************************/
BOOL CChooseFileDlg::InitListViewImageLists()
{
	HIMAGELIST himlSmall;
	HIMAGELIST himlLarge;
	SHFILEINFO sfi;

	himlSmall = (HIMAGELIST) SHGetFileInfo((LPCSTR) "C:\\", 
		0, &sfi, sizeof (SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	himlLarge = (HIMAGELIST) SHGetFileInfo((LPCSTR) "C:\\", 
		0, &sfi, sizeof (SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

	if (himlSmall && himlLarge)
	{
		::SendMessage(m_FilesList.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_SMALL, (LPARAM)ImageList_Duplicate(himlSmall));
		::SendMessage(m_FilesList.m_hWnd, LVM_SETIMAGELIST, (WPARAM)LVSIL_NORMAL, (LPARAM)ImageList_Duplicate(himlLarge));
		return TRUE;
	}
	return FALSE;
} 


/********************************************************************/
/*																	*/
/* Function name : OnOK												*/
/* Description   : Get selected filename and close dialog.			*/
/*																	*/
/********************************************************************/
void CChooseFileDlg::OnOK() 
{
	int nIndex = m_FilesList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nIndex == -1)
		return;
	
	m_strFileName = m_FilesList.GetItemText(nIndex, 0);
	m_strPathName = m_FilesList.GetItemText(nIndex, 3) + "\\" + m_FilesList.GetItemText(nIndex, 0);
	CDialogResize::OnOK();
}


/********************************************************************/
/*																	*/
/* Function name : OnDblclkFiles									*/
/* Description   : User has double clicked on list					*/
/*																	*/
/********************************************************************/
void CChooseFileDlg::OnDblclkFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnOK();
	*pResult = 0;
}
