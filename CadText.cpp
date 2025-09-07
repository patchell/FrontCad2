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
	CopyAttributes(&this->m_atrb,&v.m_atrb);
	this->m_SelRect = v.m_SelRect;
}

CCadText::~CCadText()
{
}

BOOL CCadText::Create(CPoint ptPos, TextAttributes* pTextAttributes)
{
	BOOL bRet = TRUE;
	SetP1(ptPos);
	if (pTextAttributes){
		m_atrb.CopyFrom(pTextAttributes);
	}
	else {
		bRet = FALSE;
	}
    return 0;
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
	CPen *pOldPen = 0, penLine;
	COLORREF OldColor,OldBk;
	int FontHeight,FontWidth;
	CPoint P1;
	int OldMode;

	if (CCadText::m_RenderEnable)
	{
		P1 = (Scale * GetP1()) + Offset;
		FontHeight = int(Scale.m_ScaleX * m_atrb.m_FontHeight);
		FontWidth = int(Scale.m_ScaleX * m_atrb.m_FontWidth);
		CRect rect = GetTextRectangle(pDC, Scale);
		Rotate(m_atrb.m_Angle, rect, m_SelRect);
		switch (mode)
		{
		case ObjectMode::Selected:
				penLine.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				[[fallthrough]];
		case ObjectMode::Sketch:
		case ObjectMode::Final:
			if (Scale.m_ScaleY > 0.0)
				fontText.CreateFont(FontHeight, FontWidth, m_atrb.m_Angle, m_atrb.m_Angle,
					m_atrb.m_Weight, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
					CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH,
					m_atrb.m_pFontName);
			else
				fontText.CreateFont(FontHeight, FontWidth, -m_atrb.m_Angle, -m_atrb.m_Angle,
					m_atrb.m_Weight, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS,
					CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH,
					m_atrb.m_pFontName);

			break;
		}
	
		OldColor = pDC->SetTextColor(m_atrb.m_Color);
		OldBk = pDC->SetBkColor(m_atrb.m_BkColor);
		pOldFont = pDC->SelectObject(&fontText);
		if (m_atrb.m_Transparent)
			OldMode = pDC->SetBkMode(TRANSPARENT);
		else
			OldMode = pDC->SetBkMode(OPAQUE);
		pDC->TextOut(P1.x, P1.y, m_atrb.m_pText, strlen(m_atrb.m_pText));
		pDC->SetBkMode(OldMode);
		if (mode == ObjectMode::Selected)
		{
			pOldPen = pDC->SelectObject(&penLine);
			pDC->MoveTo(Scale * m_SelRect.GetAttributes()->m_pVertex[0] + Offset);
			pDC->LineTo(Scale * m_SelRect.GetAttributes()->m_pVertex[1] + Offset);
			pDC->LineTo(Scale * m_SelRect.GetAttributes()->m_pVertex[2] + Offset);
			pDC->LineTo(Scale * m_SelRect.GetAttributes()->m_pVertex[3] + Offset);
			pDC->LineTo(Scale * m_SelRect.GetAttributes()->m_pVertex[0] + Offset);
			pDC->SelectObject(pOldPen);
		}
		pDC->SetBkColor(OldBk);
		pDC->SetTextColor(OldColor);
		pDC->SelectObject(pOldFont);
	}
}

void CCadText::SetText(const char *s)
{
	//----------------------------------------
	// SetText
	//		This function changes the text that
	// is displayed by the CCadTexst oibject
	//
	// parameter:
	//		s......pointer to string to display
	//----------------------------------------
	GetAttributes()->SetText(s);
	// create the selection rectangle
	CRect rect = GetTextRectangle();
	Rotate(m_atrb.m_Angle,rect,m_SelRect);
}

void CCadText::SetAngle(int e)
{
	//----------------------------------------
	// SetAngle
	//		This function sets the angle to paint
	// the text at.
	//
	// parameters:
	//		e.....Angle, in tenths of a degree
	//----------------------------------------
	m_atrb.m_Angle = e;
	CRect rect = GetTextRectangle();
	Rotate(m_atrb.m_Angle,rect,this->m_SelRect);
}

