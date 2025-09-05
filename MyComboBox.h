#if !defined(AFX_MYCOMBOBOX_H__4B22F8D1_F0AD_4E21_9CBB_9EFB918F5789__INCLUDED_)
#define AFX_MYCOMBOBOX_H__4B22F8D1_F0AD_4E21_9CBB_9EFB918F5789__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyComboBox.h : header file
//

////////////////////////////////////////////////////
// CMyComboBox window

class CMyComboBox : public CComboBox
{
// Construction
public:
	CMyComboBox();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyComboBox();
	void SetTheMaster(CWnd *pW){m_pW = pW;}
	void SetMsgValue(int m){m_ObjMsg=m;}
	int GetMsgValue(void){return m_ObjMsg;}
	void SetWMsgValue(int m){m_WMsg=m;}
	int GetWMsgValue(void){return m_WMsg;}

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
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

#endif // !defined(AFX_MYCOMBOBOX_H__4B22F8D1_F0AD_4E21_9CBB_9EFB918F5789__INCLUDED_)
