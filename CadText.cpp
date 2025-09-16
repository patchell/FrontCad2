// CadText.cpp: implementation of the CCadText class.
//
///////////////////////////////////////////////

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern FILE *pO;
///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadText::CCadText():CCadObject(OBJECT_TYPE_TEXT)
{
}

CCadText::CCadText(CCadText& v):CCadObject(OBJECT_TYPE_TEXT)
{

	m_atrb.m_pText = 0;
	m_atrb.m_pFontName = new char[LF_FACESIZE];
	SetP1(v.GetP1());
	m_atrb.CopyFrom(&v.m_atrb);
}

CCadText::~CCadText()
{
}

BOOL CCadText::Create(CPoint ptPos, TextAttributes* pTextAttributes, const char* sText)
{
	BOOL bRet = TRUE;
	SetP1(ptPos);
	if (pTextAttributes){
		m_atrb.CopyFrom(pTextAttributes);
		if (sText)
			m_atrb.SetText(sText);
		else
			m_atrb.SetText("No Text");
	}
	else {
		bRet = FALSE;
	}
    return bRet;
}

CCadObject* CCadText::Copy()
{
	//---------------------------------------
	// Copy
	//		This function creates a copy of
	// the object and returns a pointer to
	// the new object.
	//
	// returns:
	//		pointer to the new object
	//---------------------------------------
	CCadText *pNew = new CCadText(*this);
	return (CCadObject*)pNew;
}

void CCadText::Draw(CDC *pDC, ObjectMode mode,CPoint Offset,CScale Scale)
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
	CFont *pOldFont, fontText;
	CBrush* pOldBrush = 0, brushFill, brushPointFill;
	CPen *pOldPen = 0, penLine, penPoints;
	COLORREF OldTextColor,OldBackgroundColor;
	int FontHeight,FontWidth;
	CPoint P1;
	int OldTransparentMode = 0;
	BOOL bFontCreated = FALSE;

	if (CCadText::m_RenderEnable)
	{
		P1 = (Scale * GetP1()) + Offset;
		FontHeight = int(Scale.m_ScaleX * m_atrb.m_FontHeight);
		FontWidth = int(Scale.m_ScaleX * m_atrb.m_FontWidth);
		//--------------------------------
		// Create the font
		//--------------------------------
		bFontCreated = fontText.CreateFontA(
			FontHeight, 
			FontWidth, 
			m_atrb.m_Angle,
			m_atrb.m_Angle,
			m_atrb.m_Weight, 
			FALSE, 
			FALSE, 
			0, 
			DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS,
			PROOF_QUALITY,
			DEFAULT_PITCH,
			m_atrb.m_pFontName
		);
		switch (mode)
		{
		case ObjectMode::Selected:
			penLine.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
			brushFill.CreateStockObject(NULL_BRUSH);
//			penPoints.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
//			brushPointFill.CreateSolidBrush(RGB(0, 0, 255));
			break;
		case ObjectMode::Sketch:
			penLine.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
			brushFill.CreateStockObject(NULL_BRUSH);
			//			penPoints.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			//			brushPointFill.CreateSolidBrush(RGB(0, 0, 255));
			break;
		case ObjectMode::Erase:
			break;
		case ObjectMode::Final:
			break;
		}
		//--------------------------------
		switch(mode)
		{
		case ObjectMode::Sketch:
			pOldFont = pDC->SelectObject(&fontText);
			pDC->TextOutA(P1.x, P1.y, m_atrb.m_pText, strlen(m_atrb.m_pText));
			// Draw Select Rectangle
			GetTextRectangle(pDC);
			RotateTextRectangle();
//			ScaleTextRectangle(Scale);
			pOldPen = pDC->SelectObject(&penLine);
			pOldBrush = pDC->SelectObject(&brushFill);
			pDC->Polygon(m_pTextRect, 4);
			// clean up
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			pDC->SelectObject(pOldFont);
			break;
		case ObjectMode::Selected:
			//---------- Setup the DC --------------
			pOldFont = pDC->SelectObject(&fontText);
			OldTransparentMode = pDC->SetBkMode(TRANSPARENT);
			OldTextColor = pDC->SetTextColor(RGB(255,0,0));
			//-------- Draw the text ------------
			pDC->TextOutA(P1.x, P1.y, m_atrb.m_pText, strlen(m_atrb.m_pText));
			GetTextRectangle(pDC);
			RotateTextRectangle();
			ScaleTextRectangle(Scale);
			//			ScaleTextRectangle(Scale);
			pOldPen = pDC->SelectObject(&penLine);
			pOldBrush = pDC->SelectObject(&brushFill);
			pDC->Polygon(m_pTextRect, 4);
			//-------- Cleanup ------------
			pDC->SelectObject(pOldFont);
			pDC->SetTextColor(OldTextColor);
			pDC->SetBkMode(OldTransparentMode);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pOldBrush);
			break;
		case ObjectMode::Erase:
			break;
		case ObjectMode::Final:
			OldTextColor = pDC->SetTextColor(m_atrb.m_Color);
			OldBackgroundColor = pDC->SetBkColor(m_atrb.m_BkColor);
			OldTransparentMode = pDC->SetBkMode(m_atrb.m_Transparent);
			pOldFont = pDC->SelectObject(&fontText);
			//-------- Draw the text ------------
			pDC->TextOutA(P1.x, P1.y, m_atrb.m_pText, strlen(m_atrb.m_pText));
			//-------- Cleanup ------------
			pDC->SetBkColor(OldBackgroundColor);
			pDC->SetTextColor(OldTextColor);
			pDC->SelectObject(pOldFont);
			pDC->SetBkMode(OldTransparentMode);
			break;
		}
	}
}

