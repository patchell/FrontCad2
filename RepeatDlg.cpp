// RepeatDlg.cpp : implementation file
//

#include "stdafx.h"


// CRepeatDlg dialog

IMPLEMENT_DYNAMIC(CRepeatDlg, CDialog)

CRepeatDlg::CRepeatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_REPEAT, pParent)
{

	m_Xinc = 0;
	m_Yinc = 0;
	m_RepeatCountX = 0;
	m_RepeatCountY = 0;
}

CRepeatDlg::~CRepeatDlg()
{
}

void CRepeatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_REPEAT_REPEATS, m_Edit_RepeatsX);
	DDX_Control(pDX, IDC_EDIT_REPEAT_YCOUNT, m_Edit_RepeatsY);
	DDX_Control(pDX, IDC_EDIT_REPEAT_X, m_Edit_Xinc);
	DDX_Control(pDX, IDC_EDIT_REPEAT_Y, m_Edit_Yinc);
}


BEGIN_MESSAGE_MAP(CRepeatDlg, CDialog)
END_MESSAGE_MAP()


// CRepeatDlg message handlers


BOOL CRepeatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Edit_Xinc.SetDecimalPlaces(3);
	m_Edit_Yinc.SetDecimalPlaces(3);
	m_Edit_Xinc.SetValue(m_Xinc);
	m_Edit_Yinc.SetValue(m_Yinc);
	m_Edit_RepeatsX.SetDecimalPlaces(0);
	m_Edit_RepeatsY.SetDecimalPlaces(0);
	m_Edit_RepeatsX.SetValue(m_RepeatCountX);
	m_Edit_RepeatsY.SetValue(m_RepeatCountY);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CRepeatDlg::OnOK()
{
	CWnd *wC;
	// locate control that has gocus
	wC = GetFocus();
	// Get the ID of that control
	int id = wC->GetDlgCtrlID();
	switch (id)							//parse the id
	{
	case IDOK:
		m_Xinc = m_Edit_Xinc.GetValue();
		m_Yinc = m_Edit_Yinc.GetValue();
		m_RepeatCountX = m_Edit_RepeatsX.GetValue();
		m_RepeatCountY = m_Edit_RepeatsY.GetValue();
		CDialog::OnOK();
		break;
	default:
		wC = GetNextDlgTabItem(wC);	//reset the focus
		wC->SetFocus();
		break;
	}
}
