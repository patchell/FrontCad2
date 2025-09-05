#if !defined(AFX_SPLITTERUTILITY_H__8654228C_3623_472E_BA26_6FB0242E9F15__INCLUDED_)
#define AFX_SPLITTERUTILITY_H__8654228C_3623_472E_BA26_6FB0242E9F15__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplitterUtility.h : header file
//

////////////////////////////////////////////////////
// CSplitterUtility frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CSplitterUtility : public CSplitterWnd
{
	DECLARE_DYNCREATE(CSplitterUtility)
public:
	CSplitterUtility();           // protected constructor used by dynamic creation

// Attributes
protected:
	CSplitterWnd    m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplitterUtility)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void SetActivePane(int row, int col, CWnd *pWnd=NULL);
	BOOL CreateUtility(CWnd* pParent, CCreateContext* pContext,DWORD dwStyle=WS_CHILD | WS_VISIBLE , UINT nID=AFX_IDW_PANE_FIRST );
	virtual ~CSplitterUtility();

	// Generated message map functions
	//{{AFX_MSG(CSplitterUtility)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLITTERUTILITY_H__8654228C_3623_472E_BA26_6FB0242E9F15__INCLUDED_)