void CCadText::GetText(char *s,int n)
{
	//---------------------------------------
	// GetText
	//		This function retrieves the text
	// thatis being displayed.
	//
	// parameters:
	//		s.....pointer to array to put text into
	//		n.....maximum number of chars to copy
	//---------------------------------------
	strcpy_s(s, n, (const char *)m_atrb.m_pText);
}

void CCadText::SettAttrib(TextAttributes &atrb)
{
	//--------------------------------------
	// AetAttrib
	//
	//		This function sets the CCadText
	// attributes.
	//
	// parameters:
	//		atrb....reference to attribute structure
	//--------------------------------------
	m_atrb.m_Color = atrb.m_Color;
	m_atrb.m_BkColor = atrb.m_BkColor;
	m_atrb.m_Angle = atrb.m_Angle;
	m_atrb.m_FontHeight = atrb.m_FontHeight;
	m_atrb.m_FontWidth = atrb.m_FontWidth;
	m_atrb.m_Transparent = atrb.m_Transparent;
	m_atrb.m_Weight = atrb.m_Weight;
	SetFontName(atrb.m_pFontName);
	SetText(atrb.m_pText);
}

void CCadText::SetFontName(char *s)
{
	//-----------------------------------------
	// SetFontName
	//		This function is useed to set the
	// name of the font that is used to paint
	// the text.
	//
	// parameter:
	//		s.....pointer to new font name
	//-----------------------------------------
	GetAttributes()->SetFontName(s);
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
	return m_SelRect.PointEnclosed(p);
}

