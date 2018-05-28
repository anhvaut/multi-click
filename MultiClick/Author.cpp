
#include "stdafx.h"
#include "Author.h"
#include "Regedit.h"
#include "MultiClickDlg.h"
#include "LanguageGUI.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CRegeditInfo regedit;

IMPLEMENT_DYNCREATE(CAuthorDlg, CPropertyPage)

CAuthorDlg::CAuthorDlg() : CPropertyPage(CAuthorDlg::IDD)
{
  m_psp.dwFlags &= (~PSP_HASHELP);
  m_psp.dwFlags |= PSP_USEHICON;
  HICON hIconTab = AfxGetApp()->LoadIcon( IDI_AUTHOR );
  m_psp.hIcon = hIconTab;
}

CAuthorDlg::~CAuthorDlg()
{
}

void CAuthorDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuthorDlg)
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuthorDlg, CPropertyPage)

	//{{AFX_MSG_MAP(CAuthorDlg)

	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


BOOL CAuthorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	changeAuthorDlgGUI(m_hWnd,regedit.guiLanguage);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
