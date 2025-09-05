#if !defined(AFX_UTILVIEW_H__107FE601_C0AE_410F_A5D3_34F0F65A4240__INCLUDED_)
#define AFX_UTILVIEW_H__107FE601_C0AE_410F_A5D3_34F0F65A4240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UtilView.h : header file
//

////////////////////////////////////////////////////
// CUtilView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "StaticBitmap.h"
#include "MyEdit.h"
#include "ComboBoxFontWeight.h"
#include "EditDecimal.h"
#include "ButtonMsg.h"
#include "ComboBoxPrintRect.h"

class CUtilView : public CFormView
{
protected:
	CUtilView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CUtilView)

// Form Data
public:
	//{{AFX_DATA(CUtilView)
	enum { IDD = IDD_DIALOG_UTILITY };
	CButtonMsg	m_Check_TransparentFont;
	CStatic	m_Static_TextAngle;
	CEditDecimal	m_Edit_TextAngle;
	CStaticBitmap	m_Static_Background;
	CEditDecimal	m_Edit_Y3;
	CEditDecimal	m_Edit_Y2;
	CEditDecimal	m_Edit_Y1;
	CEditDecimal	m_Edit_X3;
	CEditDecimal	m_Edit_X2;
	CEditDecimal	m_Edit_LineThickness;
	CEditDecimal	m_Edit_HoleRadius;
	CEditDecimal	m_Edit_FontWidth;
	CEditDecimal	m_Edit_FontHeight;
	CEditDecimal	m_Edit_FlatToCenterDist;
	CEditDecimal	m_Edit_X1;
	CStatic	m_Static_Bk;
	CStatic	m_Static_Fg;
	CStaticBitmap	m_Static_BkGrndColor;
	CButton	m_Button_Font;
	CComboBoxFontWeight	m_Combo_FontWeight;
	CStatic	m_Static_TextColorText;
	CStatic	m_Static_FontWidth;
	CStatic	m_Static_FontHieght;
	CStatic	m_Static_TextText;
	CStaticBitmap	m_Static_TextColor;
	CMyEdit	m_Edit_Text;
	CStatic	m_Static_FlatToCenterDist;
	CStatic	m_Static_HoleRad;
	CStatic	m_Static_Y3;
	CStatic	m_Static_Y2;
	CStatic	m_Static_Y1;
	CStatic	m_Static_X3;
	CStatic	m_Static_X2;
	CStatic	m_Static_X1;
	CStatic	m_Static_LineWidth;
	CStatic	m_Static_LineColorText;
	CStatic	m_Static_FillColorText;
	CStaticBitmap	m_Static_LineColor;
	CStaticBitmap	m_Static_FillColor;
	CComboBoxPrintRect m_Combo_PrintRect;
	CButtonMsg m_Check_TransparentFill;
public:

// Operations
public:
	CWnd * m_pCadView;
	void SetupTextSelected(int objecttype);
	void ShowHideForSelected(int objecttype);
	void SetUpText(int Drawmode);
	void ShowHide(int DrawMode);
	COLORREF m_FillColor;
	COLORREF m_LineColor;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUtilView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CUtilView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CUtilView)
	afx_msg void OnUpdateEditUtilLinethickness();
	afx_msg void OnStaticUtilFillColor();
	afx_msg void OnStaticUtilLinecolor();
	afx_msg void OnChangeEditUtilX1();
	afx_msg void OnStaticUtilTextcolor();
	afx_msg void OnButtonUtilityFont();
	afx_msg void OnStaticUtilTextbkcolor();
	afx_msg void OnStaticUtilBackgroundcolor();
	afx_msg void OnCheckTransparent();
	DECLARE_MESSAGE_MAP()
    afx_msg void OnClickedCheckUtilTransparent();
};

#endif 