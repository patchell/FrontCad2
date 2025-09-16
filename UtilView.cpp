// UtilView.cpp : implementation file
//

#include "stdafx.h"

////////////////////////////////////////////////////
// CUtilView

IMPLEMENT_DYNCREATE(CUtilView, CFormView)

CUtilView::CUtilView()
	: CFormView(CUtilView::IDD)
{
	m_pCadView = NULL;	
	m_FillColor = RGB(255, 255, 255);
	m_LineColor = RGB(0, 0, 0);
}

CUtilView::~CUtilView()
{
}

void CUtilView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CUtilView)
    DDX_Control(pDX, IDC_CHECK_TRANSPARENT, m_Check_TransparentFont);
    DDX_Control(pDX, IDC_STATIC_UTIL_TEXTANGLE, m_Static_TextAngle);
    DDX_Control(pDX, IDC_EDIT_UTIL_TEXTANGLE, m_Edit_TextAngle);
    DDX_Control(pDX, IDC_STATIC_UTIL_BACKGROUNDCOLOR, m_Static_Background);
    DDX_Control(pDX, IDC_EDIT_UTIL_Y3, m_Edit_Y3);
    DDX_Control(pDX, IDC_EDIT_UTIL_Y2, m_Edit_Y2);
    DDX_Control(pDX, IDC_EDIT_UTIL_Y1, m_Edit_Y1);
    DDX_Control(pDX, IDC_EDIT_UTIL_X3, m_Edit_X3);
    DDX_Control(pDX, IDC_EDIT_UTIL_X2, m_Edit_X2);
    DDX_Control(pDX, IDC_EDIT_UTIL_LINETHICKNESS, m_Edit_LineThickness);
    DDX_Control(pDX, IDC_EDIT_UTIL_HOLERADIUS, m_Edit_HoleRadius);
    DDX_Control(pDX, IDC_EDIT_UTIL_FONTWIDTH, m_Edit_FontWidth);
    DDX_Control(pDX, IDC_EDIT_UTIL_FONTHIEGHT, m_Edit_FontHeight);
    DDX_Control(pDX, IDC_EDIT_UTIL_FLATTOCENT, m_Edit_FlatToCenterDist);
    DDX_Control(pDX, IDC_EDIT_UTIL_X1, m_Edit_X1);
    DDX_Control(pDX, IDC_STATIC_BK, m_Static_Bk);
    DDX_Control(pDX, IDC_STATIC_FG, m_Static_Fg);
    DDX_Control(pDX, IDC_STATIC_UTIL_TEXTBKCOLOR, m_Static_BkGrndColor);
    DDX_Control(pDX, IDC_BUTTON_UTILITY_FONT, m_Button_Font);
    DDX_Control(pDX, IDC_COMBO_UTILITY_FONTWEIGHT, m_Combo_FontWeight);
    DDX_Control(pDX, IDC_STATIC_UTIL_TEXTCOLORTEXT, m_Static_TextColorText);
    DDX_Control(pDX, IDC_STATIC_UTIL_FONTWIDTH, m_Static_FontWidth);
    DDX_Control(pDX, IDC_STATIC_UTIL_FONTHIEGHT, m_Static_FontHieght);
    DDX_Control(pDX, IDC_STATIC_UTIL_TEXTTEXT, m_Static_TextText);
    DDX_Control(pDX, IDC_STATIC_UTIL_TEXTCOLOR, m_Static_TextColor);
    DDX_Control(pDX, IDC_EDIT_UTIL_TEXT, m_Edit_Text);
    DDX_Control(pDX, IDC_STATIC_UTIL_FLATTOCENT, m_Static_FlatToCenterDist);
    DDX_Control(pDX, IDC_STATIC_UTIL_RADIUSHOLE, m_Static_HoleRad);
    DDX_Control(pDX, IDC_STATIC_UTIL_Y3, m_Static_Y3);
    DDX_Control(pDX, IDC_STATIC_UTIL_Y2, m_Static_Y2);
    DDX_Control(pDX, IDC_STATIC_UTIL_Y1, m_Static_Y1);
    DDX_Control(pDX, IDC_STATIC_UTIL_X3, m_Static_X3);
    DDX_Control(pDX, IDC_STATIC_UTIL_X2, m_Static_X2);
    DDX_Control(pDX, IDC_STATIC_UTIL_X1, m_Static_X1);
    DDX_Control(pDX, IDC_STATIC_UTIL_LINEWIDTH, m_Static_LineWidth);
    DDX_Control(pDX, IDC_STATIC_UTIL_LINECOLORTEXT, m_Static_LineColorText);
    DDX_Control(pDX, IDC_STATIC_UTIL_FILLCOLORTEXT, m_Static_FillColorText);
    DDX_Control(pDX, IDC_STATIC_UTIL_LINECOLOR, m_Static_LineColor);
    DDX_Control(pDX, IDC_STATIC_UTIL_FILL_COLOR, m_Static_FillColor);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_UTIL_PRINTRECTSIZE, m_Combo_PrintRect);
    DDX_Control(pDX, IDC_CHECK_UTIL_TRANSPARENT, m_Check_TransparentFill);
}


