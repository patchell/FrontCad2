#include "stdafx.h"


CCadDimension::CCadDimension():CCadObject(OBJECT_TYPE_DIMENSION)
{
	//TextAttributes* pAtrb;
	
	//pAtrb = m_Text.GetAttributes();
	//pAtrb->m_Angle = 0;
	//pAtrb->m_BkColor = RGB(255, 255, 255);
	//pAtrb->m_Color = RGB(0, 0, 0);
	//pAtrb->m_FontHeight = 200;
	//pAtrb->m_FontWidth = 0;
	//pAtrb->m_Format = DT_BOTTOM | DT_SINGLELINE;
	//pAtrb->m_pFontName = new char[LF_FACESIZE];
	//strcpy_s(pAtrb->m_pFontName, LF_FACESIZE, "Arial");
	//pAtrb->m_pText = new char[32];
	//pAtrb->m_Transparent = 1;
	//pAtrb->m_Weight = FW_DEMIBOLD;
}

CCadDimension::CCadDimension(CCadDimension &cd) :CCadObject(OBJECT_TYPE_DIMENSION)
{
	SetP1(cd.GetP1());
	SetP2(cd.GetP2());
	m_Atrib.CopyFrom(&cd.m_Atrib);
}

CCadDimension::~CCadDimension()
{
}

BOOL CCadDimension::Create(CPoint ptPos, DimAttrib* pDimAttributes)
{
	BOOL rV = TRUE;

	SetP1(ptPos);
	SetP2(ptPos);
	rV = GetAttributes()->Create(pDimAttributes);
    return rV;
}

CCadObject* CCadDimension::Copy()
{
	CCadDimension* pNew = new CCadDimension(*this);
	return (CCadObject*)pNew;
}

CCadDimension CCadDimension::operator=(CCadDimension &v)
{
	CCadDimension* pNew = new CCadDimension(*this);
	return *pNew;
}

void CCadDimension::Move(CPoint p)
{
	CPoint Diff;
	Diff = p - GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
	GetAttributes()->m_Text.Move(GetAttributes()->m_Text.GetP1() + Diff);
}

Tokens CCadDimension::Parse(
	FILE* pIN, 
	Tokens LookAHeadToken, 
	CCadDrawing** ppDrawing, 
	CFileParser* pParser
)
{
	BOOL Loop = TRUE;
	char* s = new char[256];
	int PointOrder = 0;

	LookAHeadToken = pParser->Expect(Tokens::DIMENSION, LookAHeadToken, pIN);
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
		case Tokens::POINT_1:
			LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::POINT_2:
			LookAHeadToken = pParser->Point(Tokens::POINT_2, pIN, GetP2(), LookAHeadToken);
			break;
		case Tokens::WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens::LINE_WIDTH:
			LookAHeadToken = pParser->DecimalValue(Tokens::LINE_WIDTH, pIN, GetAttributes()->m_LineWidth, LookAHeadToken);
			break;
		case Tokens::COLOR:
			LookAHeadToken = pParser->Color(Tokens::COLOR, pIN, GetAttributes()->m_Color, LookAHeadToken);
			break;
		case Tokens::LINE_COLOR:
			LookAHeadToken = pParser->Color(Tokens::LINE_COLOR, pIN, GetAttributes()->m_Color, LookAHeadToken);
			break;
		case Tokens(','):
			LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
			break;
		case Tokens(')'):
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
			break;
		case Tokens('{'):
			LookAHeadToken = pParser->Expect(Tokens('{'), LookAHeadToken, pIN);
			LookAHeadToken = pParser->DrawObjects(pIN, LookAHeadToken, this);
			break;
		case Tokens('}'):
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
	LookAHeadToken = pParser->Expect(Tokens('}'), LookAHeadToken, pIN);
	(*ppDrawing)->AddObject(this);
	delete[] s;
	return LookAHeadToken;
}

void CCadDimension::Save(FILE *pO,  int Indent)
{
	char* s = new char[256];
	char* s1 = new char[64];
	char* s2 = new char[64];
	char* s3 = new char[64];
	char* s4 = new char[64];

	fprintf(pO, "%s%s(%s,%s,%s,%s){\n", 
		theApp.IndentString(s,256,Indent),
		CFileParser::LookupKeyword(Tokens::DIMENSION),
		CFileParser::SavePoint(s1,64,Tokens::POINT_1, GetP1()),
		CFileParser::SavePoint(s2, 64, Tokens::POINT_2, GetP2()),
		CFileParser::SaveDecimalValue(s3,64,Tokens::LINE_WIDTH, m_Atrib.m_LineWidth),
		CFileParser::SaveColor(s4,64, m_Atrib.m_Color,Tokens::LINE_COLOR)
	);
	GetAttributes()->m_Text.Save(pO,Indent+4);
	fprintf(pO, "%s}\n",s);
	delete[]s4;
	delete[]s3;
	delete[]s2;
	delete[]s1;
	delete[]s;
}

void CCadDimension::SetVertex(int Vi, CPoint p)
{
}

int CCadDimension::GrabVertex(CPoint p)
{
	int rV = -1;
	return rV;
}

