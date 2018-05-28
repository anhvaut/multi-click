/****************************************************************/
/*																*/
/*  ShortcutObject.cpp											*/
/*																*/
/*  Implementation of the CShortcutObject class.				*/
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
#include "ShortcutObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_SERIAL(CShortcutObject, CObject, 1)

CShortcutObject::CShortcutObject()
{
}

CShortcutObject::~CShortcutObject()
{
}


void CShortcutObject::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_strName;
		ar << m_strTarget;
		ar << m_strCmdLine;
		ar << m_strWorkingDir;
		ar << m_strIconPath;
		ar << m_nIconIndex;	
		ar << m_strOriginalPath;
	}
	else
	{
		ar >> m_strName;
		ar >> m_strTarget;
		ar >> m_strCmdLine;
		ar >> m_strWorkingDir;
		ar >> m_strIconPath;
		ar >> m_nIconIndex;	
		ar >> m_strOriginalPath;
	}
}



/* Copy-constructor */
CShortcutObject::CShortcutObject(const CShortcutObject &shortcutObject)
{
	m_strName = shortcutObject.m_strName;
	m_strTarget = shortcutObject.m_strTarget;
	m_strCmdLine = shortcutObject.m_strCmdLine;
	m_strWorkingDir = shortcutObject.m_strWorkingDir;
	m_strIconPath = shortcutObject.m_strIconPath;
	m_nIconIndex = shortcutObject.m_nIconIndex;	
	m_strOriginalPath = shortcutObject.m_strOriginalPath;
}

/* = operator definition */
CShortcutObject& CShortcutObject::operator=(const CShortcutObject &shortcutObject)
{
	if (&shortcutObject != this)
	{
		m_strName = shortcutObject.m_strName;
		m_strTarget = shortcutObject.m_strTarget;
		m_strCmdLine = shortcutObject.m_strCmdLine;
		m_strWorkingDir = shortcutObject.m_strWorkingDir;
		m_strIconPath = shortcutObject.m_strIconPath;
		m_nIconIndex = shortcutObject.m_nIconIndex;		
		m_strOriginalPath = shortcutObject.m_strOriginalPath;
	}
	return *this;
}
