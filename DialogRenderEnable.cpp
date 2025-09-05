// DialogRenderEnable.cpp : implementation file
//

#include "stdafx.h"

// CDialogRenderEnable dialog

IMPLEMENT_DYNAMIC(CDialogRenderEnable, CDialog)

CDialogRenderEnable::CDialogRenderEnable(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_RENDER_ENABLE, pParent)
{

}

CDialogRenderEnable::~CDialogRenderEnable()
{
}

void CDialogRenderEnable::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK_ARCCENTEREDENABLE, m_Check_ArcCenteredEnable);
    DDX_Control(pDX, IDC_CHECK_ARCENABLE, m_Check_ArcEnable);
    DDX_Control(pDX, IDC_CHECK_ARROWENABLE, m_Check_ArrowEnable);
    DDX_Control(pDX, IDC_CHECK_DIMENSIONENABLE, m_Check_DimensionEnable);
    DDX_Control(pDX, IDC_CHECK_ELLISPEENABLE, m_Check_EllipseEnable);
    DDX_Control(pDX, IDC_CHECK_FILLEDPOLYENABLE, m_Check_FillPolygonEnable);
    DDX_Control(pDX, IDC_CHECK_LINEENABLE, m_Check_LineEnable);
    DDX_Control(pDX, IDC_CHECK_ONEFLATENABLE, m_Check_OneFlatHoleEnable);
    DDX_Control(pDX, IDC_CHECK_ORIGINENABLE, m_Check_OriginEnable);
    DDX_Control(pDX, IDC_CHECK_POLYGONENABLE, m_Check_PolygonEnable);
    DDX_Control(pDX, IDC_CHECK_RECTENABLE, m_Check_RectEnable);
    DDX_Control(pDX, IDC_CHECK_RECTHOLEENABLE, m_Check_RectHoleEnable);
    DDX_Control(pDX, IDC_CHECK_ROUNDEDRECTENABLE, m_CheckRoundedRectEnable);
    DDX_Control(pDX, IDC_CHECK_ROUNDHOLEENABLE, m_Check_RoundHole);
    DDX_Control(pDX, IDC_CHECK_TEXTENABLED, m_Check_TextEnable);
    DDX_Control(pDX, IDC_CHECK_TWOFLATENABLE, m_Check_TwoFlatRoundHoleEnable);
    DDX_Control(pDX, IDC_CHECKBOX_SHAPE_FILL_ENABLE, m_CheckBox_ShapeFill);
    DDX_Control(pDX, IDC_CHECK_RENDER_CIRCLE, m_Check_Circlle);
}


BEGIN_MESSAGE_MAP(CDialogRenderEnable, CDialog)
	ON_BN_CLICKED(IDC_CHECK_ARCCENTEREDENABLE, &CDialogRenderEnable::OnClickedCheckArccenteredenable)
	ON_BN_CLICKED(IDC_CHECK_ARCENABLE, &CDialogRenderEnable::OnClickedCheckArcenable)
	ON_BN_CLICKED(IDC_CHECK_ARROWENABLE, &CDialogRenderEnable::OnClickedCheckArrowenable)
	ON_BN_CLICKED(IDC_CHECK_DIMENSIONENABLE, &CDialogRenderEnable::OnClickedCheckDimensionenable)
	ON_BN_CLICKED(IDC_CHECK_ELLISPEENABLE, &CDialogRenderEnable::OnClickedCheckEllispeenable)
	ON_BN_CLICKED(IDC_CHECK_FILLEDPOLYENABLE, &CDialogRenderEnable::OnClickedCheckFilledpolyenable)
	ON_BN_CLICKED(IDC_CHECK_LINEENABLE, &CDialogRenderEnable::OnClickedCheckLineenable)
	ON_BN_CLICKED(IDC_CHECK_ONEFLATENABLE, &CDialogRenderEnable::OnClickedCheckOneflatenable)
	ON_BN_CLICKED(IDC_CHECK_ORIGINENABLE, &CDialogRenderEnable::OnClickedCheckOriginenable)
	ON_BN_CLICKED(IDC_CHECK_POLYGONENABLE, &CDialogRenderEnable::OnClickedCheckPolygonenable)
	ON_BN_CLICKED(IDC_CHECK_RECTENABLE, &CDialogRenderEnable::OnClickedCheckRectenable)
	ON_BN_CLICKED(IDC_CHECK_RECTHOLEENABLE, &CDialogRenderEnable::OnClickedCheckRectholeenable)
	ON_BN_CLICKED(IDC_CHECK_ROUNDEDRECTENABLE, &CDialogRenderEnable::OnClickedCheckRoundedrectenable)
	ON_BN_CLICKED(IDC_CHECK_ROUNDHOLEENABLE, &CDialogRenderEnable::OnClickedCheckRoundholeenable)
	ON_BN_CLICKED(IDC_CHECK_TEXTENABLED, &CDialogRenderEnable::OnClickedCheckTextenabled)
	ON_BN_CLICKED(IDC_CHECK_TWOFLATENABLE, &CDialogRenderEnable::OnClickedCheckTwoflatenable)
	ON_BN_CLICKED(IDC_CHECKBOX_SHAPE_FILL_ENABLE, &CDialogRenderEnable::OnClickedCheckboxShapeFillEnable)
    ON_BN_CLICKED(IDC_CHECK_RENDER_CIRCLE, &CDialogRenderEnable::OnClickedCheckRenderCircle)
