// DictionaryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AutoUpdateDlg.h"
#include "Regedit.h"
#include "MultiClickDlg.h"
#include "LanguageGUI.h"
#include "AutoUpdate.h"

extern CRegeditInfo regedit;
extern CAutoUpdate m_autoupdate;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif	





CAutoUpdateDlg::CAutoUpdateDlg(CWnd* pParent /*=NULL*/)
	: CBgDialog(CAutoUpdateDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAutoUpdateDlg::DoDataExchange(CDataExchange* pDX)
{
	CBgDialog::DoDataExchange(pDX);
	
		DDX_Control(pDX, IDC_STATIC11, m_static11);
		DDX_Control(pDX, IDC_STATIC12, m_static12);
		
		//DDX_Control(pDX,IDC_AUTOUPDATE_BTN, m_autoupdatebtn);

		
}

BEGIN_MESSAGE_MAP(CAutoUpdateDlg, CBgDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()



BOOL CAutoUpdateDlg::OnInitDialog()
{
	CBgDialog::OnInitDialog();
	SetBitmap(IDB_BACKGROUND);
	ActivateEasyMoveMode(TRUE);
	

	m_static11.DrawTransparent();
	m_static12.DrawTransparent();
	


	//m_autoupdatebtn.DrawTransparent();
	//m_autoupdatebtn.SetFlat(false);
	

	//tao am thanh khi dua chuot qua nut
//#ifdef	BTNST_USE_SOUND
	//m_btn.SetSound(MAKEINTRESOURCE(IDR_HOVER), ::GetModuleHandle(NULL));
//#endif

	
	CString version=m_autoupdate.GetFileVersion(_T("MultiClick.exe"));
	SetDlgItemText(IDC_STATIC12,version);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAutoUpdateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
//		CAboutDlg dlgAbout;
	//	dlgAbout.DoModal();
	}
	else
	{
		CBgDialog::OnSysCommand(nID, lParam);
	}
}


void CAutoUpdateDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CBgDialog::OnPaint();
	}
}


HCURSOR CAutoUpdateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



