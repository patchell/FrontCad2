// ComboBoxPrintRect.cpp : implementation file
//

#include "stdafx.h"



// CComboBoxPrintRect

IMPLEMENT_DYNAMIC(CComboBoxPrintRect, CComboBox)

CComboBoxPrintRect::CComboBoxPrintRect()
{
	m_pW = 0;
	m_WMsg = 0;	//window message
	m_ObjMsg = 0;	//sub message
}

CComboBoxPrintRect::~CComboBoxPrintRect()
{
}


BEGIN_MESSAGE_MAP(CComboBoxPrintRect, CComboBox)
	ON_CONTROL_REFLECT(CBN_SELCHANGE, &CComboBoxPrintRect::OnCbnSelchange)
END_MESSAGE_MAP()



// CComboBoxPrintRect message handlers




void CComboBoxPrintRect::OnCbnSelchange()
{
	int v = GetCurSel();
	if (m_pW)m_pW->PostMessageA(m_WMsg, m_ObjMsg, v);
}

BOOL CComboBoxPrintRect::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		if (VK_RETURN == pMsg->wParam)
		{
			CWnd *wC;
			int v = GetCurSel();
			if (m_pW)m_pW->PostMessageA(m_WMsg, m_ObjMsg, v);
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

void CComboBoxPrintRect::SetupMessaging(CWnd *pW, int Wmsg, int Smsg)
{
	m_pW = pW;
	m_WMsg = Wmsg;	//window message
	m_ObjMsg = Smsg;	//sub message
}

void CComboBoxPrintRect::SetPrintRect(int w)
{
	CComboBox::SetCurSel(w);
}

static const char * const PRINTRECTstrings[4] = {
	"11 x 8.5",
	"14 x 8.5",
	"8.5 X 11",
	"8.5 X 14"
};

void CComboBoxPrintRect::Init()
{
	static int semaphore = 0;

	if (!semaphore)
	{
		++semaphore;
		for (int i = 0; i < 4; ++i)
			this->InsertString(i, PRINTRECTstrings[i]);
		SetCurSel(0);
	}
}

int CComboBoxPrintRect::GetPrintRect()
{
	int v = GetCurSel();
	return v;
}

CSize CComboBoxPrintRect::GetPrintRectSize()
{
	int v;
	CSize rV;

	v = GetCurSel();
	switch (v)
	{
	case PRINTRECT_11x85:
		rV.SetSize(8500,11000);
		break;
	case PRINTRECT_14x85:
		rV.SetSize(8500, 14000);
		break;
	case PRINTRECT_85x11:
		rV.SetSize(11000, 8500);
		break;
	case PRINTRECT_85x14:
		rV.SetSize(14000, 8500);
		break;
	}
	return rV;
}