// CadElipse.cpp: implementation of the CCadElipse class.
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

CCadElipse::CCadElipse():CCadObject(OBJECT_TYPE_ELLIPSE)
{
}

CCadElipse::CCadElipse(CCadElipse &e):CCadObject(OBJECT_TYPE_ELLIPSE)
{
	SetP1(e.GetP1());
	SetP2(e.GetP2());
	SetLineColor(e.GetLineColor());
	SetFillColor(e.GetFillColor());
	SetLineWidth(e.GetLineWidth());	
	SetTransparent(e.GetTransparent());
}

CCadElipse::~CCadElipse()
{
}

BOOL CCadElipse::Create(CPoint ptPos, ElipseAttributes* pElipseAttributes)
{
	BOOL rV = TRUE;

	SetP1(ptPos);
	SetP2(ptPos);
	if (pElipseAttributes)
	{
		rV = GetAttributes()->Create(pElipseAttributes);
	}
	return rV;
}

CCadObject* CCadElipse::Copy()
{
	CCadElipse* pE = new CCadElipse(*this);
	return pE;
}

void CCadElipse::Draw(CDC *pDC, ObjectMode mode,CPoint Offset,CScale Scale)
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
	CBrush *pOldBr, brushFill, brushPoint;
	CRect rect;
	CSize rectLWcomp;
	CPoint P1,P2;
	CSize szDiff = CSize(4,4);
	int Lw;

	if (CCadElipse::m_RenderEnable)
	{
		P1 = Scale * GetP1() + Offset;
		P2 = Scale * GetP2() + Offset;
		if ((Lw = int(Scale.m_ScaleX * GetLineWidth())) < 1) 
			Lw = 1;
		if (Lw <= 1 || ObjectMode::Sketch == mode)
		{
			Lw = 1;
			rectLWcomp = CSize(0, 0);
		}
		else
			rectLWcomp = CSize(Lw / 2, Lw / 2);
		switch (mode)
		{
		case ObjectMode::Final:
			penLine.CreatePen(PS_SOLID, Lw, GetLineColor());
			if(GetTransparent() || CCadObject::AreShapeFillsDisabled() )
				brushFill.CreateStockObject(NULL_BRUSH);
			else
				brushFill.CreateSolidBrush(GetFillColor());
			break;
		case ObjectMode::Selected:
			penLine.CreatePen(PS_SOLID, Lw, RGB(50, 50, 200));
			if (GetTransparent() || CCadObject::AreShapeFillsDisabled())
				brushFill.CreateStockObject(NULL_BRUSH);
			else
				brushFill.CreateSolidBrush(RGB(150,150,255));
			break;
		case ObjectMode::Sketch:
			penLine.CreatePen(PS_DOT, 1, GetLineColor());
			brushFill.CreateStockObject(NULL_BRUSH);
			break;
		}
		brushPoint.CreateSolidBrush(RGB(0, 0, 255));
		penPoint.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		SetRect(rect, P1, P2, rectLWcomp);
		pOld = pDC->SelectObject(&penLine);
		pOldBr = pDC->SelectObject(&brushFill);
		switch (mode)
		{
		case ObjectMode::Final:
			pDC->Ellipse(&rect);
			break;
		case ObjectMode::Selected:
		{
			pDC->Ellipse(&rect);
			pDC->SelectObject(&penPoint);
			pDC->SelectObject(&brushPoint);
			rect.SetRect(P1 - szDiff, P1 + szDiff);
			pDC->Rectangle(&rect);
			rect.SetRect(P2 - szDiff, P2 + szDiff);
			pDC->Rectangle(&rect);
		}
		break;
		case ObjectMode::Sketch:
			pDC->Ellipse(&rect);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOldBr);
		pDC->SelectObject(pOld);
	}
}

int CCadElipse::CheckSelected(CPoint p,CSize O)
{
	double a,b,xo,yo,v;
	int rV;
	static int count = 0;
	CPoint P1 = GetP1() + O;
	CPoint P2 = GetP2() + O;

	a = double(P2.x - P1.x)/2.0;
	b = double(P2.y - P1.y)/2.0;
	xo = p.x - (a + P1.x);
	yo = p.y - (b + P1.y);
	v = (xo * xo)/(a * a) + (yo * yo)/(b * b);
	if( v < 1.0) rV = TRUE;
	else rV = FALSE;
	return rV;
}

