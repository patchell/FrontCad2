// CadPolygonFill.cpp: implementation of the CCadPolygonFill class.
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

CCadPolygonFill::CCadPolygonFill():CCadPolygon(100)
{
	m_pBrFill = 0;
	m_FillColor = RGB(0, 0, 0);
	SetType(OBJECT_TYPE_POLYFILL);
}

CCadPolygonFill::CCadPolygonFill(int size):CCadPolygon(size)
{
	m_pBrFill = 0;
	m_FillColor = RGB(0, 0, 0);
	SetType(OBJECT_TYPE_POLYFILL);
}

CCadPolygonFill::~CCadPolygonFill()
{
	if(m_pBrFill)delete m_pBrFill;
}

void CCadPolygonFill::Draw(CDC *pDC,int mode,CPoint Offset,CScale Scale)
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
	if (CCadPolygonFill::m_RenderEnable)
	{
		CPen *oldpen;
		CBrush *oldBrush;
		int Lw;
		if ((Lw = int(Scale.m_ScaleX * m_Width)) < 1) Lw = 1;
		int i = 0;
		//-----------------------
		// need to scale the
		// verticies
		//-----------------------
		CPoint *pP = new CPoint[m_Count];
		for (i = 0; i < m_Count; ++i)
			pP[i] = Scale * m_pVertex[i] + Offset;

		if ((GetLastMode() != mode) || GetDirty())
		{
			if (m_pPenLine) delete m_pPenLine;
			switch (mode)
			{
			case OBJECT_MODE_FINAL:
				m_pPenLine = new CPen(PS_SOLID, Lw, m_LineColor);
				break;
			case OBJECT_MODE_SELECTED:
				m_pPenLine = new CPen(PS_SOLID, Lw, RGB(200, 50, 50));
				break;
			case OBJECT_MODE_SKETCH:
				m_pPenLine = new CPen(PS_DOT, 1, m_LineColor);
				break;
			}
		}
		if ((m_pBrFill == 0) || GetDirty())
		{
			SetDirty(0);
			if (m_pBrFill) delete m_pBrFill;
			m_pBrFill = new CBrush(m_FillColor);
		}
		switch (mode)
		{
		case OBJECT_MODE_FINAL:
			oldpen = pDC->SelectObject(m_pPenLine);
			oldBrush = pDC->SelectObject(m_pBrFill);
			pDC->Polygon(pP, m_Count);
			pDC->SelectObject(oldBrush);
			pDC->SelectObject(oldpen);
			SetLastMode(mode);
			break;
		case OBJECT_MODE_SELECTED:
			oldpen = pDC->SelectObject(m_pPenLine);
			i = 0;
			pDC->MoveTo(pP[i]);
			for (i = 1; i < this->m_Count; ++i)
				pDC->LineTo(pP[i]);
			pDC->LineTo(pP[0]);
			for (i = 0; i < this->m_Count; ++i)
			{
				CPoint p1, p2, p;
				p = pP[i];
				p1 = p + CPoint(4, 4);
				p2 = p - CPoint(4, 4);
				CRect rect;
				rect.SetRect(p2, p1);
				pDC->Rectangle(&rect);
			}
			pDC->SelectObject(oldpen);
			SetLastMode(mode);
			break;
		case OBJECT_MODE_SKETCH:
			oldpen = pDC->SelectObject(m_pPenLine);
			i = 0;
			pDC->MoveTo(pP[i]);
			for (i = 1; i < this->m_Count; ++i)
				pDC->LineTo(pP[i]);
			pDC->SelectObject(oldpen);
			SetLastMode(mode);
			break;
		case OBJECT_MODE_ERASE:
			break;
		}
	}
}

