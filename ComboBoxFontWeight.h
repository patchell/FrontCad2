#if !defined(AFX_COMBOBOXFONTWEIGHT_H__2695AE37_A5ED_459E_8341_506DCF8D5530__INCLUDED_)
#define AFX_COMBOBOXFONTWEIGHT_H__2695AE37_A5ED_459E_8341_506DCF8D5530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxFontWeight.h : header file
//

////////////////////////////////////////////////////
// CComboBoxFontWeight window

class CComboBoxFontWeight : public CComboBox
{
// Construction
public:
	CComboBoxFontWeight();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxFontWeight)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetFontWeight(void);
	void Init();
	void SetFontWeight(int w);
	void SetupMessaging(CWnd *pW,int Wmsg,int Smsg);
	virtual ~CComboBoxFontWeight();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxFontWeight)
	afx_msg void OnSelchange();
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

#endif // !defined(AFX_COMBOBOXFONTWEIGHT_H__2695AE37_A5ED_459E_8341_506DCF8D5530__INCLUDED_)