CCadElipse CCadElipse::operator=(CCadElipse &e)
{
	CCadElipse eNew;
	eNew.SetP1(e.GetP1());
	eNew.SetP2(e.GetP2());
	eNew.SetLineColor(e.GetLineColor());
	eNew.SetFillColor(e.GetFillColor());
	eNew.SetLineWidth(e.GetLineWidth());
	eNew.SetTransparent(e.GetTransparent());
	return eNew;
}

void CCadElipse::Move(CPoint p)
{
	CSize Diff = p - GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
}

Tokens CCadElipse::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	BOOL Loop = TRUE;

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::ELLIPSE, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while (Loop)
	{
		switch (LookAHeadToken)
		{
		case Tokens::POINT_1:
			LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::POINT_2:
			LookAHeadToken = pParser->Point(Tokens::POINT_2, pIN, GetP2(), LookAHeadToken);
			break;
		case Tokens::LINE_COLOR:
			LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
			break;
		case Tokens::FILL_COLOR:
			LookAHeadToken = pParser->Color(Tokens::FILL_COLOR, pIN, GetAttributes()->m_FillColor, LookAHeadToken);
			break;
		case Tokens::LINE_WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens::TRANSPARENTbkg:
			LookAHeadToken = pParser->DecimalValue(Tokens::TRANSPARENTbkg, pIN, GetAttributes()->m_Transparent, LookAHeadToken);
			break;
		case Tokens(')'):
			Loop = FALSE;
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
			break;
		case Tokens(','):
			LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
			break;
		default:
			break;
		}
	}
	(*ppDrawing)->AddObjectToEnd(this);
	return LookAHeadToken;
}

void CCadElipse::Save(FILE* pO, int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];
	char* s5 = new char[64];
	char* s6 = new char[64];

	fprintf(pO, "%s%s(%s,%s,%s,%s,%s, %s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::ELLIPSE),
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SavePoint(s2, 64, Tokens::POINT_2, GetP2()),
		CFileParser::SaveColor(s3, 64, GetAttributes()->m_LineColor, Tokens::LINE_COLOR),
		CFileParser::SaveColor(s4, 64, GetAttributes()->m_FillColor, Tokens::FILL_COLOR),
		CFileParser::SaveDecimalValue(s5,64, Tokens::LINE_WIDTH, GetAttributes()->m_LineWidth),
		CFileParser::SaveDecimalValue(s6, 64, Tokens::TRANSPARENTbkg, GetAttributes()->m_Transparent)
	);
	delete[] s6;
	delete[] s5;
	delete[] s4;
	delete[] s3;
	delete[] s2;
	delete[] s1;
	delete[] s;
}

int CCadElipse::GrabVertex(CPoint point)
{
	int rV = -1;
	CSize Diff(4,4);
	CRect rect;
	rect.SetRect(GetP1() + Diff, GetP1() - Diff);
	rect.NormalizeRect();
	if(rect.PtInRect(point))
		rV = 0;
	else
	{
		rect.SetRect(GetP2() + Diff, GetP2() - Diff);
		rect.NormalizeRect();
		if(rect.PtInRect(point))
			rV = 1;
	}
	return rV;
}

void CCadElipse::SetVertex(int Vi, CPoint p)
{
	if(Vi)
		SetP2(p);
	else
		SetP1(p);
}

CPoint CCadElipse::GetReference()
{
	return GetP1();
}

void CCadElipse::AdjustRefernce(CPoint p)
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

void CCadElipse::RenderEnable(int e)
{
	CCadElipse::m_RenderEnable = e;
}

CPoint CCadElipse::GetCenter()
{
	CRect rect = this->GetRect();
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadElipse::ChangeCenter(CSize p)
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
	SetP2(GetP2() - p);
}


CSize CCadElipse::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadElipse::ChangeSize(CSize Sz)
{
	SetP2(GetP2() + Sz);
}
