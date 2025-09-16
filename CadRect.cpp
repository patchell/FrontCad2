// CadRect.cpp: implementation of the CCadRect class.
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

CCadRect::CCadRect():CCadObject(OBJECT_TYPE_RECT)
{
}

CCadRect::CCadRect(CCadRect &r):CCadObject(OBJECT_TYPE_RECT)
{
	GetAttributes()->m_FillColor = r.GetAttributes()->m_FillColor;
	GetAttributes()->m_LineColor = r.GetAttributes()->m_LineColor;
	GetAttributes()->m_LineWidth = r.GetAttributes()->m_LineWidth;
	GetAttributes()->m_bTransparentFill = r.GetAttributes()->m_bTransparentFill;
	SetP1(r.GetP1());
	SetP2(r.GetP2());
}

CCadRect::~CCadRect()
{
}

BOOL CCadRect::Create(CPoint ptPos, RectAttributes* pRectAttributes)
{
	BOOL rV = TRUE;
	SetP1(ptPos);
	SetP2(ptPos);
	if (pRectAttributes)
		m_atrb.CopyFrom(pRectAttributes);
	else
	{
		rV = FALSE;
	}
	return rV;
}

CCadObject* CCadRect::Copy()
{
	CCadRect* pNew = new CCadRect(*this);
	return (CCadObject*)pNew;
}

void CCadRect::Draw(CDC *pDC, ObjectMode mode,CPoint Offset,CScale Scale)
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
	CPen *pOld = 0, penDraw, penPoint;
	CBrush *pOldBr = 0, brushFill, brushSelect;
	CRect rect, rectVertex;;
	CSize rectLWcomp;
	CPoint P1,P2, Diff;
	int Lw;

	if (CCadRect::m_RenderEnable)
	{
		P1 = Scale * GetP1() + Offset;
		P2 = Scale * GetP2() + Offset;
		Lw = int(GetAttributes()->m_LineWidth * Scale.m_ScaleX);
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
			penDraw.CreatePen(PS_SOLID, Lw, GetAttributes()->m_LineColor);
			if(CCadObject::AreShapeFillsDisabled() || IsTransparenet())
				brushFill.CreateStockObject(NULL_BRUSH);
			else
				brushFill.CreateSolidBrush(GetAttributes()->m_FillColor);
			break;
		case ObjectMode::Selected:
			penDraw.CreatePen(PS_SOLID, Lw, RGB(200, 50, 50));
			penPoint.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			brushSelect.CreateSolidBrush(RGB(0, 0, 255));
			if (CCadObject::AreShapeFillsDisabled() || IsTransparenet())
				brushFill.CreateStockObject(NULL_BRUSH);
			else
					brushFill.CreateSolidBrush(RGB(100, 50, 50));
			break;
		case ObjectMode::Sketch:
			penDraw.CreatePen(PS_DOT, 1, GetAttributes()->m_LineColor);
			penPoint.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			brushSelect.CreateSolidBrush(RGB(0, 0, 255));
			brushFill.CreateStockObject(NULL_BRUSH);
			break;
		}
		SetRect(rect, P1, P2, rectLWcomp);
		pOld = pDC->SelectObject(&penDraw);
		pOldBr = pDC->SelectObject(&brushFill);	
		switch (mode)
		{
		case ObjectMode::Final:
			pDC->Rectangle(&rect);
			break;
		case ObjectMode::Selected:
		case ObjectMode::Sketch:
			pDC->Rectangle(&rect);
			pDC->SelectObject(&penPoint);
			pDC->SelectObject(&brushSelect);
			Diff = CPoint(4, 4);
			rectVertex.SetRect(P1 + (-Diff), P1 + Diff);
			pDC->SelectObject(&penPoint);
			pDC->Rectangle(&rectVertex);
			rectVertex.SetRect(P2 + (-Diff), P2 + Diff);
			pDC->Rectangle(&rectVertex);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOldBr);
		pDC->SelectObject(pOld);
	}
}

