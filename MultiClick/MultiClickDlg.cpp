// MultiClickDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MultiClick.h"
#include "MultiClickDlg.h"
#include "Tray.h"
#include "typedef.h"
#include "Regedit.h"
#include "Codetable.h"
#include "Opacity.h"
#include "AboutDlg.h"
#include "SettingDlg.h"
#include "VNKeyBoardDlg.h"
#include "Database.h"
#include "common.h"
#include "Speak.h"
#include ".\multiclickdlg.h"
#include "TreePropSheet.h"
#include "Author.h"
//#include "LanguageGUI.h"
#include "Unicode2TCVN.h"
#include "UTF8.h"
#include "ReadDlg.h"
#include "ServerDlg.h"
#include "AutoUpdate.h"
#include "ReadText.h"
#include "DictionaryDlg.h"



CString currentDict;//luu loai tu dien chua tu can tra
CAutoUpdate m_autoupdate;



#define APPBAR_CALLBACK     WM_USER + 1010
#define IDT_AUTOHIDE 	1

#define SIZE_ICON_X 16
#define SIZE_ICON_Y 16

#define SIZE_CLOSE_X 15
#define SIZE_CLOSE_Y 15


//declare member
//=======================
CDatabase m_database;
int modeSwitch;
SystemTray Stray; 
CRegeditInfo regedit;
int oldAutoLook;
//extern COLORREF		backcolor,titlecolor,textcolor;
CDC *gpDC;
CCodeTable m_codetable;
HINSTANCE hInst;

int firstInit=0;
extern CString tam[500];


Opacity m_opacity;
bool keepdialog=false;
//===================


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CMultiClickDlg dialog

CMultiClickDlg::CMultiClickDlg(CWnd* pParent /*=NULL*/)
	: CNewDialog(CMultiClickDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiClickDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bMoving = FALSE;
	m_nTabRound  = 2;
	m_nXIcon = 0;
	m_nYIcon = 0;
	m_nXControlsMoved = 0;
	m_nYControlsMoved = 0;
	m_bHiddenStatus  = FALSE;
	// init poublic data

	// original Window pos
	m_nXpos = 0;
	m_nYpos = 0;

	// original Window border
	m_nBorderPos = TAB_BORDER_TOP;

	// Tab default height and width
	m_nTabHeight = 0;
	m_nTabWidth = 0;

	// Auto tab Width computation
	m_bAutoTabSize = TRUE;

	// TopMost Attribute
	m_bTopMost = TRUE;

	// AutoHide Attribute
	m_bAutoHide = TRUE;

	m_bCloseBox = TRUE;

	m_hTitleIcon = NULL;

	m_sTitle = _T("Tu dien offline - multiclick");
}

void CMultiClickDlg::DoDataExchange(CDataExchange* pDX)
{
	CNewDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiClickDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_wndBrowser);
	DDX_Control(pDX, IDC_SOUND, m_soundbtn);
	DDX_Control(pDX, IDC_KEEPIT, m_keepit);
	DDX_Control(pDX, IDC_CURRENTDICT, m_currentdict);
	
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMultiClickDlg, CNewDialog)
	//{{AFX_MSG_MAP(CMultiClickDlg)

	ON_COMMAND(ID_DEMO_PRINTPREVIEW, OnPrintpreview)
	ON_COMMAND(ID_DEMO_PAGESETUP, OnPagesetup)

	ON_WM_CREATE()
	
	ON_MESSAGE(WM_APP+MOUSE_PROC,OnMouseProc)
	ON_WM_TIMER()
	ON_MESSAGE(WM_NOTIFYICONTRAY, OnTrayNotification)
	ON_COMMAND(ID_END,OnEndKey)
	ON_COMMAND(ID_PANEL,OnShowConfig)
	ON_COMMAND(ID_AUTOLOOK_ON,CheckAutoLookOn)
	ON_COMMAND(ID_CTRL_CLICK,chooseModeLook1)
	ON_COMMAND(ID_SHIFT_CLICK,chooseModeLook2)
	ON_COMMAND(ID_CLICK,chooseModeLook3)
	ON_COMMAND(ID_OPEN_HELP,openHelp)
	
	ON_COMMAND(ID_TELEX_TYPING,telexTyping)
	ON_COMMAND(ID_VNI_TYPING,vniTyping)
	ON_COMMAND(ID_KEY_TCVN3,tcvn3Charset)
	ON_COMMAND(ID_KEY_UNICODE,unicodeCharset)
	ON_COMMAND(ID_KEY_VIQR,viqrCharset)
	ON_COMMAND(ID_KEY_VNI,vniCharset)
	ON_COMMAND(ID_KEY_VIETWAREX,vietwarexCharset)
	ON_COMMAND(ID_KEY_VIETWAREF,vietwarefCharset)
	ON_COMMAND(ID_KEY_BKHCM1,hcm1Charset)
	ON_COMMAND(ID_KEY_BKHCM2,hcm2Charset)
	ON_COMMAND(ID_KEY_VPS,vpsCharset)
	ON_COMMAND(ID_KEY_VISCII,visciiCharset)
	


	ON_COMMAND(ID_KEY_CONF,OnDialogConf)
	ON_COMMAND(ID_DICTIONARY,OpenDictionary)
	ON_COMMAND(ID_DICTIONARY_ENGLISHV,OpenEVDictionary)
	ON_COMMAND(ID_DICTIONARY_FRANCEV,OpenFVDictionary)
	ON_COMMAND(ID_DICTIONARY_GERMANYV,OpenGVDictionary)
	ON_COMMAND(ID_DICTIONARY_NAUY_NV,OpenNNVDictionary)
	ON_COMMAND(ID_INFOKEY,OpenInfoKey)
	

	ON_COMMAND(ID_LOOKUPON_ENGLISH,chooseEnglish)
	ON_COMMAND(ID_LOOKUPON_FRANCE,chooseFrance)
	ON_COMMAND(ID_LOOKUPON_GERMANY,chooseGermany)
	ON_COMMAND(ID_LOOKUPON_VIETNAMESE,chooseVietnamese)
	ON_COMMAND(ID_LOOKUPON_RUSSIA,chooseRussia)
	ON_COMMAND(ID_LOOKUPON_NAUY,chooseNauy)
	

	
	
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SOUND, OnBnClickedSound)
	ON_COMMAND(ID_DICTIONARYONLINE, OnDictionaryonline)
	ON_COMMAND(ID_LOOKUPONLINE, OnLookuponline)
	ON_BN_CLICKED(IDC_KEEPIT, OnBnClickedKeepit)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiClickDlg message handlers



