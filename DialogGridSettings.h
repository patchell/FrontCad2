#if !defined(AFX_DIALOGGRIDSETTINGS_H__FE7D256E_A264_44E7_9976_7FE4C38D5EB1__INCLUDED_)
#define AFX_DIALOGGRIDSETTINGS_H__FE7D256E_A264_44E7_9976_7FE4C38D5EB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogGridSettings.h : header file
//

////////////////////////////////////////////////////
// CDialogGridSettings dialog

class CDialogGridSettings : public CDialog
{
// Construction
public:
	COLORREF m_Color;
	int m_Snap;
	int m_Grid;
	CDialogGridSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogGridSettings)
	enum { IDD = IDD_DIALOG_GRIDSETTINGS };
	CStaticBitmap	m_Static_Color;
	CEditDecimal	m_Edit_Snap;
	CEditDecimal	m_Edit_Grid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogGridSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogGridSettings)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnStaticGridColor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGGRIDSETTINGS_H__FE7D256E_A264_44E7_9976_7FE4C38D5EB1__INCLUDED_)
