#if !defined(AFX_NEWLIBDIALOG_H__AB8F4C1B_A11F_48B5_B0A3_3198B0DA9DD2__INCLUDED_)
#define AFX_NEWLIBDIALOG_H__AB8F4C1B_A11F_48B5_B0A3_3198B0DA9DD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewLibDialog.h : header file
//

////////////////////////////////////////////////////
// CNewLibDialog dialog

class CNewLibDialog : public CDialog
{
// Construction
public:
	const char * m_pCaption;
	char m_LibName[256];
	CNewLibDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewLibDialog)
	enum { IDD = IDD_DIALOG_NEWLIBRARY };
	CEdit	m_Edit_LibName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewLibDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewLibDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWLIBDIALOG_H__AB8F4C1B_A11F_48B5_B0A3_3198B0DA9DD2__INCLUDED_)