int CCadPolygonFill::Parse(FILE* pIN, int LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	LookAHeadToken = pParser->Expect(TOKEN_POLYFILL, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect('(', LookAHeadToken, pIN);
	LookAHeadToken = PolyParams(pIN, LookAHeadToken, ppDrawing, pParser);
	LookAHeadToken = pParser->Expect(')', LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect('{', LookAHeadToken, pIN);
	LookAHeadToken = Vertex(pIN, LookAHeadToken, ppDrawing, pParser);
	LookAHeadToken = pParser->Expect('}', LookAHeadToken, pIN);
	(*ppDrawing)->AddObject(this);
	return LookAHeadToken;
}

int CCadPolygonFill::PolyParams(FILE* pIN, int LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	//--------------------------------------------------------
	// PolyParams	-> LINECOLOR '(' COLOR ')'
	//				-> FILLCOLOR '(' COLOR ')'
	//				-> LINEWIDTH '(' NUMBER ')'
	//				-> .
	//--------------------------------------------------------
	BOOL Loop = 1;
	while (Loop)
	{
		switch (LookAHeadToken)
		{
		case ',':
			LookAHeadToken = pParser->Expect(',', LookAHeadToken, pIN);
			break;
		case TOKEN_LINE_COLOR:
			LookAHeadToken = pParser->Color(TOKEN_LINE_COLOR, pIN, m_LineColor, LookAHeadToken);
			break;
		case TOKEN_FILL_COLOR:
			LookAHeadToken = pParser->Color(TOKEN_FILL_COLOR, pIN, m_FillColor, LookAHeadToken);
			break;
		case TOKEN_LINE_WIDTH:
			LookAHeadToken = pParser->DecimalValue(TOKEN_LINE_WIDTH, pIN, m_Width, LookAHeadToken);
			break;
		default:
			Loop = FALSE;
			break;
		}
	}
	return LookAHeadToken;
}

int CCadPolygonFill::Vertex(FILE* pIN, int LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	//--------------------------------------------------------
	// Vertex		-> VERTEX '(' NUMBEER ')' '[' VertexList ']';
	//--------------------------------------------------------
	LookAHeadToken = pParser->DecimalValue(TOKEN_VERTEX, pIN, m_Count, LookAHeadToken);
	LookAHeadToken = pParser->Expect('[', LookAHeadToken, pIN);
	LookAHeadToken = VertexList(pIN, LookAHeadToken, ppDrawing, pParser);
	LookAHeadToken = pParser->Expect(']', LookAHeadToken, pIN);
	return LookAHeadToken;
}

int CCadPolygonFill::VertexList(FILE* pIN, int LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	//--------------------------------------------------------
	// VertexList	-> VERTEX_POINT '(' NUMBER ',' NUMBER ')' VertexList1;
	//--------------------------------------------------------
	LookAHeadToken = pParser->Point(TOKEN_VERTEX_POINT, pIN, m_pVertex[m_InCount++], LookAHeadToken);
	LookAHeadToken = VertexList1(pIN, LookAHeadToken, ppDrawing, pParser);
	return LookAHeadToken;
}

int CCadPolygonFill::VertexList1(FILE* pIN, int LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	switch (LookAHeadToken)
	{
	case ',':
		LookAHeadToken = pParser->Expect(',', LookAHeadToken, pIN);
		LookAHeadToken = VertexList(pIN, LookAHeadToken, ppDrawing, pParser);
		break;
	}
	return LookAHeadToken;
}

void CCadPolygonFill::Save(FILE *pO,  int Indent)
{
	char* Indent1 = new char[256];
	char* Indent2 = new char[256];
	char* Indent3 = new char[256];
	char* s3 = new char[64];
	char* s4 = new char[64];
	char* s5 = new char[64];
	char* s6 = new char[64];

	Indent1 = theApp.IndentString(Indent1, 256, Indent);
	Indent2 = theApp.IndentString(Indent2, 256, Indent + 4);
	Indent3 = theApp.IndentString(Indent3, 256, Indent + 8);

	fprintf(pO, "%s%s(%s,%s,%s)\n%s{\n%s%s\n%s[\n",
		Indent1,
		CFileParser::TokenLookup(TOKEN_POLYFILL),
		CFileParser::SaveColor(s3, 64, m_LineColor, TOKEN_LINE_COLOR),
		CFileParser::SaveColor(s6, 64, m_FillColor, TOKEN_FILL_COLOR),
		CFileParser::SaveDecimalValue(s4, 64, TOKEN_LINE_WIDTH, m_Width),
		Indent1,
		Indent2,
		CFileParser::SaveDecimalValue(s5, 64, TOKEN_VERTEX, m_Count),
		Indent2
	);
	for (int i = 0; i < m_Count; ++i)
	{
		fprintf(pO, "%s%s",
			Indent3,
			CFileParser::SavePoint(s4, 64, TOKEN_VERTEX_POINT, m_pVertex[i])
		);
		if (i < (m_Count - 1))
			fprintf(pO, ",\n");
		else
			fprintf(pO, "\n%s]\n%s}\n", Indent2, Indent1);
	}
	delete[]s6;
	delete[]s5;
	delete[]s4;
	delete[]s3;
	delete[]Indent2;
	delete[]Indent1;
}

CCadPolygonFill CCadPolygonFill::operator=(CCadPolygonFill &v)
{
	this->m_pPenLine =0;
	this->m_pBrFill = 0;
	m_size = v.m_size;
	m_Count = v.m_Count;
	m_Width = v.m_Width;
	this->m_FillColor = v.m_FillColor;
	m_LineColor = v.m_LineColor;
	m_MaxY = v.m_MaxY;
	m_MinY = v.m_MinY;
	m_MaxX = v.m_MaxX;
	m_MinX = v.m_MinX;
	m_PolyID = v.m_PolyID;
	for(int i=0;i<m_Count	;++i)
		m_pVertex[i] = v.m_pVertex[i];
	return *this;
}


CPoint CCadPolygonFill::GetCenter()
{
	CRect rect = this->GetRect();
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadPolygonFill::ChangeCenter(CSize p)
{
	SetP1(GetP1() - p);
	int i;
	for (i = 0; i<m_Count; ++i)
		m_pVertex[i] -= p;
	UpdateMinMax();
}



CSize CCadPolygonFill::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadPolygonFill::ChangeSize(CSize Sz)
{
}
