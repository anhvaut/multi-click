/****************************************************************/
/*																*/
/*  TabCtrlEx.cpp												*/
/*																*/
/*  Implementation of the CTabCtrlEx class.						*/
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
#include "TabCtrlEx.h"
#include "resource.h"
#include "GeneralTab.h"
#include "FilesTab.h"
#include "ShortcutTab.h"
#include "OutputTab.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CTabCtrlEx::CTabCtrlEx()
{
	m_tabPages[0]=new CGeneralTab;
	m_tabPages[1]=new CFilesTab;
	m_tabPages[2]=new CShortcutTab;
	m_tabPages[3]=new COutputTab;

	m_nNumberOfPages = 4;
}


CTabCtrlEx::~CTabCtrlEx()
{
	for(int i=0; i < m_nNumberOfPages; i++)
	{
		delete m_tabPages[i];
	}
}


void CTabCtrlEx::Init()
{
	InsertItem(0, "General");
	InsertItem(1, "Files");
	InsertItem(2, "Shortcuts");
	InsertItem(3, "Output");

	m_nCurrentPage = 0;

	m_tabPages[0]->Create(IDD_GENERAL_TAB, this);
	m_tabPages[1]->Create(IDD_FILES_TAB, this);
	m_tabPages[2]->Create(IDD_SHORTCUT_TAB, this);
	m_tabPages[3]->Create(IDD_OUTPUT_TAB, this);
	
	m_tabPages[0]->ShowWindow(SW_SHOW);
	m_tabPages[1]->ShowWindow(SW_HIDE);
	m_tabPages[2]->ShowWindow(SW_HIDE);
	m_tabPages[3]->ShowWindow(SW_HIDE);

	SetRectangle();

	m_ImageList.Create(IDB_TABICONS, 16, 0, RGB(255, 0, 255));
	SetImageList(&m_ImageList);

	TCITEM tcItem;
	ZeroMemory(&tcItem, sizeof(TCITEM));

	tcItem.mask = TCIF_IMAGE;
	int nCount = GetItemCount();
	for (int i = 0; i < nCount; i++)
	{
		tcItem.iImage = i;
		SetItem(i, &tcItem);
	}
}


void CTabCtrlEx::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX=itemRect.left;
	nY=itemRect.bottom+1;
	nXc=tabRect.right-itemRect.left-1;
	nYc=tabRect.bottom-nY-1;

	m_tabPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for(int i=1; i < m_nNumberOfPages; i++)
	{
		m_tabPages[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}

BEGIN_MESSAGE_MAP(CTabCtrlEx, CTabCtrl)
	//{{AFX_MSG_MAP(CTabCtrlEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx message handlers

void CTabCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CTabCtrl::OnLButtonDown(nFlags, point);

	if(m_nCurrentPage != GetCurFocus())
	{
		m_tabPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage = GetCurFocus();
		m_tabPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
		m_tabPages[m_nCurrentPage]->SetFocus();
	}
}


void CTabCtrlEx::OnSize(UINT nType, int cx, int cy) 
{
	CTabCtrl::OnSize(nType, cx, cy);

	CRect rect;
	RECT rcTab;

	GetWindowRect(rect);
	ScreenToClient(rect);
	
	GetItemRect(0, &rcTab);

	int dx = 2 * GetSystemMetrics(SM_CXEDGE);
	int dy = 2 * GetSystemMetrics(SM_CYEDGE);

	for(int nCount=0; nCount < m_nNumberOfPages; nCount++)
	{
		m_tabPages[nCount]->SetWindowPos(NULL, 0, 0, rect.Width() - (2 * dx), rect.Height() - (2 * dy) - (rcTab.bottom - rcTab.top), SWP_NOMOVE | SWP_NOZORDER);;
	}
}



void CTabCtrlEx::PreSubclassWindow() 
{
	Init();	
	CTabCtrl::PreSubclassWindow();
}



void CTabCtrlEx::SetCurFocusEx(int nItem)
{
	if(m_nCurrentPage != nItem)
	{
		CTabCtrl::SetCurFocus(nItem);
		m_tabPages[m_nCurrentPage]->ShowWindow(SW_HIDE);
		m_nCurrentPage = GetCurFocus();
		m_tabPages[m_nCurrentPage]->ShowWindow(SW_SHOW);
		m_tabPages[m_nCurrentPage]->SetFocus();
	}
}

