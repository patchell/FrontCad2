#if !defined(AFX_STATICPREVIEW_H__5C700A14_0191_4CE9_B36F_D5F0B59B0E95__INCLUDED_)
#define AFX_STATICPREVIEW_H__5C700A14_0191_4CE9_B36F_D5F0B59B0E95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticPreview.h : header file
//

#include "CadLibObject.h"

////////////////////////////////////////////////////
// CStaticPreview window

class CStaticPreview : public CStatic
{
// Construction
public:
	CStaticPreview();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticPreview)
	//}}AFX_VIRTUAL

// Implementation
public:
	CCadLibObject * m_pLibObj;
	virtual ~CStaticPreview();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticPreview)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICPREVIEW_H__5C700A14_0191_4CE9_B36F_D5F0B59B0E95__INCLUDED_)
