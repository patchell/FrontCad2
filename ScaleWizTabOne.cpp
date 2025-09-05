// ScaleWizTabOne.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CScaleWizTabOne dialog


CScaleWizTabOne::CScaleWizTabOne(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleWizTabOne::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleWizTabOne)
	//}}AFX_DATA_INIT
}


void CScaleWizTabOne::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleWizTabOne)
	DDX_Control(pDX, IDC_EDIT_TAB1_ENDANGLE, m_Edit_EndAngle);
	DDX_Control(pDX, IDC_EDIT_TAB1_FLATDIST, m_Edit_FlatDist);
	DDX_Control(pDX, IDC_EDIT_TAB1_HOLERADIUS, m_Edit_HoleRadius);
	DDX_Control(pDX, IDC_EDIT_TAB1_STARTANGLE, m_Edit_StartAngle);
	DDX_Control(pDX, IDC_EDIT_TAB1_SUBDIVSIONS, m_Edit_Subdivisions);
	DDX_Control(pDX, IDC_EDIT_TAB1_SUBLINEWIDTH, m_Edit_SubLineWidth);
	DDX_Control(pDX, IDC_EDIT_TAB1_SUBTICKLEN, m_Edit_SubLineLen);
	DDX_Control(pDX, IDC_EDIT_TAB1_DIVLINEWD, m_Edit_DivisionLineWidth);
	DDX_Control(pDX, IDC_EDIT_TAB1_DIVLINELEN, m_Edit_DivLineLen);
	DDX_Control(pDX, IDC_EDIT_TAB1_DIVISIONS, m_Edit_Divisions);
	DDX_Control(pDX, IDC_EDIT_TAB1_ARCWIDTH, m_Edit_ArcLineWidth);
	DDX_Control(pDX, IDC_EDIT_TAB1_ARCRADIUS, m_Edit_ArcRadius);
	DDX_Control(pDX, IDC_STATIC_TAB_SUBCOLOR, m_Static_SubColor);
	DDX_Control(pDX, IDC_STATIC_TAB1_DIVCOLOR, m_Static_DivColor);
	DDX_Control(pDX, IDC_STATIC_TAB1_ARCCOLOR, m_Static_ArcColor);
	DDX_Control(pDX, IDC_COMBO_TAB1_HOLETYPE, m_Combo_HoleType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleWizTabOne, CDialog)
	//{{AFX_MSG_MAP(CScaleWizTabOne)
	ON_BN_CLICKED(IDC_STATIC_TAB_SUBCOLOR, OnStaticTab1Subcolor)
	ON_BN_CLICKED(IDC_STATIC_TAB1_ARCCOLOR, OnStaticTab1Arccolor)
	ON_BN_CLICKED(IDC_STATIC_TAB1_DIVCOLOR, OnStaticTab1Divcolor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CScaleWizTabOne message handlers

BOOL CScaleWizTabOne::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  
}

void CScaleWizTabOne::OnStaticTab1Subcolor() 
{
	CColorDialog dlg;
	int id = dlg.DoModal();
	if(id == IDOK)
	{
		this->m_Static_SubColor.SetColor(dlg.GetColor());
		GetParent()->GetParent()->PostMessageA(WM_TAB1_MESSAGE,TAB1_SUBCOLOR,dlg.GetColor());
	}
}

void CScaleWizTabOne::OnStaticTab1Arccolor() 
{
	CColorDialog dlg;
	int id = dlg.DoModal();
	if(id == IDOK)
	{
		this->m_Static_ArcColor.SetColor(dlg.GetColor());
		GetParent()->GetParent()->PostMessageA(WM_TAB1_MESSAGE,TAB1_ARCCOLOR,dlg.GetColor());
	}
	
}

void CScaleWizTabOne::OnStaticTab1Divcolor() 
{
	CColorDialog dlg;
	int id = dlg.DoModal();
	if(id == IDOK)
	{
		this->m_Static_DivColor.SetColor(dlg.GetColor());
		GetParent()->GetParent()->PostMessageA(WM_TAB1_MESSAGE,TAB1_DIVCOLOR,dlg.GetColor());
	}
	
}