int CCadText::CheckSelected(CPoint p,CSize O)
{
	//-------------------------------------------
	// CheckSelected
	//		This function is used to check to see
	// if the mouse pointer is over this object.
	// It does not check to see if the m_Selected
	// is set and does not set that flag.
	//
	// parameter:
	//		p......point to check
	//-------------------------------------------
	CDC* pDC;
	CFont Font, *pOldFont;
	int Angle;
	int FontHeight, FontWidth;
	CScale Scale;

	Scale = theApp.GetMainView()->GetScale();
	FontHeight = int(Scale.m_ScaleX * m_atrb.m_FontHeight);
	FontWidth = int(Scale.m_ScaleX * m_atrb.m_FontWidth);
	Font.CreateFontA(
		FontHeight,
		FontWidth,
		0,
		0,
		m_atrb.m_Weight,
		FALSE,
		FALSE,
		0,
		DEFAULT_CHARSET,
		OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,
		PROOF_QUALITY,
		DEFAULT_PITCH,
		m_atrb.m_pFontName
	);
	pDC = theApp.GetMainView()->GetDC();
	pOldFont = pDC->SelectObject(&Font);
	GetTextRectangle(pDC, TRUE);
	RotateTextRectangle(TRUE);
	pDC->SelectObject(pOldFont);
	theApp.GetMainView()->ReleaseDC(pDC);
	return theApp.IsPointInPoly(m_pTextRect, 4, p);
}

Tokens CCadText::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	//-----------------------------------------
	// Parse
	//		This function is called to parse
	// a text object from the input file.
	//
	// parameters:
	//		pIN............pointer to the input file
	//		LookAHeadToken...the look ahead token
	//		ppDrawing......pointer to the current drawing
	//		pParser.......pointer to the file parser
	//
	// returns:
	//		the next look ahead token
	//-----------------------------------------
	char* s = new char[256];
	BOOL Loop = TRUE;
	int ColorOrder = 0;

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::TEXT, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	GetAttributes()->SetText(pParser->GetLexBuff());
	LookAHeadToken = pParser->Expect(Tokens::STRING, LookAHeadToken, pIN);
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
		case Tokens::COLOR:
			switch (ColorOrder)
			{
			case 0:
				LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, m_atrb.m_Color, LookAHeadToken);
				ColorOrder++;
				break;
			case 1:
				LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, m_atrb.m_BkColor, LookAHeadToken);
				ColorOrder++;
				break;
			}
			break;
		case Tokens::TEXT_COLOR:
			LookAHeadToken = pParser->Color(Tokens::TEXT_COLOR, pIN, m_atrb.m_Color, LookAHeadToken);
			break;
		case Tokens::BACKGROUND_COLOR:
			LookAHeadToken = pParser->Color(Tokens::BACKGROUND_COLOR, pIN, m_atrb.m_BkColor, LookAHeadToken);
			break;
		case Tokens::FONT:
			LookAHeadToken = pParser->Font(pIN, &m_atrb.m_pFontName, LookAHeadToken);
			break;
		case Tokens::WEIGHT:
			LookAHeadToken = pParser->DecimalValue(Tokens::WEIGHT, pIN, m_atrb.m_Weight, LookAHeadToken);
			break;
		case Tokens::HEIGHT:
			LookAHeadToken = pParser->DecimalValue(Tokens::HEIGHT, pIN, m_atrb.m_FontHeight, LookAHeadToken);
			break;
		case Tokens::FONTHIEGHT:
			LookAHeadToken = pParser->DecimalValue(Tokens::FONTHIEGHT, pIN, m_atrb.m_FontHeight, LookAHeadToken);
			break;
		case Tokens::WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::WIDTH, pIN, m_atrb.m_FontWidth, LookAHeadToken);
			break;
		case Tokens::FONTWIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::FONTWIDTH, pIN, m_atrb.m_FontWidth, LookAHeadToken);
			break;
		case Tokens::ANGLE:
			LookAHeadToken = pParser->DecimalValue(Tokens::ANGLE, pIN, m_atrb.m_Angle, LookAHeadToken);
			break;
		case Tokens::TRANSPARENTbkg:
			LookAHeadToken = pParser->DecimalValue(Tokens::TRANSPARENTbkg, pIN, m_atrb.m_Transparent, LookAHeadToken);
			break;
		case Tokens(')'):
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
			Loop = FALSE;
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
	delete[]s;
	return LookAHeadToken;
}


