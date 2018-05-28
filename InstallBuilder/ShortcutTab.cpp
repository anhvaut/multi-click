/****************************************************************/
/*																*/
/*  ShortcutTab.cpp												*/
/*																*/
/*  Implementation of the CShortcutTab class.					*/
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
#include "ShortcutTab.h"
#include "AddShortcutDlg.h"
#include "ChooseFileDlg.h"

#include "InstallBuilderDoc.h"
#include "InstallBuilderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CShortcutTab::CShortcutTab(CWnd* pParent /*=NULL*/)
	: CDialogResize(CShortcutTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShortcutTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CShortcutTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogResize::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShortcutTab)
	DDX_Control(pDX, IDC_SHORTCUTS, m_ShortcutList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShortcutTab, CDialogResize)
	//{{AFX_MSG_MAP(CShortcutTab)
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_SHORTCUTS, OnDblclkShortcuts)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_NOTIFY(NM_RCLICK, IDC_SHORTCUTS, OnRclickShortcuts)
	ON_COMMAND(ID_SHORTCUT_ADD, OnShortcutAdd)
	ON_COMMAND(ID_SHORTCUT_EDIT, OnShortcutEdit)
	ON_COMMAND(ID_SHORTCUT_REMOVE, OnShortcutRemove)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BEGIN_DLGRESIZE_MAP(CShortcutTab)
	DLGRESIZE_CONTROL(IDC_SHORTCUTS, DLSZ_SIZE_X | DLSZ_SIZE_Y)
	DLGRESIZE_CONTROL(IDC_ADD, DLSZ_MOVE_X)
	DLGRESIZE_CONTROL(IDC_EDIT, DLSZ_MOVE_X)
	DLGRESIZE_CONTROL(IDC_REMOVE, DLSZ_MOVE_X)
END_DLGRESIZE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CShortcutTab::OnInitDialog() 
{
	CDialogResize::OnInitDialog();
	
	InitResizing(FALSE, TRUE, NULL);	

	DWORD dwStyle = m_ShortcutList.GetExtendedStyle();
	dwStyle |= (LVS_EX_FULLROWSELECT);
    m_ShortcutList.SetExtendedStyle(dwStyle);

	m_ShortcutList.InsertColumn(0, "Name");
	m_ShortcutList.InsertColumn(1, "Type");
	m_ShortcutList.InsertColumn(2, "Shortcut To");

	// create CImageList
	VERIFY (m_ImageList.Create (16, 16, TRUE, 0, 1));
	CBitmap bm;
	
	VERIFY (bm.LoadBitmap (IDB_SHORTCUTS));
	VERIFY (-1 != m_ImageList.Add(&bm, RGB (255, 0, 255)));
	
	m_ShortcutList.SetImageList(&m_ImageList, LVSIL_SMALL);

	AutoSizeColumns(&m_ShortcutList);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


/********************************************************************/
/*																	*/
/* Function name : OnAdd											*/
/* Description   : Add shortcut to filelist							*/
/*																	*/
/********************************************************************/
void CShortcutTab::OnAdd() 
{
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();

	CChooseFileDlg dlg;
	int i;
	for (i=0; i<pDoc->m_strFiles.GetSize(); i++)
		dlg.m_strFiles.Add(pDoc->m_strFiles[i]);

	if (dlg.DoModal() == IDOK)
	{
		CAddShortcutDlg dialog;

		for (i=0; i<pDoc->m_strFiles.GetSize(); i++)
			dialog.m_strFiles.Add(pDoc->m_strFiles[i]);

		dialog.m_strName = dlg.m_strFileName;
		int nPos = dlg.m_strFileName.ReverseFind('.');
		
		if (nPos != -1)
			dialog.m_strName = dlg.m_strFileName.Left(nPos);

		dialog.m_strTarget = "%AppDir%\\" + dlg.m_strFileName;
		dialog.m_strWorkingDir = "%AppDir%";
		dialog.m_strOriginalPath = dlg.m_strPathName;

		if (dialog.DoModal() == IDOK)
		{
			CShortcutObject shortcutObject;

			shortcutObject.m_strName = dialog.m_strName;
			shortcutObject.m_strTarget = dialog.m_strTarget;
			shortcutObject.m_strCmdLine = dialog.m_strCmdLine;
			shortcutObject.m_strWorkingDir = dialog.m_strWorkingDir;
			shortcutObject.m_strIconPath = dialog.m_strIconPath;
			shortcutObject.m_nIconIndex = dialog.m_nIconIndex;
			shortcutObject.m_strOriginalPath = dialog.m_strOriginalPath;

			CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
			pView->AddShortcut(shortcutObject, -1);
			AutoSizeColumns(&m_ShortcutList);
		}
	}
}


/********************************************************************/
/*																	*/
/* Function name : OnEdit											*/
/* Description   : Edit selected shortcut							*/
/*																	*/
/********************************************************************/
void CShortcutTab::OnEdit() 
{
	int nItem = m_ShortcutList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nItem == -1)
		return;
	
	CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
	CInstallBuilderDoc *pDoc = pView->GetDocument();

	CAddShortcutDlg dlg;

	for (int i=0; i<pDoc->m_strFiles.GetSize(); i++)
		dlg.m_strFiles.Add(pDoc->m_strFiles[i]);

	dlg.m_strName = pDoc->m_ShortcutObjects[nItem].m_strName;
	dlg.m_strTarget = pDoc->m_ShortcutObjects[nItem].m_strTarget;
	dlg.m_strCmdLine = pDoc->m_ShortcutObjects[nItem].m_strCmdLine;
	dlg.m_strIconPath = pDoc->m_ShortcutObjects[nItem].m_strIconPath;
	dlg.m_strWorkingDir = pDoc->m_ShortcutObjects[nItem].m_strWorkingDir;
	dlg.m_nIconIndex = pDoc->m_ShortcutObjects[nItem].m_nIconIndex;
	dlg.m_strOriginalPath = pDoc->m_ShortcutObjects[nItem].m_strOriginalPath;
	
	dlg.m_strTitle = "Edit Shortcut";
	if (dlg.DoModal() == IDOK)
	{
		pDoc->m_ShortcutObjects[nItem].m_strName = dlg.m_strName;
		pDoc->m_ShortcutObjects[nItem].m_strTarget = dlg.m_strTarget;
		pDoc->m_ShortcutObjects[nItem].m_strCmdLine = dlg.m_strCmdLine;
		pDoc->m_ShortcutObjects[nItem].m_strIconPath = dlg.m_strIconPath;
		pDoc->m_ShortcutObjects[nItem].m_strWorkingDir = dlg.m_strWorkingDir;
		pDoc->m_ShortcutObjects[nItem].m_nIconIndex = dlg.m_nIconIndex;
		pDoc->m_ShortcutObjects[nItem].m_strOriginalPath = dlg.m_strOriginalPath;

		m_ShortcutList.SetItemText(nItem, 0, dlg.m_strName);
		m_ShortcutList.SetItemText(nItem, 2, dlg.m_strTarget);
	}
}