BEGIN_MESSAGE_MAP(CUtilView, CFormView)
	//{{AFX_MSG_MAP(CUtilView)
	ON_EN_UPDATE(IDC_EDIT_UTIL_LINETHICKNESS, OnUpdateEditUtilLinethickness)
	ON_BN_CLICKED(IDC_STATIC_UTIL_FILL_COLOR, OnStaticUtilFillColor)
	ON_BN_CLICKED(IDC_STATIC_UTIL_LINECOLOR, OnStaticUtilLinecolor)
	ON_EN_CHANGE(IDC_EDIT_UTIL_X1, OnChangeEditUtilX1)
	ON_BN_CLICKED(IDC_STATIC_UTIL_TEXTCOLOR, OnStaticUtilTextcolor)
	ON_BN_CLICKED(IDC_BUTTON_UTILITY_FONT, OnButtonUtilityFont)
	ON_BN_CLICKED(IDC_STATIC_UTIL_TEXTBKCOLOR, OnStaticUtilTextbkcolor)
	ON_BN_CLICKED(IDC_STATIC_UTIL_BACKGROUNDCOLOR, OnStaticUtilBackgroundcolor)
	ON_BN_CLICKED(IDC_CHECK_TRANSPARENT, OnCheckTransparent)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_UTIL_TRANSPARENT, &CUtilView::OnClickedCheckUtilTransparent)
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CUtilView diagnostics

#ifdef _DEBUG
void CUtilView::AssertValid() const
{
	CFormView::AssertValid();
}

void CUtilView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

////////////////////////////////////////////////////
// CUtilView message handlers

void CUtilView::OnUpdateEditUtilLinethickness() 
{
}

void CUtilView::OnStaticUtilFillColor() 
{
	CColorDialog dlg;
	
	if(dlg.DoModal() == IDOK) m_FillColor = dlg.GetColor();
	m_Static_FillColor.SetColor(m_FillColor);
	m_Static_FillColor.SendChange();

}

void CUtilView::OnStaticUtilLinecolor() 
{
	CColorDialog dlg;
	
	if(dlg.DoModal() == IDOK) m_LineColor = dlg.GetColor();
	m_Static_LineColor.SetColor(m_LineColor);
	m_Static_LineColor.SendChange();
	
}

void CUtilView::OnChangeEditUtilX1() 
{
}


