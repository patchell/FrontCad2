#if !defined(AFX_EDITDECIMAL_H__84B6E677_4BBB_4172_B243_D407F7328B3A__INCLUDED_)
#define AFX_EDITDECIMAL_H__84B6E677_4BBB_4172_B243_D407F7328B3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditDecimal.h : header file
//

////////////////////////////////////////////////////
// CEditDecimal window

class CEditDecimal : public CEdit
{
	int m_DecimalPlaces;
	int m_ObjMsg;
	int m_WMsg;
	CWnd *m_pW;
// Construction
public:
	CEditDecimal();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditDecimal)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditDecimal();
	void SetupMessaging(CWnd *pWdest,int WMsg,int SubMsg);
	void SetDecimalPlaces(int p);
	int GetDecimalPlaces(void);
	void SetValue(int v);
	int GetValue(void);

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditDecimal)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITDECIMAL_H__84B6E677_4BBB_4172_B243_D407F7328B3A__INCLUDED_)
