// CadArcCentered.cpp: implementation of the CCadArcCentered class.
//
///////////////////////////////////////////////

#include "stdafx.h"

///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadArcCentered::CCadArcCentered():CCadObject(OBJECT_TYPE_ARCCENTERED)
{
}

CCadArcCentered::CCadArcCentered(CCadArcCentered &arc):CCadObject(OBJECT_TYPE_ARCCENTERED)
{
	SetP1(arc.GetP1());
	SetP2(arc.GetP2());
	m_atrb.m_End = arc.m_atrb.m_End;
	m_atrb.m_EndAngle = arc.m_atrb.m_EndAngle;
	m_atrb.m_LineColor = arc.m_atrb.m_LineColor;
	m_atrb.m_Start = arc.m_atrb.m_Start;
	m_atrb.m_StartAngle = arc.m_atrb.m_StartAngle;
	m_atrb.m_LineWidth = arc.m_atrb.m_LineWidth;
}

CCadArcCentered::~CCadArcCentered()
{
}

void CCadArcCentered::Draw(CDC *pDC, ObjectMode mode,CPoint O,CScale Scale)
{
	CPen *pOld, penLine, penPoint;
	CBrush brushNULL, brushPointFill, * pOldBrush = 0;
	CRect rect;
	CSize rectLWcomp;
	CPoint p1,p2;
	int dx,dy;
	CPoint P1,P2,Start,End;
	CSize szDiff(4, 4);
	int Lw;

	if (CCadArcCentered::m_RenderEnable)
	{
		P1 = Scale * GetP1() + O;
		P2 = Scale * GetP2() + O;
		Start = Scale * m_atrb.m_Start + O;
		End = Scale * m_atrb.m_End + O;
		Lw = int(m_atrb.m_LineWidth * Scale.m_ScaleX);
		if (Lw <= 1 || ObjectMode::Sketch == mode)
		{
			Lw = 1;
			rectLWcomp = CSize(0, 0);
		}
		else
			rectLWcomp = CSize(Lw / 2, Lw / 2);

		if (P1.x >= P2.x)
		{
			if (P1.y > P2.y)
			{
				dx = P1.x - P2.x;
				dy = P1.y - P2.y;
			}
			else if (P1.y == P2.y)
			{
				dx = P1.x - P2.x;
				dy = P1.y - P2.y;
			}
			else
			{
				dx = P1.x - P2.x;
				dy = P2.y - P1.y;
			}
		}
		else
		{
			if (P1.y > P2.y)
			{
				dx = P2.x - P1.x;
				dy = P1.y - P2.y;
			}
			else if (P1.y == P2.y)
			{
				dx = P2.x - P1.x;
				dy = P1.y - P2.y;
			}
			else
			{
				dx = P2.x - P1.x;
				dy = P2.y - P1.y;
			}
		}
		p1 = P1 + CPoint(-dx, -dy);
		p2 = P1 + CPoint(dx, dy);
		SetRect(rect, p1, p2, rectLWcomp);
		//	rect.SetRect(p1,p2);
		switch (mode)
		{
		case ObjectMode::Final:
			penLine.CreatePen(PS_SOLID, Lw, m_atrb.m_LineColor);
			break;
		case ObjectMode::Selected:
			penLine.CreatePen(PS_DOT, Lw, RGB(200, 0, 0));
			break;
		case ObjectMode::Sketch:
			penLine.CreatePen(PS_DOT, 1, m_atrb.m_LineColor);
			break;
		case ObjectMode::ArcStart:
		case ObjectMode::ArcEnd:
			penLine.CreatePen(PS_DOT, 1, m_atrb.m_LineColor);
			break;
		}
		pOld = pDC->SelectObject(&penLine);
		penPoint.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		brushPointFill.CreateSolidBrush(RGB(0, 0, 255));
		brushNULL.CreateStockObject(NULL_BRUSH);
		pOldBrush = (CBrush*)pDC->SelectObject(&brushNULL);
		switch (mode)
		{
		case ObjectMode::Final:
			pDC->Arc(&rect, Start, End);
			break;
		case ObjectMode::Selected:
			pDC->Arc(&rect, Start, End);
			break;
		case ObjectMode::Sketch:
			pDC->Rectangle(&rect);
			pDC->SelectObject(&brushPointFill);
			pDC->SelectObject(&brushPointFill);
			pDC->Rectangle(CRect(Start - szDiff, Start + szDiff));
			pDC->Rectangle(CRect(End - szDiff, End + szDiff));
			pDC->Rectangle(CRect(p1 - szDiff, p1 + szDiff));
			pDC->Rectangle(CRect(p2 - szDiff, p2 + szDiff));
			pDC->Rectangle(CRect(P1 - szDiff, P1 + szDiff));	//Center point
			break;
		case ObjectMode::Erase:
			break;
		case ObjectMode::ArcStart:
			pDC->Ellipse(&rect);
			pDC->MoveTo(P1);
			pDC->LineTo(Start);
			pDC->SelectObject(&brushPointFill);
			pDC->SelectObject(&brushPointFill);
			pDC->Rectangle(CRect(Start - szDiff, Start + szDiff));
			pDC->Rectangle(CRect(End - szDiff, End + szDiff));
			pDC->Rectangle(CRect(p1 - szDiff, p1 + szDiff));
			pDC->Rectangle(CRect(p2 - szDiff, p2 + szDiff));
			pDC->Rectangle(CRect(P1 - szDiff, P1 + szDiff));	//Center point
			break;
		case ObjectMode::ArcEnd:
			pDC->Arc(&rect, Start, End);
			pDC->MoveTo(P1);
			pDC->LineTo(End);
			pDC->SelectObject(&brushPointFill);
			pDC->SelectObject(&brushPointFill);
			pDC->Rectangle(CRect(Start - szDiff, Start + szDiff));
			pDC->Rectangle(CRect(End - szDiff, End + szDiff));
			pDC->Rectangle(CRect(p1 - szDiff, p1 + szDiff));
			pDC->Rectangle(CRect(p2 - szDiff, p2 + szDiff));
			pDC->Rectangle(CRect(P1 - szDiff, P1 + szDiff));	//Center point
			break;
		}
		pDC->SelectObject(pOld);
		pDC->SelectObject(pOldBrush);
	}
}

