#if !defined(AFX_SCALEWIZTABONE_H__ABEBC087_7321_4EDA_9A17_03577F95B822__INCLUDED_)
#define AFX_SCALEWIZTABONE_H__ABEBC087_7321_4EDA_9A17_03577F95B822__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScaleWizTabOne.h : header file
//
#include "MyEdit.h"
#include "MyComboBox.h"
#include "ComboBoxHoleType.h"
#include "EditDecimal.h"

////////////////////////////////////////////////////
// CScaleWizTabOne dialog

class CScaleWizTabOne : public CDialog
{
// Construction
public:
	CScaleWizTabOne(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScaleWizTabOne)
	enum { IDD = IDD_DIALOG_WIZ_TAB1 };
	CEditDecimal	m_Edit_EndAngle;
	CEditDecimal	m_Edit_FlatDist;
	CEditDecimal	m_Edit_HoleRadius;
	CEditDecimal	m_Edit_StartAngle;
	CEditDecimal	m_Edit_Subdivisions;
	CEditDecimal	m_Edit_SubLineWidth;
	CEditDecimal	m_Edit_SubLineLen;
	CEditDecimal	m_Edit_DivisionLineWidth;
	CEditDecimal	m_Edit_DivLineLen;
	CEditDecimal	m_Edit_Divisions;
	CEditDecimal	m_Edit_ArcLineWidth;
	CEditDecimal	m_Edit_ArcRadius;
	CStaticBitmap	m_Static_SubColor;
	CStaticBitmap	m_Static_DivColor;
	CStaticBitmap	m_Static_ArcColor;
	CComboBoxHoleType	m_Combo_HoleType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScaleWizTabOne)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScaleWizTabOne)
	virtual BOOL OnInitDialog();
	afx_msg void OnStaticTab1Subcolor();
	afx_msg void OnStaticTab1Arccolor();
	afx_msg void OnStaticTab1Divcolor();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCALEWIZTABONE_H__ABEBC087_7321_4EDA_9A17_03577F95B822__INCLUDED_)
