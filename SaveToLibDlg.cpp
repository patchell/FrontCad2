// SaveToLibDlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CSaveToLibDlg dialog


CSaveToLibDlg::CSaveToLibDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveToLibDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSaveToLibDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSaveToLibDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveToLibDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSaveToLibDlg, CDialog)
	//{{AFX_MSG_MAP(CSaveToLibDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CSaveToLibDlg message handlers

void CSaveToLibDlg::OnOK() 
{
	CDialog::OnOK();
}

BOOL CSaveToLibDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	return TRUE;  
}