BOOL CMultiClickDlg::OnInitDialog()
{
	
		AfxInitRichEdit();
	// Add "About..." menu item to system menu.

	//CString version=m_autoupdate.GetFileVersion(_T("MultiClick.exe"));
	//MessageBox(version);
	CRect rect;


	GetWindowRect(&rect);
	m_nInitialWidth  = rect.Width() ;
	m_nInitialHeight = rect.Height() ;

	// make sure X and Y positions are correct depending on the window position
	if ((m_nBorderPos == TAB_BORDER_BOTTOM) || (m_nBorderPos == TAB_BORDER_TOP))
		m_nYpos  = 0;
	else
		m_nXpos = 0;
	CNewDialog::OnInitDialog();

	//ComputeTabSize();	
	//InitTitleDC();
	CreateTabPolygon();
	
	OnAutoHide();
	OnTopMost();


	////////////////button

	m_soundbtn.DrawTransparent();
	m_soundbtn.SetIcon(IDI_SOUND);
	m_soundbtn.SetTooltipText(_T("say"));

	short	shBtnColor = 30;
	m_keepit.DrawTransparent();
	m_keepit.SetIcon(IDI_LEDON, IDI_LEDOFF);
	m_keepit.OffsetColor(CustomBtn::BTNST_COLOR_BK_IN, shBtnColor);
	m_keepit.SetTooltipText(_T("auto hide"));

	m_currentdict.DrawTransparent();
	m_currentdict.OffsetColor(CustomBtn::BTNST_COLOR_BK_IN, shBtnColor);

	
	InitHash();

	//m_keepit.SetCheck(1);

	/////////////// button
	//initSapi();
	//speakText(_T("this is my dictionary"));

	//VoiceChange();
	//setSpeakRate(10);
	//setVolume(20);

//	m_database.GetMeaning("vietanh","a");
//	m_database.GetIndex();
	
	// TODO: Add extra initialization here
	
//	m_wndBrowser.Write();

	//ReSize();
	//String st=
	//m_codetable.Convert_String(
//	speakText("this is my text");

	//changeMenuGUI(m_hWnd,3);
	return TRUE;  // return TRUE  unless you set the focus to a control
}


//////////// begin event for web ///////////////////////////

void CMultiClickDlg::OnPrintpreview() 
{
	// Verify the Web Browser control is valid.
	LPDISPATCH lpDispApp = m_wndBrowser.GetApplication();
	if(lpDispApp)
	{
		// Get the HTMLDocument interface.
		LPDISPATCH lpDispDoc = m_wndBrowser.GetDocument();
		if (lpDispDoc != NULL)
		{
			// Get the IOleCommandTarget interface so that we can dispatch the command.
			LPOLECOMMANDTARGET lpTarget = NULL;
			if (SUCCEEDED(lpDispDoc->QueryInterface(IID_IOleCommandTarget,	(LPVOID*) &lpTarget)))
			{
				// Execute the print preview command. The control will handle the print preview GUI.
				// OLECMDID_PRINTPREVIEW is defined in "docobj.h".
				lpTarget->Exec(NULL, OLECMDID_PRINTPREVIEW, 0, NULL, NULL);
				lpTarget->Release();
			}
			lpDispDoc->Release();
		}
		lpDispApp->Release();
	}
}

void CMultiClickDlg::OnPagesetup()
{
	m_wndBrowser.ExecWB(OLECMDID_PAGESETUP, OLECMDEXECOPT_PROMPTUSER, NULL, NULL);
}


/////////////// end event for web////////////////////
/*
 * OnCreate
 *
 * Tao Message Handle
 * Sua lai window style: xoa caption, xoa border
 */

int CMultiClickDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CNewDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	Stray.TRAY_Init(m_hWnd,lpCreateStruct->hInstance,this);
	
	hInst=lpCreateStruct->hInstance;

	// Lam cho window khong co Border,Title 
	ModifyStyle( WS_CAPTION | WS_BORDER,0);

	
	// remove dialog tu taskbar
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW);

	hHookDLL= AfxLoadLibrary(TEXT("ClickHook.dll"));
	if(!hHookDLL)
	{	AfxMessageBox(TEXT("DLL Init failed #1!"));
		return -1;
	}

	///CString a=_T("MyMouseProc");

	HOOKPROC pMouseHookFunc= (HOOKPROC)GetProcAddress(hHookDLL,"MyMouseProc" );
	pSetHHook= (SETHHOOK)GetProcAddress(hHookDLL,"SetHHook");
	pGetStr= (GETSTR)GetProcAddress(hHookDLL,"GetSharedString");
	pGetStrW= (GETSTRW)GetProcAddress(hHookDLL,"GetSharedStringW");
	pSetLookMode=(SetLMode)GetProcAddress(hHookDLL,"SetLookMode");
	pSetTextMode=(SetTextMode)GetProcAddress(hHookDLL,"SetTextMode");


	hMouseHook = SetWindowsHookEx(WH_MOUSE,pMouseHookFunc,hHookDLL,0); 
	if(!hMouseHook)
	{	AfxFreeLibrary(hHookDLL);
		AfxMessageBox(TEXT("DLL Init failed #2!"));
		return -1;
	}

	//set dll shared variables
	(pSetHHook)(m_hWnd,hMouseHook);

	/*
	shMem.lookMode=1;
	InitMem(&shMem);
	*/

	////load viet speech
/*
	hSpeechDll = LoadLibrary(_T("VNSPEECH.DLL"));
	VietTTS = (VietTTSFuntion*)GetProcAddress(hSpeechDll,"VietTTS");
	if(!hSpeechDll)
	{	FreeLibrary(hSpeechDll);
		AfxMessageBox(TEXT("DLL Init failed #2!"));
		return -1;
	}
*/
	InitSetting(); 
	initSapi();
	
	 
	 
	
	return 0;
}



