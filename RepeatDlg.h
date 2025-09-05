#pragma once
#include "afxwin.h"
#include "EditDecimal.h"


// CRepeatDlg dialog

class CRepeatDlg : public CDialog
{
	DECLARE_DYNAMIC(CRepeatDlg)

public:
	CRepeatDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRepeatDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REPEAT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEditDecimal m_Edit_RepeatsX;
	CEditDecimal m_Edit_RepeatsY;
	CEditDecimal m_Edit_Xinc;
	CEditDecimal m_Edit_Yinc;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	int m_Xinc;
	int m_Yinc;
	int m_RepeatCountX;
	int m_RepeatCountY;
};
