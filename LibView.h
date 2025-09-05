#if !defined(AFX_LIBVIEW_H__E359169D_42B2_4796_A705_8B10C0FAAA1C__INCLUDED_)
#define AFX_LIBVIEW_H__E359169D_42B2_4796_A705_8B10C0FAAA1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LibView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLibView view

class CLibView : public CView
{
protected:
	CLibView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLibView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLibView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLibView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLibView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIBVIEW_H__E359169D_42B2_4796_A705_8B10C0FAAA1C__INCLUDED_)