Tokens CCadArcCentered::Parse(
	FILE* pIN,
	Tokens LookAHeadToken,
	CCadDrawing** ppDrawing,
	CFileParser* pParser
)
{
	BOOL bLoop = TRUE;
	int PointOrder = 0;

	LookAHeadToken = pParser->Expect(Tokens::ARC_CENTER, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while (bLoop)
	{
		switch (LookAHeadToken)
		{
			case Tokens::POINT:
				switch(PointOrder)
				{
				case 0:
					LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP1(), LookAHeadToken);
					PointOrder++;
					break;
			case 1:
				LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP2(), LookAHeadToken);
				PointOrder++;
				break;
			case 2:
				LookAHeadToken = pParser->Point(Tokens::POINT, pIN, m_atrb.m_Start, LookAHeadToken);
				PointOrder++;
				break;
			case 3:
				LookAHeadToken = pParser->Point(Tokens::POINT, pIN, m_atrb.m_End, LookAHeadToken);
				PointOrder++;
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
			break;
		case Tokens::POINT_1:
			LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::POINT_2:
			LookAHeadToken = pParser->Point(Tokens::POINT_2, pIN, GetP2(), LookAHeadToken);
			break;
		case Tokens::START_POINT:
			LookAHeadToken = pParser->Point(Tokens::START_POINT, pIN, m_atrb.m_Start, LookAHeadToken);
			break;
		case Tokens::END_POINT:
			LookAHeadToken = pParser->Point(Tokens::END_POINT, pIN, m_atrb.m_End, LookAHeadToken);
			break;
		case Tokens::COLOR:
			LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, m_atrb.m_LineColor, LookAHeadToken);
			break;
		case Tokens::LINE_COLOR:
			LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, m_atrb.m_LineColor, LookAHeadToken);
			break;
		case Tokens::WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::WIDTH, pIN, m_atrb.m_LineWidth, LookAHeadToken);
			break;
		case Tokens::LINE_WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, m_atrb.m_LineWidth, LookAHeadToken);
			break;
		case Tokens(')'):
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
			bLoop = FALSE;
			break;
		case Tokens(','):
			LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
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

void CCadArcCentered::Save(FILE *pO,  int Indent)
{
	char* s = new char[256];
	char* s1 = new char[256];
	char* s2 = new char[256];
	char* s3 = new char[256];
	char* s4 = new char[256];
	char* s5 = new char[256];
	char* s6 = new char[64];

	fprintf(pO,"%sARCCENT(%s,%s,%s,%s,%s,%s)\n",
		theApp.IndentString(s,256,Indent),
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SavePoint(s2, 64, Tokens::POINT_2, GetP2()),
		CFileParser::SavePoint(s3, 64, Tokens::START_POINT, m_atrb.m_Start),
		CFileParser::SavePoint(s4, 64, Tokens::END_POINT, m_atrb.m_End),
		CFileParser::SaveColor(s5,64, m_atrb.m_LineColor,Tokens::LINE_COLOR),
		CFileParser::SaveDecimalValue(s6, 64, Tokens::LINE_WIDTH, m_atrb.m_LineWidth)
	);
	delete[]s6;
	delete[]s5;
	delete[]s4;
	delete[]s3;
	delete[]s2;
	delete[]s1;
	delete[]s;
}

