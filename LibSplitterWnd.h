#if !defined(AFX_LIBSPLITTERWND_H__477F68AF_B3A2_4344_A73F_F96FB02ED4B0__INCLUDED_)
#define AFX_LIBSPLITTERWND_H__477F68AF_B3A2_4344_A73F_F96FB02ED4B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibSplitterWnd.h : header file
//

////////////////////////////////////////////////////
// CLibSplitterWnd frame with splitter

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CLibSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNCREATE(CLibSplitterWnd)
public:
	CLibSplitterWnd();           // protected constructor used by dynamic creation

// Attributes
protected:
	CSplitterWnd    m_wndSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibSplitterWnd)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL CreateLibraryPane(CWnd* pParent, CCreateContext* pContext,DWORD dwStyle=WS_CHILD | WS_VISIBLE , UINT nID=AFX_IDW_PANE_FIRST );
	virtual ~CLibSplitterWnd();

	// Generated message map functions
	//{{AFX_MSG(CLibSplitterWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBSPLITTERWND_H__477F68AF_B3A2_4344_A73F_F96FB02ED4B0__INCLUDED_)
