// LibSplitterWnd.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CLibSplitterWnd

IMPLEMENT_DYNCREATE(CLibSplitterWnd, CSplitterWnd)

CLibSplitterWnd::CLibSplitterWnd()
{
}

CLibSplitterWnd::~CLibSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CLibSplitterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CLibSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CLibSplitterWnd message handlers

BOOL CLibSplitterWnd::CreateLibraryPane(CWnd* pParent, CCreateContext* pContext,DWORD dwStyle,UINT nID)
{
	CRect rect;
	pParent->GetClientRect(&rect);
	if (!CreateStatic(pParent, 1, 2))				
		return FALSE;														
																			
	if (!CreateView(0, 1, RUNTIME_CLASS(CLibFormView), CSize(0,0), pContext))				
		return FALSE;														

	SetColumnInfo(1, 285, 50);
	SetColumnInfo(0,rect.Width()-285,50);
	return TRUE;
}

void CLibSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
    //Lock Splitter
	CWnd::OnLButtonDown(nFlags, point);
}

void CLibSplitterWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
    //Lock Splitter
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CLibSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
