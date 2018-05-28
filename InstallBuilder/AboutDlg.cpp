/****************************************************************/
/*																*/
/*  AboutDlg.cpp												*/
/*																*/
/*  Implementation of the CAboutDlg class.						*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 15 may 2002									*/
/*																*/
/****************************************************************/


#include "stdafx.h"
#include "resource.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAboutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAboutDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_STATIC_MAIL, m_MailLink);
	DDX_Control(pDX, IDC_STATIC_LINK, m_HomePageLink);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : OnInitDialog										*/
/* Description   : Initialize dialog.								*/
/*																	*/
/********************************************************************/
BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_MailLink.SetURL("mailto:info@pablovandermeer.nl");
	m_HomePageLink.SetURL("http://www.pablovandermeer.nl");

    CString strExeName = AfxGetApp()->m_pszExeName;
    strExeName += ".exe";

	UpdateVersionInformation(strExeName);
	return TRUE; 
}


/********************************************************************/
/*																	*/
/* Function name : UpdateVersionInformation							*/
/* Description   : Show version information from resource.			*/
/*																	*/
/********************************************************************/
void CAboutDlg::UpdateVersionInformation(LPCTSTR lpszModuleName)
{
	BYTE		*pDataBlock = NULL;
	DWORD FAR	*translation;
	DWORD FAR	*buffer;     
	DWORD		dwHandle;
	UINT		nBytes;
	
	// WinAPI wants non-const arguments
	LPTSTR lpszExeName = const_cast<LPTSTR>(lpszModuleName); 

	char szName[512];       // StringFileInfo data block.
	char szData[256];

	// Get the actual size of the information block.
	nBytes = (UINT)GetFileVersionInfoSize(lpszExeName, &dwHandle);

	if (nBytes)
	{
		pDataBlock = new BYTE[nBytes];

		// Get the actual block for the version information
		if (GetFileVersionInfo(lpszExeName, dwHandle, nBytes, pDataBlock))
		{
			if (VerQueryValue(pDataBlock, "\\VarFileInfo\\Translation", (VOID FAR * FAR *)&translation, (UINT FAR *)&nBytes)) 
			{
				// The File Version for this application
				wsprintf(szName, "\\StringFileInfo\\%04x%04x\\PrivateBuild", LOWORD(*translation), HIWORD(*translation));

				if (VerQueryValue(pDataBlock, szName, (VOID FAR * FAR *)&buffer, (UINT FAR *)&nBytes)) 
				{
					lstrcpy(szData, (char far *)buffer);
					GetDlgItem(IDC_FILE_VERSION)->SetWindowText(szData);
				}
			}
			else 
			{
				// sorry ...
			}
		}
		if (pDataBlock)
			delete[] pDataBlock;
	}
}