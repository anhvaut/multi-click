#include "stdafx.h"
#include "ReadText.h"
#include ".\readtext.h"
#include "resource.h"
//#include "speak.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif	

// ITextDocument interface guid

BOOL                bFileOpened = FALSE;
UINT                cNumChar = 0;
HRESULT             hr = S_OK;
TCHAR               szAFileName[NORM_SIZE] = _T("");
static BOOL			bIsUnicode = FALSE;
//BOOL                bWavFileOpened = FALSE;
int                 iFormat;
//CComPtr<ISpStream>  cpWavStream;
//CComPtr<ISpStreamFormat>    cpOldStream;
HWND                hwndEdit;


    

CReadTextDlg ::CReadTextDlg (CWnd* pParent /*=NULL*/)
	: CBgDialog(CReadTextDlg ::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	   m_bPause                = FALSE; // pause audio?
       m_bStop                 = TRUE;  // stop audio?
       m_DefaultVolume         = 0;     // default volume
       m_DefaultRate           = 0;     // default rate
       m_DefaultFormatIndex    = 0;     // default output format
       m_pszwFileText          = NULL;  // text from file
       m_szWFileName[0]        = NULL;  // wid
}

void CReadTextDlg ::DoDataExchange(CDataExchange* pDX)
{
	CBgDialog::DoDataExchange(pDX);
		
		
		DDX_Control(pDX, IDC_STATIC1, m_static1);
		DDX_Control(pDX, IDC_STATIC2, m_static2);
		DDX_Control(pDX, IDC_STATIC3, m_static3);
		DDX_Control(pDX, IDC_STATIC4, m_static4);
	
		
		DDX_Control(pDX, IDC_MOFILE, m_btn1);
		DDX_Control(pDX, IDC_DOCVB, m_btn2);
		DDX_Control(pDX, IDC_NGUNG, m_btn3);
		DDX_Control(pDX, IDC_DUNG, m_btn4);
		DDX_Control(pDX, IDC_TEXTBOX, m_text);
}

BEGIN_MESSAGE_MAP(CReadTextDlg , CBgDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//}}AFX_MSG_MAP
	
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeComboVoices)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnNMCustomdrawSlider2)

	ON_MESSAGE(WM_TTSAPPCUSTOMEVENT,MainHandleSynthEvent)
	
	ON_BN_CLICKED(IDC_MOFILE, OnBnClickedMofile)
	ON_BN_CLICKED(IDC_DOCVB, OnBnClickedDocvb)
	ON_BN_CLICKED(IDC_NGUNG, OnBnClickedNgung)
	ON_BN_CLICKED(IDC_DUNG, OnBnClickedDung)
END_MESSAGE_MAP()



