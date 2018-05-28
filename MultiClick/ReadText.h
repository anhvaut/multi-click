// DictionaryDlg.h : header file
//
#include <richedit.h>
#include <richole.h>
#include "resource.h"
#include "CustomStatic.h"
#include "BgDialog.h"
#include "CustomBtn.h"
#include <sapi.h>
#define MAX_FILE_PATH			256
#define NORM_SIZE               256
#define MAX_SIZE                102400
#define WM_TTSAPPCUSTOMEVENT       WM_APP 

#pragma once

// CAuthorDlg dialog
class CReadTextDlg : public CBgDialog
{
// Construction
public:
	CReadTextDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_READTEXT};
	
	

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();	


	
private:
	CComPtr<ISpVoice>   m_cpVoice;
    CComPtr<ISpAudio>   m_cpOutAudio;
    BOOL                m_bPause;
    BOOL                m_bStop;
    USHORT              m_DefaultVolume;
    long                m_DefaultRate;
    int                 m_DefaultFormatIndex;
    WCHAR*              m_pszwFileText;
    WCHAR               m_szWFileName[MAX_FILE_PATH];

	CustomStatic			m_static1;
	CustomStatic			m_static2;
	CustomStatic			m_static3;
	CustomStatic			m_static4;
	CustomStatic			m_static5;
	CustomStatic			m_static6;
	

	CustomBtn				m_btn1;
	CustomBtn				m_btn2;
	CustomBtn				m_btn3;
	CustomBtn				m_btn4;
	CEdit					m_text;
	DECLARE_MESSAGE_MAP()

public:
	BOOL CallOpenFileDialog( TCHAR* szFileName, TCHAR* szFilter );  
	HRESULT ReadTheFile( TCHAR* szFileName, BOOL* bIsUnicode, WCHAR** ppszwBuff );
	HRESULT     InitSapi();
    void        Stop();
	HRESULT     VoiceChange();

	
	afx_msg void OnCbnSelchangeComboVoices();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);

	LRESULT  MainHandleSynthEvent(WPARAM wParam,LPARAM lParam);
	
	afx_msg void OnBnClickedMofile();
	afx_msg void OnBnClickedDocvb();
	afx_msg void OnBnClickedNgung();
	afx_msg void OnBnClickedDung();
};


