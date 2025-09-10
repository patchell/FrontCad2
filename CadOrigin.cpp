#include "stdafx.h"

CCadOrigin::CCadOrigin() :CCadObject(OBJECT_TYPE_ORIGIN)
{
	m_pMainView = 0;
}

CCadOrigin::CCadOrigin(CCadOrigin &v) : CCadObject(OBJECT_TYPE_ORIGIN)
{
	m_pMainView = 0;
	m_Atrib.m_LineWidth = v.GetAttributes()->m_LineWidth;
	m_Atrib.m_Color = v.m_Atrib.m_Color;
	SetP1(v.GetP1());
}

CCadOrigin::~CCadOrigin()
{
}

BOOL CCadOrigin::Create(CPoint m_Pos, OriginAttrib* pAttributes)
{
	BOOL rV = TRUE;

	SetP1(m_Pos);
	SetP2(m_Pos);
	if (pAttributes)
		m_Atrib.CopyFrom(pAttributes);
	else
		rV = FALSE;
    return rV;
}

CCadObject* CCadOrigin::Copy()
{
	CCadOrigin* pO = new CCadOrigin(*this);
	return pO;
}

void CCadOrigin::Move(CPoint p)
{
	SetP1(p);
}

Tokens CCadOrigin::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	BOOL Loop = TRUE;

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::ORG, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while(Loop)
	{
		switch(LookAHeadToken)
		{
		case Tokens::POINT:
			LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::POINT_1:
			LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::LINE_COLOR:
			LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, GetAttributes()->m_Color, LookAHeadToken);
			break;
		case Tokens::COLOR:
			LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, GetAttributes()->m_Color, LookAHeadToken);
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

void CCadOrigin::Save(FILE *pO,  int Indent)
{
	char *s = new char[256];
	char* s1 = new char[64];

	fprintf(pO, "%s%s(%s)\n", 
		theApp.IndentString(s,256,Indent),
		CFileParser::LookupKeyword(Tokens::ORG),
		CFileParser::SavePoint(s1,64,Tokens::POINT_1,GetP1())
	);
	delete[] s1;
	delete[] s;
}

void CCadOrigin::Draw(CDC *pDC, ObjectMode mode, CPoint Offset, CScale Scale)
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
	CRect rect;
	CPoint P1, P2;
	int Lw;

	if (CCadOrigin::m_RenderEnable)
	{
		P1 = (Scale * GetP1()) + Offset + CSize(10, 10);
		P2 = (Scale * GetP1()) + Offset - CSize(10, 10);
		Lw = int(Scale.m_ScaleX * m_Atrib.m_LineWidth);
		if (Lw < 1) Lw = 1;
		rect.SetRect(P1, P2);
		rect.NormalizeRect();
		pOld = pDC->SelectObject(&penLine);
		switch (mode)
		{
		case ObjectMode::Final:
			penLine.CreatePen(PS_SOLID, Lw, m_Atrib.m_Color);
			break;
		case ObjectMode::Selected:
			penLine.CreatePen(PS_SOLID, Lw, RGB(0, 255, 50));
			break;
		case ObjectMode::Sketch:
			penLine.CreatePen(PS_DOT, 1, RGB(0, 0, 255));
			break;
		}
		switch (mode)
		{
		case ObjectMode::Final:
		case ObjectMode::Selected:
		case ObjectMode::Sketch:
			pDC->Ellipse(&rect);
			P1 = (Scale * GetP1()) + Offset;
			pDC->MoveTo(P1.x, P1.y + 15);
			pDC->LineTo(P1.x, P1.y - 15);
			pDC->MoveTo(P1.x + 15, P1.y);
			pDC->LineTo(P1.x - 15, P1.y);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOld);
	}
}

int CCadOrigin::CheckSelected(CPoint p,CSize O)
{
	int rV = 0;
	CRect rect;
	CPoint P1, P2;
	P1 = GetP1() + O;
	P2 = GetP1() + O;
	P1 += CSize(100, 100);
	P2 -= CSize(100, 100);
	rect.SetRect(P1, P2);
	rect.NormalizeRect();
	rV = rect.PtInRect(p);
	return rV;
}

CPoint CCadOrigin::GetReference()
{
	return GetP1();
}

void CCadOrigin::AdjustRefernce(CPoint Ref)
{
	SetP1(GetP1() - Ref);
	if (m_pMainView) m_pMainView->PostMessageA(WM_UPDATEDIMENSIONS);
}

CRect CCadOrigin::GetRect(void)
{
	CRect rR;
	CPoint P1, P2;
	P1 = GetP1() + CSize(100, 100);
	P2 = GetP1() - CSize(100, 100);
	rR.SetRect(P1, P2);
	rR.NormalizeRect();
	return rR;
}

void CCadOrigin::RenderEnable(int e)
{
	CCadOrigin::m_RenderEnable = e;
}

CPoint CCadOrigin::GetCenter()
{
	return GetP1();
}

// Moves the center of the object to the spcified point
void CCadOrigin::ChangeCenter(CSize p)
{
	SetP1(GetP1() - p);
}


CSize CCadOrigin::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadOrigin::ChangeSize(CSize Sz)
{
	SetP2(GetP2() + Sz);
}