void CUtilView::ShowHide(int DrawMode)
{
	switch(DrawMode)
	{
	case CFrontCadView::DrawMode::SELECT:	//ShowHide()
	case CFrontCadView::DrawMode::NONE:
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_HIDE);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_HIDE);
			this->m_Edit_LineThickness.ShowWindow(SW_HIDE);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::LINE:	//ShowHide()
		case CFrontCadView::DrawMode::ORIGIN:
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::POLYGON:	//ShowHide()
			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::ARC:			//ShowHide()
		case CFrontCadView::DrawMode::ARC_CENTER:
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::HOLE_RECT:	//ShowHide()
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_SHOW);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_SHOW);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_SHOW);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_SHOW);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::RECTANGLE:	//ShowHide()
		case CFrontCadView::DrawMode::ELIPSE:
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);

			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::RNDRECT:	//ShowHide()
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);

			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_SHOW);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_SHOW);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_SHOW);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_SHOW);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::HOLE_ROUND:	//ShowHide()
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_SHOW);
			this->m_Edit_HoleRadius.ShowWindow(SW_SHOW);
			break;
		case CFrontCadView::DrawMode::HOLE_RND1F:	//ShowHide()
		case CFrontCadView::DrawMode::HOLE_RND2F:
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_SHOW);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_SHOW);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);

			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_SHOW);
			this->m_Edit_HoleRadius.ShowWindow(SW_SHOW);
			break;
		case CFrontCadView::DrawMode::TEXT:	//ShowHide()
			this->m_Combo_FontWeight.ShowWindow(SW_SHOW);
			this->m_Button_Font.ShowWindow(SW_SHOW);
			this->m_Static_Fg.ShowWindow(SW_SHOW);
			this->m_Static_Bk.ShowWindow(SW_SHOW);
			this->m_Static_BkGrndColor.ShowWindow(SW_SHOW);
			this->m_Edit_Text.ShowWindow(SW_SHOW);
			this->m_Edit_TextAngle.ShowWindow(SW_SHOW);
			this->m_Edit_FontHeight.ShowWindow(SW_SHOW);
			this->m_Edit_FontWidth.ShowWindow(SW_SHOW);
			this->m_Check_TransparentFont.ShowWindow(SW_SHOW);
			this->m_Static_TextAngle.ShowWindow(SW_SHOW);
			this->m_Static_FontHieght.ShowWindow(SW_SHOW);
			this->m_Static_FontWidth.ShowWindow(SW_SHOW);
			this->m_Static_TextColor.ShowWindow(SW_SHOW);
			this->m_Static_TextColorText.ShowWindow(SW_SHOW);
			this->m_Static_TextText.ShowWindow(SW_SHOW);

			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_HIDE);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_HIDE);
			this->m_Edit_LineThickness.ShowWindow(SW_HIDE);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::ARROW:	//ShowHide()
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_SHOW);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_SHOW);

			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_SHOW);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_SHOW);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::DIMENSION:	//ShowHide()
			this->m_Combo_FontWeight.ShowWindow(SW_SHOW);
			this->m_Button_Font.ShowWindow(SW_SHOW);
			this->m_Static_Fg.ShowWindow(SW_SHOW);
			this->m_Static_Bk.ShowWindow(SW_SHOW);
			this->m_Static_BkGrndColor.ShowWindow(SW_SHOW);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_SHOW);
			this->m_Edit_FontWidth.ShowWindow(SW_SHOW);
			this->m_Check_TransparentFont.ShowWindow(SW_SHOW);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_SHOW);
			this->m_Static_FontWidth.ShowWindow(SW_SHOW);
			this->m_Static_TextColor.ShowWindow(SW_SHOW);
			this->m_Static_TextColorText.ShowWindow(SW_SHOW);

			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case CFrontCadView::DrawMode::CIRCLE:	//ShowHide()
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);

			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);
			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
	}
}

