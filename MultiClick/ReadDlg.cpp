
#include "stdafx.h"
#include "ReadDlg.h"
#include "Regedit.h"
#include "MultiClickDlg.h"
#include "LanguageGUI.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CRegeditInfo regedit;

IMPLEMENT_DYNCREATE(CReadDlg, CPropertyPage)

CReadDlg::CReadDlg() : CPropertyPage(CReadDlg::IDD)
{
  m_psp.dwFlags &= (~PSP_HASHELP);
  m_psp.dwFlags |= PSP_USEHICON;
  HICON hIconTab = AfxGetApp()->LoadIcon( IDI_SOUND );
  m_psp.hIcon = hIconTab;
}

CReadDlg::~CReadDlg()
{
}

void CReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadDlg)
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReadDlg, CPropertyPage)

	//{{AFX_MSG_MAP(CReadDlg)

	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


BOOL CReadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	changeReadDlgGUI(m_hWnd,regedit.guiLanguage);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
