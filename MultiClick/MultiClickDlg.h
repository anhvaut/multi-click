// MultiClickDlg.h : header file
//
//{{AFX_INCLUDES()
#include "Polygon.h"
#include "webbrowser2.h"
#include "CustomBtn.h"
//}}AFX_INCLUDES

#if !defined(AFX_MultiClickDLG_H__3916B450_FB76_11D4_868C_00E02930B0CE__INCLUDED_)
#define AFX_MultiClickDLG_H__3916B450_FB76_11D4_868C_00E02930B0CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MOUSE_PROC 8	
#define BUFFER_COUNT 256
#define TAB_BORDER_LEFT    0
#define TAB_BORDER_RIGHT   1
#define TAB_BORDER_TOP     2
#define TAB_BORDER_BOTTOM  3

typedef void (*SETHHOOK) (HWND,HHOOK);
typedef CHAR * (CALLBACK *GETSTR) () ;
typedef WCHAR * (CALLBACK *GETSTRW) () ;
typedef void (*SetLMode)(int);
typedef void (*SetTextMode)(int);
typedef void (*SetBuildCode)(int,int,int);
typedef void (*SwitchLanguage)(int);

typedef int (WINAPI VietTTSFuntion)(LPSTR str);


/////////////////////////////////////////////////////////////////////////////
// CMultiClickDlg dialog

class CMultiClickDlg : public CNewDialog
{

	//datas for Hook 
	HINSTANCE hHookDLL;
	HHOOK hKeyHook;
	HHOOK hMouseHook;
	//func. addresses in Dll
	SETHHOOK pSetHHook;
	GETSTR pGetStr;
	GETSTRW pGetStrW;
	SetLMode pSetLookMode;
	SetTextMode pSetTextMode;
	SetBuildCode pBuildCode;
	SwitchLanguage pSwitchLanguage;

	//for Speech
	HINSTANCE hSpeechDll;
	VietTTSFuntion *VietTTS;

	CHAR pChar[BUFFER_COUNT+1];
	WCHAR pCharW[BUFFER_COUNT+1];
	wchar_t *myword;

	void InitHash();
	void SetText_CurrentDictBtn();


// Construction
public:
	CMultiClickDlg(CWnd* pParent = NULL);	// standard constructor
	LRESULT OnTrayNotification(WPARAM wParam,LPARAM lParam);

// Dialog Data
	//{{AFX_DATA(CMultiClickDlg)
	enum { IDD = IDD_MULTICLICK_DIALOG };
	CWebBrowser2	m_wndBrowser;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMultiClickDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

//private members
private :	

	CPolygon m_polygon;		// polygon used to draw the Tab borders
	CRgn m_Rgn;				// region  used to draw the Window
	CRgn m_testRgn;			// region  used for hitTest
	int m_nInitialWidth;	// initial window Width
	int m_nInitialHeight;	// initial window Height	

	BOOL m_bMoving;			// moving state of the window
	int m_dx;				// delta between Window left border and mouse x position
	int m_dy;				// delta between Window top border and mouse y position

	int m_bHiddenStatus;	// Current Hidden status of the Window
	int m_nXControlsMoved;	// old x translation of the controls
	int m_nYControlsMoved;	// old y translation of the controls
	int m_nXIcon;			// x Icon Position
	int m_nYIcon;			// y Icon Position
	int m_nXDC;				// x Title Position
	int m_nYDC;				// y Title Position
	CRect m_DCRect;			// x Title Rectangle
	CRect m_closeRect;		// closeBox Rectangle

	int m_nTabRound;		// round tab value

	CDC m_pDC;				// CDC used to draw the text in memory 
	CBitmap m_bitmap;		// Bitmap used to draw the text in memory 
	
// private functions
	void CreateTabPolygon();

	void OnAutoHide();

	void OnTopMost();

	void HideTabWindow();
	void ShowTabWindow();
	void MoveDialogControls(int nX,int nY);

	void PositionWindowOnBorder( CPoint point);
	void moveWindow(CPoint point);
	void ComputeTabSize();

	
// public members
public  :
	int m_nBorderPos;	// position of the Window on the Desktop border
	int m_nXpos;		// X position of the Window on the Desktop border
	int m_nYpos;		// Y position of the Window on the Desktop border
	int m_nTabHeight;	// Default tab height
	int m_nTabWidth;	// Default tab width

	HICON m_hTitleIcon; // Icon used on the Tab
	BOOL m_bAutoTabSize;// True if the tab is autoSized
	CString m_sTitle;	// Title String 
	BOOL m_bCloseBox;	// True if we want a close box

	BOOL m_bTopMost;		// True if Window needs to be topMost
	BOOL m_bAutoHide;		// True if Window autoHides when the mouse leave it


	void reDrawTitle(CDC* pDC,CString newTitle);
	


// Implementation
protected:
	HICON m_hIcon;
	void ReSize();

	// Generated message map functions
	//{{AFX_MSG(CMultiClickDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPrintpreview();
	afx_msg void OnPagesetup();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL CMultiClickDlg::OnEraseBkgnd(CDC *pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnMouseProc(WPARAM, LPARAM) ;
	//}}AFX_MSG
private:
	CustomBtn m_soundbtn;
	CustomBtn m_keepit;
	CustomBtn m_currentdict;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSound();
			
	afx_msg	void OnEndKey();
	afx_msg	void OnShowConfig();
	afx_msg	void SetTopMost(BOOL bTopMost);
	afx_msg	void SetAutoHide(BOOL bAutoHide);
	afx_msg	void CheckAutoLookOn();
	afx_msg	void chooseModeLook1();
	afx_msg	void chooseModeLook2();
	afx_msg	void chooseModeLook3();
	afx_msg	void InitSetting();
	afx_msg	void SetRegeditVal();
	afx_msg	void openHelp();
			//===inputmethod
	afx_msg	void telexTyping();
	afx_msg	void vniTyping();
			//===charset
	afx_msg	void checkCharset(UINT item);
	afx_msg	void tcvn3Charset();
	afx_msg	void unicodeCharset();
	afx_msg	void vniCharset();
	afx_msg	void viqrCharset();
	afx_msg	void vietwarexCharset();
	afx_msg	void vietwarefCharset();
	afx_msg	void hcm1Charset();
	afx_msg	void hcm2Charset();
	afx_msg	void vpsCharset();
	afx_msg	void visciiCharset();
	
			//===============
	afx_msg	void OpenDictionary();
	afx_msg	void OpenEVDictionary();
	afx_msg	void OpenFVDictionary();
	afx_msg	void OpenGVDictionary();
	afx_msg	void OpenNNVDictionary();
	afx_msg	void OpenInfoKey();
	afx_msg	void chooseEnglish();
	afx_msg	void chooseFrance();
	afx_msg	void chooseGermany();
	afx_msg	void chooseVietnamese();
	afx_msg	void chooseRussia();
	afx_msg	void chooseNauy();



			
			//===============
	afx_msg	void OnDialogConf();
	afx_msg void OnDictionaryonline();
	afx_msg void OnLookuponline();
	afx_msg void OnBnClickedKeepit();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MultiClickDLG_H__3916B450_FB76_11D4_868C_00E02930B0CE__INCLUDED_)
