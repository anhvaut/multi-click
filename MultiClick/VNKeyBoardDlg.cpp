#include "stdafx.h"
#include "VNKeyBoardDlg.h"
#include "typedef.h"
#include "Regedit.h"

extern CRegeditInfo regedit;

CVNKeyBoardDlg::CVNKeyBoardDlg() : CDialog(CVNKeyBoardDlg::IDD)
{
	
}

void CVNKeyBoardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVNKeyBoardDlg, CDialog)
	ON_COMMAND(IDC_CHARSET,Charset)
	ON_COMMAND( IDC_INPUT_METHOD,InputMethodChange)
	ON_COMMAND(IDC_SWKEY1,SwitchKey1)
	ON_COMMAND(IDC_SWKEY2,SwitchKey2)
	ON_COMMAND(IDC_KEY_TASKBAR,Taskbar)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
BOOL CVNKeyBoardDlg::OnInitDialog() {
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

	 m_WhiteBrush.CreateSolidBrush(RGB(173,233,237));

	InitData();
	

	return TRUE;
}
BOOL CVNKeyBoardDlg::OnEraseBkgnd(CDC* pDC) 
{
  CBrush  m_WhiteBrush;
  m_WhiteBrush.CreateSolidBrush(RGB(250,250,250));
   CBrush* pOld=pDC->SelectObject(&m_WhiteBrush);

   // get area to be erased
   CRect rect;
   pDC->GetClipBox(&rect);

   // erase it! (with our brush :)
   pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
     CBrush brush(RGB(173,233,237));
	pDC->SetBkMode(TRANSPARENT);
				
	pDC->FillRect(&rect,&brush);// clean up

   // clean up
   pDC->SelectObject(pOld);
	return TRUE;
}

HBRUSH CVNKeyBoardDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
   if(nCtlColor==CTLCOLOR_STATIC)
   {
	   // change the text back mode for the DC to transparent
      pDC->SetBkMode(TRANSPARENT);
      // and return the same brush used on the dialog background
      return m_WhiteBrush;
   }
   else
      return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}


void CVNKeyBoardDlg::InitData(){
	/////Init
	/*
		for (int i=0; i < NUM_CHARSET; i++)
			GetDlgItem(IDC_CHARSET)->SendMessage( CB_ADDSTRING, 0, (LPARAM)CharsetText[i].displayText);
		GetDlgItem(IDC_CHARSET)->SendMessage(CB_SETCURSEL,regedit.charset, 0);

		
		for (i=0; i < NUM_TYPING; i++)
			GetDlgItem( IDC_INPUT_METHOD)->SendMessage(CB_ADDSTRING, 0, (LPARAM)InputMethod[i].inputText);
		GetDlgItem( IDC_INPUT_METHOD)->SendMessage( CB_SETCURSEL,regedit.inputMethod, 0); 

			//switch key :ATL+Z
		GetDlgItem( IDC_SWKEY1)->SendMessage( BM_SETCHECK, 
					regedit.switchKey?BST_CHECKED:BST_UNCHECKED, 
					0);
		//switch key :CTRL+SHIFT
		GetDlgItem( IDC_SWKEY2)->SendMessage(BM_SETCHECK, 
					regedit.switchKey?BST_UNCHECKED:BST_CHECKED, 
					0);
		
		GetDlgItem( IDC_FREE_MARKING)->SendMessage( BM_SETCHECK, 
					(regedit.notFreeMarking)?BST_CHECKED:BST_UNCHECKED, 
					0);

		GetDlgItem( IDC_U_CLIPBOARD)->SendMessage( BM_SETCHECK, 
					(regedit.uClipboard)?BST_CHECKED:BST_UNCHECKED, 
					0);
				*/
}

void CVNKeyBoardDlg::Charset(){
	regedit.charset=(int)GetDlgItem(IDC_CHARSET)->SendMessage(CB_GETCURSEL,0,0);
}
void CVNKeyBoardDlg::InputMethodChange(){
	regedit.inputMethod=(int)GetDlgItem( IDC_INPUT_METHOD)->SendMessage(CB_GETCURSEL,0,0);
}
void CVNKeyBoardDlg::SwitchKey1(){
	regedit.switchKey=ALT_Z;
}
void CVNKeyBoardDlg::SwitchKey2(){
	regedit.switchKey=CTRL_SHIFT;
}
void CVNKeyBoardDlg::Taskbar(){
}