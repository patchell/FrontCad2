// StaticBitmap.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CStaticBitmap

CStaticBitmap::CStaticBitmap()
{
	m_Color = RGB(0,0,0);
	m_Msg = 0;
	m_WMsg = 0;
	m_pMaster = 0;
}

CStaticBitmap::~CStaticBitmap()
{
}


BEGIN_MESSAGE_MAP(CStaticBitmap, CStatic)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CStaticBitmap message handlers

void CStaticBitmap::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);
	CBrush br;
	br.CreateSolidBrush(m_Color);
	dc.FillRect(&rect,&br);
}

void CStaticBitmap::SetMsgValue(int m)
{
	m_Msg = m;
}

void CStaticBitmap::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	if(m_pMaster) m_pMaster->PostMessageA(WM_UTILMESSAGE,m_Msg);
	CStatic::OnLButtonDown(nFlags, point);
}

void CStaticBitmap::SendChange()
{
	if(m_pMaster) m_pMaster->PostMessageA(m_WMsg,m_Msg,m_Color);

}

void CStaticBitmap::SetupMessaging(CWnd *pW, int Wmsg, int Smsg)
{
	this->m_pMaster = pW;
	this->m_WMsg = Wmsg;
	this->m_Msg = Smsg;
}
