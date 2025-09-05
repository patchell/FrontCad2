#if !defined(AFX_BUTTONMSG_H__1200EA9F_81B6_4453_B79D_B2CD29CD6AC5__INCLUDED_)
#define AFX_BUTTONMSG_H__1200EA9F_81B6_4453_B79D_B2CD29CD6AC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButtonMsg.h : header file
//

////////////////////////////////////////////////////
// CButtonMsg window

class CButtonMsg : public CButton
{
	int m_ObjMsg;
	int m_WMsg;
	CWnd *m_pW;
// Construction
public:
	CButtonMsg();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonMsg)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetCheck(int nCheck,int Message);
	void SetCheck(int nCheck);
	void SetupMessaging(CWnd *pW,int msg,int submsg);
	virtual ~CButtonMsg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonMsg)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONMSG_H__1200EA9F_81B6_4453_B79D_B2CD29CD6AC5__INCLUDED_)