END_MESSAGE_MAP()


// CDialogRenderEnable message handlers


void CDialogRenderEnable::OnClickedCheckArccenteredenable()
{
	CCadArcCentered::SetRenderEnable(m_Check_ArcCenteredEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckArcenable()
{
	CCadArc::SetRenderEnable(m_Check_ArcEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckArrowenable()
{
	CCadArrow::SetRenderEnable(m_Check_ArrowEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckDimensionenable()
{
	CCadDimension::SetRenderEnable(m_Check_DimensionEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckEllispeenable()
{
	CCadElipse::SetRenderEnable ( m_Check_EllipseEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckFilledpolyenable()
{
//	CCadPolygonFill::SetRenderEnable(m_Check_FillPolygonEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckLineenable()
{
	CCadLine::SetRenderEnable ( m_Check_LineEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckOneflatenable()
{
	CCadHoleRnd1Flat::SetRenderEnable ( m_Check_OneFlatHoleEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckOriginenable()
{
	CCadOrigin::SetRenderEnable ( m_Check_OriginEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckPolygonenable()
{
	CCadPolygon::SetRenderEnable ( m_Check_PolygonEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckRectenable()
{
	CCadRect::SetRenderEnable ( m_Check_RectEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckRectholeenable()
{
	CCadRectHole::SetRenderEnable( m_Check_RectHoleEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckRoundedrectenable()
{
	CCadRoundRect::SetRenderEnable( m_CheckRoundedRectEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckRoundholeenable()
{
	CCadHoleRound::SetRenderEnable( m_Check_RoundHole.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckTextenabled()
{
	CCadText::SetRenderEnable( m_Check_TextEnable.GetCheck());
}


void CDialogRenderEnable::OnClickedCheckTwoflatenable()
{
	CCadHoleRnd2Flat::SetRenderEnable ( m_Check_TwoFlatRoundHoleEnable.GetCheck());
}


BOOL CDialogRenderEnable::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Check_ArcCenteredEnable.SetCheck(CCadArcCentered::IsRenderEnabled());
	m_Check_ArcEnable.SetCheck(CCadArc::IsRenderEnabled());
	m_CheckRoundedRectEnable.SetCheck(CCadRoundRect::IsRenderEnabled());
	m_Check_ArrowEnable.SetCheck(CCadArrow::IsRenderEnabled());
	m_Check_DimensionEnable.SetCheck(CCadDimension::IsRenderEnabled());
	m_Check_EllipseEnable.SetCheck(CCadElipse::IsRenderEnabled());
	m_Check_LineEnable.SetCheck(CCadLine::IsRenderEnabled());
	m_Check_OneFlatHoleEnable.SetCheck(CCadHoleRnd1Flat::IsRenderEnabled());
	m_Check_OriginEnable.SetCheck(CCadOrigin::IsRenderEnabled());
	m_Check_PolygonEnable.SetCheck(CCadPolygon::IsRenderEnabled());
	m_Check_RectEnable.SetCheck(CCadRect::IsRenderEnabled());
	m_Check_RectHoleEnable.SetCheck(CCadRectHole::IsRenderEnabled());
	m_Check_RoundHole.SetCheck(CCadHoleRound::IsRenderEnabled());
	m_Check_TextEnable.SetCheck(CCadText::IsRenderEnabled());
	m_Check_TwoFlatRoundHoleEnable.SetCheck(CCadHoleRnd2Flat::IsRenderEnabled());
	m_Check_Circlle.SetCheck(CCadCircle::IsRenderEnabled());
	if (CCadObject::AreShapeFillsEnable())
	{
		m_CheckBox_ShapeFill.SetCheck(BST_CHECKED);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogRenderEnable::OnClickedCheckboxShapeFillEnable()
{
	if (m_CheckBox_ShapeFill.GetCheck())
		CCadObject::EnableRenderFills();
	else
		CCadObject::DisableRenderFills();
}

void CDialogRenderEnable::OnClickedCheckRenderCircle()
{
	CCadCircle::SetRenderEnable(m_Check_Circlle.GetCheck());
}