LRESULT CMultiClickDlg::OnMouseProc(WPARAM wParam, LPARAM lParam) 
{	

	/*
	* Phan Doc
	*/
	CReadTextDlg   m_rtext;
	int doc=0;
	switch(wParam)
		{
			case 9:
				Sleep(50);
				doc=1;
				
				 m_rtext.DoModal();	
			
				break;
			default:break;
		}

	/*
	* Phan Autolook
	*/
	if(doc!=1){

				int isUnicode=0;
				//char buffer[128];
				if(regedit.autoLook!=oldAutoLook){
				(pSetLookMode)(regedit.autoLook);
					oldAutoLook=regedit.autoLook;
				}

				if(Stray.OnAutoLook()){
					CHAR *pStr;
					WCHAR *pStrW;

					
					HGLOBAL hGlobalText;
			//		LPTSTR  myText;
					LPCWSTR myTextU;
			//		WCHAR pCharW[256];

					
					
					POINT point;
					::GetCursorPos(&point); 
					strcpy(pChar,"");
					//_tcscpy(myword,_T(""));
					myword=_T("");
					
					//modeSwitch=ENGLISH_VIETNAMESE;

					
					switch(wParam)
					{
					case -3:
						break;
					case 0:
							Sleep(50);
					
					if(IsClipboardFormatAvailable(CF_UNICODETEXT)){
						if(OpenClipboard()){				
							hGlobalText = GetClipboardData(CF_UNICODETEXT);			
							if (hGlobalText != NULL) { 			
									myTextU =(LPCWSTR)GlobalLock(hGlobalText); 
									myword=(wchar_t *)GlobalLock(hGlobalText); 
									if (myTextU != NULL){ 
										int len=lstrlenW(myTextU);
										// memcpy(pCharW,myTextU,len);
											//WideCharToMultiByte(CP_ACP,0,pCharW,-1,pChar,0,NULL,NULL);
											
											//m_database.GetMeaning("vietanh.dict","vietanh.index",myword);
										//strcpy(pCharW,myTextU);
										::GetCursorPos(&point);		
										//strcpy(pChar,StrCat(_gcvt(point.x,4,temp),_gcvt(point.y,4,pChar)));				StrCat(pChar,pTemp);
										GlobalUnlock(hGlobalText);	
										::CloseClipboard();
									} 
								} 
							}
					}
					/*
					if (!isUnicode&&IsClipboardFormatAvailable(CF_TEXT)) {		
						if(OpenClipboard()){				
							hGlobalText = GetClipboardData(CF_TEXT);			
							if (hGlobalText != NULL) { 			
								
									myText = (TCHAR*)GlobalLock(hGlobalText); 
									if (myText != NULL){ 
										//strcpy(pChar,myText);
										memcpy(pChar,myText,lstrlen(myText));
										if(m_codetable.isVietNamese(pChar)) modeSwitch=VIETNAMESE_ENGLISH;
										else modeSwitch=ENGLISH_VIETNAMESE;
										::GetCursorPos(&point);		
										GlobalUnlock(hGlobalText);	
										::EmptyClipboard();
										::CloseClipboard();
									} 
								} 
							}
						}	
						*/
						
							//strcpy(pChar,"You can get string in the clipboard now");
					
							break;
						case 1:
							pStr= (pGetStr)();
							strcpy(pChar,pStr);
							
							break;
						case 2:
							pStrW= (pGetStrW)();
							WideCharToMultiByte(CP_ACP,0,pStrW,-1,pChar,0,NULL,NULL);
							
							break;
					}
					
					
					
					if(regedit.onlineLookup==0){
						if(strcmp(pChar,"")!=0){
							
							PositionWindowOnBorder(point);
							SetText_CurrentDictBtn();

							//WORD a[2]={0x00e1, 0x00e0};
							//m_database.GetMeaning("anhviet68K.dict","anhviet68K.index",pChar);
							/*
								if(m_database.isWord_InDict("vietanh.index",pChar))
									m_database.GetMeaning("vietanh.dict","vietanh.index",pChar);
								else 
									m_database.GetMeaning("anhviet68K.dict","anhviet68K.index",pChar);
							*/
							m_database.chooseDictionary(regedit.kindDictionary,pChar);
							CString csAddress("");
							csAddress=CurrentDirectory();
							csAddress+="temp.htm";
							COleVariant vtEmpty;
							m_wndBrowser.Navigate(csAddress, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
							
						
						}//end if pChar
						else if(_tcscmp(myword,_T(""))){
						PositionWindowOnBorder(point);
						SetText_CurrentDictBtn();
							//WORD a[2]={0x00e1, 0x00e0};
							//m_database.GetMeaning("anhviet68K.dict","anhviet68K.index",pChar);
						/*
								if(m_database.isWord_InDict("vietanh.index",myword))
									m_database.GetMeaning("vietanh.dict","vietanh.index",myword);
								else 
									m_database.GetMeaning("anhviet68K.dict","anhviet68K.index",myword);
							*/
						   
							m_database.chooseDictionary(regedit.kindDictionary,myword);

							
							CString csAddress("");
							csAddress=CurrentDirectory();
							csAddress+="temp.htm";

							COleVariant vtEmpty;
							m_wndBrowser.Navigate(csAddress, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
							
						}else{
							//AfxMessageBox(_T("High light text before lookup"));
							MessageBox(_T("Hight light text Before Lookup!!! "));
						}
					}else{

						if(strcmp(pChar,"")!=0){
							
							PositionWindowOnBorder(point);
							SetText_CurrentDictBtn();
						
							COleVariant vtEmpty;
						//	CString Length("");
						//	CString offset("");

						//	Length=m_database.GetOffSet_LengthOnline("vietanh.index",myword,offset);
							
							//MessageBox(pChar);
							
							//address+=myword;
							
							CString dict("");
							CString argURL=m_database.chooseDictionaryOnline(regedit.kindDictionary,pChar,dict);
							
							CString address=TEXT("http://multidict.net/java/net/forever/rain/blue/multidict/onlinedictionary.jsp?"+argURL);
							//MessageBox(argURL);
							currentDict=dict;


							//UpdateData(TRUE);
							m_wndBrowser.Navigate(address, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
							
							//Sleep(1000);
							//m_wndBrowser.Refresh();

						
						}//end if pChar
						else if(_tcscmp(myword,_T(""))){
							
							PositionWindowOnBorder(point);
							SetText_CurrentDictBtn();
							
						  

							COleVariant vtEmpty;
							//CString address("");
							//CString Length("");
							//CString offset("");

							//Length=m_database.GetOffSet_LengthOnline("vietanh.index",myword,offset);
							
							
							
							
							//address+=myword;
							
							CString dict("");
							//	m_database.chooseDictionaryOnline(regedit.kindDictionary,myword,dict);
							CString argURL=m_database.chooseDictionaryOnline(regedit.kindDictionary,myword,dict);
							CString address=TEXT("http://multidict.net/java/net/forever/rain/blue/multidict/onlinedictionary.jsp?"+argURL);
							currentDict=dict;
							//MessageBox(argURL);
						
							//UpdateData(TRUE);
							m_wndBrowser.Navigate(address, &vtEmpty, &vtEmpty, &vtEmpty, &vtEmpty);
							
							//Sleep(1000);
							//m_wndBrowser.Refresh();
							
						}else{
							//AfxMessageBox(_T("High light text before lookup"));
							MessageBox(_T("Hight light text Before Lookup!!! "));
						}
					}
					
					
					
				Stray.CheckAutoLookOnF();

				 
				}//end if onautoLook
				
				
					//CDC* pDC=GetDC();
					//reDrawTitle(pDC,_T("ab"));
   }//end if doc!=1
		
	return true; 
}

/*
 * PositionWindowOnBorder
 *
 * Dat window tai vi tri nao do cua window
 */
void CMultiClickDlg::PositionWindowOnBorder( CPoint point)
{
POINT ptCursor = {point.x, point.y};
LONG cxScreen, cyScreen;
RECT rFrame;
int frameWidth;
int frameHeight;
int x,y;

	
	ClientToScreen(&ptCursor);
	GetWindowRect(&rFrame);


	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);

	frameWidth =  rFrame.right - rFrame.left;
	frameHeight =  rFrame.bottom - rFrame.top;
	x=point.x;
	y=point.y;
	if(point.x>cxScreen/2){
		x=point.x-frameWidth;
	}
	if(point.y>cyScreen/2){
		y=point.y-frameHeight;
	}
	
	if(pChar!=NULL){
				
			SetWindowPos(NULL,x,y, NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER |SWP_SHOWWINDOW);
			BringWindowToTop();
	}
}

/*
 * OnLButtonDown
 *
 * Xu li su kien nhan chuot trong dialog
 */
void CMultiClickDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
POINT ptCursor = {point.x, point.y};
RECT rFrame;

	ClientToScreen(&ptCursor);

	if (m_closeRect.PtInRect(point))
		SendMessage(WM_CLOSE,0,0);
	else
	{
		// Stop the Timer
		KillTimer (IDT_AUTOHIDE);


		m_bMoving = TRUE;
		GetWindowRect(&rFrame);
		
		// get the original pointer position
		m_dx = ptCursor.x - rFrame.left;
		m_dy = ptCursor.y - rFrame.top;

		// Luu lai  Window
		// Truoc khi di chuyen window
		SetCapture();	
	}
	
	CNewDialog::OnLButtonDown(nFlags, point);
}

/*
 * OnMouseMove
 *
 * Xu li su kien mouse move trong dialog
 */
void CMultiClickDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bMoving)
    {
		return;
    }

	moveWindow(point);


	CNewDialog::OnMouseMove(nFlags, point);
}

/*
 * OnLButtonUp
 *
 * Xu li chuot trai nha ra
 */
void CMultiClickDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{

	if (!m_bMoving)
    {
		return;
    }
	// di chuyen window theo chuot
	moveWindow(point);

	// Thoi khong capture window
	ReleaseCapture();				

	m_bMoving = FALSE;

	// Khoi dong lai AutoHide Timer
	SetTimer(IDT_AUTOHIDE,500,NULL);
	
    CNewDialog::OnLButtonUp(nFlags, point);
}