void CUtilView::ShowHideForSelected(int objecttype)
{
	switch(objecttype)
	{
		case OBJECT_TYPE_NONE:	//ShowHideForSelected
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_HIDE);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_HIDE);
			this->m_Edit_LineThickness.ShowWindow(SW_HIDE);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_ORIGIN:	//ShowHideForSelected
		case OBJECT_TYPE_LINE:
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_SHOW);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_SHOW);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_SHOW);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_SHOW);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_RECT:		//ShowHideForSelected
		case OBJECT_TYPE_ELLIPSE:		
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);

			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_SHOW);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_SHOW);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_SHOW);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_SHOW);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_RNDRECT:		//ShowHideForSelected	
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);

			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_SHOW);
			this->m_Static_X3.ShowWindow(SW_SHOW);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_SHOW);
			this->m_Static_Y3.ShowWindow(SW_SHOW);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_SHOW);
			this->m_Edit_X3.ShowWindow(SW_SHOW);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_SHOW);
			this->m_Edit_Y3.ShowWindow(SW_SHOW);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_POLY:		//ShowHideForSelected
		case OBJECT_TYPE_POLYFILL:	
		case OBJECT_TYPE_LIBCOMP:
			break;
		case OBJECT_TYPE_HOLEROUND:		//ShowHideForSelected
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_SHOW);
			this->m_Edit_HoleRadius.ShowWindow(SW_SHOW);
			break;
		case OBJECT_TYPE_HOLERECT:		//ShowHideForSelected
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_SHOW);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_SHOW);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_SHOW);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_SHOW);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_HOLERND1FLAT:		//ShowHideForSelected
		case OBJECT_TYPE_HOLERND2FLAT:
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_SHOW);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_SHOW);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_SHOW);
			this->m_Edit_HoleRadius.ShowWindow(SW_SHOW);
			break;
		case OBJECT_TYPE_TEXT:		//ShowHideForSelected
			this->m_Combo_FontWeight.ShowWindow(SW_SHOW);
			this->m_Button_Font.ShowWindow(SW_SHOW);
			this->m_Static_Fg.ShowWindow(SW_SHOW);
			this->m_Static_Bk.ShowWindow(SW_SHOW);
			this->m_Static_BkGrndColor.ShowWindow(SW_SHOW);
			this->m_Static_TextColor.ShowWindow(SW_SHOW);
			this->m_Edit_TextAngle.ShowWindow(SW_SHOW);
			this->m_Check_TransparentFont.ShowWindow(SW_SHOW);
			this->m_Static_TextAngle.ShowWindow(SW_SHOW);
			this->m_Edit_FontHeight.ShowWindow(SW_SHOW);
			this->m_Static_FontHieght.ShowWindow(SW_SHOW);
			this->m_Edit_FontWidth.ShowWindow(SW_SHOW);
			this->m_Static_FontWidth.ShowWindow(SW_SHOW);
			this->m_Static_TextText.ShowWindow(SW_SHOW);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Edit_Text.ShowWindow(SW_SHOW);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_HIDE);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_HIDE);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_HIDE);
			this->m_Edit_LineThickness.ShowWindow(SW_HIDE);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_ARC:		//ShowHideForSelected		
		case OBJECT_TYPE_ARCCENTERED:
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_SHOW);
			this->m_Static_X3.ShowWindow(SW_SHOW);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_SHOW);
			this->m_Static_Y3.ShowWindow(SW_SHOW);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_SHOW);
			this->m_Edit_X3.ShowWindow(SW_SHOW);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_SHOW);
			this->m_Edit_Y3.ShowWindow(SW_SHOW);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_ARROW:		//ShowHideForSelected
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Static_TextColorText.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);

			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_SHOW);
			this->m_Static_X3.ShowWindow(SW_SHOW);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_SHOW);
			this->m_Static_Y3.ShowWindow(SW_SHOW);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_SHOW);
			this->m_Edit_X3.ShowWindow(SW_SHOW);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_SHOW);
			this->m_Edit_Y3.ShowWindow(SW_SHOW);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_DIMENSION:		//ShowHideForSelected
			this->m_Combo_FontWeight.ShowWindow(SW_SHOW);
			this->m_Button_Font.ShowWindow(SW_SHOW);
			this->m_Static_Fg.ShowWindow(SW_SHOW);
			this->m_Static_Bk.ShowWindow(SW_SHOW);
			this->m_Static_BkGrndColor.ShowWindow(SW_SHOW);
			this->m_Static_TextColor.ShowWindow(SW_SHOW);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_SHOW);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_SHOW);
			this->m_Static_FontHieght.ShowWindow(SW_SHOW);
			this->m_Edit_FontWidth.ShowWindow(SW_SHOW);
			this->m_Static_FontWidth.ShowWindow(SW_SHOW);
			this->m_Static_TextText.ShowWindow(SW_HIDE);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFill.ShowWindow(SW_HIDE);

			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_HIDE);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_HIDE);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_HIDE);
			this->m_Static_Y1.ShowWindow(SW_HIDE);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_HIDE);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_HIDE);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_HIDE);
			this->m_Edit_Y1.ShowWindow(SW_HIDE);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
		case OBJECT_TYPE_CIRCLE:		//ShowHideForSelected
			this->m_Combo_FontWeight.ShowWindow(SW_HIDE);
			this->m_Button_Font.ShowWindow(SW_HIDE);
			this->m_Static_Fg.ShowWindow(SW_HIDE);
			this->m_Static_Bk.ShowWindow(SW_HIDE);
			this->m_Static_TextColor.ShowWindow(SW_HIDE);
			this->m_Edit_TextAngle.ShowWindow(SW_HIDE);
			this->m_Check_TransparentFont.ShowWindow(SW_HIDE);
			this->m_Static_TextAngle.ShowWindow(SW_HIDE);
			this->m_Edit_FontHeight.ShowWindow(SW_HIDE);
			this->m_Static_FontHieght.ShowWindow(SW_HIDE);
			this->m_Edit_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_FontWidth.ShowWindow(SW_HIDE);
			this->m_Static_TextText.ShowWindow(SW_HIDE);

			this->m_Check_TransparentFill.ShowWindow(SW_SHOW);
			this->m_Static_BkGrndColor.ShowWindow(SW_HIDE);
			this->m_Edit_Text.ShowWindow(SW_HIDE);
			this->m_Static_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Edit_FlatToCenterDist.ShowWindow(SW_HIDE);
			this->m_Static_FillColor.ShowWindow(SW_SHOW);
			this->m_Static_LineColor.ShowWindow(SW_SHOW);
			this->m_Static_X1.ShowWindow(SW_SHOW);
			this->m_Static_X2.ShowWindow(SW_HIDE);
			this->m_Static_X3.ShowWindow(SW_SHOW);
			this->m_Static_Y1.ShowWindow(SW_SHOW);
			this->m_Static_Y2.ShowWindow(SW_HIDE);
			this->m_Static_Y3.ShowWindow(SW_HIDE);
			this->m_Static_LineWidth.ShowWindow(SW_SHOW);
			this->m_Static_FillColorText.ShowWindow(SW_SHOW);
			this->m_Static_LineColorText.ShowWindow(SW_SHOW);
			this->m_Edit_LineThickness.ShowWindow(SW_SHOW);
			this->m_Edit_X1.ShowWindow(SW_SHOW);
			this->m_Edit_X2.ShowWindow(SW_HIDE);
			this->m_Edit_X3.ShowWindow(SW_SHOW);
			this->m_Edit_Y1.ShowWindow(SW_SHOW);
			this->m_Edit_Y2.ShowWindow(SW_HIDE);
			this->m_Edit_Y3.ShowWindow(SW_HIDE);
			this->m_Static_HoleRad.ShowWindow(SW_HIDE);
			this->m_Edit_HoleRadius.ShowWindow(SW_HIDE);
			break;
	}
}	//ShowHideForSelected