void CShortcutTab::OnOK() 
{
//	CDialogResize::OnOK();
}

void CShortcutTab::OnCancel() 
{
//	CDialogResize::OnCancel();
}

void CShortcutTab::OnDblclkShortcuts(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnEdit();
	*pResult = 0;
}


/********************************************************************/
/*																	*/
/* Function name : OnRemove											*/
/* Description   : Remove selected shortcut(s) from list			*/
/*																	*/
/********************************************************************/
void CShortcutTab::OnRemove() 
{
	int nItem = m_ShortcutList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if (nItem == -1)
		return;

	// delete items
	while (nItem != -1)
	{
		CInstallBuilderView *pView = (CInstallBuilderView *)GetParent()->GetParent();
		CInstallBuilderDoc *pDoc = pView->GetDocument();

		pDoc->m_ShortcutObjects.RemoveAt(nItem);
		m_ShortcutList.DeleteItem(nItem);
		nItem = m_ShortcutList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	}
}


/********************************************************************/
/*																	*/
/* Function name : OnRclickFiles									*/
/* Description   : Handle listview context menu						*/
/*																	*/
/********************************************************************/
void CShortcutTab::OnRclickShortcuts(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu;
	if (menu.LoadMenu(IDR_SHORTCUTMENU))
	{
		POINT pt;
		GetCursorPos(&pt);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}		
	
	*pResult = 0;
}


/********************************************************************/
/*																	*/
/* Function name : OnShortcutAdd									*/
/* Description   : Handle Add-command of listview context menu		*/
/*																	*/
/********************************************************************/
void CShortcutTab::OnShortcutAdd() 
{
	OnAdd();
}


/********************************************************************/
/*																	*/
/* Function name : OnShortcutEdit									*/
/* Description   : Handle Edit-command of listview context menu		*/
/*																	*/
/********************************************************************/
void CShortcutTab::OnShortcutEdit() 
{
	OnEdit();
}


/********************************************************************/
/*																	*/
/* Function name : OnShortcutRemove									*/
/* Description   : Handle Remove-command of listview context menu	*/
/*																	*/
/********************************************************************/
void CShortcutTab::OnShortcutRemove() 
{
	OnRemove();	
}


/********************************************************************/
/*																	*/
/* Function name : PreTranslateMessage								*/
/* Description   : Catch WM_KEYDOWN for keyboard shortcuts			*/
/*																	*/
/********************************************************************/
BOOL CShortcutTab::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)		
		{
			case VK_INSERT:
				OnAdd();	
				return TRUE;
			case VK_RETURN:
				OnEdit();	
				return TRUE;
			case VK_DELETE:
				OnRemove();	
				return TRUE;
		}
	}
	
	return CDialogResize::PreTranslateMessage(pMsg);
}
