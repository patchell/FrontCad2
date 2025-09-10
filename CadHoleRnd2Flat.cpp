// CadHoleRnd2Flat.cpp: implementation of the CCadHoleRnd2Flat class.
//
///////////////////////////////////////////////

#include "stdafx.h"


///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadHoleRnd2Flat::CCadHoleRnd2Flat():CCadObject(OBJECT_TYPE_HOLERND2FLAT)
{
}

CCadHoleRnd2Flat::CCadHoleRnd2Flat(CCadHoleRnd2Flat &h):CCadObject(OBJECT_TYPE_HOLERND2FLAT)
{

	SetP1(h.GetP1());
	SetP2(h.GetP2());
	GetAttributes()->m_FlatDist = h.GetAttributes()->m_FlatDist;
	GetAttributes()->m_LineColor = h.GetAttributes()->m_LineColor;
	GetAttributes()->m_Radius = h.GetAttributes()->m_Radius;
	GetAttributes()->m_LineWidth = h.GetAttributes()->m_LineWidth;
}

CCadHoleRnd2Flat::~CCadHoleRnd2Flat()
{
}

BOOL CCadHoleRnd2Flat::Create(CPoint m_Pos, HoleRnd2FlatAttributes* pHoleRnd2FlatAttributes)
{
	BOOL rV = TRUE;

	SetP1(m_Pos);
	SetP2(m_Pos);
	if (pHoleRnd2FlatAttributes)
		m_atrb.CopyFrom(pHoleRnd2FlatAttributes);
	else
		rV = FALSE;
	return rV;
}

CCadObject* CCadHoleRnd2Flat::Copy()
{
	CCadHoleRnd2Flat* pNew = new CCadHoleRnd2Flat(*this);
	return pNew;
}

void CCadHoleRnd2Flat::AdjustRefernce(CPoint p)
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
}

void CCadHoleRnd2Flat::Draw(CDC *pDC, ObjectMode mode,CPoint Offset,CScale Scale)
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
	CPen* pOld = 0, penLine;
	CBrush* pBrush = 0, brushFill;
	CRect rect;
	int dx = GetAttributes()->m_Radius;
	CPoint start,end;
	CPoint P1,P2;
	int Lw,Fd;
	int Rad;

	if (CCadHoleRnd2Flat::m_RenderEnable)
	{
		P1 = (Scale * GetP1()) + Offset;
		dx = int(Scale.m_ScaleX * dx);
		Rad = dx;
		Lw = int(Scale.m_ScaleX * GetAttributes()->m_LineWidth);
		Fd = int(Scale.m_ScaleX * GetAttributes()->m_FlatDist);
		if (Lw < 1) Lw = 1;

		rect.SetRect(P1.x - dx, P1.y - dx, P1.x + dx, P1.y + dx);
		dx = dx / 2;

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
		brushFill.CreateStockObject(NULL_BRUSH);
		pBrush = pDC->SelectObject(&brushFill);	
		pOld = pDC->SelectObject(&penLine);
		switch (mode)
		{
		case ObjectMode::Final:
		case ObjectMode::Selected:
			[[fallthrough]];
		case ObjectMode::Sketch:
			start.x = P1.x + Fd;
			start.y = int(SolveIntersection(1, P1, Fd, Rad));
			end.x = P1.x - Fd;
			end.y = start.y;
			pDC->Arc(&rect, start, end);
			start.x = P1.x - Fd;
			end.x = P1.x + Fd;
			start.y = int(SolveIntersection(0, P1, Fd, Rad));
			end.y = start.y;
			pDC->Arc(&rect, start, end);
			pDC->MoveTo(P1.x + Fd, int(SolveIntersection(1, P1, Fd, Rad)));
			pDC->LineTo(P1.x + Fd, int(SolveIntersection(0, P1, Fd, Rad)));
			pDC->MoveTo(P1.x - Fd, int(SolveIntersection(1, P1, Fd, Rad)));
			pDC->LineTo(P1.x - Fd, int(SolveIntersection(0, P1, Fd, Rad)));
			pDC->MoveTo(P1.x + dx, P1.y + dx);
			pDC->LineTo(P1.x - dx, P1.y - dx);
			pDC->MoveTo(P1.x - dx, P1.y + dx);
			pDC->LineTo(P1.x + dx, P1.y - dx);
			pDC->SelectObject(pOld);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOld);
		pDC->SelectObject(pBrush);
	}
}

