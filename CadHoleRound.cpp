// CadHoleRound.cpp: implementation of the CCadHoleRound class.
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

CCadHoleRound::CCadHoleRound():CCadObject(OBJECT_TYPE_HOLEROUND)
{
	m_VtxGrabSize = 0;
	m_VtxSize2 = 0;
	m_VtxGrabSize2 = 0;
	m_VtxGrabSize = 0;
	m_VtxSize = 0;
	m_HighlightVertex = 0;
	m_GrabVertex = 0;
}

CCadHoleRound::CCadHoleRound(CCadHoleRound &h):CCadObject(OBJECT_TYPE_HOLEROUND)
{
	SetP1(h.GetP1());
	SetP2(h.GetP2());
	GetAttributes()->m_LineColor = h.GetAttributes()->m_LineColor;
	GetAttributes()->m_Radius = h.GetAttributes()->m_Radius;
	GetAttributes()->m_LineWidth = h.GetAttributes()->m_LineWidth;
}

CCadHoleRound::~CCadHoleRound()
{
}

BOOL CCadHoleRound::Create(CPoint m_Pos, HoleRoundAttributes* pHoleRoundAttributes)
{
	BOOL rV = TRUE;

	SetP1(m_Pos);
	SetP2(m_Pos);
	if (pHoleRoundAttributes)
		m_atrb.CopyFrom(pHoleRoundAttributes);
	else
		rV = FALSE;
    return rV;
}

CCadObject* CCadHoleRound::Copy()
{
	CCadHoleRound* pNew = new CCadHoleRound(*this);
	return (CCadObject*)pNew;
}

void CCadHoleRound::Draw(CDC *pDC, ObjectMode mode,CPoint O,CScale Scale)
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
	CRect rect;
	int dx = GetAttributes()->m_Radius;
	CPoint start;
	CPoint P1,P2;
	int Lw;

	if (CCadHoleRound::m_RenderEnable)
	{
		brushFill.CreateSolidBrush(RGB(255, 255, 255));
		P1 = Scale * GetP1() + O;
		dx = int(Scale.m_ScaleX * dx);
		Lw = int(Scale.m_ScaleX * GetAttributes()->m_LineWidth);
		if (Lw < 1) Lw = 1;

		rect.SetRect(P1 + CPoint(-dx, -dx), P1 + CPoint(dx, dx));
		start = P1 + CPoint(dx, 0);
		dx = dx / 2;

		switch (mode)
		{
		case ObjectMode::Final:
			penLine.CreatePen(PS_SOLID, Lw, GetAttributes()->m_LineColor);
			break;
		case ObjectMode::Selected:
			penLine.CreatePen(PS_SOLID, Lw, RGB(0, 255, 0));
			break;
		case ObjectMode::Sketch:
			penLine.CreatePen(PS_SOLID, 1, GetAttributes()->m_LineColor);
			break;
		}
		pOld = pDC->SelectObject(&penLine);
		pOldBrush = pDC->SelectObject(&brushFill);
		switch (mode)
		{
		case ObjectMode::Final:
		case ObjectMode::Selected:
		case ObjectMode::Sketch:
			pDC->Ellipse(&rect);
			pDC->MoveTo(P1 + CPoint(dx, dx));
			pDC->LineTo(P1 + CPoint(-dx, -dx));
			pDC->MoveTo(P1 + CPoint(-dx, dx));
			pDC->LineTo(P1 + CPoint(dx, -dx));
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOld);
		pDC->SelectObject(pOldBrush);
	}
}

int CCadHoleRound::CheckSelected(CPoint p,CSize O)
{
	double a,b,xo,yo,v;
	int rV;
	static int count = 0;

	CPoint P1 = GetP1() + O;
	a = double(GetAttributes()->m_Radius);
	b = double(GetAttributes()->m_Radius);
	xo = double(p.x) - double(P1.x);
	yo = double(p.y) - double(P1.y);
	v = (xo * xo)/(a * a) + (yo * yo)/(b * b);
	if( v < 1.0) rV = TRUE;
	else rV = FALSE;
	return rV;
}


CCadHoleRound CCadHoleRound::operator=(CCadHoleRound &v)
{
	CCadHoleRound Hole;

	Hole.SetP1(v.GetP1());
	Hole.SetP2(v.GetP2());
	Hole.GetAttributes()->CopyFrom(v.GetAttributes());
	return Hole;
}

void CCadHoleRound::Move(CPoint p)
{
	SetP1(p);
}

Tokens CCadHoleRound::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	BOOL Loop = TRUE;

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::HOLERND, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while (Loop)
	{
		switch (LookAHeadToken)
		{
		case Tokens::POINT:
			LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::POINT_1:
			LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::RADIUS:
			LookAHeadToken = pParser->DecimalValue(Tokens::RADIUS, pIN, GetAttributes()->m_Radius, LookAHeadToken);
			break;
		case Tokens::COLOR:
			LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
			break;
		case Tokens::LINE_COLOR:
			LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
			break;
		case Tokens::WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens::LINE_WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens(','):
			LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
			break;
		case Tokens(')'):
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
			Loop = FALSE;
			break;
		default:
			sprintf_s(Exception.ErrorString, 256, "Syntax Error:Line %d Col %d  UnExpected Token %s\n",
				pParser->GetLine(),
				pParser->GetCol(),
				CFileParser::LookupKeyword(LookAHeadToken)
			);
			throw Exception;
			break;
		}
	}
	(*ppDrawing)->AddObjectToEnd(this);
	return LookAHeadToken;
}

void CCadHoleRound::Save(FILE* pO, int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];

	fprintf(pO, "%s%s(%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::HOLERND),
		CFileParser::SavePoint(s1,64,Tokens::POINT_1,GetP1()),
		CFileParser::SaveDecimalValue(s2,64,Tokens::RADIUS, GetAttributes()->m_Radius),
		CFileParser::SaveColor(s3,64, GetAttributes()->m_LineColor,Tokens::LINE_COLOR),
		CFileParser::SaveDecimalValue(s4,64,Tokens::LINE_WIDTH, GetAttributes()->m_LineWidth)
	);
	delete[]s4;
	delete[]s3;
	delete[]s2;
	delete[]s1;
	delete[]s;
}

int CCadHoleRound::GrabVertex(CPoint point)
{
	return -1;
}

void CCadHoleRound::SetVertex(int Vi, CPoint p)
{

}

CPoint CCadHoleRound::GetReference()
{
	return GetP1();
}

void CCadHoleRound::AdjustRefernce(CPoint p)
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

CRect CCadHoleRound::GetRect()
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

void CCadHoleRound::RenderEnable(int e)
{
	CCadHoleRound::m_RenderEnable = e;
}

CPoint CCadHoleRound::GetCenter()
{
	return GetP1();
}

// Moves the center of the object to the spcified point
void CCadHoleRound::ChangeCenter(CSize p)
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


CSize CCadHoleRound::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadHoleRound::ChangeSize(CSize Sz)
{
	GetAttributes()->m_Radius = Sz.cx / 2;
}
