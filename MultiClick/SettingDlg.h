#ifndef _CSETTING_DLG_H
#define _CSETTING_DLG_H

#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CSettingDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CSettingDlg)


public:
	CSettingDlg();
	~CSettingDlg();

// Dialog
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_CONFIGDLG };
		
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	//}}AFX_VIRTUAL

// Implement
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CSettingDlg)
		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	afx_msg void InitData();
	afx_msg void AutoStart();
	afx_msg void Ctrl();
	afx_msg void Shift();
	afx_msg void NoKeyboard();

	afx_msg void OnCbnSelchangeGuilanguage();
};


#endif 
