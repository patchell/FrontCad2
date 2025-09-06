// CadRectHole.cpp: implementation of the CCadRectHole class.
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

CCadRectHole::CCadRectHole():CCadObject(OBJECT_TYPE_HOLERECT)
{
}


CCadRectHole::CCadRectHole(CCadRectHole &r):CCadObject(OBJECT_TYPE_HOLERECT)
{
	GetAttributes()->m_LineColor = r.GetAttributes()->m_LineColor;
	GetAttributes()->m_LineWidth = r.GetAttributes()->m_LineWidth;
	SetP1(r.GetP1());
	SetP2(r.GetP2());
	GetAttributes()->m_W = r.GetAttributes()->m_W;
	GetAttributes()->m_H = r.GetAttributes()->m_H;
}

CCadRectHole::~CCadRectHole()
{
}

CCadObject* CCadRectHole::Copy()
{
	CCadRectHole* pNew = new CCadRectHole(*this);
	return (CCadObject*)pNew;
}

void CCadRectHole::Draw(CDC *pDC, ObjectMode mode,CPoint Offset,CScale Scale)
{
	//---------------------------------------------
	//	Draw
	//		This function draws the object onto the
	//	specified device context.
	//
	// parameters:
	//		pDC......pointer to the device context
	//		mode.....mode to use when drawing
	//		Offset...Offset to add to points
	//		Scale....Sets Units to Pixels ratio
	//---------------------------------------------
	CPen *pOld = 0, penLine;
	CBrush* pOldBrush = 0, brushFill;
	int dx,dy;
	CPoint P1,P2;
	CRect rectHole;
	int Lw;

	if (CCadRectHole::m_RenderEnable)
	{
		P1 = Scale * GetP1() + Offset;
		P2 = Scale * GetP2() + Offset;
		dx = int((Scale.m_ScaleX * GetAttributes()->m_W) / 2.0);
		dy = int((Scale.m_ScaleY * GetAttributes()->m_H) / 2.0);
		rectHole.SetRect(P1 + CPoint(-dx, -dy), P1 + CPoint(dx, dy));
		rectHole.NormalizeRect();
		Lw = int(GetAttributes()->m_LineWidth * Scale.m_ScaleX);
		if (Lw < 1) Lw = 1;

		switch (mode)
		{
		case ObjectMode::Final:
			penLine.CreatePen(PS_SOLID, Lw, GetAttributes()->m_LineColor);
			break;
		case ObjectMode::Selected:
			penLine.CreatePen(PS_SOLID, Lw, RGB(0, 250, 0));
			break;
		case ObjectMode::Sketch:
			penLine.CreatePen(PS_SOLID, 1, GetAttributes()->m_LineColor);
			break;
		}
		brushFill.CreateSolidBrush(RGB(255,255,255));
		pOld = pDC->SelectObject(&penLine);
		pOldBrush = (CBrush*)pDC->SelectObject(&brushFill);	
		switch (mode)
		{
		case ObjectMode::Final:
		case ObjectMode::Selected:
		case ObjectMode::Sketch:
			pDC->Rectangle(&rectHole);
			dx /= 2;
			dy /= 2;
			pDC->MoveTo(P1 + CPoint(dx, dy));
			pDC->LineTo(P1 + CPoint(-dx, -dy));
			pDC->MoveTo(P1 + CPoint(-dx, dy));
			pDC->LineTo(P1 + CPoint(dx, -dy));
			pDC->SelectObject(pOld);
			pDC->SelectObject(pOldBrush);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOld);
		pDC->SelectObject(pOldBrush);	
	}
}

int CCadRectHole::CheckSelected(CPoint p,CSize O)
{
	int dx,dy;
	dx = GetAttributes()->m_W/2;
	dy = GetAttributes()->m_H/2;
	CPoint P1 = GetP1() + O;
	CRect rect(P1 + CPoint(-dx,-dy),P1 + CPoint(dx,dy));
	rect.NormalizeRect();
	return rect.PtInRect(p);
}

CCadRectHole CCadRectHole::operator=(CCadRectHole &v)
{
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	GetAttributes()->m_H = v.GetAttributes()->m_H;
	GetAttributes()->m_W = v.GetAttributes()->m_W;
	GetAttributes()->m_LineColor = v.GetAttributes()->m_LineColor;
	GetAttributes()->m_LineWidth = v.GetAttributes()->m_LineWidth;
	return *this;
}


void CCadRectHole::Move(CPoint p)
{
	SetP1(p);
}

