// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9F29999B_CE29_462A_B749_29E3B1C6C165__INCLUDED_)
#define AFX_STDAFX_H__9F29999B_CE29_462A_B749_29E3B1C6C165__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <shlobj.h>
#include "shfolder.h"

CString BrowseForFolder(HWND hWnd, LPCSTR lpszTitle, UINT nFlags);
BOOL GetStartMenuFolder(CString &strFolder);
BOOL CreateDirectories(LPCTSTR lpszDirectory);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9F29999B_CE29_462A_B749_29E3B1C6C165__INCLUDED_)