double CCadHoleRnd2Flat::SolveIntersection(int m,CPoint P1,int FlatDist,int Radius)
{
	double Y,T,Xd,R;

	Xd = double(FlatDist);
	R = double(Radius);
	Y = double(P1.y);
	if(m)
		T = Y - sqrt(R*R-Xd*Xd);
	else
		T = Y + sqrt(R*R-Xd*Xd);
	return T;
}


int CCadHoleRnd2Flat::CheckSelected(CPoint p,CSize O)
{
	int dx,dy;
	CPoint P1 = GetP1() + O;
	dx = GetAttributes()->m_FlatDist;
	dy = GetAttributes()->m_Radius;
	CRect rect(P1 + CPoint(-dx,-dy),P1 + CPoint(dx,dy));
	rect.NormalizeRect();
	return rect.PtInRect(p);
}

CCadHoleRnd2Flat CCadHoleRnd2Flat::operator =(CCadHoleRnd2Flat &v)
{
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	GetAttributes()->m_FlatDist = v.GetAttributes()->m_FlatDist;
	GetAttributes()->m_LineColor = v.GetAttributes()->m_LineColor;
	GetAttributes()->m_Radius = v.GetAttributes()->m_Radius;
	GetAttributes()->m_LineWidth = v.GetAttributes()->m_LineWidth;
	return *this;
}

void CCadHoleRnd2Flat::Move(CPoint p)
{
	SetP1(p);
}

Tokens CCadHoleRnd2Flat::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::HOLE_2FLAT, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->DecimalValue(Tokens::RADIUS, pIN, GetAttributes()->m_Radius, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->DecimalValue(Tokens::FLATDIST, pIN, GetAttributes()->m_FlatDist, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
	(*ppDrawing)->AddObjectToEnd(this);
	return LookAHeadToken;
}

void CCadHoleRnd2Flat::Save(FILE* pO, int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];
	char* s5 = new char[64];

	fprintf(pO, "%s%s(%s,%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::HOLE_2FLAT),
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SaveDecimalValue(s2, 64, Tokens::RADIUS, GetAttributes()->m_Radius),
		CFileParser::SaveDecimalValue(s3, 64, Tokens::FLATDIST, GetAttributes()->m_FlatDist),
		CFileParser::SaveColor(s4, 64, GetAttributes()->m_LineColor, Tokens::LINE_COLOR),
		CFileParser::SaveDecimalValue(s5, 64, Tokens::LINE_WIDTH, GetAttributes()->m_LineWidth)
	);
	delete[]s5;
	delete[]s4;
	delete[]s3;
	delete[]s2;
	delete[]s1;
	delete[]s;
}

int CCadHoleRnd2Flat::GrabVertex(CPoint point)
{
	return -1;
}

void CCadHoleRnd2Flat::SetVertex(int Vi, CPoint p)
{

}

CPoint CCadHoleRnd2Flat::GetReference()
{
	return GetP1();
}

CRect CCadHoleRnd2Flat::GetRect()
{
	CRect rect;
	CPoint p1,p2;
	int dx,dy;

	dx = GetAttributes()->m_Radius;
	dy = GetAttributes()->m_Radius;
	rect.SetRect(GetP1() + CPoint(dx, dy), GetP1() + CPoint(-dx, -dy));
	rect.NormalizeRect();
	return rect;
}

void CCadHoleRnd2Flat::RenderEnable(int e)
{
	CCadHoleRnd2Flat::m_RenderEnable = e;
}

CPoint CCadHoleRnd2Flat::GetCenter()
{
	return GetP1();
}

// Moves the center of the object to the spcified point
void CCadHoleRnd2Flat::ChangeCenter(CSize p)
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


CSize CCadHoleRnd2Flat::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadHoleRnd2Flat::ChangeSize(CSize Sz)
{
	GetAttributes()->m_Radius = Sz.cx / 2;
}
