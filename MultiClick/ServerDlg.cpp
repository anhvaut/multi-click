
#include "stdafx.h"
#include "ServerDlg.h"
#include "Regedit.h"
#include "MultiClickDlg.h"
#include "LanguageGUI.h"
#include "AutoUpdate.h"
#include ".\serverdlg.h"
#include "AutoUpdateDlg.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CRegeditInfo regedit;
extern CAutoUpdate m_autoupdate;



IMPLEMENT_DYNCREATE(CServerDlg, CPropertyPage)

CServerDlg::CServerDlg() : CPropertyPage(CServerDlg::IDD)
{
	 m_psp.dwFlags &= (~PSP_HASHELP);
  m_psp.dwFlags |= PSP_USEHICON;
  HICON hIconTab = AfxGetApp()->LoadIcon( IDI_SERVER);
  m_psp.hIcon = hIconTab;
}

CServerDlg::~CServerDlg()
{
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
		DDX_Control(pDX,IDC_CONNECT,m_connectbtn);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerDlg, CPropertyPage)

	//{{AFX_MSG_MAP(CServerDlg)

	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_CHECK_NEW_VERSION, OnBnClickedCheckNewVersion)
END_MESSAGE_MAP()


BOOL CServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	changeServerDlgGUI(m_hWnd,regedit.guiLanguage);
	
	m_connectbtn.DrawTransparent();

	if(m_autoupdate.InternetOkay()) 
		m_connectbtn.SetIcon(IDI_CONNECT);
	else
		m_connectbtn.SetIcon(IDI_DISCONNECT);
		
	InitData();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::InitData(){
	GetDlgItem(IDC_URL)->SetWindowText(_T("http://multidict.net"));
	GetDlgItem(IDC_AUTOUPDATE)->SendMessage(BM_SETCHECK,regedit.autoUpdate?BST_CHECKED:BST_UNCHECKED ,0);
}
void CServerDlg::OnBnClickedCheckNewVersion()
{
	regedit.autoUpdate=(GetDlgItem(IDC_AUTOUPDATE)->SendMessage(BM_GETCHECK,0,0)==BST_CHECKED)?1:0;
	CAutoUpdateDlg dlg;
	dlg.DoModal();
}