void CCadText::Save(FILE* pO, int Indent)
{
	//-----------------------------------------
	// Save
	//		This is the functtion that is called
	// when ever you save a file or library
	//
	// parameter:
	//		pO...Pointer to file to store data
	//-----------------------------------------
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];
	char* s5 = new char[64];
	char* s6 = new char[64];
	char* s7 = new char[64];
	char* s8 = new char[64];

	fprintf(pO, "%s%s(\"%s\",%s,%s,%s,%s(\"%s\"),%s,%s,%s,%s,%s)\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::TEXT),
		m_atrb.m_pText,
		CFileParser::SavePoint(s1, 64, Tokens::POINT_1, GetP1()),
		CFileParser::SaveColor(s2, 64, m_atrb.m_Color, Tokens::TEXT_COLOR),
		CFileParser::SaveColor(s3, 64, m_atrb.m_BkColor, Tokens::BACKGROUND_COLOR),
		CFileParser::LookupKeyword(Tokens::FONT),
		m_atrb.m_pFontName,
		CFileParser::SaveDecimalValue(s4, 64, Tokens::WEIGHT, m_atrb.m_Weight),
		CFileParser::SaveDecimalValue(s5, 64, Tokens::FONTHIEGHT, m_atrb.m_FontHeight),
		CFileParser::SaveDecimalValue(s6, 64, Tokens::FONTWIDTH, m_atrb.m_FontWidth),
		CFileParser::SaveDecimalValue(s7, 64, Tokens::ANGLE, m_atrb.m_Angle),
		CFileParser::SaveDecimalValue(s8, 64, Tokens::TRANSPARENTbkg, m_atrb.m_Transparent)
	);
	delete[]s8;
	delete[]s7;
	delete[]s6;
	delete[]s5;
	delete[]s4;
	delete[]s3;
	delete[]s2;
	delete[]s1;
	delete[]s;
}

TextAttributes * CCadText::GetAttributes()
{
	//-------------------------------------------
	// GetAttributes
	//		This function gets a pointer to the
	//	text attribute structure
	//-------------------------------------------
	return &m_atrb;
}

void CCadText::RotateTextRectangle(BOOL bPrint)
{
	//----------------------------------------------
	// Rotate
	//		Thhis function rotates the selection
	// rectangle.
	//
	//		parameters:
	//			pSimplePoly..... pointer to an array
	// of points representing the enclosing polygon
	//
	//----------------------------------------------
	double Ang = double(GetAttributes()->m_Angle)/ 10.0;
	double Pi = atan(1.0) * 4;
	int i;

	Ang *= Pi / 180.0;
	for(i=1;i<4;i++)
	{
		theApp.RotatePoint(m_pTextRect[i], m_pTextRect[0], Ang);
	}
	if (bPrint && theApp.HasConsol())
	{
		printf("Rotated Text Rectangle");
		PrintRect();
	}
}

void CCadText::ScaleTextRectangle(CScale Scale, BOOL bPrint)
{
	m_pTextRect[0] = Scale * m_pTextRect[0];
	m_pTextRect[1] = Scale * m_pTextRect[1];
	m_pTextRect[2] = Scale * m_pTextRect[2];
	m_pTextRect[3] = Scale * m_pTextRect[3];
	if (bPrint && theApp.HasConsol())
	{
		printf("Scaled Text Rectangle");
		PrintRect();
	}
}

CCadText CCadText::operator=(CCadText &v)
{
	//-----------------------------------------------
	// operator=
	//		This function overides the assignment
	//	operator to make a copy of the CCadText
	// object.
	//
	// parameter:
	//		v.....reference to CCadText object to copy
	//-----------------------------------------------
	CCadText* pNewText = new CCadText;

	pNewText->SetP1(v.GetP1());
	pNewText->GetAttributes()->CopyFrom(&v.m_atrb);
	return *pNewText;
}