/*
 * SetAutoHide
 *
 * Cap nhat tinh trang AutoHide cua Window
 * Khoi dong AutoHide Timer
 */
void CMultiClickDlg::SetAutoHide(BOOL bAutoHide)
{
	m_bAutoHide = bAutoHide;
	OnAutoHide();
}

void CMultiClickDlg::OnAutoHide()
{
	if (m_bAutoHide == TRUE)
	{
		HideTabWindow();
		SetTimer(IDT_AUTOHIDE,500,NULL);
	}
	else
	{
		ShowTabWindow();
		KillTimer(IDT_AUTOHIDE);
		
	}
}

void CMultiClickDlg::SetTopMost(BOOL bTopMost)
{
	m_bTopMost = bTopMost;
	OnTopMost();
}


void CMultiClickDlg::OnTopMost()
{

	//SetCursorPos(140,0);
	if (m_bTopMost == TRUE)
	    SetWindowPos(&wndTopMost,
		             0, 0, 0, 0, 
			         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	else
	    SetWindowPos(&wndNoTopMost,
		             0, 0, 0, 0, 
			         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

}

void CMultiClickDlg::OnTimer(UINT nIDEvent) 
{
CPoint pt;
HWND hwndActive;
CPoint ptCursor;
CRect rc;
	

	if (nIDEvent = IDT_AUTOHIDE)
	{
		KillTimer (nIDEvent);

	 	GetCursorPos(&pt);

		ptCursor = pt;
		
        hwndActive = (HWND) GetForegroundWindow();
	

		// offset the point for the hitTest
		ScreenToClient(&ptCursor);
		if (!m_closeRect.PtInRect(ptCursor))
		{
			
			if (m_testRgn.PtInRegion(ptCursor) || m_bAutoHide==FALSE || keepdialog==true){
				ShowTabWindow();
				if(GetFocus()==NULL){
					m_opacity.SetWindowLayered (this->GetSafeHwnd ());
					m_opacity.SetWindowOpacity (this->GetSafeHwnd (), 100);
				}else{
						m_opacity.SetWindowLayered (this->GetSafeHwnd ());
						m_opacity.SetWindowOpacity (this->GetSafeHwnd (), 255);
				}
			}
				
			else{
				HideTabWindow();
			}
				

		}
		
		SetTimer(IDT_AUTOHIDE,100,NULL);
	}
	
	CNewDialog::OnTimer(nIDEvent);
}



void CMultiClickDlg::HideTabWindow()
{
CRect rect;
int width,height;
int nX, nY;

	if (m_bHiddenStatus == TRUE) return;

	GetWindowRect(&rect);

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	if (m_nBorderPos == TAB_BORDER_LEFT)
	{
		nX = m_nXpos - (width -m_nTabHeight);
		nY = m_nYpos;
	}
	else
	if (m_nBorderPos == TAB_BORDER_RIGHT)
	{
		nX = m_nXpos + (width - m_nTabHeight);
		nY = m_nYpos;
	}
	else
	if (m_nBorderPos == TAB_BORDER_TOP)
	{
		nX = m_nXpos;
		nY = m_nYpos  - (height  - m_nTabHeight);
	}
	else
	if (m_nBorderPos == TAB_BORDER_BOTTOM)
	{
		nX = m_nXpos;
		nY = m_nYpos  + (height  - m_nTabHeight);
	}

	
	SetWindowPos(NULL, nX, nY, NULL, NULL, SWP_NOSIZE|  SWP_NOZORDER| SWP_HIDEWINDOW);
	//ShowWindow(SW_HIDE);
	m_bHiddenStatus = TRUE;
}


void CMultiClickDlg::ShowTabWindow()
{
	if (m_bHiddenStatus == FALSE) return;

	m_bHiddenStatus = FALSE;

}

BOOL CALLBACK EnumChildProc( HWND hwnd, 
							LPARAM lParam)
{
RECT rect;
CRect *pRect;
POINT pt2;

	pRect = (CRect *)(lParam);

	GetWindowRect(hwnd,&rect);

	pt2.x = rect.left - pRect->left + pRect->right;
	pt2.y = rect.top  - pRect->top + pRect->bottom;

	SetWindowPos(hwnd,NULL, pt2.x , pt2.y , NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER );

	return(TRUE);
}
void CMultiClickDlg::moveWindow(CPoint point){
	POINT ptCursor = {point.x, point.y};
LONG cxScreen, cyScreen;
RECT rFrame;
RECT rNewFrame;
int frameWidth;
int frameHeight;


	ClientToScreen(&ptCursor);

	GetWindowRect(&rFrame);


	
	cxScreen = GetSystemMetrics(SM_CXSCREEN);
	cyScreen = GetSystemMetrics(SM_CYSCREEN);

	frameWidth =  rFrame.right - rFrame.left;
	frameHeight =  rFrame.bottom - rFrame.top;

	//tinh vi tri moi
	rNewFrame.left = ptCursor.x - m_dx;
	rNewFrame.top = ptCursor.y - m_dy ;


	SetWindowPos(NULL, rNewFrame.left, rNewFrame.top, NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER );

	
}

/*
 * MoveDialogControls 
 */
void CMultiClickDlg::MoveDialogControls(int nX,int nY)
{
CRect *pRect;

	pRect = new CRect;

	GetWindowRect(pRect);

	pRect->right  = nX - m_nXControlsMoved;
	pRect->bottom = nY - m_nYControlsMoved;


	m_nXControlsMoved = nX;
	m_nYControlsMoved = nY;


	EnumChildWindows( this->m_hWnd, 
						&EnumChildProc, 
					 (LPARAM)	pRect);
 
    delete (pRect);

	
}

/*
 * CreateTabPolygon
 * Tao goc cua cho dialog
 */
void CMultiClickDlg::CreateTabPolygon()
{
int x;
int y;
CRect rect;
int tabDec;
int nXClose, nYClose;


	if ( (m_nBorderPos  == TAB_BORDER_TOP) || (m_nBorderPos == TAB_BORDER_BOTTOM))
	{
		// update Window Height in order to create the Tab
		SetWindowPos(NULL, m_nXpos, m_nYpos, m_nInitialWidth, m_nInitialHeight + m_nTabHeight, SWP_NOZORDER );
		tabDec = m_nInitialWidth - m_nTabWidth;

		// move all controls in the Window

		if (m_nBorderPos == TAB_BORDER_BOTTOM)
			MoveDialogControls(0,m_nTabHeight);
		else
			MoveDialogControls(0,0);
	}
	else
	{
		// update Window Width in order to create the Tab
		SetWindowPos(NULL, m_nXpos, m_nYpos, m_nInitialWidth + m_nTabHeight, m_nInitialHeight, SWP_NOZORDER );
		tabDec = m_nInitialHeight - m_nTabWidth;

		// move all controls in the Window
		if (m_nBorderPos == TAB_BORDER_RIGHT)
			MoveDialogControls(m_nTabHeight,0);
		else
			MoveDialogControls(0,0);

	}
	// free the old polygon 
	m_polygon.Free();

	// get window size
	GetWindowRect(&rect);

	// create a polygon used for Region and Drawing
	if (m_nBorderPos == TAB_BORDER_LEFT) 
	{
		x = 0;
		y = 0;
		m_polygon.AddPoint(x,y);
		x = rect.Width() -  m_nTabHeight -m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabHeight ;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = tabDec -m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabHeight +m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		y = tabDec + m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = rect.Height()  -m_nTabRound-1;
		m_polygon.AddPoint(x,y);
		x = rect.Width() -m_nTabRound-1;
		y = rect.Height();
		m_polygon.AddPoint(x,y);
		x = 0;
		m_polygon.AddPoint(x,y);
		y = 0;
		m_polygon.AddPoint(x,y);

		m_nXIcon = rect.Width()  - m_nTabHeight + m_nTabRound;
		m_nYIcon = rect.Height() - m_nTabRound;
	}
	else
	if (m_nBorderPos == TAB_BORDER_RIGHT) 
	{
		x = m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);
		x = 0;
		y = tabDec + m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = rect.Height() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabRound;
		y = rect.Height();
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		m_polygon.AddPoint(x,y);
		y = 0;
		m_polygon.AddPoint(x,y);
		x = m_nTabHeight +  m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabHeight;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = tabDec - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabHeight -m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);
		x = m_nTabRound;
		y = tabDec;
		m_polygon.AddPoint(x,y);

		m_nXIcon = m_nTabRound;;
		m_nYIcon = rect.Height() - m_nTabRound;
	}
	else
	if (m_nBorderPos == TAB_BORDER_TOP) 
	{
		x = 0;
		y = 0;
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		y = 0;
		m_polygon.AddPoint(x,y);
		y = rect.Height() - m_nTabHeight - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabRound;
		y = rect.Height() - m_nTabHeight;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec + m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec ;
		y = rect.Height() - m_nTabHeight + m_nTabRound;
		m_polygon.AddPoint(x,y);			
		y = rect.Height() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec  - m_nTabRound;
		y = rect.Height();
		m_polygon.AddPoint(x,y);				
		x = m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = 0;
		y = rect.Height() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = 0;
		m_polygon.AddPoint(x,y);

		
		m_nXIcon = m_nTabRound;;
		m_nYIcon = rect.Height() - (m_nTabHeight  -m_nTabRound);
	}
	else
	if (m_nBorderPos == TAB_BORDER_BOTTOM) 
	{
		x = 0;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = m_nTabRound;
		y = 0;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec;
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = m_nTabHeight - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - tabDec + m_nTabRound;
		y = m_nTabHeight;
		m_polygon.AddPoint(x,y);
		x = rect.Width() - m_nTabRound;
		m_polygon.AddPoint(x,y);
		x = rect.Width();
		y = m_nTabHeight + m_nTabRound;
		m_polygon.AddPoint(x,y);
		y = rect.Height();
		m_polygon.AddPoint(x,y);
		x = 0;
		m_polygon.AddPoint(x,y);
		y = m_nTabRound;
		m_polygon.AddPoint(x,y);
		
		m_nXIcon = m_nTabRound;
		m_nYIcon = m_nTabRound;

	}

	m_nXDC = nXClose = m_nXIcon ;
	m_nYDC = nYClose = m_nYIcon;

	// compute new position for memory DC and for the Close Rectangle
	if ((m_nBorderPos == TAB_BORDER_BOTTOM) || (m_nBorderPos == TAB_BORDER_TOP))
	{
		// if there is an icon, increase X position of the memory HDC
		if (m_hTitleIcon != NULL)
			m_nXDC += SIZE_ICON_X + m_nTabRound;

		nXClose  = m_nXDC +  m_DCRect.Width() +  2*m_nTabRound;

		m_closeRect.left	= nXClose;
		m_closeRect.right	= m_closeRect.left + SIZE_CLOSE_X;
		m_closeRect.top		= m_nYDC + (m_nTabHeight -SIZE_CLOSE_Y)  / 2 - m_nTabRound;
		m_closeRect.bottom	= m_closeRect.top + SIZE_CLOSE_Y;
	}
	else
	{
		// if there is an icon, increase Y position of the memory HDC
		if (m_hTitleIcon != NULL)
			m_nYDC -=  (SIZE_ICON_Y +m_nTabRound);

		nYClose = m_nYDC -(m_DCRect.Width()+ 2*m_nTabRound);
		
		m_closeRect.left	= m_nXDC + (m_nTabHeight -SIZE_CLOSE_X)  / 2 - m_nTabRound;;
		m_closeRect.right	= m_closeRect.left + SIZE_CLOSE_X;
		m_closeRect.bottom	= nYClose;
		m_closeRect.top 	= m_closeRect.bottom - SIZE_CLOSE_Y;
	}

	// delete old region if necessary
	if (m_Rgn.m_hObject != NULL)
		m_Rgn.DeleteObject();

	if (m_testRgn.m_hObject != NULL)
		m_testRgn.DeleteObject();

	// create a new Region based on the PolyGon
	m_Rgn.CreatePolygonRgn (m_polygon.m_pPoints,m_polygon.m_nPoints,WINDING);
	

	// region used for hit Test
	// we need another region for the HitTest because SetWindowRgn handle m_Rgn
	m_testRgn.CreatePolygonRgn(m_polygon.m_pPoints,m_polygon.m_nPoints,WINDING);

	// appy the region to the Window
	SetWindowRgn(m_Rgn, TRUE);

	// force the Window to be drawn
	Invalidate();
}



