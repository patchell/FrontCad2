// StaticPreview.cpp : implementation file
//

#include "stdafx.h"

////////////////////////////////////////////////////
// CStaticPreview

CStaticPreview::CStaticPreview()
{
	m_pLibObj = 0;
	m_Scale = CScale(0.3, 0.3);
}

CStaticPreview::~CStaticPreview()
{
}


BEGIN_MESSAGE_MAP(CStaticPreview, CStatic)
	//{{AFX_MSG_MAP(CStaticPreview)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CStaticPreview message handlers

void CStaticPreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	CBrush br(RGB(255,255,255));


	GetClientRect(&rect);
	rect.NormalizeRect();
	dc.FillRect(&rect,&br);
	CPoint Offset = rect.CenterPoint();
	if(m_pLibObj)
	{
		m_pLibObj->Draw(&dc,ObjectMode::Final,Offset,m_Scale);
	}
	ReleaseDC(&dc);
}

void CStaticPreview::OnLButtonDown(UINT nFlags, CPoint point) 
{
	char *s = new char[256];
	sprintf_s(s, 256, "x=%d y=%d\n", point.x, point.y);
	MessageBox(s,"DEBUG");
	delete[] s;
	CStatic::OnLButtonDown(nFlags, point);
}
