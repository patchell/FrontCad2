#include "stdafx.h"


CCadDimension::CCadDimension():CCadObject(OBJECT_TYPE_DIMENSION)
{
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
	CCadObject* pObj = 0;

	Diff = p - GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
	pObj = GetHead();
	while (pObj)
	{
		pObj->Move(p);
		pObj = pObj->GetNext();
	}
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

	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
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
	(*ppDrawing)->AddObjectToEnd(this);
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
	CCadObject* pObj = 0;

	fprintf(pO, "%s%s(%s,%s,%s,%s){\n", 
		theApp.IndentString(s,256,Indent),
		CFileParser::LookupKeyword(Tokens::DIMENSION),
		CFileParser::SavePoint(s1,64,Tokens::POINT_1, GetP1()),
		CFileParser::SavePoint(s2, 64, Tokens::POINT_2, GetP2()),
		CFileParser::SaveDecimalValue(s3,64,Tokens::LINE_WIDTH, m_Atrib.m_LineWidth),
		CFileParser::SaveColor(s4,64, m_Atrib.m_Color,Tokens::LINE_COLOR)
	);
	pObj = GetHead();
	while (pObj)
	{
		pObj->Save(pO, Indent + 2);
		pObj = pObj->GetNext();
	}
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
			break;
		case ObjectMode::Sketch:
			pDC->MoveTo(P1);
			pDC->LineTo(P2);
			break;
		case ObjectMode::Erase:
			break;
		}
		pDC->SelectObject(pOld);
		//---------------------------------------------
		// Draw the cild objects
		//---------------------------------------------
		CCadObject* pO = GetHead();
		while (pO)
		{
			pO->Draw(pDC, mode, Offset, Scale);
			pO = pO->GetNext();
		}
	}
}

int CCadDimension::CheckSelected(CPoint p,CSize O)
{
	int rV = 0;
	CPoint P1 = GetP1() + O;
	CPoint P2 = GetP2() + O;
	int s1 = 0, s2 = 0;
	CCadObject* pObj = 0;

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
	pObj = GetHead();
	while (pObj)
	{
		rV |= pObj->CheckSelected(p, O);
		pObj = pObj->GetNext();
	}
	return rV;
}

CPoint CCadDimension::GetReference()
{
	return GetP1();
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
	CCadObject* pObj = 0;

	SetP1(GetP1() - Ref);
	SetP2(GetP2() - Ref);
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
	CCadText* pText = 0;
	CCadObject* pObj = 0;

	pObj = GetHead();
	while (pObj)
	{
		if (pObj->GetType() == OBJECT_TYPE_TEXT)
		{
			pText = (CCadText*)pObj;
			break;
		}
		pObj = pObj->GetNext();
	}
	if (pText)
	{
		if (P1.x == P2.x)	//vertical facing dimension
		{
			Dim = P1.x - Org.x;
			SetValue(Dim, 3);
			rect = pText->GetRect();
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
			rect = pText->GetRect();
			if (P1.x > P2.x)
				ofx = rect.Width() + 60;
			else
				ofx = -60;
			off = CSize(ofx, rect.Height() / 2);
		}
		pText->SetP1(P2 - off);
	}
}

void CCadDimension::SetValue(int v, int dp)
{
	int Intpart, Fracpart, Div;
	CCadText* pText = 0;

	Div = 1;

	int i;

	for (i = 0; i < dp; ++i)
		Div *= 10;
	Intpart = v / Div;
	Fracpart = v % Div;
	Fracpart = int(((double)Fracpart / (double)Div) * double(Div));
	char *s = new char[32];
	sprintf_s(s,32, "%d.%03d", Intpart,Fracpart);
	pText = GetTextObject();
	if (pText)
		pText->SetText(s);
	delete[] s;

}

void CCadDimension::RemoveObject(CCadObject *pO)
{
		MessageBox(NULL, "Remove Only TEXT objects in DIMENSION", "ERROR", MB_OK | MB_ICONHAND);
}

CCadText* CCadDimension::GetTextObject(void)
{
	CCadObject* pObj = 0;

	pObj = GetHead();
	while (pObj)
	{
		if (pObj->GetType() == OBJECT_TYPE_TEXT)
		{
			return (CCadText*)pObj;
		}
		pObj = pObj->GetNext();
	}		
	return NULL;
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
	CCadText* pText = 0;

	pText = GetTextObject();
	if (pText)
		pText->SetFontName(pN);
}

char * CCadDimension::GetFontName()
{
	CCadText* pText = 0;
	char* pFN = 0;

	pText = GetTextObject();
	if(pText)
		pFN = pText->GetFontName();
	return pFN;
}
