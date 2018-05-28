
#include "stdafx.h"
#include "DictionaryDlg.h"
#include "Regedit.h"
#include "MultiClickDlg.h"
#include "LanguageGUI.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CRegeditInfo regedit;

IMPLEMENT_DYNCREATE(CDictionaryDlg, CPropertyPage)

CDictionaryDlg::CDictionaryDlg() : CPropertyPage(CDictionaryDlg::IDD)
{
  m_psp.dwFlags &= (~PSP_HASHELP);
  m_psp.dwFlags |= PSP_USEHICON;
  HICON hIconTab = AfxGetApp()->LoadIcon( IDI_DICT );
  m_psp.hIcon = hIconTab;
}

CDictionaryDlg::~CDictionaryDlg()
{
}

void CDictionaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDictionaryDlg)
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDictionaryDlg, CPropertyPage)

	//{{AFX_MSG_MAP(CDictionaryDlg)

	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


BOOL CDictionaryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//changeAuthorDlgGUI(m_hWnd,regedit.guiLanguage);
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
