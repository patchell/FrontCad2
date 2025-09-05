#if !defined(AFX_WIZTAB2DIALOG_H__ED7DB59C_96F1_40DF_8A52_58D2AB85057F__INCLUDED_)
#define AFX_WIZTAB2DIALOG_H__ED7DB59C_96F1_40DF_8A52_58D2AB85057F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizTab2Dialog.h : header file
//

#include "MyEdit.h"
#include "HorzScrollBar.h"
#include "ComboBoxFontWeight.h"
#include "EditDecimal.h"
#include "ButtonMsg.h"

////////////////////////////////////////////////////
// CWizTab2Dialog dialog

class CWizTab2Dialog : public CDialog
{
// Construction
public:
	CWizTab2Dialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWizTab2Dialog)
	enum { IDD = IDD_DIALOG_WIZ_TAB2 };
	CButtonMsg	m_CheckBox_RotateText;
	CEditDecimal	m_Edit_DistToTick;
	CEditDecimal	m_Edit_FontSize;
	CStaticBitmap	m_Static_BkColor;
	CStaticBitmap	m_Static_FgColor;
	CStatic	m_Static_Font;
	CComboBoxFontWeight	m_ComboBox_FontWeight;
	CStatic	m_Static_FontLable;
	CMyEdit	m_Edit_Label;
	CHorzScrollBar	m_SB_LableSelect;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizTab2Dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWizTab2Dialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonTab2Selfont();
	afx_msg void OnStaticSwtab2Fgcolor();
	afx_msg void OnStaticSwtab2Bkcolor();
	afx_msg void OnCheckTab2Rotatetext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZTAB2DIALOG_H__ED7DB59C_96F1_40DF_8A52_58D2AB85057F__INCLUDED_)
