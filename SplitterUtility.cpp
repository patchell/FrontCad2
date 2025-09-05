// SplitterUtility.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



////////////////////////////////////////////////////
// CSplitterUtility

IMPLEMENT_DYNCREATE(CSplitterUtility, CSplitterWnd)

CSplitterUtility::CSplitterUtility()
{
}

CSplitterUtility::~CSplitterUtility()
{
}


BEGIN_MESSAGE_MAP(CSplitterUtility, CSplitterWnd)
	//{{AFX_MSG_MAP(CSplitterUtility)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CSplitterUtility message handlers

BOOL CSplitterUtility::CreateUtility(CWnd* pParent, CCreateContext* pContext,DWORD dwStyle, UINT nID)
{
	if (!CreateStatic(pParent, 2, 1))				
		return FALSE;														
																			
	if (!CreateView(0, 0, RUNTIME_CLASS(CUtilView), CSize(0,0), pContext))				
		return FALSE;														
																			
	SetColumnInfo(0, 0, 0);				
	SetRowInfo(0, 140, 0);				
																			
       
	return TRUE;
}

void CSplitterUtility::OnLButtonDown(UINT nFlags, CPoint point) 
{
    //Lock Splitter
	CWnd::OnLButtonDown(nFlags, point);
}

void CSplitterUtility::OnMouseMove(UINT nFlags, CPoint point) 
{
    //Lock Splitter
	CWnd::OnMouseMove(nFlags, point);
}

void CSplitterUtility::SetActivePane(int row, int col, CWnd *pWnd)
{
	CSplitterWnd::SetActivePane(row,col,pWnd);
}

BOOL CSplitterUtility::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
