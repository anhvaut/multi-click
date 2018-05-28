#ifndef _AUTHOR_DLG_H
#define _AUTHOR_DLG_H

#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CAuthorDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CAuthorDlg)


public:
	CAuthorDlg();
	~CAuthorDlg();

// Dialog
	//{{AFX_DATA(CAuthorDlg)
	enum { IDD = IDD_AUTHOR };
		
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CAuthorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	//}}AFX_VIRTUAL

// Implement
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CAuthorDlg)
		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


#endif 