CCadArcCentered CCadArcCentered::operator=(CCadArcCentered &v)
{
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	m_atrb.m_LineColor = v.m_atrb.m_LineColor;
	m_atrb.m_End = v.m_atrb.m_End;
	m_atrb.m_Start = v.m_atrb.m_Start;
	m_atrb.m_LineWidth = v.m_atrb.m_LineWidth;
	return *this;
}

int CCadArcCentered::CheckSelected(CPoint p,CSize Offset)
{
	extern double ArcTan(double X, double Y);
	double StartAngle,EndAngle,Angle;
	int rV = 0;
	CPoint P1,P2,Start,End;

	P1 = GetP1() + Offset;
	P2 = GetP2() +Offset;
	Start = m_atrb.m_Start+Offset;
	End = m_atrb.m_End+Offset;
	StartAngle = ArcTan(double( Start.x-P1.x ),double(P1.y - Start.y));
	EndAngle = ArcTan(double(End.x-P1.x ),double(P1.y - End.y));
	Angle = ArcTan(double(p.x-P1.x),double(P1.y - p.y));
	rV = CheckAngle(StartAngle,EndAngle,Angle);

	// 1 = x^2/A^2 + y^2/B^2
	double W = double(this->GetLineWidth())/2.0;
	if( W < 50.0) W = 50.0;
	double A,B;
	double X,Y,X1,Y1,X2,Y2;	
	A = double(P2.x-P1.x);
	B = double(P2.y - P1.y);
	X = double(p.x) - double(P1.x);
	Y = double(p.y) - double(P1.y);
	X1 = double(P2.x) - double(P1.x) + W;
	Y1 = 0.0;
	X2 = double(P2.x) - double(P1.x) - W;
	Y2 =  0.0;
	double Rad = (X*X)/(A*A) + (Y*Y)/(B*B);
	double Rad1 = (X1*X1)/(A*A) + (Y1 * Y1)/(B*B);
	double Rad2 = (X2*X2)/(A*A) + (Y2 * Y2)/(B*B);
	if(Rad < Rad2 || Rad > Rad1) rV = 0;
	
	return rV;
}

void CCadArcCentered::Move(CPoint p)
{
	CPoint Diff = p- GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
	m_atrb.m_Start += Diff;
	m_atrb.m_End += Diff;
}

int CCadArcCentered::GrabVertex(CPoint point)
{
	int rV = -1;
	return rV;
}

void CCadArcCentered::SetVertex(int Vi, CPoint p)
{

}

CPoint CCadArcCentered::GetReference()
{
	return GetP1();
}


void CCadArcCentered::SetStartAngle(int Angle)
{

}

void CCadArcCentered::SetEndAngle(int Angle)
{

}

void CCadArcCentered::SetStartPoint(CPoint p)
{
	m_atrb.m_Start = p;
	//----------------------------
	// calculate the Angle
	// associated with this start
	// point
	//---------------------------
	double Pi = atan(1) * 4.0;
	double A = ArcTan(double(m_atrb.m_Start.x ) - double(GetP1().x), double(GetP1().y)-double(m_atrb.m_Start.y));

	A *= 180.0 / Pi;
	m_atrb.m_StartAngle = int(A * 10.0);
}

void CCadArcCentered::SetEndPoint(CPoint p)
{
	m_atrb.m_End = p;
	double Pi = atan(1) * 4.0;
	double A = ArcTan(double(m_atrb.m_End.x ) - double(GetP1().x),double(GetP1().y)-double(m_atrb.m_End.y));
	A *= 180.0 / Pi;
	m_atrb.m_EndAngle = int(A * 10.0);
}

void CCadArcCentered::AdjustRefernce(CPoint p)
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
	this->m_atrb.m_Start -= p;
	this->m_atrb.m_End -= p;
}

void CCadArcCentered::RenderEnable(int e)
{
	CCadArcCentered::m_RenderEnable = e;
}

CPoint CCadArcCentered::GetCenter()
{
	return GetP1();
}

// Moves the center of the object to the spcified point
void CCadArcCentered::ChangeCenter(CSize p)
{
}


CSize CCadArcCentered::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadArcCentered::ChangeSize(CSize Sz)
{
	SetP2(GetP2() + Sz);
}
