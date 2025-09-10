// CadBitmap.cpp: implementation of the CCadBitmap class.
//
///////////////////////////////////////////////

#include "stdafx.h"


///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadBitmap::CCadBitmap():CCadObject(OBJECT_TYPE_BITMAP)
{
	m_pBM = 0;
	m_pFilename = new char[512];
	m_MaintainAspectRatio = 1;
}


CCadBitmap::CCadBitmap(CCadBitmap &v):CCadObject(OBJECT_TYPE_BITMAP)
{
	m_pBM = 0;
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	m_pFilename = new char[512];
	if (v.m_pFilename)
	{
		strcpy_s(m_pFilename,512,v.m_pFilename);
		LoadBitmapImage(m_pFilename);
	}
	this->m_MaintainAspectRatio = v.m_MaintainAspectRatio;
}	


CCadBitmap CCadBitmap::operator =(CCadBitmap &v)
{
	SetP1(v.GetP1());
	SetP2(v.GetP2());
	m_pFilename = new char[512];
	strcpy_s(m_pFilename,512,v.m_pFilename);
	LoadBitmapImage(m_pFilename);
	this->m_MaintainAspectRatio = v.m_MaintainAspectRatio;
	return *this;
}

CCadBitmap::~CCadBitmap()
{
	if(m_pBM) delete m_pBM;
	delete[] m_pFilename;
}

BOOL CCadBitmap::Create(CPoint ptPos, char* pFilename, CMyBitmap* pBM)
{
	BOOL rV = TRUE;

	SetP1(ptPos);
	SetP2(ptPos);
	if (pFilename)
		rV = LoadBitmapImage(pFilename);
    return rV;
}

CCadObject* CCadBitmap::Copy()
{
	CCadBitmap *pNew = new CCadBitmap(*this);
	return (CCadObject*)pNew;
}

void CCadBitmap::Move(CPoint p)
{
	CSize Diff = p - GetP1();
	SetP1(GetP1() + Diff);
	SetP2(GetP2() + Diff);
}

