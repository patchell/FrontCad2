// WizTab2Dialog.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CWizTab2Dialog dialog


CWizTab2Dialog::CWizTab2Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWizTab2Dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizTab2Dialog)
	//}}AFX_DATA_INIT
}


void CWizTab2Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizTab2Dialog)
	DDX_Control(pDX, IDC_CHECK_TAB2_ROTATETEXT, m_CheckBox_RotateText);
	DDX_Control(pDX, IDC_EDIT_TAB2_DISTTOTICK, m_Edit_DistToTick);
	DDX_Control(pDX, IDC_EDIT_TAB2_FONTSIZE, m_Edit_FontSize);
	DDX_Control(pDX, IDC_STATIC_SWTAB2_BKCOLOR, m_Static_BkColor);
	DDX_Control(pDX, IDC_STATIC_SWTAB2_FGCOLOR, m_Static_FgColor);
	DDX_Control(pDX, IDC_STATIC_TAB2_FONT, m_Static_Font);
	DDX_Control(pDX, IDC_COMBO_TAB2_FONTWEIGHT, m_ComboBox_FontWeight);
	DDX_Control(pDX, IDC_STATIC_TAB2_LABLENUMBER, m_Static_FontLable);
	DDX_Control(pDX, IDC_EDIT_TAB2_LABVALUE, m_Edit_Label);
	DDX_Control(pDX, IDC_SCROLLBAR_TAB2_LABSELECT, m_SB_LableSelect);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizTab2Dialog, CDialog)
	//{{AFX_MSG_MAP(CWizTab2Dialog)
	ON_BN_CLICKED(IDC_BUTTON_TAB2_SELFONT, OnButtonTab2Selfont)
	ON_BN_CLICKED(IDC_STATIC_SWTAB2_FGCOLOR, OnStaticSwtab2Fgcolor)
	ON_BN_CLICKED(IDC_STATIC_SWTAB2_BKCOLOR, OnStaticSwtab2Bkcolor)
	ON_BN_CLICKED(IDC_CHECK_TAB2_ROTATETEXT, OnCheckTab2Rotatetext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CWizTab2Dialog message handlers

BOOL CWizTab2Dialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	m_SB_LableSelect.SetDisplayText(&m_Static_FontLable);

	return TRUE;
}

void CWizTab2Dialog::OnButtonTab2Selfont() 
{
	CFontDialog dlg;
	LOGFONT lf;

	int Id = dlg.DoModal();
	if(Id == IDOK)
	{
		dlg.GetCurrentFont(&lf);
		m_Static_Font.SetWindowText(lf.lfFaceName);
		GetParent()->GetParent()->PostMessageA(WM_TAB2_MESSAGE,TAB2_FONT,0);
	}
}

void CWizTab2Dialog::OnStaticSwtab2Fgcolor() 
{
	CColorDialog dlg;
	int id = dlg.DoModal();
	if(id == IDOK)
	{
		this->m_Static_FgColor.SetColor(dlg.GetColor());
		GetParent()->GetParent()->PostMessageA(WM_TAB2_MESSAGE,TAB2_TEXTCOLOR,dlg.GetColor());
	}
}

void CWizTab2Dialog::OnStaticSwtab2Bkcolor() 
{
	CColorDialog dlg;
	int id = dlg.DoModal();
	if(id == IDOK)
	{
		this->m_Static_BkColor.SetColor(dlg.GetColor());
		GetParent()->GetParent()->PostMessageA(WM_TAB2_MESSAGE,TAB2_TEXTBKCOLOR,dlg.GetColor());
	}
	
}

void CWizTab2Dialog::OnCheckTab2Rotatetext() 
{
	int check = this->m_CheckBox_RotateText.GetCheck();
	check ^= 1;
	m_CheckBox_RotateText.SetCheck(check);
}