Tokens CCadText::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	char* s = new char[256];
	BOOL Loop = TRUE;
	int ColorOrder = 0;

	LookAHeadToken = pParser->Expect(Tokens::TEXT, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	while (Loop)
	{
		switch (LookAHeadToken)
		{
		case Tokens::STRING:
			strcpy_s(s, 256, pParser->GetLexBuff());
			LookAHeadToken = pParser->Expect(Tokens::STRING, LookAHeadToken, pIN);
			break;
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
	SetText(s);
	(*ppDrawing)->AddObject(this);
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

void CCadText::Rotate(int Angle,CRect rect,CCadPolygon &Poly)
{
	//----------------------------------------------
	// Rotate
	//		Thhis function rotates the selection
	// rectangle.
	//
	//		parameters:
	//			Angle....Angle to rotate by in tenths of a degree
	//			rect.....None Rotated Rectangle
	//			Poly.....Reference to a Polygon that
	//						The rotated rectangle is put in
	//----------------------------------------------
	Poly.Reset();
	double Ang = double(Angle)/ 10.0;
	double Pi = atan(1.0) * 4;
	Ang = Ang * Pi / 180.0;
	CPoint p,p1;
	p.x = (int)(rect.Width() * cos(Ang)) + rect.TopLeft().x;
	p.y = -(int)(rect.Width() * sin(Ang)) + rect.TopLeft().y;
	Poly.AddPoint(p, TRUE, TRUE);
	Poly.AddPoint(rect.TopLeft(), TRUE, TRUE);
	p1.x = (int)(rect.Height() * sin(Ang)) + rect.TopLeft().x;
	p1.y = (int)(rect.Height() * cos(Ang)) + rect.TopLeft().y;
	Poly.AddPoint(p1, TRUE, TRUE);
	p.x = (int)(rect.Width() * cos(Ang)) + rect.TopLeft().x;
	p.y = -(int)(rect.Width() * sin(Ang)) + rect.TopLeft().y;
	p = p + p1 - rect.TopLeft();
	Poly.AddPoint(p, TRUE, TRUE);
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
	m_atrb.m_pText = 0;
	SetP1(v.GetP1());
	CopyAttributes(&this->m_atrb,&v.m_atrb);
	this->m_SelRect =v.m_SelRect;
	return *this;
}

void CCadText::CopyAttributes(TextAttributes *d, TextAttributes *s)
{
	//------------------------------------------------
	// CopyAttriutes
	//		This function copies a TextAttributes
	// Structure.
	//
	//	parameters:
	//		d.....Detination pointer
	//		s.....Source Pointer
	//------------------------------------------------
	d->m_Color = s->m_Color;
	d->m_BkColor = s->m_BkColor;
	d->m_Angle = s->m_Angle;
	d->m_FontHeight = s->m_FontHeight;
	d->m_FontWidth = s->m_FontWidth;
	d->m_Format = s->m_Format;
	d->m_Transparent = s->m_Transparent;
	d->m_Weight = s->m_Weight;
	strcpy_s(d->m_pFontName, LF_FACESIZE,s->m_pFontName);
	if(s->m_pText)
	{
		if(d->m_pText) delete[] d->m_pText;
		int len = strlen(s->m_pText) + 1;
		d->m_pText = new char[len];
		strcpy_s(d->m_pText,len,s->m_pText);
	}
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
	CRect rect = GetTextRectangle();
	Rotate(m_atrb.m_Angle,rect,m_SelRect);
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

char * CCadText::GetText()
{
	//----------------------------------------
	// GetText
	//		This function returns a pointer to
	// the string that is being displayed by
	// by the text object
	//----------------------------------------
	return this->m_atrb.m_pText;
}


CRect CCadText::GetTextRectangle()
{
	//------------------------------------------
	// GetTextRectangle
	//		This function is used to get the
	// rectangle that surrounds the text displayed
	// bu the text object.
	//------------------------------------------
	CWnd *pW = CWnd::GetActiveWindow();
	CDC *pDC = pW->GetDC();
	//	CDC *pDC = ((CFrontCadApp *)AfxGetApp())->m_pMainView->GetDC();
	CFont font,*old;
	font.CreateFont(m_atrb.m_FontHeight,m_atrb.m_FontWidth,0,0,
			m_atrb.m_Weight,0,0,0,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS,PROOF_QUALITY,DEFAULT_PITCH,
			m_atrb.m_pFontName);
	old = pDC->SelectObject(&font);
	CSize cz = pDC->GetTextExtent(m_atrb.m_pText,strlen(m_atrb.m_pText));
	pDC->SelectObject(old);
	CRect rect;
	rect.SetRect(GetP1(), GetP1() + CPoint(cz.cx, cz.cy));
	char *s = new char[256];
	sprintf_s(s, 256, "Text Rect:p1=%d,%d p2=%d,%d", rect.left, rect.top, rect.right, rect.bottom);
	((CFrontCadApp *)AfxGetApp())->WriteToLogFile(s);

	delete[] s;
	return rect;
}

CRect CCadText::GetTextRectangle(CDC *pDC, CScale Scale)
{
	//------------------------------------------
	// GetTextRectangle
	//		This function is used to get the
	// rectangle that surrounds the text displayed
	// bu the text object.
	//
	//	parameters:
	//		pDC.....pointer to the device context
	//		Scale...Scale factor for display
	//------------------------------------------
	CFont font,*old;
	font.CreateFont(int(m_atrb.m_FontHeight * Scale.m_ScaleX),int(m_atrb.m_FontWidth * Scale.m_ScaleX),0,0,
			m_atrb.m_Weight,0,0,0,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS,PROOF_QUALITY,DEFAULT_PITCH,
			m_atrb.m_pFontName);
	old = pDC->SelectObject(&font);
	CSize cz = pDC->GetTextExtent(m_atrb.m_pText,strlen(m_atrb.m_pText));
	pDC->SelectObject(old);
	CRect rect;
	Scale.m_ScaleX = 1.0/Scale.m_ScaleX;
	Scale.m_ScaleY = 1.0/Scale.m_ScaleY;
	cz = Scale * cz;
	rect.SetRect(GetP1(), GetP1() + CPoint(cz.cx, cz.cy));
	return rect;
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
	return GetTextRectangle();
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
