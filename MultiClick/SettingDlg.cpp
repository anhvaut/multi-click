
#include "stdafx.h"
#include "SettingDlg.h"
#include "Regedit.h"
#include "typedef.h"
#include "utf8.h"
#include "MultiClickDlg.h"
#include "tray.h"
#include "LanguageGUI.h"

extern CRegeditInfo regedit;
extern SystemTray Stray; 
CComboBox languageOption;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



IMPLEMENT_DYNCREATE(CSettingDlg, CPropertyPage)

CSettingDlg::CSettingDlg() : CPropertyPage(CSettingDlg::IDD)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	//}}AFX_DATA_INIT
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, IDC_GUILANGUAGE, languageOption);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CPropertyPage)

	//{{AFX_MSG_MAP(CSettingDlg)
	ON_COMMAND(IDC_AUTOSTART,AutoStart)
	ON_COMMAND(IDC_CTRL,Ctrl)
	ON_COMMAND(IDC_SHIFT,Shift)
	ON_COMMAND(IDC_NO_KEYBOARD,NoKeyboard)

	ON_CBN_SELCHANGE(IDC_GUILANGUAGE, OnCbnSelchangeGuilanguage)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


BOOL CSettingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	changeSettingDlgGUI(m_hWnd,regedit.guiLanguage);
	
	InitData();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CSettingDlg::InitData(){

	
		changeSettingDlgComboboxGUI(regedit.guiLanguage);
	 
		
		GetDlgItem( IDC_GUILANGUAGE)->SendMessage( CB_SETCURSEL,regedit.guiLanguage, 0);
		
		if(regedit.autoLook==CTRL_RIGHT_CLICK){
			   GetDlgItem(IDC_CTRL)->SendMessage(BM_SETCHECK, 
					BST_CHECKED, 
					0);
			  
		}else if(regedit.autoLook==SHIFT_RIGHT_CLICK){
			   GetDlgItem(IDC_SHIFT)->SendMessage(BM_SETCHECK, 
					BST_CHECKED, 
					0);
			 
		}else if(regedit.autoLook==RIGHT_CLICK){
			  GetDlgItem(IDC_NO_KEYBOARD)->SendMessage(BM_SETCHECK, 
					BST_CHECKED, 
					0);
		}
		GetDlgItem(IDC_AUTOSTART)->SendMessage( BM_SETCHECK, 
					(regedit.autoStart)?BST_CHECKED:BST_UNCHECKED, 
					0);
		

		GetDlgItem(IDC_CLOSEMODE)->SendMessage( BM_SETCHECK, 
					BST_CHECKED, 
					0);

}

void CSettingDlg::AutoStart(){
	regedit.autoStart=(GetDlgItem(IDC_AUTOSTART)->SendMessage(BM_GETCHECK,0,0) == BST_CHECKED) ? 1 : 0;
	regedit.enableAutoStart(regedit.autoStart);
}

void CSettingDlg::Ctrl(){
	regedit.autoLook=CTRL_RIGHT_CLICK;
   
}
void CSettingDlg::Shift(){
	regedit.autoLook=SHIFT_RIGHT_CLICK;

}
void CSettingDlg::NoKeyboard(){
	regedit.autoLook=RIGHT_CLICK;
}


void CSettingDlg::OnCbnSelchangeGuilanguage()
{
	// TODO: Add your control notification handler code here
	regedit.guiLanguage=(int)GetDlgItem( IDC_GUILANGUAGE)->SendMessage(CB_GETCURSEL,0,0);
}




