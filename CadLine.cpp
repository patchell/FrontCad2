// CadLine.cpp: implementation of the CCadLine class.
//
///////////////////////////////////////////////

#include "stdafx.h"


///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadLine::CCadLine():CCadObject(OBJECT_TYPE_LINE)
{
	m_pPoly = 0;
}

CCadLine::CCadLine(CCadLine &line):CCadObject(OBJECT_TYPE_LINE)
{
	GetAttributes()->m_LineWidth = 1;
	GetAttributes()->m_LineColor = line.GetAttributes()->m_LineColor;	//black line
	m_pPoly = 0;
	SetP1(line.GetP1());
	SetP2(line.GetP2());
}

CCadLine::~CCadLine()
{
}

CCadObject* CCadLine::Copy()
{
	CCadLine* pNew = new CCadLine(*this);
	return (CCadObject*)pNew;
}

void CCadLine::Draw(CDC *pDC, ObjectMode mode,CPoint O,CScale Scale)
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
	CPen *pOld, penLine, penPoint;
	LOGBRUSH lbMode;
	CBrush brushFill, * pOldB;
	CPoint P1,P2,Diff;
	int Lw;
	CRect rect;

	if (CCadLine::m_RenderEnable)
	{
		P1 = (Scale * GetP1()) + O;
		P2 = (Scale * GetP2()) + O;
		Lw = int(Scale.m_ScaleX * GetAttributes()->m_LineWidth);
		if (Lw < 1) Lw = 1;
		brushFill.CreateSolidBrush(RGB(0,0,255));
		switch (mode)
		{
		case ObjectMode::Final:
			if(CCadObject::AreShapeFillsDisabled())
				lbMode.lbStyle = BS_HOLLOW;
			else
			{
				lbMode.lbStyle = BS_SOLID;
				lbMode.lbColor = GetAttributes()->m_LineColor;
				lbMode.lbHatch = 0;
			}
			penLine.CreatePen(PS_GEOMETRIC | PS_ENDCAP_ROUND | PS_JOIN_ROUND, Lw, &lbMode);
			break;
		case ObjectMode::Selected:
			if (CCadObject::AreShapeFillsDisabled())
				lbMode.lbStyle = BS_HOLLOW;
			else
			{
				lbMode.lbStyle = BS_SOLID;
				lbMode.lbColor = RGB(255,0,0);
				lbMode.lbHatch = 0;
			}
			penLine.CreatePen(PS_GEOMETRIC | PS_ENDCAP_ROUND | PS_JOIN_ROUND, Lw, &lbMode);
			penPoint.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			break;
		case ObjectMode::Sketch:
			penLine.CreatePen(PS_DOT , 1, RGB(0, 0, 255));
			break;
		}
		pOld = pDC->SelectObject(&penLine);
		pOldB = pDC->SelectObject(&brushFill);
		switch (mode)
		{
		case ObjectMode::Final:
			pDC->MoveTo(P1);
			pDC->LineTo(P2);
			break;
		case ObjectMode::Selected:
		case ObjectMode::Sketch:
			pDC->MoveTo(P1);
			pDC->LineTo(P2);
			Diff = CPoint(4, 4);
			rect.SetRect(P1 + (-Diff), P1 + Diff);
			pDC->SelectObject(&penPoint);
			pDC->Rectangle(&rect);
			rect.SetRect(P2 + (-Diff), P2 + Diff);
			pDC->Rectangle(&rect);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOld);
		pDC->SelectObject(pOldB);
	}
}

int CCadLine::CheckSelected(CPoint p,CSize O)
{
	if(m_pPoly == 0)
		m_pPoly = new CCadPolygon();
	else
		m_pPoly->Reset();

	//-----------------------------
	// enclose the line inside
	// of a polygon
	//-----------------------------
	CPoint P1 = GetP1() + O;
	CPoint P2 = GetP2() + O;
	int d = GetAttributes()->m_LineWidth/2;
	if(d < 10) d = 10;
	if((P1.x < P2.x) && (P1.y < P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y+d), TRUE, TRUE);
	}
	else if((P1.x > P2.x) && (P1.y < P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y-d), TRUE, TRUE);
	}
	else if((P1.x < P2.x) && (P1.y > P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y-d), TRUE, TRUE);
	}
	else if((P1.x > P2.x) && (P1.y > P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y+d), TRUE, TRUE);
	}
	else if((P1.x == P2.x)&& (P1.y < P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y+d), TRUE, TRUE);
	}
	else if((P1.x == P2.x)&& (P1.y > P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y-d), TRUE, TRUE);
	}
	else if((P1.x > P2.x)&& (P1.y == P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x+d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x-d,P2.y+d), TRUE, TRUE);
	}
	else if((P1.x < P2.x)&& (P1.y == P2.y))
	{
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y+d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P1.x-d,P1.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y-d), TRUE, TRUE);
		m_pPoly->AddPoint(CPoint(P2.x+d,P2.y+d), TRUE, TRUE);
	}
	return m_pPoly->PointEnclosed(p);
}