BOOL CReadTextDlg ::OnInitDialog()
{
	
	CBgDialog::OnInitDialog();
	SetBitmap(IDB_BACKGROUND);
	ActivateEasyMoveMode(TRUE);
	
	m_static1.DrawTransparent();
	m_static2.DrawTransparent();
	m_static3.DrawTransparent();
	m_static4.DrawTransparent();
	
	
	m_btn1.DrawTransparent();
	m_btn1.SetFlat(false);
	
	m_btn2.DrawTransparent();
	m_btn2.SetFlat(false);
	m_btn3.DrawTransparent();
	m_btn3.SetFlat(false);
	m_btn4.DrawTransparent();
	m_btn4.SetFlat(false);
	
	///////////// khoi dong toc do
	SendDlgItemMessage( IDC_SLIDER1, TBM_SETRANGE, TRUE, MAKELONG( SPMIN_RATE, SPMAX_RATE ) );
    SendDlgItemMessage( IDC_SLIDER1, TBM_SETPOS, TRUE, 3 );
    SendDlgItemMessage(IDC_SLIDER1, TBM_SETPAGESIZE, TRUE, 5 );
	//////////////////
    ////////////volume
	    SendDlgItemMessage( IDC_SLIDER2, TBM_SETRANGE, TRUE, MAKELONG( SPMIN_VOLUME, SPMAX_VOLUME ) );
	    SendDlgItemMessage(  IDC_SLIDER2, TBM_SETPOS, TRUE, 10 );
	    SendDlgItemMessage(  IDC_SLIDER2, TBM_SETPAGESIZE, TRUE, 10 );
	
	//tao am thanh khi dua chuot qua nut
//#ifdef	BTNST_USE_SOUND
	//m_btn.SetSound(MAKEINTRESOURCE(IDR_HOVER), ::GetModuleHandle(NULL));
//#endif

	////set window at center
	POINT point;
	::GetCursorPos(&point);	
	RECT    rc;


    GetWindowRect(&rc);

    int     nWidth, nHeight;
        
    nWidth = rc.right - rc.left;//do rong cua dialog
    nHeight = rc.bottom - rc.top;//chieu cao cua dialog
        
    int     cxScreen, cyScreen;
        
    cxScreen = GetSystemMetrics(SM_CXSCREEN);//be rong cua man hinh
    cyScreen = GetSystemMetrics(SM_CYSCREEN);//chieu cao cua man hinh

	int Vt_x,Vt_y;

	if(point.x>cxScreen/2){
		Vt_x=point.x-nWidth;
	}
	else{
		Vt_x=point.x;
	}
	if(point.y>cyScreen/2){
		Vt_y=point.y-nHeight;
	}else{
		Vt_y=point.y;
	}
	SetWindowPos(NULL,Vt_x,Vt_y, NULL, NULL, SWP_NOSIZE |  SWP_NOZORDER |SWP_SHOWWINDOW);
	

	/*
	* Khoi tao giong noi cho combobox
	*/
	SpInitTokenComboBox( GetDlgItem(IDC_COMBO1 )->m_hWnd , SPCAT_VOICES );
	 
	/*
	* Khoi dong ham Doc Giong Noi
	*/
	InitSapi();

	m_cpVoice->SetNotifyWindowMessage( m_hWnd, WM_TTSAPPCUSTOMEVENT, 0, 0 );
	
     m_cpVoice->SetInterest( SPFEI_ALL_TTS_EVENTS, SPFEI_ALL_TTS_EVENTS );
    
	 HGLOBAL hGlobalText;
		

   if(IsClipboardFormatAvailable(CF_UNICODETEXT)){
			if(OpenClipboard()){				
				hGlobalText = GetClipboardData(CF_UNICODETEXT);			
				if (hGlobalText != NULL) { 		
					  LPCWSTR myTextUU;
						myTextUU =(LPCWSTR)GlobalLock(hGlobalText); 
						//myword=(wchar_t *)GlobalLock(hGlobalText); 
						if (myTextUU != NULL){ 
						SetDlgItemText(IDC_TEXTBOX,myTextUU);
							//MessageBox(myTextUU);
							   		
							GlobalUnlock(hGlobalText);	
							::CloseClipboard();
						} 
					} 
				}
		}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CReadTextDlg ::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CBgDialog::OnSysCommand(nID, lParam);
		Stop();
	}
}


void CReadTextDlg ::OnPaint() 
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


