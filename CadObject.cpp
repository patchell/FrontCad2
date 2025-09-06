// CadObject.cpp: implementation of the CCadObject class.
//
///////////////////////////////////////////////

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

ObjectTypeMembers TypeLUT[] = {
	{"None",OBJECT_TYPE_NONE},
	{"Line",OBJECT_TYPE_LINE},
	{"Rectangle",OBJECT_TYPE_RECT},
	{"Ellipse",OBJECT_TYPE_ELLIPSE},
	{"Rounded Rect",OBJECT_TYPE_RNDRECT},
	{"Polygon",OBJECT_TYPE_POLY},
	{"Filled Poly",OBJECT_TYPE_POLYFILL},
	{"Lib Obj",OBJECT_TYPE_LIBCOMP},
	{"Round Hole",OBJECT_TYPE_HOLEROUND},
	{"Rect Hole",OBJECT_TYPE_HOLERECT},
	{"Rnd Hole 1 flat",OBJECT_TYPE_HOLERND1FLAT},
	{"Rnd Hole 2 flats",OBJECT_TYPE_HOLERND2FLAT},
	{"Text",OBJECT_TYPE_TEXT},
	{"Arc",OBJECT_TYPE_ARC},
	{"Arc Centered",OBJECT_TYPE_ARCCENTERED},
	{"Drawing",OBJECT_TYPE_DRAWING},
	{"Bitmap",OBJECT_TYPE_BITMAP},
	{"Arrow",OBJECT_TYPE_ARROW},
	{"Origin",OBJECT_TYPE_ORIGIN},
	{"Dimension",OBJECT_TYPE_DIMENSION},
	{"PrintRect",OBJECT_TYPE_PRINTRECT},
	{"Circle",OBJECT_TYPE_CIRCLE},
	{NULL,-1}
};

const char* CCadObject::LookupTypeName(int TypeToken)
{
	int i;
	const char* s = 0;
	BOOL Loop = TRUE;

	for (i = 0; TypeLUT[i].m_pName && Loop; ++i)
	{
		if (TypeLUT[i].Is(TypeToken))
		{
			s = TypeLUT[i].m_pName;
			Loop = FALSE;
		}
	}
	if (!s)
		s = "Bad Type Token";
	return s;
}

///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadObject::CCadObject()
{
	m_pNext = 0;
	m_pPrev = 0;
	m_pSelNext = 0;
	SetSelected(0);
	m_Type = OBJECT_TYPE_NONE;
	m_P1 = CPoint(0,0);
	m_P2 = CPoint(0,0);
}

CCadObject::CCadObject(int type)
{
	m_pNext = 0;
	m_pPrev = 0;
	m_pSelNext = 0;
	SetSelected(0);
	m_Type = type;
	m_P1 = CPoint(0,0);
	m_P2 = CPoint(0,0);
}

CCadObject::~CCadObject()
{
	CCadObject* pO;

	pO = m_pHead;
	while(pO)
	{
		m_pHead = pO->GetNext();
		delete pO;
		pO = m_pHead;
	}
}

void CCadObject::Draw(CDC* pDC, ObjectMode mode,CPoint Offset,CScale Scale)
{
	//---------------------------------------------
	//	Draw
	//		This function draws the object onto the
	//	specified device context.
	// Base Class Methode does nothing
	//
	// parameters:
	//		pDC......pointer to the device context
	//		mode.....mode to use when drawing
	//		Offset...Offset to add to points
	//		Scale....Sets Units to Pixels ratio
	//---------------------------------------------

}

int CCadObject::CheckSelected(CPoint p,CSize Offset)
{
	return 0;
}

void CCadObject::Save(FILE *pO, int Indent)
{

}

void CCadObject::Move(CPoint p)
{
}

Tokens CCadObject::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	return LookAHeadToken;
}

int CCadObject::GrabVertex(CPoint point)
{
	return -1;
}

void CCadObject::SetVertex(int Vi, CPoint p)
{

}

CPoint CCadObject::GetReference()
{
	return CPoint(0,0);
}

CPoint CCadObject::ScalePoint(CPoint p, int Scale, int ScaleDiv)
{
	p.x = (Scale * p.x)/ ScaleDiv;
	p.y = (Scale * p.y)/ ScaleDiv;
	return p;
}

const char * CCadObject::GetTypeString()
{
	return LookupTypeName(m_Type);
}

void CCadObject::AdjustRefernce(CPoint p)
{
}

CRect CCadObject::GetRect()
{
	CRect Rect;
	Rect.SetRect(m_P1,m_P2);
	Rect.NormalizeRect();
	return Rect;
}

void CCadObject::SetRect(CRect & rect, CPoint P1, CPoint P2, CSize Lw)
{
	if (((P1.x > P2.x) && (P1.y > P2.y)))
	{
		CPoint temp;
		temp = P2;
		P2 = P1;
		P1 = temp;
	}
	else if (((P1.x > P2.x) && (P1.y < P2.y)))
	{
		CPoint t1, t2;
		t1 = P1;
		t2 = P2;
		P1.x = t2.x;
		P2.x = t1.x;
	}
	else if ((P1.x < P2.x) && (P1.y > P2.y))
	{
		CPoint t1, t2;
		t1 = P1;
		t2 = P2;
		P1.y = t2.y;
		P2.y = t1.y;
	}
	rect.SetRect(P1 + Lw, P2 - Lw + CSize(1, 1));
}

void CCadObject::RenderEnable(int e)
{
}


CCadObject * CCadObject::PopHead()
{
	return nullptr;
}


CCadObject * CCadObject::PopTail()
{
	return nullptr;
}



// Moves the center of the object to the spcified point
void CCadObject::ChangeCenter(CSize p)
{
}


CSize CCadObject::GetSize()
{
	return CSize();
}


void CCadObject::ChangeSize(CSize Sz)
{
}

int CCadObject::GetTop()
{
	int y1, y2, rV;

	y1 = m_P1.y;
	y2 = m_P2.y;
	if (y1 < y2)
		rV = y1;
	else if (y1 > y2)
		rV = y2;
	else
		rV = y1;
	return rV;
}

int CCadObject::GetBottom()
{
	int y1, y2, rV;

	y1 = m_P1.y;
	y2 = m_P2.y;
	if (y1 > y2)
		rV = y1;
	else if (y1 < y2)
		rV = y2;
	else
		rV = y1;
	return rV;
}

int CCadObject::GetLeft()
{
	int x1, x2, rV;

	x1 = m_P1.x;
	x2 = m_P2.x;
	if (x1 < x2)
		rV = x1;
	else if (x1 > x2)
		rV = x2;
	else
		rV = x1;
	return rV;
}

int CCadObject::GetRight()
{
	int x1, x2, rV;

	x1 = m_P1.x;
	x2 = m_P2.x;
	if (x1 > x2)
		rV = x1;
	else if (x1 < x2)
		rV = x2;
	else
		rV = x1;
	return rV;
}

CPoint CCadObject::GetCenter()
{
	CPoint ptRv;

	ptRv = CRect(m_P1, m_P2).CenterPoint();
	return ptRv;
}

CPoint CCadObject::GetUpperLeftPoint()
{
	int x, y;

	x = GetLeft();
	y = GetTop();
	return CPoint(x,y);
}

CPoint CCadObject::GetLowerRightPoint()
{
	int x, y;

	x = GetRight();
	y = GetBottom();
	return CPoint(x, y);
}

