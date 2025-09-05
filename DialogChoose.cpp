// DialogChoose.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CDialogChoose dialog


CDialogChoose::CDialogChoose(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogChoose::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogChoose)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogChoose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogChoose)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogChoose, CDialog)
	//{{AFX_MSG_MAP(CDialogChoose)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_CREATE, OnButtonChooseCreate)
	ON_BN_CLICKED(IDC_BUTTON_CHOOSE_LOADLIB, OnButtonChooseLoadlib)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CDialogChoose message handlers

void CDialogChoose::OnButtonChooseCreate() 
{
	CWnd *pW = this->GetFocus();
	this->EndDialog(pW->GetDlgCtrlID());
}

void CDialogChoose::OnButtonChooseLoadlib() 
{
	CWnd *pW = this->GetFocus();
	this->EndDialog(pW->GetDlgCtrlID());
}
