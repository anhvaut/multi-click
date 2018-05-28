/****************************************************************/
/*																*/
/*  InstallBuilderDoc.cpp										*/
/*																*/
/*  Implementation of the CInstallBuilderDoc class.				*/
/*	This file is part of the Install Builder application.		*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 14 june 2002									*/
/*																*/
/****************************************************************/


#include "stdafx.h"
#include "InstallBuilder.h"

#include "InstallBuilderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CInstallBuilderDoc, CDocument)

BEGIN_MESSAGE_MAP(CInstallBuilderDoc, CDocument)
	//{{AFX_MSG_MAP(CInstallBuilderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CInstallBuilderDoc::CInstallBuilderDoc()
{
}

CInstallBuilderDoc::~CInstallBuilderDoc()
{
}


/********************************************************************/
/*																	*/
/* Function name : SerializeElements								*/
/* Description   : Needed to serialize CShortcutObject objects		*/
/*																	*/
/********************************************************************/
template <> void AFXAPI SerializeElements <CShortcutObject> (CArchive& ar, CShortcutObject* pNewObjects, int nCount)
{
    for (int i = 0; i < nCount; i++, pNewObjects++)
    {
        // Serialize each CShortcutObject object
        pNewObjects->Serialize(ar);
    }
}


/********************************************************************/
/*																	*/
/* Function name : Serialize										*/
/* Description   : Store/Load document data							*/
/*																	*/
/********************************************************************/
void CInstallBuilderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strCompanyName;
		ar << m_strProductName;
		ar << m_strProductURL;
		ar << m_strProductVersion;
		ar << m_strCopyrightNotice;
		ar << m_strProductDescription;
		ar << m_strOutputFolder;
		ar << m_strSetupFileName;
		ar << m_strApplicationName;
		ar << m_bShowRunCheckbox;

		AfxGetApp()->WriteProfileString("Settings", "CompanyName", m_strCompanyName);
		AfxGetApp()->WriteProfileString("Settings", "ProductURL", m_strProductURL);
		AfxGetApp()->WriteProfileString("Settings", "CopyrightNotice", m_strCopyrightNotice);
		AfxGetApp()->WriteProfileString("Settings", "OutputFolder", m_strOutputFolder);
		AfxGetApp()->WriteProfileString("Settings", "SetupFileName", m_strSetupFileName);
	}
	else
	{
		ar >> m_strCompanyName;
		ar >> m_strProductName;
		ar >> m_strProductURL;
		ar >> m_strProductVersion;
		ar >> m_strCopyrightNotice;
		ar >> m_strProductDescription;
		ar >> m_strOutputFolder;
		ar >> m_strSetupFileName;
		ar >> m_strApplicationName;
		ar >> m_bShowRunCheckbox;
	}
	m_strFiles.Serialize(ar);
	// serialize files
	m_ShortcutObjects.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CInstallBuilderDoc diagnostics

#ifdef _DEBUG
void CInstallBuilderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInstallBuilderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


/********************************************************************/
/*																	*/
/* Function name : DeleteContents									*/
/* Description   : Ensure that doc is empty before it is reused.	*/
/*																	*/
/********************************************************************/
void CInstallBuilderDoc::DeleteContents() 
{
	m_strCompanyName = AfxGetApp()->GetProfileString("Settings", "CompanyName", "My Company");
	m_strProductName = "My Application";
	m_strProductURL = AfxGetApp()->GetProfileString("Settings", "ProductURL", "www.pablovandermeer.nl");
	m_strProductVersion = "1.0";
	m_strCopyrightNotice = AfxGetApp()->GetProfileString("Settings", "CopyrightNotice", "Copyright (c) 2002");
	m_strProductDescription = "My Application Description";
	m_strOutputFolder = AfxGetApp()->GetProfileString("Settings", "OutputFolder", "c:\\SetupProjects");
	m_strSetupFileName = AfxGetApp()->GetProfileString("Settings", "SetupFileName", "setup.exe");
	m_strApplicationName = "";
	m_bShowRunCheckbox = FALSE;

	m_strFiles.RemoveAll();
	m_ShortcutObjects.RemoveAll();

	CDocument::DeleteContents();
}
