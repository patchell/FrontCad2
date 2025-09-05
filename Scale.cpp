// Scale.cpp: implementation of the CScale class.
//
///////////////////////////////////////////////

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CScale::CScale(double x,double y)
{
	m_ScaleX = x;
	m_ScaleY = y;
}

CScale::~CScale()
{

}


CPoint CScale::operator*(CPoint p)
{
	CPoint rP;
	rP.x = (int)(p.x * m_ScaleX);
	rP.y = (int)(p.y * m_ScaleY);
	return rP;
}

CSize CScale::operator*(CSize& sz)
{
	CSize rS;

	rS.cx = (int)(sz.cx * m_ScaleX);
	rS.cy = (int)(sz.cy * m_ScaleY);
	return rS;
}