int CCadRect::CheckSelected(CPoint p,CSize O)
{
	CRect rect;
	int rV;
	CPoint P1 = GetP1() + O;
	CPoint P2 = GetP2() + O;
	rect.SetRect(P1,P2);
	rect.NormalizeRect();
	rV = (int)rect.PtInRect(p);
	return rV;
}

Tokens CCadRect::Parse(
	FILE* pIN,
	Tokens LookAHeadToken,
	CCadDrawing** ppDrawing,
	CFileParser* pParser
)
{
	BOOL bLoop = TRUE;
	int PointOrder = 0;
	int ColorOrder = 0;
	char* pToken1 = new char[64];

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::RECT, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while(bLoop)
	{
		switch (LookAHeadToken)
		{
		case Tokens::POINT:
			switch (PointOrder)
			{
			case 0:
				LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP1(), LookAHeadToken);
				++PointOrder;
				break;
			case 1:
				LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP2(), LookAHeadToken);
				++PointOrder;
				break;
			}
			break;
		case Tokens::COLOR:
			switch (ColorOrder)
			{
			case 0:
				LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, GetAttributes()->m_LineColor, LookAHeadToken);
				ColorOrder++;
				break;
			case 1:
				LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, GetAttributes()->m_FillColor, LookAHeadToken);
				ColorOrder++;
				break;
			}
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
		case Tokens::FILL_COLOR:
			LookAHeadToken = pParser->Color(Tokens::FILL_COLOR, pIN, GetAttributes()->m_FillColor, LookAHeadToken);
			break;
		case Tokens::WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens::LINE_WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens::TRANSPARENTbkg:
			LookAHeadToken = pParser->DecimalValue(Tokens::TRANSPARENTbkg, pIN, GetAttributes()->m_bTransparentFill, LookAHeadToken);
			break;
		case Tokens(','):
			LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
			break;
		case Tokens(')'):
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
			bLoop = FALSE;
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
	delete[] pToken1;
	(*ppDrawing)->AddObjectToEnd(this);
	return LookAHeadToken;
}

void CCadRect::Save(FILE *pO,  int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];
	char* s5 = new char[64];
	char* s6 = new char[64];

	fprintf(pO, "%s%s(%s,%s,%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::RECT),
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SavePoint(s2, 64, Tokens::POINT_2, GetP2()),
		CFileParser::SaveColor(s3,64,GetAttributes()->m_LineColor,Tokens::LINE_COLOR),
		CFileParser::SaveColor(s4, 64, GetAttributes()->m_FillColor, Tokens::FILL_COLOR),
		CFileParser::SaveDecimalValue(s5,64,Tokens::LINE_WIDTH, GetAttributes()->m_LineWidth),
		CFileParser::SaveDecimalValue(s5, 64, Tokens::TRANSPARENTbkg, GetAttributes()->m_bTransparentFill)
	);
	delete[]s6;	
	delete[]s5;
	delete[]s4;
	delete[]s3;
	delete[]s2; 
	delete[]s1;	
	delete[]s;
}

CCadRect CCadRect::operator=(CCadRect &v)
{
	CCadRect Rect;

	Rect.SetP1(v.GetP1());
	Rect.SetP2(v.GetP2());
	Rect.GetAttributes()->CopyFrom(v.GetAttributes());
	return Rect;
}


void CCadRect::Move(CPoint p)
{
	CSize Diff = p - GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
}

int CCadRect::GrabVertex(CPoint point)
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

void CCadRect::SetVertex(int Vi, CPoint p)
{
	if (Vi)
		SetP2(p);
	else
		SetP1(p);
}

CPoint CCadRect::GetReference()
{
	return GetP1();
}

void CCadRect::AdjustRefernce(CPoint p)
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

void CCadRect::RenderEnable(int e)
{
	CCadRect::m_RenderEnable = e;
}

CPoint CCadRect::GetCenter()
{
	CRect rect = this->GetRect();
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadRect::ChangeCenter(CSize p)
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


CSize CCadRect::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadRect::ChangeSize(CSize Size)
{
	SetP2(GetP2() + Size);
}