HCURSOR CReadTextDlg ::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CReadTextDlg::CallOpenFileDialog( TCHAR* szFileName, TCHAR* szFilter )  
{
    OPENFILENAME    ofn;
    BOOL            bRetVal     = TRUE;
    LONG            lRetVal;
    HKEY            hkResult;
    TCHAR           szPath[256]       = _T("");
    DWORD           size = 256;

    // Open the last directory used by this app (stored in registry)
    lRetVal = RegCreateKeyEx( HKEY_CURRENT_USER, 
                        _T("SOFTWARE\\Bluerain\\MultiClick"), 0, NULL, 0,
                        KEY_ALL_ACCESS, NULL, &hkResult, NULL );

    if( lRetVal == ERROR_SUCCESS )
    {
        RegQueryValueEx( hkResult, _T("TTSFiles"), NULL, NULL, (PBYTE)szPath, &size );
    }

	size_t ofnsize = (BYTE*)&ofn.lpTemplateName + sizeof(ofn.lpTemplateName) - (BYTE*)&ofn;
    ZeroMemory( &ofn, ofnsize);


    ofn.lStructSize       = ofnsize;
    ofn.hwndOwner         = m_hWnd;    
    ofn.lpstrFilter       = szFilter;
    ofn.lpstrCustomFilter = NULL;    
    ofn.nFilterIndex      = 1;    
    ofn.lpstrInitialDir   = szPath;
    ofn.lpstrFile         = szFileName;  
    ofn.nMaxFile          = 256;
    ofn.lpstrTitle        = NULL;
    ofn.lpstrFileTitle    = NULL;    
    ofn.lpstrDefExt       = NULL;
    ofn.Flags             = OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;

    // Pop the dialog
    bRetVal = GetOpenFileName( &ofn );

    // Write the directory path you're in to the registry
    TCHAR   pathstr[256] = _T("");
    _tcscpy( pathstr, szFileName );

    int i=0; 
    while( pathstr[i] != NULL )
    {
        i++;
    }
    while( pathstr[i] != '\\' )
    {
        i --;
    }
    pathstr[i] = NULL;

    // Now write the string to the registry
    RegSetValueEx( hkResult, _T("TTSFiles"), NULL, REG_EXPAND_SZ, (PBYTE)pathstr, _tcslen(pathstr)+1 );

    RegCloseKey( hkResult );

    return bRetVal;
}
HRESULT CReadTextDlg::ReadTheFile( TCHAR* szFileName, BOOL* bIsUnicode, WCHAR** ppszwBuff )
/////////////////////////////////////////////////////
//
// This file opens and reads the contents of a file. It
// returns a pointer to the string.
// Warning, this function allocates memory for the string on 
// the heap so the caller must free it with 'delete'.
//
{
    // Open up the file and copy it's contents into a buffer to return
	HRESULT		hr = 0;
	
    HANDLE		hFile;
	DWORD		dwSize = 0;
	DWORD		dwBytesRead = 0;
		
    hFile = CreateFile( szFileName, GENERIC_READ,
        FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY, NULL );
    if( hFile == INVALID_HANDLE_VALUE )
    {
		*ppszwBuff = NULL;
		hr = E_FAIL;
    }

	if( SUCCEEDED( hr ) )
	{
		dwSize = GetFileSize( hFile, NULL );
		if( dwSize == 0xffffffff )
		{
			*ppszwBuff = NULL;
			hr = E_FAIL;        
		}
	}
 
	if( SUCCEEDED( hr ) )
	{
		// Read the file contents into a wide buffer and then determine
		// if it's a unicode or ascii file
		WCHAR	Signature = 0;

		ReadFile( hFile, &Signature, 2, &dwBytesRead, NULL );
			
		// Check to see if its a unicode file by looking at the signature of the first character.
		if( 0xFEFF == Signature )
		{
			*ppszwBuff = new WCHAR [dwSize/2];

			*bIsUnicode = TRUE;
			ReadFile( hFile, *ppszwBuff, dwSize-2, &dwBytesRead, NULL );
			(*ppszwBuff)[dwSize/2-1] = NULL;

			CloseHandle( hFile );
		}			
		else  // MBCS source
		{
			char*	pszABuff = new char [dwSize+1];
			*ppszwBuff = new WCHAR [dwSize+1];

			*bIsUnicode = FALSE;
			SetFilePointer( hFile, NULL, NULL, FILE_BEGIN );
			ReadFile( hFile, pszABuff, dwSize, &dwBytesRead, NULL );
			pszABuff[dwSize] = NULL;
            ::MultiByteToWideChar( CP_ACP, 0, pszABuff, -1, *ppszwBuff, dwSize + 1 );

			delete( pszABuff );
			CloseHandle( hFile );
		}
	}

	return hr;
}


////////////// Danh cho xu li giong noi

HRESULT CReadTextDlg::InitSapi()
/////////////////////////////////////////////////////////////////
{
    HRESULT                 hr;
    
   hr = m_cpVoice.CoCreateInstance( CLSID_SpVoice );

    return hr;
}

void CReadTextDlg::Stop()

{
    // Stop current rendering with a PURGEBEFORESPEAK...
    HRESULT hr = m_cpVoice->Speak( NULL, SPF_PURGEBEFORESPEAK, 0 );

    m_bPause = FALSE;
    m_bStop = TRUE;             

}

/////////////////////////////////////////////////////////////////
HRESULT CReadTextDlg::VoiceChange()
{
    HRESULT         hr = S_OK;
    GUID*           pguidAudioFormat = NULL;
    int             iFormat = 0;

 
    ISpObjectToken* pToken = SpGetCurSelComboBoxToken( GetDlgItem(IDC_COMBO1 )->m_hWnd );
   	
    CComPtr<ISpObjectToken> pOldToken;
    hr = m_cpVoice->GetVoice( &pOldToken );

    if (SUCCEEDED(hr))
    {
        if (pOldToken != pToken)
        {        
            hr = m_cpVoice->Speak( NULL, SPF_PURGEBEFORESPEAK, 0);
            if (SUCCEEDED (hr) )
            {
                hr = m_cpVoice->SetVoice( pToken );
            }
        }
    }


    return hr;
}


void CReadTextDlg::OnCbnSelchangeComboVoices()
{
	VoiceChange();
}

void CReadTextDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int hpos =  GetDlgItem(IDC_SLIDER1)->SendMessage( TBM_GETPOS, 0, 0 );
	m_cpVoice->SetRate((USHORT)hpos);
}