void CCadText::Move(CPoint p)
{
	//-----------------------------------------------
	// Move
	//		Move the object to a new location.
	//
	// parameters:
	//		p.....New location.
	//-----------------------------------------------
	SetP1(p);
}

int CCadText::GrabVertex(CPoint point)
{
	//-----------------------------------------------
	// GrabVertex
	//		This function returns an index to a vertex
	// that the mouse is over.  CCadText does not
	// have any so it always returns negatory.
	//
	// parameters:
	//		point....point to check against.
	//		Scale....current scale factor
	// returns:
	//		Returns -1 if no vertex is selected
	//		Returns an index , starting at 0 and uup
	//		if a vertex is selected
	//-----------------------------------------------
	return -1;
}

void CCadText::SetVertex(int Vi, CPoint p)
{
	//-----------------------------------------------
	// SetVertex
	//		This function is used to move a vertex to
	// a new location.
	//
	//	parameters:
	//		Vi.....Vertex Index
	//		p......New location
	//-----------------------------------------------
}

CPoint CCadText::GetReference()
{
	//-----------------------------------------
	//	GetReference
	//		This function was added mostly so that
	// I could have a virtual function to do this
	// for all CCadObjects.  Generally, it is jmust
	// m_P1.
	//
	//	returns:
	//		m_P1
	//-----------------------------------------
	return GetP1();
}

void CCadText::GetTextRectangle(CDC *pDC, BOOL bPrint)
{
	//------------------------------------------
	// GetTextRectangle
	//		This function is used to get the
	// rectangle that surrounds the text displayed
	// bu the text object.
	//
	//	parameters:
	//		pDC.....pointer to the device context
	// On entry, the text font needs to be
	// selected into the DC before calling this
	// method.
	// 
	// On exit, m_pTextRect[] contains the
	// in units of pixels
	//------------------------------------------
	CSize cz;
	CScale Scale;
	CPoint P;

	cz = pDC->GetTextExtent(m_atrb.m_pText, strlen(m_atrb.m_pText));
	Scale = theApp.GetScale();
	Scale.m_ScaleX = 1.0/Scale.m_ScaleX;
	Scale.m_ScaleY = 1.0/Scale.m_ScaleY;
	cz = Scale * cz;	// Convert pixels to mils

	P = GetP1();	
	m_pTextRect[0] = P;	
	m_pTextRect[1] = m_pTextRect[0] + CPoint(cz.cx, 0);
	m_pTextRect[2] = m_pTextRect[1] + CPoint(0, cz.cy);
	m_pTextRect[3] = m_pTextRect[0] + CPoint(0, cz.cy);
	if (bPrint && theApp.HasConsol())
	{
		printf("Text Rectangle");
		PrintRect();
	}
}

CSize CCadText::GetTextSize(CDC* pDC)
{

	CSize sz = pDC->GetTextExtent(m_atrb.m_pText, strlen(m_atrb.m_pText));
	return sz;
}

CPoint CCadText::CalcTextShiftonRotation(CPoint p1, CPoint Center, double angle)
{
	//--------------------------------------------
	//	CalcTextShiftonRotation
	//		This function is just a little complicated.
	// What this does is it calculates the point to
	// draw text at for a rotated text object.  This
	// makes it so the text apears to be centered
	// at point p1 at the given angle from the
	// center.
	//
	// parameters:
	//		p1...place you want text
	//		Center...Center of the text rectangle
	//		Angle...Angle in degree
	//
	// returns:
	//		point at wich to paint text.
	//--------------------------------------------
	CPoint rP;
	double r2;
	double dx = double(p1.x - Center.x);
	double dy = double(p1.y - Center.y);

	r2 = sqrt(dx*dx+dy*dy);
	rP.x = int(r2 * cos(angle - 90.0));
	rP.y = int(r2 * sin(angle - 90.0));
	return p1 - rP;
}

void CCadText::AdjustRefernce(CPoint p)
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


CRect CCadText::GetRect()
{
	return CRect();
}

void CCadText::RenderEnable(int e)
{
	CCadText::m_RenderEnable = e;
}

CPoint CCadText::GetCenter()
{
	CRect rect = this->GetRect();
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadText::ChangeCenter(CSize p)
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


CSize CCadText::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadText::ChangeSize(CSize Sz)
{
//	m_P2.x += Sz.cx;
//	m_P2.y += Sz.cy;
}

void CCadText::PrintRect()
{
	int i;
	for(i=0;i<4;i++)
	{
		if(theApp.HasConsol())
			printf("VERTEX[%d](%d,%d)\n",i ,m_pTextRect[i].x,m_pTextRect[i].y);
	}
	if(theApp.HasConsol())
		printf("---------\n");
}
