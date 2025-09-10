// CadArc.cpp: implementation of the CCadArc class.
//
///////////////////////////////////////////////

#include "stdafx.h"

CFileParser* pP;

extern double ArcTan(double X, double Y);

///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadArc::CCadArc():CCadObject(OBJECT_TYPE_ARC)
{
}

CCadArc::CCadArc(CCadArc &arc):CCadObject(OBJECT_TYPE_ARC)
{
	SetP2(arc.GetP1());
	SetP2(arc.GetP2());
	GetAttributes()->CopyFrom(arc.GetAttributes());
}

CCadArc::~CCadArc()
{
}

BOOL CCadArc::Create(CPoint ptPos, ArcAttributes* pArcAttributes)
{
	BOOL bRet = TRUE;
	SetP1(ptPos);
	SetP2(ptPos);
	if (pArcAttributes)
		bRet = GetAttributes()->Create(pArcAttributes);
	else
		bRet = FALSE;
    return bRet;
}

CCadObject* CCadArc::Copy()
{
	CCadArc* pNew = new CCadArc(*this);
	return (CCadObject*)pNew;
}

void CCadArc::Draw(CDC* pDC, ObjectMode mode,CPoint O,CScale Scale)
{
	//------------------------------------------
	// Draw
	//		This function draws an Arc on the
	//	specified device context
	//
	//	parameters:
	//		pDC......pointer to the device context
	//		mode.....Drawing mode, Final, Selected, etdc
	//		O........Offset objects by this amount
	//		Scale....Scale Drawing by this much
	//------------------------------------------
	CPen* pOld, penLine, penPoint;
	CBrush brushNULL, brushPointFill, *pOldBrush = 0;
	CRect rect;
	CSize rectLWcomp;
	CPoint Center;
	CPoint P1,P2,Start,End;
	CSize szDiff = CSize(4, 4);
	int Lw;

	if (CCadArc::m_RenderEnable)
	{
		P1 = Scale * GetP1() + O;
		P2 = Scale * GetP2() + O;
		Start = Scale * m_atrb.m_Start + O;
		End = Scale * m_atrb.m_End + O;
		Lw = int(m_atrb.m_LineWidth * Scale.m_ScaleX);
		if (Lw <= 1)
		{
			Lw = 1;
			rectLWcomp = CSize(0, 0);
		}
		else
			rectLWcomp = CSize(Lw / 2, Lw / 2);
		SetRect(rect, P1, P2, rectLWcomp);
		Center = rect.CenterPoint();
		switch (mode)
		{
		case ObjectMode::Final:
			penLine.CreatePen(PS_SOLID, Lw, m_atrb.m_LineColor);
			break;
		case ObjectMode::Selected:
			penLine.CreatePen(PS_DOT, Lw, RGB(200,0,0));
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
			pDC->SelectObject(&brushPointFill);
			pDC->SelectObject(&penPoint);
			pDC->Rectangle(CRect(Start - szDiff, Start + szDiff));
			pDC->Rectangle(CRect(End - szDiff, End + szDiff));	
			pDC->Rectangle(CRect(P1 - szDiff, P1 + szDiff));
			pDC->Rectangle(CRect(P2 - szDiff, P2 + szDiff));	
			pDC->Rectangle(CRect(Center - szDiff, Center + szDiff));
			break;
		case ObjectMode::Sketch:
			pDC->Rectangle(&rect);
			pDC->SelectObject(&brushPointFill);
			pDC->SelectObject(&brushPointFill);
			pDC->Rectangle(CRect(Start - szDiff, Start + szDiff));
			pDC->Rectangle(CRect(End - szDiff, End + szDiff));
			pDC->Rectangle(CRect(P1 - szDiff, P1 + szDiff));
			pDC->Rectangle(CRect(P2 - szDiff, P2 + szDiff));
			pDC->Rectangle(CRect(Center - szDiff, Center + szDiff));
			break;
		case ObjectMode::Erase:
			break;
		case ObjectMode::ArcStart:
			pDC->Ellipse(&rect);
			pDC->MoveTo(Center);
			pDC->LineTo(Start);
			pDC->SelectObject(&brushPointFill);
			pDC->SelectObject(&brushPointFill);
			pDC->Rectangle(CRect(Start - szDiff, Start + szDiff));
			pDC->Rectangle(CRect(End - szDiff, End + szDiff));
			pDC->Rectangle(CRect(P1 - szDiff, P1 + szDiff));
			pDC->Rectangle(CRect(P2 - szDiff, P2 + szDiff));
			pDC->Rectangle(CRect(Center - szDiff, Center + szDiff));
			break;
		case ObjectMode::ArcEnd:
			pDC->Arc(&rect, Start, End);
			pDC->MoveTo(Center);
			pDC->LineTo(End);
			pDC->SelectObject(&brushPointFill);
			pDC->SelectObject(&brushPointFill);
			pDC->Rectangle(CRect(Start - szDiff, Start + szDiff));
			pDC->Rectangle(CRect(End - szDiff, End + szDiff));
			pDC->Rectangle(CRect(P1 - szDiff, P1 + szDiff));
			pDC->Rectangle(CRect(P2 - szDiff, P2 + szDiff));
			pDC->Rectangle(CRect(Center - szDiff, Center + szDiff));
			break;
		}
		pDC->SelectObject(pOld);
		pDC->SelectObject(pOldBrush);
	}
}

