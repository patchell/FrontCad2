#if !defined(AFX_MYTABCTRL_H__9D037CC7_EC3C_46EB_8690_51C70F83E9A8__INCLUDED_)
#define AFX_MYTABCTRL_H__9D037CC7_EC3C_46EB_8690_51C70F83E9A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTabCtrl.h : header file
//

////////////////////////////////////////////////////
// CMyTabCtrl window

class CMyTabCtrl : public CTabCtrl
{
// Construction
public:
	CDialog *m_tabPages[3];
	int m_tabCurrent;
	int m_nNumberOfPages;
	CMyTabCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTabCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetRectangle();
	void Init();
	virtual ~CMyTabCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyTabCtrl)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTABCTRL_H__9D037CC7_EC3C_46EB_8690_51C70F83E9A8__INCLUDED_)
