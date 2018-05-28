#ifndef _DICTIONARY_DLG_H
#define _DICTIONARY_DLG_H

#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




class CDictionaryDlg : public CPropertyPage
{
	DECLARE_DYNCREATE(CDictionaryDlg)


public:
	CDictionaryDlg();
	~CDictionaryDlg();

// Dialog
	//{{AFX_DATA(CDictionaryDlg)
	enum { IDD = IDD_DICTIONARYDLG};
		
	//}}AFX_DATA



	//{{AFX_VIRTUAL(CDictionaryDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	//}}AFX_VIRTUAL

// Implement
protected:
	virtual BOOL OnInitDialog();
	//{{AFX_MSG(CDictionaryDlg)
		
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


#endif 
