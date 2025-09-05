// Scale.h: interface for the CScale class.
//
///////////////////////////////////////////////

#pragma once

class CScale  
{
public:
	double m_ScaleX;
	double m_ScaleY;
	CScale() {
		m_ScaleX = 0;
		m_ScaleY = 0;
	};
	CScale(double x,double y);
	virtual ~CScale();
	CPoint operator*(CPoint p);
	CSize operator*(CSize& sz);
};
