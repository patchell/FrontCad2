// MyEdit.cpp : implementation file
//

#include "stdafx.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{
	m_ObjMsg = UtilMsg::DEFAULT;
	this->m_pW = 0;
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CMyEdit message handlers


BOOL CMyEdit::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_KEYDOWN:
			if(VK_RETURN == pMsg->wParam)
			{
//				CWnd *wC;
//				char *s = new char[256];
//				GetWindowText(s,255);
//				int v = atoi(s);
//				delete s;
				if(m_pW)m_pW->PostMessageA(m_WMsg,m_ObjMsg,0);
//				wC = GetParent()->GetFocus();
//				wC = GetParent()->GetNextDlgTabItem(wC);	//reset the focus
//				wC->SetFocus();

				return TRUE;
			}
			break;
		default:
			return CEdit::PreTranslateMessage(pMsg);
			break;
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CMyEdit::SetupMessaging(CWnd *pWdest, int WMsg, int SubMsg)
{
	m_pW = pWdest;
	this->m_WMsg = WMsg;
	this->m_ObjMsg = SubMsg;
}
