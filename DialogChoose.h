#if !defined(AFX_DIALOGCHOOSE_H__02C1BC3A_E832_45B4_9528_AC2F92A20491__INCLUDED_)
#define AFX_DIALOGCHOOSE_H__02C1BC3A_E832_45B4_9528_AC2F92A20491__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogChoose.h : header file
//

////////////////////////////////////////////////////
// CDialogChoose dialog

class CDialogChoose : public CDialog
{
// Construction
public:
	CDialogChoose(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogChoose)
	enum { IDD = IDD_DIALOG_CHOOSE_LIB };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogChoose)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogChoose)
	afx_msg void OnButtonChooseCreate();
	afx_msg void OnButtonChooseLoadlib();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGCHOOSE_H__02C1BC3A_E832_45B4_9528_AC2F92A20491__INCLUDED_)
