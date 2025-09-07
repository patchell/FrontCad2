#pragma once

////////////////////////////////////////////////////
// CUtilView form view


class CUtilView : public CFormView
{
	CWnd* m_pCadView;
	COLORREF m_FillColor;
	COLORREF m_LineColor;
protected:
	CUtilView();           // protected constructor used by dynamic creation
	virtual ~CUtilView();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_DYNCREATE(CUtilView)
public:
	enum { IDD = IDD_DIALOG_UTILITY };
	CButtonMsg	m_Check_TransparentFont;
	CStatic	m_Static_TextAngle;
	CEditDecimal	m_Edit_TextAngle;
	CStaticBitmap	m_Static_Background;
	CEditDecimal	m_Edit_X1;
	CEditDecimal	m_Edit_Y1;
	CEditDecimal	m_Edit_X2;
	CEditDecimal	m_Edit_Y2;
	CEditDecimal	m_Edit_X3;	// Used for Rounded Rectangles, Arrows Width
	CEditDecimal	m_Edit_Y3;	// Used for Rounded Rectangles, Arrows Length
	CEditDecimal	m_Edit_LineThickness;
	CEditDecimal	m_Edit_HoleRadius;
	CEditDecimal	m_Edit_FontWidth;
	CEditDecimal	m_Edit_FontHeight;
	CEditDecimal	m_Edit_FlatToCenterDist;
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
	void SetupTextSelected(int objecttype);
	void ShowHideForSelected(int objecttype);
	void SetUpText(int Drawmode);
	void ShowHide(int DrawMode);
	virtual void OnInitialUpdate();
	void SetCadView(CWnd* pCadView) { m_pCadView = pCadView; }
protected:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	afx_msg void OnUpdateEditUtilLinethickness();
	afx_msg void OnStaticUtilFillColor();
	afx_msg void OnStaticUtilLinecolor();
	afx_msg void OnChangeEditUtilX1();
	afx_msg void OnStaticUtilTextcolor();
	afx_msg void OnButtonUtilityFont();
	afx_msg void OnStaticUtilTextbkcolor();
	afx_msg void OnStaticUtilBackgroundcolor();
	afx_msg void OnCheckTransparent();
    afx_msg void OnClickedCheckUtilTransparent();
	DECLARE_MESSAGE_MAP()
};

