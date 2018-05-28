/****************************************************************/
/*																*/
/*  ChildView.cpp												*/
/*																*/
/*  Implementation of the CChildView class.						*/
/*	This file is part of the Setup application.					*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 22 July 2002									*/
/*																*/
/****************************************************************/


#include "stdafx.h"
#include "Setup.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : PreCreateWindow									*/
/* Description   : Called by the framework before the creation of	*/
/*                 the Windows window attached to this CWnd object.	*/
/*																	*/
/********************************************************************/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	// Create special font
	LOGFONT lf;			
	::ZeroMemory(&lf, sizeof(lf));

	lf.lfHeight			= 36;
	lf.lfWidth			= 0;
	lf.lfEscapement		= 0;
	lf.lfOrientation	= 0;
	lf.lfWeight			= FW_BOLD;
	lf.lfItalic			= TRUE;
	lf.lfUnderline		= FALSE;
	lf.lfStrikeOut		= FALSE;
	lf.lfCharSet		= DEFAULT_CHARSET;
	lf.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lf.lfQuality		= DEFAULT_QUALITY;
	lf.lfPitchAndFamily	= VARIABLE_PITCH | FF_ROMAN;

	// create font
	m_NormalFont.CreateFontIndirect(&lf);

	lf.lfHeight			= 16;
	lf.lfWeight			= FW_NORMAL;
	lf.lfItalic			= TRUE;

	// create small font
	m_SmallFont.CreateFontIndirect(&lf);
	return TRUE;
}


/********************************************************************/
/*																	*/
/* Function name : OnPaint											*/
/* Description   : Paint gradient background.						*/
/*																	*/
/********************************************************************/
void CChildView::OnPaint() 
{
	CPaintDC dc(this);	// device context for painting
	CDC dcMem;			// memory deice context
	CBitmap bitmap;
	CRect rc, rcLine;
	
	GetClientRect(rc);
	dcMem.CreateCompatibleDC(&dc);
	bitmap.CreateCompatibleBitmap(&dc, rc.Width(), rc.Height());

	// select the bitmap into the meory device context
	CBitmap *pOldBitmap = dcMem.SelectObject(&bitmap);

	// select the font into the memory dc
	CFont *pOldFont = dcMem.SelectObject(&m_NormalFont);

	// very simple routine to create gradient effect
	for (int i=0; i < rc.Height(); i++)
	{
		rcLine.top = i;
		rcLine.bottom = i+1;
		rcLine.left = 0;
		rcLine.right = rc.Width();
		int nBlue = (int)(255 * (float)((float)i/(float)rc.Height()));
		COLORREF clr = RGB(0, 0, 255 - nBlue);
		dcMem.FillSolidRect(rcLine, clr);
	}

	dcMem.SetTextAlign(TA_LEFT | TA_TOP);
	dcMem.SetBkMode(TRANSPARENT);
	dcMem.SetTextColor(RGB(0,0,0));
	dcMem.TextOut(19, 19, ((CSetupApp *)AfxGetApp())->m_strApplicationName);
	dcMem.SetTextColor(RGB(255,255,255));
	dcMem.TextOut(15, 15, ((CSetupApp *)AfxGetApp())->m_strApplicationName);
	
	dcMem.SelectObject(&m_SmallFont);
	dcMem.TextOut(15, rc.Height() - 25, ((CSetupApp *)AfxGetApp())->m_strCopyright);

	// transfer memory dc to display
	dc.BitBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, SRCCOPY);

	// unselect font
	dcMem.SelectObject(pOldFont);
	// unselect bitmap
	dcMem.SelectObject(pOldBitmap);
}


/********************************************************************/
/*																	*/
/* Function name : OnEraseBkgnd										*/
/* Description   : Prevent flicker.									*/
/*																	*/
/********************************************************************/
BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
	// prevent flicker
	return FALSE;//CWnd ::OnEraseBkgnd(pDC);
}