BOOL CMultiClickDlg::OnEraseBkgnd(CDC *pDC)
{
CPen PenBorder(PS_SOLID,2,GetSysColor(COLOR_3DDKSHADOW ));
CPen PenLightBorder(PS_SOLID,2,GetSysColor(COLOR_3DDKSHADOW ));
BOOL bRet;

	// calls the bas Dialog Method
	bRet = CNewDialog::OnEraseBkgnd(pDC);


	// if there are no points in the polygon, we return.....

	if (m_polygon.m_nPoints == 0) return(bRet);

	// draw the light border all around the window
	pDC->SelectObject(&PenLightBorder);
	pDC->Polyline(m_polygon.m_pPoints,m_polygon.m_nPoints);

	//=============== to mau cho nen==============
	//backcolor
	CBrush brush(RGB(210,228,252));
	CRect rect;
	GetWindowRect(&rect);
	pDC->SetBkMode(TRANSPARENT);
	
	//pDC->FillSolidRect(10,10,rect.Width,rect.Height,RGB(255,0,0));
	rect.left=0;
	rect.top=0;

	pDC->FillRect(&rect,&brush);

	

	
	

	
	// draw the dark border depending of the window position

	pDC->SelectObject(&PenBorder);

	

	if (m_nBorderPos == TAB_BORDER_LEFT)
	{
		pDC->MoveTo (m_polygon.m_pPoints[2]);
		pDC->LineTo (m_polygon.m_pPoints[3]);

		pDC->MoveTo (m_polygon.m_pPoints[6]);
		pDC->LineTo (m_polygon.m_pPoints[7]);
		pDC->LineTo (m_polygon.m_pPoints[8]);
		pDC->LineTo (m_polygon.m_pPoints[9]);
	}
	else
	if (m_nBorderPos == TAB_BORDER_RIGHT)
	{
		pDC->MoveTo (m_polygon.m_pPoints[3]);
		pDC->LineTo (m_polygon.m_pPoints[4]);

		pDC->LineTo (m_polygon.m_pPoints[5]);
	}
	else
	if (m_nBorderPos == TAB_BORDER_TOP)
	{
		pDC->MoveTo (m_polygon.m_pPoints[1]);
		pDC->LineTo (m_polygon.m_pPoints[2]);
		pDC->LineTo (m_polygon.m_pPoints[3]);
		pDC->LineTo (m_polygon.m_pPoints[4]);
		pDC->LineTo (m_polygon.m_pPoints[5]);
		pDC->LineTo (m_polygon.m_pPoints[6]);
		pDC->LineTo (m_polygon.m_pPoints[7]);
		pDC->LineTo (m_polygon.m_pPoints[8]);

	}
	else
	if (m_nBorderPos == TAB_BORDER_BOTTOM)
	{
		pDC->MoveTo (m_polygon.m_pPoints[3]);
		pDC->LineTo (m_polygon.m_pPoints[4]);

		pDC->MoveTo (m_polygon.m_pPoints[7]);
		pDC->LineTo (m_polygon.m_pPoints[8]);
		pDC->LineTo (m_polygon.m_pPoints[9]);

	}



   
	// if the title hdc is OK we draw it back to the Window
	if (m_pDC.m_hDC != NULL)
	{
		if ((m_nBorderPos == TAB_BORDER_BOTTOM) || (m_nBorderPos == TAB_BORDER_TOP))
		{
			// on the top and bottom border the title is hrizontal
			pDC->BitBlt( m_nXDC,m_nYDC, m_DCRect.Width(),  m_DCRect.Height(), &m_pDC, 0, 0, SRCCOPY );
		}
		else
		{
			// on the left and right border the title is vertical, so we need to rotate the DC

			POINT	pnts[3];
			CBitmap bitmap;

			pnts[0].x	=	m_nXDC;
			pnts[0].y	=	m_nYDC;
			pnts[1].x	=	m_nXDC;
			pnts[1].y	=	m_nYDC - m_DCRect.Width() ;
			pnts[2].x	=	m_nXDC + m_DCRect.Height();
			pnts[2].y	=	m_nYDC;
			
			pDC->PlgBlt(pnts,
						&m_pDC,
						0,
						0,
						m_DCRect.Width(),
						m_DCRect.Height(),
						CBitmap(),
						0,
						0);

		}

	}


	return(bRet);
}