void CUtilView::SetupTextSelected(int objecttype)
{
	switch(objecttype)
	{
		case OBJECT_TYPE_NONE:
			break;
		case OBJECT_TYPE_CIRCLE:		// SetupTextSelected
			this->m_Static_X1.SetWindowText("Xc");
			this->m_Static_Y1.SetWindowText("Yc");
			this->m_Static_X3.SetWindowText("Radius");
			break;
		case OBJECT_TYPE_LINE:		// SetupTextSelected
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case OBJECT_TYPE_RNDRECT:
			m_Static_X3.SetWindowTextA("X Radius");
			m_Static_Y3.SetWindowTextA("Y Radius");	
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case OBJECT_TYPE_RECT:		// SetupTextSelected
		case OBJECT_TYPE_ELLIPSE:		
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case OBJECT_TYPE_POLY:		// SetupTextSelected
		case OBJECT_TYPE_POLYFILL:	
		case OBJECT_TYPE_LIBCOMP:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case OBJECT_TYPE_HOLEROUND:		// SetupTextSelected
			this->m_Static_X1.SetWindowText("Xc");
			this->m_Static_Y1.SetWindowText("Yc");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case OBJECT_TYPE_HOLERECT:		// SetupTextSelected
			this->m_Static_X1.SetWindowText("Xc");
			this->m_Static_Y1.SetWindowText("Yc");
			this->m_Static_X2.SetWindowText("H");
			this->m_Static_Y2.SetWindowText("W");
			break;
		case OBJECT_TYPE_HOLERND1FLAT:		// SetupTextSelected
		case OBJECT_TYPE_HOLERND2FLAT:
			this->m_Static_X1.SetWindowText("Xc");
			this->m_Static_Y1.SetWindowText("Yc");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case OBJECT_TYPE_TEXT:		// SetupTextSelected
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case OBJECT_TYPE_ARC:				// SetupTextSelected
		case OBJECT_TYPE_ARCCENTERED:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			this->m_Static_X3.SetWindowText("STRT ANG");
			this->m_Static_Y3.SetWindowText("END  ANG");
			break;
		case OBJECT_TYPE_ARROW:		// SetupTextSelected
			m_Static_X1.SetWindowTextA("P X");
			m_Static_Y1.SetWindowTextA("P Y");
			m_Static_X2.SetWindowTextA("B X");
			m_Static_Y2.SetWindowTextA("B Y");
			this->m_Static_X3.SetWindowText("Length");
			this->m_Static_Y3.SetWindowText("Base Width");
			break;
		case OBJECT_TYPE_ORIGIN:		// SetupTextSelected
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			break;
		case OBJECT_TYPE_DIMENSION:		// SetupTextSelected
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
	}
}	//SetupTextSelected

