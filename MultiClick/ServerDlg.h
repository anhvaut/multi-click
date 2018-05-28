#ifndef _SERVER_DLG_H
#define _SERVER_DLG_H

#include "resource.h"
#include "CustomBtn.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CServerDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CServerDlg)


public:
	CServerDlg();
	~CServerDlg();

// Dialog
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER};
		
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	//}}AFX_VIRTUAL

public :
	void InitData();

private:
	CustomBtn m_connectbtn;
// Implement
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CServerDlg)
		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCheckNewVersion();
};


#endif 