Tokens CCadLine::Parse(
	FILE* pIN,
	Tokens LookAHeadToken,
	CCadDrawing** ppDrawing,
	CFileParser* pParser
)
{
	BOOL Loop = TRUE;
	int PointOrder = 0;

	LookAHeadToken = pParser->Expect(Tokens::LINE, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while (Loop)
	{
		switch (LookAHeadToken)
		{
		case Tokens::POINT:
			switch (PointOrder)
			{
			case 0:
				LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP1(), LookAHeadToken);
				PointOrder++;
				break;
			case 1:
				LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP2(), LookAHeadToken);
				PointOrder++;
				break;
			}
			break;
		case Tokens::COLOR:
			LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
			break;
		case Tokens::WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens::POINT_1:
			LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::POINT_2:
			LookAHeadToken = pParser->Point(Tokens::POINT_2, pIN, GetP2(), LookAHeadToken);
			break;
		case Tokens::LINE_COLOR:
			LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
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
	(*ppDrawing)->AddObject(this);
	return LookAHeadToken;
}

void CCadLine::Save(FILE *pO,  int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];

	fprintf(pO, "%s%s(%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::LINE),
		CFileParser::SavePoint(s1,64,Tokens::POINT_1,GetP1()),
		CFileParser::SavePoint(s2, 64, Tokens::POINT_2, GetP2()),
		CFileParser::SaveColor(s3,64, GetAttributes()->m_LineColor, Tokens::LINE_COLOR),
		CFileParser::SaveDecimalValue(s4,64,Tokens::LINE_WIDTH, GetAttributes()->m_LineWidth)
	);
	delete[] s4;
	delete[] s3;
	delete[] s2;
	delete[] s1;
	delete[] s;
}

CCadLine CCadLine::operator=(CCadLine &v)
{
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	GetAttributes()->m_LineColor = v.GetAttributes()->m_LineColor;
	GetAttributes()->m_LineWidth = v.GetAttributes()->m_LineWidth;
	if((m_pPoly == NULL) && (v.m_pPoly != NULL))
		m_pPoly = (CCadPolygon *)v.m_pPoly->Copy();
	return *this;
}

void CCadLine::Move(CPoint p)
{
	CPoint Diff;
	Diff = p - GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
}


int CCadLine::GrabVertex(CPoint point)
{
	int rV = -1;
	CRect rect;
	CPoint p1,p2,p;
	p = CPoint(4,4);
	p1 = GetP1() + p;
	p2 = GetP1() - p;
	rect.SetRect(p1,p2);
	rect.NormalizeRect();
	if(rect.PtInRect(point))
		rV = 0;
	else
	{
		p1 = GetP2() + p;
		p2 = GetP2() - p;
		rect.SetRect(p1,p2);
		rect.NormalizeRect();
		if(rect.PtInRect(point))
			rV = 1;
	}
	return rV;
}

void CCadLine::SetVertex(int Vi, CPoint p)
{
	if(Vi)
	{
		SetP2(p);
	}
	else
		SetP1(p);
}

CPoint CCadLine::GetReference()
{
	return GetP1();
}

void CCadLine::AdjustRefernce(CPoint p)
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

void CCadLine::RenderEnable(int e)
{
	CCadLine::m_RenderEnable = e;
}

CPoint CCadLine::GetCenter()
{
	CPoint Center((GetP1().x + GetP2().x) / 2, (GetP1().y + GetP2().y) / 2);
	return Center;
}

// Moves the center of the object to the spcified point
void CCadLine::ChangeCenter(CSize p)
{
}


CSize CCadLine::GetSize()
{
	return CSize(abs(GetP1().x - GetP2().x), abs(GetP1().y - GetP2().y));
}


void CCadLine::ChangeSize(CSize Sz)
{
	SetP2(GetP2() + Sz);
}
