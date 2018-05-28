// DictionaryDlg.h : header file
//
#include "resource.h"
#include "CustomStatic.h"
#include "BgDialog.h"
#include "CustomBtn.h"



#pragma once


// CAboutDlg dialog
class CAboutDlg : public CBgDialog
{
// Construction
public:
	CAboutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ABOUT };

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

	

	afx_msg void OnOK();
private:
	CustomStatic			m_static3;
	//CustomBtn				m_btn;
	DECLARE_MESSAGE_MAP()

};
