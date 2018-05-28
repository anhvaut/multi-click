#ifndef _READ_DLG_H
#define _READ_DLG_H

#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CReadDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CReadDlg)


public:
	CReadDlg();
	~CReadDlg();

// Dialog
	//{{AFX_DATA(CReadDlg)
	enum { IDD = IDD_READ };
		
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CReadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	//}}AFX_VIRTUAL

// Implement
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CReadDlg)
		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


#endif 