Tokens CCadRectHole::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	LookAHeadToken = pParser->Expect(Tokens::HOLERECT, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->DecimalValue(Tokens::RECTWIDTH, pIN, GetAttributes()->m_W, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->DecimalValue(Tokens::RECTHIEGHT, pIN, GetAttributes()->m_H, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
	(*ppDrawing)->AddObject(this);
	return LookAHeadToken;
}

void CCadRectHole::Save(FILE* pO, int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];
	char* s5 = new char[64];

	fprintf(pO, "%sHOLERECT(%s,%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SaveDecimalValue(s2, 64, Tokens::RECTWIDTH, GetAttributes()->m_W),
		CFileParser::SaveDecimalValue(s3, 64, Tokens::RECTHIEGHT, GetAttributes()->m_H),
		CFileParser::SaveColor(s4, 64, GetAttributes()->m_LineColor, Tokens::LINE_COLOR),
		CFileParser::SaveDecimalValue(s5,64,Tokens::LINE_WIDTH, GetAttributes()->m_LineWidth)
	);
	delete[] s5;
	delete[] s4;
	delete[] s3;
	delete[] s2;
	delete[] s1;
	delete[] s;
}

int CCadRectHole::GrabVertex(CPoint point)
{
	int rV = -1;
	return rV;
}

void CCadRectHole::SetVertex(int Vi, CPoint p)
{

}

CPoint CCadRectHole::GetReference()
{
	return GetP1();
}

void CCadRectHole::AdjustRefernce(CPoint p)
{
	//-----------------------------------------
	//	AdjustRefernce
	//		Thhis function is used to normalize
	//	the location of points in the object
	// relative to a point choseen on the
	// drawing.
	//	parameters:
	//		p.....selected reference point
	//-----------------------------------------
	SetP1(GetP1() - p);
	SetP2(GetP2() - p);
}


CRect CCadRectHole::GetRect()
{
	CRect rect;
	CPoint p1,p2;
	int dx,dy;

	dx = GetAttributes()->m_W/2;
	dy = GetAttributes()->m_H/2;
	rect.SetRect(GetP1() + CPoint(dx, dy), GetP1() + CPoint(-dx, -dy));
	rect.NormalizeRect();
	return rect;
}

void CCadRectHole::RenderEnable(int e)
{
	CCadRectHole::m_RenderEnable = e;
}

CPoint CCadRectHole::GetCenter()
{
	return GetP1();
}

CPoint CCadRectHole::GetLowerRightPoint()
{
	CPoint pointCenter, pointLR;
	int cx, cy;
	
	pointCenter = GetP1();
	cx = GetAttributes()->m_W / 2;
	cy = GetAttributes()->m_H / 2;
	pointLR = pointCenter + CSize(cx, cy);
	return pointLR;
}

CPoint CCadRectHole::GetUpperLeftPoint()
{
	CPoint pointCenter, pointUL;
	int cx, cy;

	pointCenter = GetP1();
	cx = GetAttributes()->m_W / 2;
	cy = GetAttributes()->m_H / 2;
	pointUL = pointCenter + CSize(-cx, -cy);
	return pointUL;
}


int CCadRectHole::GetTop()
{
	int h, rV;
	CPoint pointCenter;

	pointCenter = GetP1();
	h = GetAttributes()->m_H / 2;
	rV = pointCenter.y - h;
	return rV;
}

int CCadRectHole::GetBottom()
{
	int h, rV;
	CPoint pointCenter;

	pointCenter = GetP1();
	h = GetAttributes()->m_H / 2;
	rV = pointCenter.y + h;
	return rV;
}

int CCadRectHole::GetLeft()
{
	int w, rV;
	CPoint pointCenter;

	pointCenter = GetP1();
	w = GetAttributes()->m_W / 2;
	rV = pointCenter.x - w;
	return rV;
}

int CCadRectHole::GetRight()
{
	int w, rV;
	CPoint pointCenter;

	pointCenter = GetP1();
	w = GetAttributes()->m_W / 2;
	rV = pointCenter.x + w;
	return rV;
}

// Moves the center of the object to the spcified point
void CCadRectHole::ChangeCenter(CSize p)
{
	//-----------------------------------------
	//	ChangeCenter
	//		Thhis function is used to normalize
	//	the location of points in the object
	// relative to a point choseen on the
	// drawing.
	//	parameters:
	//		p.....selected reference point
	//-----------------------------------------
	SetP1(GetP1() - p);
}


CSize CCadRectHole::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadRectHole::ChangeSize(CSize Sz)
{
	SetP2(GetP2() + Sz);
}

