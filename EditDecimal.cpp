// EditDecimal.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CEditDecimal

CEditDecimal::CEditDecimal()
{
	m_pW = 0;
}

CEditDecimal::~CEditDecimal()
{
}


BEGIN_MESSAGE_MAP(CEditDecimal, CEdit)
	//{{AFX_MSG_MAP(CEditDecimal)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CEditDecimal message handlers

BOOL CEditDecimal::PreTranslateMessage(MSG* pMsg) 
{
	switch(pMsg->message)
	{
		case WM_KEYDOWN:
			if(VK_RETURN == pMsg->wParam)
			{
				CWnd *wC;
				int v = GetValue();
				if(m_pW)m_pW->PostMessageA(m_WMsg,m_ObjMsg,v);
				wC = GetParent()->GetFocus();
				wC = GetParent()->GetNextDlgTabItem(wC);	//reset the focus
				wC->SetFocus();

				return TRUE;
			}
			break;
		default:
			return CEdit::PreTranslateMessage(pMsg);
			break;
	}
	return CEdit::PreTranslateMessage(pMsg);
}

void CEditDecimal::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

int CEditDecimal::GetValue()
{
	char *s = new char[256];
	char *pP;
	int ipart,fpart,mult;
	GetWindowText(s,255);
	if((pP = strrchr(s,'.')) != NULL)
	{
		*pP = 0;
		++pP;
		int l = strlen(pP);
		if(l == m_DecimalPlaces)
			fpart = atoi(pP);
		else if(l > m_DecimalPlaces)
		{
			fpart = atoi(pP);
			for(int i=0;i<(l - m_DecimalPlaces);++i)
				fpart /= 10;
		}
		else
		{
			fpart = atoi(pP);
			for(int i=0;i<(m_DecimalPlaces - l);++i)
				fpart *= 10;
		}
	}
	else
		fpart = 0;
	int i;
	for(i=0,mult=1;i<this->m_DecimalPlaces;++i)
		mult *= 10;
	ipart = atoi(s) * mult + fpart;
	delete[] s;
	return ipart;
}

void CEditDecimal::SetValue(int v)
{
	int Div=1;
	int i;
	for(i=0;i<m_DecimalPlaces;++i)
		Div *= 10;
	int intpart,decpart;
	intpart = v/Div;
	decpart = v%Div;
	char *s = new char[256];
	char *sd = new char[256];
	for(i=m_DecimalPlaces-1;i>=0;--i)
	{
		sd[i] = '0' + decpart % 10;
		decpart /= 10;
	}
	sd[m_DecimalPlaces] = 0;
	if (m_DecimalPlaces)
		sprintf_s(s,256, "%d.%s", intpart, sd);
	else
		sprintf_s(s,256, "%d", intpart);
	SetWindowText(s);
	delete[] s;
	delete[] sd;
}

int CEditDecimal::GetDecimalPlaces()
{
	return m_DecimalPlaces;
}

void CEditDecimal::SetDecimalPlaces(int p)
{
	m_DecimalPlaces = p;
}

void CEditDecimal::SetupMessaging(CWnd *pWdest, int WMsg, int SubMsg)
{
	m_pW = pWdest;
	this->m_WMsg = WMsg;
	this->m_ObjMsg = SubMsg;
}
