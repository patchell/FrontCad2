#include "stdafx.h"


CCadPrintRect::CCadPrintRect():CCadObject(OBJECT_TYPE_PRINTRECT)
{
}

CCadPrintRect::CCadPrintRect(CCadPrintRect &PR) : CCadObject(OBJECT_TYPE_PRINTRECT)
{
	m_Attrib.m_LineColor = PR.m_Attrib.m_LineColor;
	m_Attrib.m_LineWidth = PR.m_Attrib.m_LineWidth;
	GetAttributes()->m_Size = PR.GetAttributes()->m_Size;
	SetP1(PR.GetP1());
	SetP2(PR.GetP2());
}


CCadPrintRect::~CCadPrintRect()
{
}

BOOL CCadPrintRect::Create(CPoint ptPos, PrintRectAttributes* pPrintRectAttributes)
{
	BOOL rV = TRUE;

	SetP1(ptPos);
	SetP2(ptPos);
	if (pPrintRectAttributes)
		m_Attrib.CopyFrom(pPrintRectAttributes);
	else
	{
		rV = FALSE;
	}
    return rV;
}

CCadObject* CCadPrintRect::Copy()
{
	CCadPrintRect* pNew = new CCadPrintRect(*this);
	return (CCadObject*)pNew;
}

void CCadPrintRect::Draw(CDC *pDC, ObjectMode mode, CPoint Offset, CScale Scale)
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
	CBrush* pOldB, brushFill, brushPoint;
	CRect rect;
	CSize rectLWcomp;
	CPoint P1, P2;
	int Lw;
	CSize p = CSize(4, 4);

	if (!CCadPrintRect::m_RenderEnable) return;	//don't print
	P1 = Scale * GetP1() + Offset;
	P2 = P1 + Scale * GetAttributes()->m_Size;;
	Lw = int(m_Attrib.m_LineWidth * Scale.m_ScaleX);
	if (Lw <= 1 || ObjectMode::Sketch == mode)
	{
		Lw = 1;
		rectLWcomp = CSize(0, 0);
	}
	else
		rectLWcomp = CSize(Lw / 2, Lw / 2);
	SetRect(rect, P1 - rectLWcomp, P2 + rectLWcomp, CSize(Lw, Lw));
	switch (mode)
	{
	case ObjectMode::Final:
		penLine.CreatePen(PS_SOLID, Lw, m_Attrib.m_LineColor);
		break;
	case ObjectMode::Selected:
		penLine.CreatePen(PS_SOLID, Lw, RGB(200, 50, 50));
		break;
	case ObjectMode::Sketch:
		penLine.CreatePen(PS_DOT, 1, m_Attrib.m_LineColor);
		break;
	}
	brushFill.CreateStockObject(NULL_BRUSH);
	penPoint.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	brushPoint.CreateSolidBrush(RGB(0, 0, 255));
	pOld = (CPen*)pDC->SelectObject(&penLine);
	pOldB = (CBrush*)pDC->SelectObject(&brushFill);
	switch (mode)
	{
	case ObjectMode::Final:
		pDC->Rectangle(&rect);
		break;
	case ObjectMode::Selected:
		pDC->Rectangle(&rect);
		pDC->SelectObject(&penPoint);
		pDC->SelectObject(&brushPoint);
		rect.SetRect(P1 - p, P1 + p);
		pDC->Rectangle(&rect);
		rect.SetRect(P2 - p, P2 + p);
		pDC->Rectangle(&rect);
		break;
	case ObjectMode::Sketch:
		pDC->Rectangle(&rect);
		pDC->SelectObject(&penPoint);
		pDC->SelectObject(&brushPoint);
		rect.SetRect(P1 - p, P1 + p);
		pDC->Rectangle(&rect);
		rect.SetRect(P2 - p, P2 + p);
		pDC->Rectangle(&rect);
		break;
	case ObjectMode::Erase:
		break;
	}
	pDC->SelectObject(pOld);
	pDC->SelectObject(pOldB);
}

int CCadPrintRect::CheckSelected(CPoint p,CSize O)
{
	CRect rect;
	int rV;
	CPoint P1 = GetP1() + O;
	CPoint P2 = P1 + GetAttributes()->m_Size;
	rect.SetRect(P1, P2);
	rect.NormalizeRect();
	rV = (int)rect.PtInRect(p);
	return rV;
}

Tokens CCadPrintRect::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	BOOL Loop = TRUE;

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::PRINTRECT, LookAHeadToken, pIN);
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
		case Tokens::SIZE:
			LookAHeadToken = pParser->Size(Tokens::SIZE, pIN, GetAttributes()->m_Size, LookAHeadToken);
			break;
		case Tokens::WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::WIDTH, pIN, m_Attrib.m_LineWidth, LookAHeadToken);
			break;
		case Tokens::LINE_WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, m_Attrib.m_LineWidth, LookAHeadToken);
			break;
		case Tokens::COLOR:
			LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, m_Attrib.m_LineColor, LookAHeadToken);
			break;
		case Tokens::LINE_COLOR:
			LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, m_Attrib.m_LineColor, LookAHeadToken);
			break;
		case Tokens(','):
			LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
			break;
		case Tokens(')'):
			Loop = FALSE;
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
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

void CCadPrintRect::Save(FILE *pO,  int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];

	fprintf(pO, "%s%s(%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::PRINTRECT),
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SaveSize(s2, 64, Tokens::SIZE, GetAttributes()->m_Size),
		CFileParser::SaveDecimalValue(s3,64,Tokens::LINE_WIDTH,m_Attrib.m_LineWidth),
		CFileParser::SaveColor(s4,64, m_Attrib.m_LineColor,Tokens::LINE_COLOR)
	);
	delete[]s4;
	delete[]s3;
	delete[]s2;
	delete[]s1;
	delete[]s;
}

CCadPrintRect CCadPrintRect::operator=(CCadPrintRect &v)
{
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	m_Attrib.m_LineColor = v.m_Attrib.m_LineColor;
	m_Attrib.m_LineWidth = v.m_Attrib.m_LineWidth;
	return *this;
}


void CCadPrintRect::Move(CPoint p)
{
	CSize Diff = p - GetP1();
	SetP1(GetP1() + Diff);
}

int CCadPrintRect::GrabVertex(CPoint point)
{
	int rV = -1;
	CSize Diff(4, 4);
	CRect rect;
	rect.SetRect(GetP1() + Diff, GetP1() - Diff);
	rect.NormalizeRect();
	if (rect.PtInRect(point))
		rV = 0;
	else
	{
		rect.SetRect(GetP2() + Diff, GetP2() - Diff);
		rect.NormalizeRect();
		if (rect.PtInRect(point))
			rV = 1;
	}
	return rV;
}

void CCadPrintRect::SetVertex(int Vi, CPoint p)
{
	if (Vi)
		SetP2(p);
	else
		SetP1(p);
}

CPoint CCadPrintRect::GetReference()
{
	return GetP1();
}

void CCadPrintRect::AdjustRefernce(CPoint p)
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

CRect CCadPrintRect::GetRect()
{
	CRect rect;

	rect.SetRect(GetP1(), GetP1() + GetAttributes()->m_Size);
	rect.NormalizeRect();
	return rect;
}
void CCadPrintRect::RenderEnable(int e)
{
	CCadPrintRect::m_RenderEnable = e;
}

CPoint CCadPrintRect::GetCenter()
{
	CRect rect = this->GetRect();
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadPrintRect::ChangeCenter(CSize p)
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

void CCadPrintRect::ChangeSize(CSize Sz)
{
	SetP2(GetP2() - Sz);
}