void CUtilView::SetUpText(int Drawmode)
{
	switch(Drawmode)
	{
		case CFrontCadView::DrawMode::NONE:
			break;
		case CFrontCadView::DrawMode::HOLE_RECT:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("H");
			this->m_Static_Y2.SetWindowText("W");
			break;
		case CFrontCadView::DrawMode::LINE:
		case CFrontCadView::DrawMode::ARC:
		case CFrontCadView::DrawMode::POLYGON:	
		case CFrontCadView::DrawMode::ARC_CENTER:	
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case CFrontCadView::DrawMode::RECTANGLE:	
		case CFrontCadView::DrawMode::ELIPSE:		
		case CFrontCadView::DrawMode::POLYFILL:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case CFrontCadView::DrawMode::SELECT:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case CFrontCadView::DrawMode::RNDRECT:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case CFrontCadView::DrawMode::HOLE_ROUND:
		case CFrontCadView::DrawMode::HOLE_RND1F:
		case CFrontCadView::DrawMode::HOLE_RND2F:
			this->m_Static_X1.SetWindowText("Xc");
			this->m_Static_Y1.SetWindowText("Yc");
			this->m_Static_X2.SetWindowText("X2");
			this->m_Static_Y2.SetWindowText("Y2");
			break;
		case CFrontCadView::DrawMode::TEXT:
			break;
		case CFrontCadView::DrawMode::ARROW:
			this->m_Static_X3.SetWindowText("Length");
			this->m_Static_Y3.SetWindowText("Base Width");
			break;
		case CFrontCadView::DrawMode::ORIGIN:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			break;
		case CFrontCadView::DrawMode::DIMENSION:
			this->m_Static_X1.SetWindowText("X1");
			this->m_Static_Y1.SetWindowText("Y1");
			break;
		case CFrontCadView::DrawMode::CIRCLE:
			break;
	}
}	//SetupText

void CUtilView::OnStaticUtilTextcolor() 
{
	CColorDialog dlg;
	
	if(dlg.DoModal() == IDOK) m_LineColor = dlg.GetColor();
	m_Static_TextColor.SetColor(m_LineColor);
	m_Static_TextColor.SendChange();
	
}

void CUtilView::OnButtonUtilityFont() 
{
	CFontDialog dlg;
	CString F;
	LOGFONT lF;

	int id = dlg.DoModal();
	if(id == IDOK)
	{
		dlg.GetCurrentFont(&lF);
		m_Button_Font.SetWindowText(lF.lfFaceName);
		m_pCadView->PostMessageA(WM_UTILMESSAGE,UtilMsg::FONT,0);
	}
}

void CUtilView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_Combo_FontWeight.Init();
	m_Combo_PrintRect.Init();
}

void CUtilView::OnStaticUtilTextbkcolor() 
{
	CColorDialog dlg;
	
	if(dlg.DoModal() == IDOK) m_LineColor = dlg.GetColor();
	m_Static_BkGrndColor.SetColor(m_LineColor);
	m_Static_BkGrndColor.SendChange();
}

void CUtilView::OnStaticUtilBackgroundcolor() 
{
	
	CColorDialog dlg;
	
	if(dlg.DoModal() == IDOK)
	{
		m_Static_Background.SetColor(dlg.GetColor());
		m_Static_Background.SendChange();
	}
}

void CUtilView::OnCheckTransparent() 
{
	int check = m_Check_TransparentFont.GetCheck() ^ 1;
	this->m_Check_TransparentFont.SetCheck(check,1);
}

void CUtilView::OnClickedCheckUtilTransparent()
{
	int check = m_Check_TransparentFill.GetCheck() ^ 1;
	this->m_Check_TransparentFill.SetCheck(check, 1);
}