int CCadArc::CheckSelected(CPoint p,CSize Offset)
{
	//------------------------------------------
	// CheckSelected
	//		This function is used to see if the
	// the given point is withing the confines
	// of the object.  This function does not
	// actually check to see if it is selected.
	// Guess I did not pick a very good name for
	// this function.
	//
	//	parameter:
	//		p......Is this point in this object?
	//	returns:
	//		True if point is inside, false if outside
	//------------------------------------------
	int rV = 0;

	double StartAngle,EndAngle,Angle;
	double CenterX,CenterY;
	CPoint P1,P2,Start,End;

	P1 = GetP1() + Offset;
	P2 = GetP2() +Offset;
	Start = m_atrb.m_Start+Offset;
	End = m_atrb.m_End+Offset;

	CenterX = double(P1.x) + double(P2.x - P1.x)/2.0;
	CenterY = double(P1.y) + double(P2.y - P1.y)/2.0;
	StartAngle = ArcTan((double(Start.x)-CenterX),-(double(Start.y)-CenterY));
	EndAngle = ArcTan((double(End.x)-CenterX),-(double(End.y)-CenterY));
	Angle = ArcTan(double(p.x)-CenterX,-(double(p.y)-CenterY));
	rV = CheckAngle(StartAngle,EndAngle,Angle);
	CRect rect;
	rect.SetRect(P1,P2);
	rect.NormalizeRect();

	// 1 = x^2/A^2 + y^2/B^2
	double W = double(this->GetLineWidth())/2.0;
	if( W < 50.0) W = 50.0;
	double A,B;
	double X,Y,X1,Y1,X2,Y2;	
	A = double(rect.Width())/2.0;
	B = double(rect.Height())/2.0;
	X = double(p.x) - CenterX;
	Y = double(p.y) - CenterY;
	X1 = double(rect.right) - CenterX + W;
	Y1 = 0.0;
	X2 = double(rect.right) - CenterX - W;
	Y2 =  0.0;
	double Rad = (X*X)/(A*A) + (Y*Y)/(B*B);
	double Rad1 = (X1*X1)/(A*A) + (Y1 * Y1)/(B*B);
	double Rad2 = (X2*X2)/(A*A) + (Y2 * Y2)/(B*B);
	if(Rad < Rad2 || Rad > Rad1) rV = 0;
	return rV;
}

Tokens CCadArc::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	BOOL bLoop = TRUE;
	int PointOrder = 0;

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::ARC, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while (bLoop)
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
	(*ppDrawing)->AddObjectToEnd(this);
	return LookAHeadToken;
}