LRESULT CMultiClickDlg::OnTrayNotification(WPARAM wParam,LPARAM lParam)
{
	
	Stray.OnNotifyTray(lParam);

	return 0L;

}

void CMultiClickDlg::OnEndKey(){
	//Stray.OnShowConfig();
	//Stray.OnDestroyTray();
	if(hMouseHook)
		UnhookWindowsHookEx(hMouseHook);
	if(hKeyHook)
		UnhookWindowsHookEx(hKeyHook);

	AfxFreeLibrary(hHookDLL);

	m_database.DestroyHash();
	//FreeLibrary(hSpeechDll);
	//SetRegeditVal();
	Stray.OnEndKey();
	
	
}

void CMultiClickDlg::OnShowConfig(){
	
	//CSettingDlg dlg;
	//dlg.DoModal();
	
	CSettingDlg wndPageSetting;
	CAuthorDlg wndPageAuthor;
	CReadDlg	wndPageRead;
	CServerDlg	wndPageServer;
	CPropertyPage wndPageAbout(IDD_ABOUT);
	CDictionaryDlg	wndPageDictionary;

	// disable help button
	wndPageSetting.m_psp.dwFlags&= ~PSP_HASHELP;
	wndPageAuthor.m_psp.dwFlags&= ~PSP_HASHELP;
	wndPageAbout.m_psp.dwFlags&= ~PSP_HASHELP;
	wndPageRead.m_psp.dwFlags&= ~PSP_HASHELP;
	wndPageServer.m_psp.dwFlags&= ~PSP_HASHELP;
	wndPageDictionary.m_psp.dwFlags&= ~PSP_HASHELP;


	// set images
	CImageList	DefaultImages, Images,ImageAbout;
	DefaultImages.Create(IDB_DEFAULT, 16, 0, RGB(0x00, 0x80, 0x80));
//	ImageServer.Create(IDB_SERVER, 16, 0, RGB(0x00, 0x80, 0x80));
	//ImageAuthor.Create(IDB_AUTHOR, 16, 0, RGB(0x00, 0x80, 0x80));
	ImageAbout.Create(IDB_ABOUT, 16, 0, RGB(0x00, 0x80, 0x80));
	//ImageRead.Create(IDB_R, 16, 0, RGB(0x00, 0x80, 0x80));
	//ImageDict.Create(IDB_DICTIONARY, 16, 0, RGB(0x00, 0x80, 0x80));
	
	//TreePropSheet::CTreePropSheet::SetPageIcon(&wndPageSetting, DefaultImages, 0);
	//TreePropSheet::CTreePropSheet::SetPageIcon(&wndPageAuthor, ImageAuthor, 0);
	TreePropSheet::CTreePropSheet::SetPageIcon(&wndPageAbout, ImageAbout, 0);
	//TreePropSheet::CTreePropSheet::SetPageIcon(&wndPageServer, ImageServer, 0);
	//TreePropSheet::CTreePropSheet::SetPageIcon(&wndPageRead, ImageRead, 0);
	//TreePropSheet::CTreePropSheet::SetPageIcon(&wndPageDictionary, ImageDict, 0);


	TreePropSheet::CTreePropSheet sht(_T("InfoDict 2.0"));
	sht.m_psh.dwFlags&= ~PSH_HASHELP;
	sht.AddPage(&wndPageSetting);
	sht.AddPage(&wndPageRead);
	sht.AddPage(&wndPageServer);
	sht.AddPage(&wndPageDictionary);
	sht.AddPage(&wndPageAuthor);
	sht.AddPage(&wndPageAbout);



	sht.SetEmptyPageText(_T("Please select a child item of '%s'."));

	sht.SetTreeViewMode(TRUE, TRUE, TRUE);
	sht.SetTreeWidth(170);

		

	sht.SetTreeDefaultImages(&DefaultImages);
	sht.SetActivePage(&wndPageSetting);

	sht.setHWND(m_hWnd);


	//sht.DestroyPageIcon(&wndPageSetting);
	
	sht.DoModal();

}
void CMultiClickDlg::CheckAutoLookOn(){

	if(Stray.OnAutoLook()){
		//AfxMessageBox("DLL Init failed #1!");
		Stray.CheckAutoLookOff();
		regedit.onAutoLook=0;
	}
	else{
		Stray.CheckAutoLookOn();
		regedit.onAutoLook=1;
	}
}
void CMultiClickDlg::chooseModeLook1(){
	Stray.chooseModeLook1();
	(pSetLookMode)(CTRL_RIGHT_CLICK);
}
void CMultiClickDlg::chooseModeLook2(){
	Stray.chooseModeLook2();
	(pSetLookMode)(SHIFT_RIGHT_CLICK);
}

void CMultiClickDlg::chooseModeLook3(){
	Stray.chooseModeLook3();
	(pSetLookMode)(RIGHT_CLICK);
}


void CMultiClickDlg::InitSetting(){
	
	regedit.getValue();
	//(pBuildCode)(regedit.charset,regedit.inputMethod,regedit.switchKey);//index,typing
	(pSetLookMode)(regedit.autoLook);
	//(pSetTextMode)(regedit.onlyText);
	oldAutoLook=regedit.autoLook;
//	backcolor=(COLORREF)regedit.backcolor;
//	titlecolor=(COLORREF)regedit.titlecolor;
//	textcolor=(COLORREF)regedit.textcolor;
	
}

