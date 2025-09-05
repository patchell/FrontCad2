#if !defined(AFX_COMBOBOXHOLETYPE_H__320A4B6C_7F4D_4C09_8A84_4473D74187A4__INCLUDED_)
#define AFX_COMBOBOXHOLETYPE_H__320A4B6C_7F4D_4C09_8A84_4473D74187A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxHoleType.h : header file
//

////////////////////////////////////////////////////
// CComboBoxHoleType window

class CComboBoxHoleType : public CComboBox
{
// Construction
public:
	CComboBoxHoleType();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxHoleType)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetupMessaging(CWnd *pW,int Wmsg,int Smsg);
	void Init(void);
	virtual ~CComboBoxHoleType();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxHoleType)
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

#endif // !defined(AFX_COMBOBOXHOLETYPE_H__320A4B6C_7F4D_4C09_8A84_4473D74187A4__INCLUDED_)
