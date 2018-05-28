#ifndef _AUTOUPDATEDLG_H
#define _AUTOUPDATEDLG_H

#include "resource.h"
#include "CustomStatic.h"
#include "BgDialog.h"
#include "CustomBtn.h"



#pragma once


// CAutoUpdateDlgdialog
class CAutoUpdateDlg: public CBgDialog
{
// Construction
public:
	CAutoUpdateDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AUTOUPDATE_VERSION };
	
	
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
	CustomStatic			m_static11;
	CustomStatic			m_static12;
	
	CustomBtn				m_autoupdatebtn;
	

	
	DECLARE_MESSAGE_MAP()

	
};

#endif