void CMultiClickDlg::SetRegeditVal(){
	if(Stray.OnAutoLook()) regedit.onAutoLook=1;
	else regedit.onAutoLook=0;
	regedit.enableAutoStart(regedit.autoStart);
	regedit.setValue();
}
void CMultiClickDlg::openHelp(){
	
	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	//tra? ve^` te^n va` du+o+`ng da^~n lu+u trong bie^'n path
	// vi' du. : D:\multiclick\multiclick.exe

	TCHAR *p = _tcsrchr(path, _TEXT('\\'));
	_tcscpy(p+1, _TEXT("help.chm"));						

	ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);
	
	
	
}
//==========Input Method
void checkInputMethod(UINT item){
	for(int i=0;i<NUM_TYPING;i++){
			if(InputMethod[i].id==item){
				Stray.CheckItem(InputMethod[i].id,TRUE);
				regedit.inputMethod=i;
			}
			else
				Stray.CheckItem(InputMethod[i].id,FALSE);
	}
}
void CMultiClickDlg::telexTyping(){
	Stray.CheckItem(ID_TELEX_TYPING,TRUE);
	Stray.CheckItem(ID_VNI_TYPING,FALSE);
	regedit.inputMethod=0;
	(pBuildCode)(regedit.charset,regedit.inputMethod,regedit.switchKey);//index,typing
}
void CMultiClickDlg::vniTyping(){
	Stray.CheckItem(ID_TELEX_TYPING,FALSE);
	Stray.CheckItem(ID_VNI_TYPING,TRUE);
	regedit.inputMethod=0;
	(pBuildCode)(regedit.charset,regedit.inputMethod,regedit.switchKey);//index,typing
}
//=========Charset
UINT charsetArray[]={ID_KEY_TCVN3,
					 ID_KEY_VIETWAREF,ID_KEY_VIQR,ID_KEY_VIETWAREX,ID_KEY_VNI,ID_KEY_UNICODE,ID_KEY_BKHCM2,ID_KEY_BKHCM1,ID_KEY_VPS,ID_KEY_VISCII};
void CMultiClickDlg::checkCharset(UINT item){
	for(int i=0;i<NUM_CHARSET;i++){  
			if(charsetArray[i]==item){
				Stray.CheckItem(charsetArray[i],TRUE);
				regedit.charset=i;
			}
			else
				Stray.CheckItem(charsetArray[i],FALSE);
	}
	(pBuildCode)(regedit.charset,regedit.inputMethod,regedit.switchKey);//index,typing
	
}

void CMultiClickDlg::tcvn3Charset(){
	checkCharset(ID_KEY_TCVN3);
	
}
void CMultiClickDlg::unicodeCharset(){
	checkCharset(ID_KEY_UNICODE);
}
void CMultiClickDlg::vniCharset(){
		checkCharset(ID_KEY_VNI);
}
void CMultiClickDlg::viqrCharset(){
	checkCharset(ID_KEY_VIQR);
}
void CMultiClickDlg::vietwarexCharset(){
	checkCharset(ID_KEY_VIETWAREX);
}
void CMultiClickDlg::vietwarefCharset(){
	checkCharset(ID_KEY_VIETWAREF);
}
void CMultiClickDlg::hcm1Charset(){
	checkCharset(ID_KEY_BKHCM1);
}
void CMultiClickDlg::hcm2Charset(){
	checkCharset(ID_KEY_BKHCM2);
}
void CMultiClickDlg::vpsCharset(){
	checkCharset(ID_KEY_VPS);
}
void CMultiClickDlg::visciiCharset(){
	checkCharset(ID_KEY_VISCII);
}

//==================================================
void CMultiClickDlg::OnDialogConf(){
	CVNKeyBoardDlg dlg;
	dlg.DoModal();
}

void CMultiClickDlg::OpenDictionary(){
	

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	//tra? ve^` te^n va` du+o+`ng da^~n lu+u trong bie^'n path
	// vi' du. : D:\multiclick\multiclick.exe

	TCHAR *p = _tcsrchr(path, _TEXT('\\'));
	_tcscpy(p+1, _TEXT("MultiDictionary.exe"));						

	ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);
	
	
}

void CMultiClickDlg::OpenEVDictionary(){
	///Tao Thanh Tien Trinh Loading data
	CString progress=CurrentDirectory()+_T("ProgressEV.exe");
	ShellExecute(NULL,_T("open"),progress, NULL, NULL, SW_SHOWNORMAL);

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	//tra? ve^` te^n va` du+o+`ng da^~n lu+u trong bie^'n path
	// vi' du. : D:\multiclick\multiclick.exe

	TCHAR *p = _tcsrchr(path, _TEXT('\\'));
	_tcscpy(p+1, _TEXT("EVDict.exe"));						

	ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);


	
	
}
void CMultiClickDlg::OpenFVDictionary(){
	//Tao Than hTien Trinh Loading Data
	CString progress=CurrentDirectory()+_T("Progress.exe");
	ShellExecute(NULL,_T("open"),progress, NULL, NULL, SW_SHOWNORMAL);

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	//tra? ve^` te^n va` du+o+`ng da^~n lu+u trong bie^'n path
	// vi' du. : D:\multiclick\multiclick.exe

	TCHAR *p = _tcsrchr(path, _TEXT('\\'));
	_tcscpy(p+1, _TEXT("FVDict.exe"));						

	ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);


	
}
void CMultiClickDlg::OpenGVDictionary(){
	//Tao Than hTien Trinh Loading Data
	CString progress=CurrentDirectory()+_T("ProgressDV.exe");
	ShellExecute(NULL,_T("open"),progress, NULL, NULL, SW_SHOWNORMAL);


	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	//tra? ve^` te^n va` du+o+`ng da^~n lu+u trong bie^'n path
	// vi' du. : D:\multiclick\multiclick.exe

	TCHAR *p = _tcsrchr(path, _TEXT('\\'));
	_tcscpy(p+1, _TEXT("DVDict.exe"));						

	ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);

	
}
void CMultiClickDlg::OpenNNVDictionary(){
	//Tao Than hTien Trinh Loading Data
	CString progress=CurrentDirectory()+_T("ProgressDV.exe");
	ShellExecute(NULL,_T("open"),progress, NULL, NULL, SW_SHOWNORMAL);

	TCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		
	//tra? ve^` te^n va` du+o+`ng da^~n lu+u trong bie^'n path
	// vi' du. : D:\multiclick\multiclick.exe

	TCHAR *p = _tcsrchr(path, _TEXT('\\'));
	_tcscpy(p+1, _TEXT("NVADict.exe"));						

	ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);

	

}
//======================================================
//Cho.n loa.i tu+. die^?n
void CMultiClickDlg::chooseEnglish(){
	Stray.CheckItem(ID_LOOKUPON_FRANCE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_ENGLISH,TRUE);
	Stray.CheckItem(ID_LOOKUPON_GERMANY,FALSE);
	Stray.CheckItem(ID_LOOKUPON_VIETNAMESE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_RUSSIA,FALSE);
	Stray.CheckItem(ID_LOOKUPON_NAUY,FALSE);
	regedit.kindDictionary=0;
	InitHash();
	
}
void CMultiClickDlg::chooseFrance(){
	Stray.CheckItem(ID_LOOKUPON_FRANCE,TRUE);
	Stray.CheckItem(ID_LOOKUPON_ENGLISH,FALSE);
	Stray.CheckItem(ID_LOOKUPON_GERMANY,FALSE);
	Stray.CheckItem(ID_LOOKUPON_VIETNAMESE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_RUSSIA,FALSE);
	Stray.CheckItem(ID_LOOKUPON_NAUY,FALSE);
	regedit.kindDictionary=1;
	InitHash();
}
void CMultiClickDlg::chooseGermany(){
	Stray.CheckItem(ID_LOOKUPON_FRANCE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_ENGLISH,FALSE);
	Stray.CheckItem(ID_LOOKUPON_GERMANY,TRUE);
	Stray.CheckItem(ID_LOOKUPON_VIETNAMESE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_RUSSIA,FALSE);
	Stray.CheckItem(ID_LOOKUPON_NAUY,FALSE);
	regedit.kindDictionary=2;
	InitHash();
}
void CMultiClickDlg::chooseVietnamese(){
	Stray.CheckItem(ID_LOOKUPON_FRANCE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_ENGLISH,FALSE);
	Stray.CheckItem(ID_LOOKUPON_GERMANY,FALSE);
	Stray.CheckItem(ID_LOOKUPON_VIETNAMESE,TRUE);
	Stray.CheckItem(ID_LOOKUPON_RUSSIA,FALSE);
	Stray.CheckItem(ID_LOOKUPON_NAUY,FALSE);
	regedit.kindDictionary=3;
	InitHash();
	
}
void  CMultiClickDlg::chooseRussia(){
	Stray.CheckItem(ID_LOOKUPON_FRANCE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_ENGLISH,FALSE);
	Stray.CheckItem(ID_LOOKUPON_GERMANY,FALSE);
	Stray.CheckItem(ID_LOOKUPON_VIETNAMESE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_RUSSIA,TRUE);
	Stray.CheckItem(ID_LOOKUPON_NAUY,FALSE);
	regedit.kindDictionary=4;
	InitHash();
}
void  CMultiClickDlg::chooseNauy(){
	Stray.CheckItem(ID_LOOKUPON_FRANCE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_ENGLISH,FALSE);
	Stray.CheckItem(ID_LOOKUPON_GERMANY,FALSE);
	Stray.CheckItem(ID_LOOKUPON_VIETNAMESE,FALSE);
	Stray.CheckItem(ID_LOOKUPON_RUSSIA,FALSE);
	Stray.CheckItem(ID_LOOKUPON_NAUY,TRUE);
	regedit.kindDictionary=5;
	InitHash();
}
	

