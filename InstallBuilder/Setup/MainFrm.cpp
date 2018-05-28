/****************************************************************/
/*																*/
/*  MainFrm.cpp													*/
/*																*/
/*  Implementation of the CMainFrm class.						*/
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

#include "MainFrm.h"
#include "SetupSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CMainFrame::CMainFrame()
{
	// initialization
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMainFrame::~CMainFrame()
{
}


/********************************************************************/
/*																	*/
/* Function name : OnCreate											*/
/* Description   : Perform initialization for CMainFrame.			*/
/*																	*/
/********************************************************************/
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	SetIcon(m_hIcon, FALSE);
	SetIcon(m_hIcon, TRUE);

	SetTimer(1, 100, NULL);
	return 0;
}


/********************************************************************/
/*																	*/
/* Function name : PreCreateWindow									*/
/* Description   : Called by the framework before the creation of	*/
/*                 the Windows window attached to this CWnd object.	*/
/*																	*/
/********************************************************************/
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	cs.hMenu = NULL;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


/********************************************************************/
/*																	*/
/* Function name : OnSetFocus										*/
/* Description   : Route focus to view.								*/
/*																	*/
/********************************************************************/
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}


/********************************************************************/
/*																	*/
/* Function name : OnCmdMsg											*/
/* Description   : Route commands to view.							*/
/*																	*/
/********************************************************************/
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


/********************************************************************/
/*																	*/
/* Function name : OnTimer											*/
/* Description   : I'm using a timer to launch the setup wizard.	*/
/*				   So I can be pretty sure the window is created. 	*/
/*																	*/
/********************************************************************/
void CMainFrame::OnTimer(UINT nIDEvent) 
{
	KillTimer(1);

	LaunchWizard();
	
	CFrameWnd::OnTimer(nIDEvent);
}


/********************************************************************/
/*																	*/
/* Function name : LaunchWizard										*/
/* Description   : Launch the setup wizard.							*/
/*																	*/
/********************************************************************/
void CMainFrame::LaunchWizard()
{
	CSetupSheet propSheet;
	if (propSheet.DoModal() == ID_WIZFINISH)
	{
	}
}
