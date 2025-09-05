// WizTab3Dialog.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CWizTab3Dialog dialog


CWizTab3Dialog::CWizTab3Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWizTab3Dialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizTab3Dialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWizTab3Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizTab3Dialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWizTab3Dialog, CDialog)
	//{{AFX_MSG_MAP(CWizTab3Dialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CWizTab3Dialog message handlers