//======================================================
void CMultiClickDlg::reDrawTitle(CDC* pDC,CString newTitle){
	
	if(regedit.onlineLookup==0){
		CRect titleRect;
		GetWindowRect(&titleRect);
		titleRect.top=20;
		titleRect.left=100;
		//CBrush brush(backcolor);
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetTextColor(backcolor);
		//pDC->DrawText( m_sTitle,&titleRect, DT_LEFT | DT_VCENTER |DT_NOPREFIX |DT_END_ELLIPSIS);
		pDC->SetTextColor(RGB(123,123,123));
		wchar_t unicode_string[256];
	 
		Utf8_Unicode((BYTE*)"InfoDict 2.0 -- Phiên Bản Cục Bộ",unicode_string);
		pDC->DrawText(unicode_string,&titleRect, DT_LEFT | DT_VCENTER |DT_NOPREFIX |DT_END_ELLIPSIS);
	}else if(regedit.onlineLookup==1){
		CRect titleRect;
		GetWindowRect(&titleRect);
		titleRect.top=20;
		titleRect.left=100;
		//CBrush brush(backcolor);
		pDC->SetBkMode(TRANSPARENT);
		//pDC->SetTextColor(backcolor);
		//pDC->DrawText( m_sTitle,&titleRect, DT_LEFT | DT_VCENTER |DT_NOPREFIX |DT_END_ELLIPSIS);
		pDC->SetTextColor(RGB(123,123,123));
		wchar_t unicode_string[256];
	 
		Utf8_Unicode((BYTE*)"InfoDict 2.0 Phiên Bản Trực Tuyến",unicode_string);
		pDC->DrawText(unicode_string,&titleRect, DT_LEFT | DT_VCENTER |DT_NOPREFIX |DT_END_ELLIPSIS);
	}
	
	
}





void CMultiClickDlg::OnBnClickedSound()
{
	
	if(strcmp(pChar,"")!=0){
		speakText(pChar);

	}else{
		
	
		//if(currentDict=="vietanh"){
		//	CHAR thut[256];
		//	strcpy(thut,convert1(myword));
		//	VietTTS(thut);
		//}else{
			speakText(myword);
		//}
			
	}

	


	
}
void CMultiClickDlg::OpenInfoKey()
{
	/*
		TCHAR path[MAX_PATH];
		GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		

		TCHAR *p = _tcsrchr(path, _TEXT('\\'));
		_tcscpy(p+1, _TEXT("MyKey.exe"));
		ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);
		*/
}

void CMultiClickDlg::OnDictionaryonline()
{
		TCHAR path[MAX_PATH];
		GetModuleFileName(NULL, path, sizeof(path)/sizeof(TCHAR));
		

		TCHAR *p = _tcsrchr(path, _TEXT('\\'));
		_tcscpy(p+1, _TEXT("AllOnlineDict.exe"));
		ShellExecute(NULL, _T("open"),path, NULL, NULL, SW_SHOWNORMAL);
}

void CMultiClickDlg::OnLookuponline()
{
	if(regedit.onlineLookup){
		regedit.onlineLookup=0;
		Stray.CheckItem(ID_LOOKUPONLINE,FALSE);
	}else{
		regedit.onlineLookup=1;
		Stray.CheckItem(ID_LOOKUPONLINE,TRUE);
	}
}

void CMultiClickDlg::OnBnClickedKeepit()
{
	if(keepdialog==false) keepdialog=true;
	else keepdialog=false;
	
}

void CMultiClickDlg::InitHash(){
	if(regedit.kindDictionary==0){
		m_database.InitHashEV();
	}
	else if(regedit.kindDictionary==1){
		m_database.InitHashFV();
	}
	else if(regedit.kindDictionary==2){
		m_database.InitHashDV();
	}
	else if(regedit.kindDictionary==3){
		m_database.InitHashVV();
	}
	else if(regedit.kindDictionary==4){
		m_database.InitHashNV();
	}
	else if(regedit.kindDictionary==4){
		m_database.InitHashNauyV();
	}
}

void CMultiClickDlg::SetText_CurrentDictBtn(){
	wchar_t unicode_string[256];
	
	if(currentDict=="anhviet"){
		Utf8_Unicode((BYTE*)"Tự điển Anh Việt",unicode_string);
		m_currentdict.SetWindowText(unicode_string);
		
	}
	else if(currentDict=="vietanh"){
		m_currentdict.SetWindowText(_T("English Vietnamese Dictionary"));
	}
	else if(currentDict=="phapviet"){
		Utf8_Unicode((BYTE*)"Tự điển Pháp Việt",unicode_string);
		m_currentdict.SetWindowText(unicode_string);
	}
	else if(currentDict=="vietphap"){
		m_currentdict.SetWindowText(_T("French-Vietnamese Dictionaire"));
	}
	else if(currentDict=="ducviet"){
		Utf8_Unicode((BYTE*)"Tự điển Đức Việt",unicode_string);
		m_currentdict.SetWindowText(unicode_string);
	}
	else if(currentDict=="vietduc"){
		m_currentdict.SetWindowText(_T("German-Vietnamese Lexikon"));
	}
	else if(currentDict=="ngaviet"){
		Utf8_Unicode((BYTE*)"Tự điển Nga Việt",unicode_string);
		m_currentdict.SetWindowText(unicode_string);
	}
	else if(currentDict=="nauyviet"){
		Utf8_Unicode((BYTE*)"Tự điển Nauy Việt",unicode_string);
		m_currentdict.SetWindowText(unicode_string);
	}
		
	else if(currentDict=="vietviet"){
		 Utf8_Unicode((BYTE*)"Tự điển Việt Việt",unicode_string);
		m_currentdict.SetWindowText(unicode_string);
	}
}
