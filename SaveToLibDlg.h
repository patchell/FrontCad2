#if !defined(AFX_SAVETOLIBDLG_H__DB08258A_E838_499C_8AFA_6F57394C8333__INCLUDED_)
#define AFX_SAVETOLIBDLG_H__DB08258A_E838_499C_8AFA_6F57394C8333__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SaveToLibDlg.h : header file
//

////////////////////////////////////////////////////
// CSaveToLibDlg dialog

class CSaveToLibDlg : public CDialog
{
// Construction
public:
	CSaveToLibDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSaveToLibDlg)
	enum { IDD = IDD_DIALOG_SAVETOLIBRARY };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSaveToLibDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSaveToLibDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAVETOLIBDLG_H__DB08258A_E838_499C_8AFA_6F57394C8333__INCLUDED_)
