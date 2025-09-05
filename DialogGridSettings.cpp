// DialogGridSettings.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CDialogGridSettings dialog


CDialogGridSettings::CDialogGridSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogGridSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogGridSettings)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogGridSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogGridSettings)
	DDX_Control(pDX, IDC_STATIC_GRID_COLOR, m_Static_Color);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_Snap);
	DDX_Control(pDX, IDC_EDIT2, m_Edit_Grid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogGridSettings, CDialog)
	//{{AFX_MSG_MAP(CDialogGridSettings)
	ON_BN_CLICKED(IDC_STATIC_GRID_COLOR, OnStaticGridColor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CDialogGridSettings message handlers

BOOL CDialogGridSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Edit_Grid.SetDecimalPlaces(3);
	m_Edit_Grid.SetValue(m_Grid);
	m_Edit_Snap.SetDecimalPlaces(3);
	m_Edit_Snap.SetValue(m_Snap);

	m_Static_Color.SetColor(m_Color);

	return TRUE; 
}

void CDialogGridSettings::OnOK() 
{
	CWnd *wC;
	//locate control that has gocus
	wC = GetFocus();
	// Get the ID of that control
	int id = wC->GetDlgCtrlID();
	switch(id)							//parse the id
	{
		case IDOK:
			m_Snap = m_Edit_Snap.GetValue();
			m_Grid = m_Edit_Grid.GetValue();
			m_Color = m_Static_Color.GetColor();
			CDialog::OnOK();
			break;
		default:
			wC = GetNextDlgTabItem(wC);	//reset the focus
			wC->SetFocus();
			break;
	}
}

void CDialogGridSettings::OnStaticGridColor() 
{
	CColorDialog dlg;

	if(dlg.DoModal() == IDOK)
	{
		m_Static_Color.SetColor(dlg.GetColor());
	}
}
