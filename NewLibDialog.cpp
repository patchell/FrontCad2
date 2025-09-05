// NewLibDialog.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CNewLibDialog dialog


CNewLibDialog::CNewLibDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CNewLibDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewLibDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pCaption = 0;
}


void CNewLibDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewLibDialog)
	DDX_Control(pDX, IDC_EDIT_NEWLIB_NAME, m_Edit_LibName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewLibDialog, CDialog)
	//{{AFX_MSG_MAP(CNewLibDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CNewLibDialog message handlers

void CNewLibDialog::OnOK() 
{
	m_Edit_LibName.GetWindowText(this->m_LibName,255);	
	CDialog::OnOK();
}

BOOL CNewLibDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_Edit_LibName.SetWindowText("New Library");
	if(m_pCaption)SetWindowText(m_pCaption);
	return TRUE;
}