Tokens CCadBitmap::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	SetLineNumber(pParser->GetLine());
	SetCollumnNumber(pParser->GetCol());
	LookAHeadToken = pParser->Expect(Tokens::BITMAP, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Point(Tokens::POINT_2, pIN, GetP2(), LookAHeadToken);
	LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens::FILE, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
	LoadBitmapImage(pParser->GetLexBuff());
	LookAHeadToken = pParser->Expect(Tokens::STRING, LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
	LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
	(*ppDrawing)->AddObjectToEnd(this);
	return LookAHeadToken;
}

void CCadBitmap::Save(FILE *pO,  int Indent)
{
	char* s = new char[256];

	fprintf(pO, "%sBITMAP(POINT(%d,%d),POINT(%d,%d),FILE(\"%s\"))\n",
		theApp.IndentString(s, 256, Indent),
		GetP1().x,
		GetP1().y,
		GetP2().x,
		GetP2().y,
		m_pFilename
	);
	delete[]s;
}

void CCadBitmap::SetVertex(int Vi,CPoint p)
{
	if(Vi)
		SetP2(p);
	else
		SetP1(p);
	if(m_MaintainAspectRatio)
		RestoreAspectRatio();
}

int CCadBitmap::GrabVertex(CPoint point)
{
	int rV = -1;
	CSize Diff(6,6);
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

void CCadBitmap::Draw(CDC* pDC, ObjectMode mode,CPoint Offset,CScale Scale)
{
	CPen pen,*oldpen;
	CRect rect;
	CPoint P1,P2;

	if (CCadBitmap::m_RenderEnable)
	{
		if (mode == ObjectMode::Sketch)
		{
			double AspectRatioBM;
			AspectRatioBM = double(m_Size.cy) / double(m_Size.cx);
			SetP2Y(int(AspectRatioBM * double(abs(GetP2().x - GetP1().x))) + GetP1().y);
		}
		P1 = Scale * GetP1() + Offset;
		P2 = Scale * GetP2() + Offset;
		rect.SetRect(P1, P2);

		switch (mode)
		{
		case ObjectMode::Final:
		{
			CDC bmDC;
			CBitmap *pOld;
			bmDC.CreateCompatibleDC(pDC);
			pOld = bmDC.SelectObject(this->m_pBM);
			pDC->StretchBlt(P1.x, P1.y, rect.Width(), rect.Height(), &bmDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
			bmDC.SelectObject(pOld);
		}
		break;
		case ObjectMode::Selected:
		{
			CPen bPen;
			CRect Vrect;
			bPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			pen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			oldpen = pDC->SelectObject(&pen);
			CDC bmDC;
			CBitmap *pOld;
			bmDC.CreateCompatibleDC(pDC);
			pOld = bmDC.SelectObject(this->m_pBM);
			pDC->StretchBlt(P1.x, P1.y, rect.Width(), rect.Height(), &bmDC, 0, 0, m_Size.cx, m_Size.cy, SRCCOPY);
			pDC->MoveTo(P1);
			pDC->LineTo(P1.x, P2.y);
			pDC->LineTo(P2);
			pDC->LineTo(P2.x, P1.y);
			pDC->LineTo(P1);
			pDC->SelectObject(&bPen);
			Vrect.SetRect(P1 + CSize(6, 6), P1 + CSize(-6, -6));
			pDC->Rectangle(Vrect);
			Vrect.SetRect(P2 + CSize(6, 6), P2 + CSize(-6, -6));
			pDC->Rectangle(Vrect);
			bmDC.SelectObject(pOld);
			pDC->SelectObject(oldpen);
		}
		break;
		case ObjectMode::Sketch:
			pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			oldpen = pDC->SelectObject(&pen);
			pDC->DrawDragRect(&rect, CSize(1, 1), NULL, CSize(1, 1));
			pDC->SelectObject(oldpen);
			break;
		}
	}
}

int CCadBitmap::CheckSelected(CPoint p,CSize Off)
{
	CRect rect;
	int rV;
	CPoint P1 = GetP1() + Off;
	CPoint P2 = GetP2() + Off;
	rect.SetRect(P1,P2);
	rect.NormalizeRect();
	rV = (int)rect.PtInRect(p);
	return rV;
}

CPoint CCadBitmap::GetReference()
{
	return GetP1();
}

void CCadBitmap::AddObject(CCadObject *pO)
{
}

void CCadBitmap::RemoveObject(CCadObject *pO)
{
}

void CCadBitmap::AdjustRefernce(CPoint p)
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

CRect CCadBitmap::GetRect(void)
{
	CRect rR;
	rR.SetRect(GetP1(), GetP2());
	rR.NormalizeRect();
	return rR;
}

BOOL CCadBitmap::LoadBitmapImage(char *path)
{
	BOOL rV = TRUE;

	if(path)
	{ 
		if (m_pBM) 
			delete m_pBM;
		m_pBM = new CMyBitmap;
		m_pBM->LoadBitmapImage(path);
		strcpy_s(this->m_pFilename, 512, path);
		BITMAP bm;
		m_pBM->GetBitmap(&bm);
		m_Size = CSize(bm.bmWidth, bm.bmHeight);
	}
	return rV;
}

void CCadBitmap::RestoreAspectRatio()
{
	CPoint P1,P2;
	double AspectRatioBM;
	AspectRatioBM = double(m_Size.cy)/double(m_Size.cx);
	SetP2Y(int(AspectRatioBM * double(abs(GetP2().x - GetP1().x))) + GetP1().y);
	m_MaintainAspectRatio = 1;
}

void CCadBitmap::RenderEnable(int e)
{
	CCadBitmap::m_RenderEnable = e;
}

CPoint CCadBitmap::GetCenter()
{
	CRect rect = this->GetRect();
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadBitmap::ChangeCenter(CSize p)
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


CSize CCadBitmap::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadBitmap::ChangeSize(CSize Sz)
{
	SetP2(GetP2() + Sz);
}
