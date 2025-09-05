// ComboBoxHoleType.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static int HT[4] = {
	OBJECT_TYPE_HOLEROUND,
	OBJECT_TYPE_HOLERECT,	
	OBJECT_TYPE_HOLERND1FLAT,
	OBJECT_TYPE_HOLERND2FLAT
};

static const char *HTstrings [4] = {
	"Round",
	"Rectangle",
	"Round 1 Flat",
	"Round 2 Flat"
};

////////////////////////////////////////////////////
// CComboBoxHoleType

CComboBoxHoleType::CComboBoxHoleType()
{
}

CComboBoxHoleType::~CComboBoxHoleType()
{
}


BEGIN_MESSAGE_MAP(CComboBoxHoleType, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxHoleType)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CComboBoxHoleType message handlers

BOOL CComboBoxHoleType::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_KEYDOWN:
			if(VK_RETURN == pMsg->wParam)
			{
				CWnd *wC;
				int v = GetCurSel();
				if(m_pW)m_pW->PostMessageA(m_WMsg,m_ObjMsg,HT[v]);
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

void CComboBoxHoleType::Init()
{
	for(int i=0;i<4;++i)
		InsertString(i,HTstrings[i]);
	SetCurSel(0);
}

void CComboBoxHoleType::SetupMessaging(CWnd *pW, int Wmsg, int Smsg)
{
	this->m_pW = pW;
	this->m_WMsg = Wmsg;	//window message
	this->m_ObjMsg = Smsg;	//sub message
}
