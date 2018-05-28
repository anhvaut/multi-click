// DictionaryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AboutDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif	





CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CBgDialog(CAboutDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBgDialog::DoDataExchange(pDX);
		
		DDX_Control(pDX, IDC_STATIC1, m_static3);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBgDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()



BOOL CAboutDlg::OnInitDialog()
{
	CBgDialog::OnInitDialog();
	//SetBitmap(IDB_BACKGROUND);
	//ActivateEasyMoveMode(TRUE);
	
	m_static3.DrawTransparent();
	//m_btn.DrawTransparent();
	//m_btn.SetIcon(IDI_LEDON,IDI_LEDOFF);
	

	//tao am thanh khi dua chuot qua nut
//#ifdef	BTNST_USE_SOUND
	//m_btn.SetSound(MAKEINTRESOURCE(IDR_HOVER), ::GetModuleHandle(NULL));
//#endif

	
	////set window at center
	RECT    rc;

    GetWindowRect(&rc);

    int     nWidth, nHeight;
        
    nWidth = rc.right - rc.left;
    nHeight = rc.bottom - rc.top;
        
    int     cxScreen, cyScreen;
        
    cxScreen = GetSystemMetrics(SM_CXSCREEN);
    cyScreen = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(NULL,(cxScreen - nWidth) / 2,(cyScreen - nHeight) / 2, NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER |SWP_SHOWWINDOW);
////end set window at center
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAboutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CAboutDlg::OnPaint() 
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


HCURSOR CAboutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CAboutDlg::OnOK()
{
	//return static_cast<HCURSOR>(m_hIcon);
	//MessageBox(_T("OK"));
}


