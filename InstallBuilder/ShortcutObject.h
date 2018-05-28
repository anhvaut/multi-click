#if !defined(AFX_SHORTCUTOBJECT_H__F6CFC0EC_EBA5_4134_9566_6CA014330B6C__INCLUDED_)
#define AFX_SHORTCUTOBJECT_H__F6CFC0EC_EBA5_4134_9566_6CA014330B6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShortcutObject : public CObject
{
	DECLARE_SERIAL(CShortcutObject)

// Attributes
public:
	CShortcutObject();           // protected constructor used by dynamic creation
	virtual ~CShortcutObject();

// Operations
public:
	CString m_strName;
	CString m_strTarget;
	CString m_strOriginalPath;
	CString m_strCmdLine;
	CString m_strWorkingDir;
	CString m_strIconPath;
	int m_nIconIndex;
	
	virtual void Serialize(CArchive&);
	CShortcutObject (const CShortcutObject &shortcutObject);			// copy-constructor
	CShortcutObject &operator=(const CShortcutObject &shortcutObject);	// =-operator

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutObject)
	//}}AFX_VIRTUAL

// Implementation
protected:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTOBJECT_H__F6CFC0EC_EBA5_4134_9566_6CA014330B6C__INCLUDED_)