void CReadTextDlg::OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	int hpos =  GetDlgItem(IDC_SLIDER2)->SendMessage( TBM_GETPOS, 0, 0 );
	m_cpVoice->SetVolume((USHORT)hpos+20);
}

LRESULT  CReadTextDlg::MainHandleSynthEvent(WPARAM wParam,LPARAM lParam)

{

    CSpEvent        event;  // helper class in sphelper.h for events that releases any 
                            // allocated memory in it's destructor - SAFER than SPEVENT
    SPVOICESTATUS   Stat;
    WPARAM          nStart;
    LPARAM          nEnd;
    int             i = 0;
    HRESULT 		hr = S_OK;


	
    while( event.GetFrom(m_cpVoice) == S_OK )
    {
        switch( event.eEventId )
        {
		
            case SPEI_END_INPUT_STREAM:
                // Set global boolean stop to TRUE when finished speaking
                m_bStop = TRUE; 
                // Highlight entire text
                nStart = 0;
                nEnd = SendDlgItemMessage(  IDC_TEXTBOX, WM_GETTEXTLENGTH, 0, 0 );
                SendDlgItemMessage(IDC_TEXTBOX, EM_SETSEL, nStart, nEnd );
               
                break;     

            case SPEI_WORD_BOUNDARY:
                hr = m_cpVoice->GetStatus( &Stat, NULL );
                if( FAILED( hr ) )
                {
                	
                }

                // Highlight word
                nStart = (LPARAM)( Stat.ulInputWordPos / sizeof(char) );
                nEnd = nStart + Stat.ulInputWordLen;
                SendDlgItemMessage( IDC_TEXTBOX, EM_SETSEL, nStart, nEnd );
               
                break;
			

            default: break;
        }
    }
	

	return 0L;
}



void CReadTextDlg::OnBnClickedMofile()
{
	bFileOpened = CallOpenFileDialog( szAFileName,
                        _T("TXT (*.txt)\0*.txt\0XML (*.xml)\0*.xml\0All Files (*.*)\0*.*\0") );
            if( bFileOpened )
            {
				DWORD	dwFileSize = 0;
				
                USES_CONVERSION;
                wcscpy( m_szWFileName, T2W( szAFileName ) );
				ReadTheFile( szAFileName, &bIsUnicode, &m_pszwFileText );
				
				if( bIsUnicode )
				{
					MessageBox(_T(""));
				}
				else
				{
										
					// MBCS source
#ifdef _UNICODE
					TCHAR *pszFileText = _tcsdup( m_pszwFileText );
#else
					// We're compiling ANSI, so we need to convert the string to MBCS
					// Note that a W2T may not be good here, since this string might 
					// be very big
                    TCHAR *pszFileText = NULL;
                    int iNeeded = ::WideCharToMultiByte( CP_ACP, 0, m_pszwFileText, -1, NULL, 0, NULL, NULL );
                    pszFileText = (TCHAR *) ::malloc( sizeof( TCHAR ) * ( iNeeded + 1 ) );
                    ::WideCharToMultiByte( CP_ACP, 0, m_pszwFileText, -1, pszFileText, iNeeded + 1, NULL, NULL );
#endif
                    if ( pszFileText )
                    {
					    SetDlgItemText(IDC_TEXTBOX,pszFileText);
						
                        free( pszFileText );
                    }

				}
            }
            else
            {
                wcscpy( m_szWFileName, L"" );
            }
            
            SetFocus();
}

void CReadTextDlg::OnBnClickedDocvb()
{
	CString  t ("");
		m_text.GetWindowText(t);
		HRESULT             hr = S_OK;
		WCHAR               *szWTextString = NULL;

		GetDlgItem( IDC_TEXTBOX )->SetFocus();
		m_bStop = FALSE;
		
		// only get the string if we're not paused
		if( !m_bPause )
		{
			
			// do we speak or interpret the XML
			hr = m_cpVoice->Speak(t, SPF_ASYNC , 0 );

			delete[] szWTextString;

			}
		m_bPause = FALSE;
		GetDlgItem( IDC_TEXTBOX )->SetFocus();
		// Set state to run
		hr = m_cpVoice->Resume();            

	
}

void CReadTextDlg::OnBnClickedNgung()
{
	if( !m_bStop )
            {
                if( !m_bPause )
                {
                   
                    // Pause the voice...
                    m_cpVoice->Pause();
                    m_bPause = TRUE;
                   
                }
               
            }
			
}

void CReadTextDlg::OnBnClickedDung()
{
	Stop();
}

