#if !defined(AFX_MYEDIT_H__94DACCC9_721A_4393_A01C_C33AF09B8F4A__INCLUDED_)
#define AFX_MYEDIT_H__94DACCC9_721A_4393_A01C_C33AF09B8F4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyEdit.h : header file
//


////////////////////////////////////////////////////
// CMyEdit window

class CMyEdit : public CEdit
{
// Construction
public:
	CMyEdit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetupMessaging(CWnd *pWdest,int WMsg,int SubMsg);
	virtual ~CMyEdit();
	void SetTheMaster(CWnd *pW){m_pW = pW;}
	void SetMsgValue(int m){m_ObjMsg=m;}
	int GetMsgValue(void){return m_ObjMsg;}
	void SetWMsgValue(int m){m_WMsg=m;}
	int GetWMsgValue(void){return m_WMsg;}
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyEdit)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int m_ObjMsg;
	int m_WMsg;
	CWnd *m_pW;
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYEDIT_H__94DACCC9_721A_4393_A01C_C33AF09B8F4A__INCLUDED_)