void CCadDimension::Draw(CDC *pDC, ObjectMode mode, CPoint Offset, CScale Scale)
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
	CPen *pOld, penLine;
	CRect rect;
	CPoint P1, P2;
	int Lw;

	if (CCadDimension::m_RenderEnable)
	{
		P1 = (Scale * GetP1()) + Offset;
		P2 = (Scale * GetP2()) + Offset;
		Lw = int(Scale.m_ScaleX * m_Atrib.m_LineWidth);
		if (Lw < 1) Lw = 1;
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
		pOld = pDC->SelectObject(&penLine);
		switch (mode)
		{
		case ObjectMode::Selected:
		case ObjectMode::Final:
			pDC->MoveTo(P1);
			pDC->LineTo(P2);
			GetAttributes()->m_Text.Draw(pDC, mode, Offset, Scale);
			break;
		case ObjectMode::Sketch:
			pDC->MoveTo(P1);
			pDC->LineTo(P2);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOld);
	}
}

int CCadDimension::CheckSelected(CPoint p,CSize O)
{
	int rV = 0;
	CPoint P1 = GetP1() + O;
	CPoint P2 = GetP2() + O;
	int s1 = 0, s2 = 0;

	if (P1.x == P2.x)
	{
		s1 = 20;
		s2 = 0;
	}
	else if (P1.y == P2.y)
	{
		s2 = 20;
		s1 = 0;
	}
	CSize rOff = CSize(s1, s2);
	P1 += rOff;
	P2 -= rOff;
	CRect rect;
	rect.SetRect(P1, P2);
	rect.NormalizeRect();
	rV = rect.PtInRect(p);
	rV |= GetAttributes()->m_Text.CheckSelected(p);
	return rV;
}

CPoint CCadDimension::GetReference()
{
	return GetP1();
}

void CCadDimension::SetSelected(int Flag)
{
	CCadObject::SetSelected(Flag);
	GetAttributes()->m_Text.SetSelected(Flag);
}

void CCadDimension::AdjustRefernce(CPoint Ref)
{
	//-----------------------------------------
	//	AdjustRefernce
	//		Thhis function is used to normalize
	//	the location of points in the object
	// relative to a point choseen on the
	// drawing.
	//	parameters:
	//		Ref.....selected reference point
	//-----------------------------------------
	SetP1(GetP1() - Ref);
	SetP2(GetP2() - Ref);
	GetAttributes()->m_Text.AdjustRefernce(Ref);
	CPoint Org = ((CFrontCadApp *)AfxGetApp())->GetMainView()->GetOrigin();
	UpdateText(Org);
}

CRect CCadDimension::GetRect(void)
{
	CRect rR;
	return rR;
}

void CCadDimension::UpdateText(CPoint Org)
{
	CPoint P1, P2;
	P1 = GetP1();
	P2 = GetP2();
	int Dim,ofx;
	CRect rect;
	CSize off;

	if (P1.x == P2.x)	//vertical facing dimension
	{
		Dim = P1.x - Org.x;
		SetValue(Dim, 3);
		GetAttributes()->m_Text.SetAngle(-900);
		rect = GetAttributes()->m_Text.GetRect();
		if (P1.y > P2.y)
			ofx = -(rect.Width() + 60);
		else
			ofx = 60;
		off = CSize(-rect.Height() / 2, -ofx);
	}
	else if (P1.y == P2.y)	//horizontal facing dimension
	{
		Dim = -(P2.y - Org.y);
		SetValue(Dim, 3);
		rect = GetAttributes()->m_Text.GetRect();
		if (P1.x > P2.x)
			ofx = rect.Width()+60;
		else
			ofx = -60;
		off = CSize(ofx, rect.Height() / 2);
	}
	GetAttributes()->m_Text.SetP1(P2 - off);
}

void CCadDimension::SetValue(int v, int dp)
{
	int Intpart, Fracpart, Div;

	Div = 1;

	int i;

	for (i = 0; i < dp; ++i)
		Div *= 10;
	Intpart = v / Div;
	Fracpart = v % Div;
	Fracpart = int(((double)Fracpart / (double)Div) * double(Div));
	char *s = new char[32];
	sprintf_s(s,32, "%d.%03d", Intpart,Fracpart);
	GetAttributes()->m_Text.SetText(s);
	delete[] s;

}

void CCadDimension::RemoveObject(CCadObject *pO)
{
		MessageBox(NULL, "Remove Only TEXT objects in DIMENSION", "ERROR", MB_OK | MB_ICONHAND);
}

void CCadDimension::RenderEnable(int e)
{
	CCadDimension::m_RenderEnable = e;
}


void CCadDimension::AlignToPoint(CPoint p)
{
	if (GetP1().x == GetP2().x)	//vertical dimension
	{
		SetP1X(p.x);
		SetP2X(p.x);
	}
	else if (GetP1().y == GetP2().y)	//Horizontal dimension
	{
		SetP1Y(p.y);
		SetP2Y(p.y);
	}
}

CPoint CCadDimension::GetCenter()
{
	return GetP1();
}

// Moves the center of the object to the spcified point
void CCadDimension::ChangeCenter(CSize p)
{
}


CSize CCadDimension::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadDimension::ChangeSize(CSize Sz)
{
}


void CCadDimension::SetFontName(char * pN)
{
	GetAttributes()->m_Text.SetFontName(pN);
}


char * CCadDimension::GetFontName()
{
	return GetAttributes()->m_Text.GetFontName();
}