void CCadArc::Save(FILE *pO,  int Indent)
{
	//------------------------------------------
	// Save
	//		This fucntion is called whenever the
	// user saves a document of library.
	//
	// parameter:
	//		pO.....pointer to Output File Stream
	//------------------------------------------
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];
	char* s5 = new char[64];
	char* s6 = new char[64];

	fprintf(pO, "%sARC(%s,%s,%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SavePoint(s2, 64, Tokens::POINT_2, GetP2()),
		CFileParser::SavePoint(s3, 64, Tokens::START_POINT, m_atrb.m_Start),
		CFileParser::SavePoint(s4, 64, Tokens::END_POINT, m_atrb.m_End),
		CFileParser::SaveColor(s5, 64, m_atrb.m_LineColor,Tokens::LINE_COLOR),
		CFileParser::SaveDecimalValue(s6,64,Tokens::LINE_WIDTH, m_atrb.m_LineWidth)
	);
	delete[]s6;
	delete[]s5;
	delete[]s4;
	delete[]s3;
	delete[]s2;
	delete[]s1;
	delete[]s;
}

CCadArc CCadArc::operator=(CCadArc &v)
{
	//------------------------------------------
	// operator=
	//		This function implements the assign
	//	operator
	//------------------------------------------
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	m_atrb.m_Start = v.m_atrb.m_Start;
	m_atrb.m_End = v.m_atrb.m_Start;
	m_atrb.m_LineWidth = v.m_atrb.m_LineWidth;
	m_atrb.m_LineColor = v.m_atrb.m_LineColor;
	return *this;
}

void CCadArc::Move(CPoint p)
{
	CPoint Diff = p- GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
	m_atrb.m_Start += Diff;
	m_atrb.m_End += Diff;
}

int CCadArc::GrabVertex(CPoint point)
{
	int rV = -1;
	return rV;
}

void CCadArc::SetVertex(int Vi, CPoint p)
{

}

CPoint CCadArc::GetReference()
{
	return GetP1();
}

void CCadArc::SetStartAngle(int Angle)
{
	//------------------------------
	// SetStartAngle
	//
	//	This function allows you to
	// specify the angle that the
	// starts and and it calculates
	// the StartPoint that will give
	// you that angle.
	//------------------------------
}

void CCadArc::SetEndAngle(int Angle)
{
}

void CCadArc::SetStartPoint(CPoint p)
{
	m_atrb.m_Start = p;
	//----------------------------
	// calculate the Angle
	// associated with this start
	// point
	//---------------------------
	double Pi = atan(1) * 4.0;
	double CenterX,CenterY;
	CenterX = double(GetP2().x - GetP1().x)/2.0;
	CenterX += double(GetP1().x);
	CenterY = double(GetP2().y - GetP1().y)/2.0;
	CenterY += double(GetP1().y);
	double A = ArcTan(double(m_atrb.m_Start.x ) - CenterX, CenterY-double(m_atrb.m_Start.y));

	A *= 180.0 / Pi;
	m_atrb.m_StartAngle = int(A * 10.0);
}

void CCadArc::SetEndPoint(CPoint p)
{
	m_atrb.m_End = p;
	double Pi = atan(1) * 4.0;
	double CenterX,CenterY;
	CenterX = double(GetP2().x - GetP1().x)/2.0;
	CenterX += double(GetP1().x);
	CenterY = double(GetP2().y - GetP1().y)/2.0;
	CenterY += double(GetP1().y);
	double A = ArcTan(double(m_atrb.m_End.x ) - CenterX,CenterY-double(m_atrb.m_End.y));
	A *= 180.0 / Pi;
	m_atrb.m_EndAngle = int(A * 10.0);
}

void CCadArc::AdjustRefernce(CPoint p)
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

void CCadArc::RenderEnable(int e)
{
	CCadArc::m_RenderEnable = e;
}

CPoint CCadArc::GetCenter()
{
	//--------------------------------------
	// GetCecnter
	//		Returns the centerpoint of the ARC
	//	Because of the nature of the beast, the
	// returned point may not be the exact center.
	//	returns:
	//		Point in the center of the arc.
	//--------------------------------------
	CRect rect(GetP1(), GetP2());
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadArc::ChangeCenter(CSize p)
{
}


CSize CCadArc::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadArc::ChangeSize(CSize Sz)
{
	SetP2(GetP2() + Sz);
}
