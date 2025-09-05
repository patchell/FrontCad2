// MyComboBox.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CMyComboBox

CMyComboBox::CMyComboBox()
{
	m_pW = 0;
}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	//{{AFX_MSG_MAP(CMyComboBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CMyComboBox message handlers

BOOL CMyComboBox::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_KEYDOWN:
			if(VK_RETURN == pMsg->wParam)
			{
				CWnd *wC;
				int v = GetCurSel();
				if(m_pW)m_pW->PostMessageA(m_WMsg,m_ObjMsg,v);
				wC = GetParent()->GetFocus();
				wC = GetParent()->GetNextDlgTabItem(wC);	//reset the focus
				wC->SetFocus();

				return TRUE;
			}
			break;
		default:
			return CComboBox::PreTranslateMessage(pMsg);
			break;
	}
	
	return CComboBox::PreTranslateMessage(pMsg);
}
