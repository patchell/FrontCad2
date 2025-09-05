// CadLibObject.cpp: implementation of the CCadLibObject class.
//
///////////////////////////////////////////////

#include "stdafx.h"


///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CCadLibObject::CCadLibObject():CCadObject(OBJECT_TYPE_LIBCOMP)
{
}

CCadLibObject::CCadLibObject(CCadObject *pChain): CCadObject(OBJECT_TYPE_LIBCOMP)
{
	GetAttributes()->m_Ref = CPoint(0,0);
	GetAttributes()->m_pName = 0;
	//copy from this object
	CCadObject *pLobj = pChain;
	while(pLobj)
	{
		switch(pLobj->GetType())
		{
			case OBJECT_TYPE_LINE:
				{
					CCadLine *pL;
					pL = (CCadLine *)((CCadLine *)pLobj)->CopyObject();
					AddObjectToEnd(pL);
				}
				break;
			case OBJECT_TYPE_RECT:
				{
					CCadRect *pR = new CCadRect;
					*pR = *(CCadRect *)pLobj;
					AddObjectToEnd(pR);
				}
				break;
			case OBJECT_TYPE_ELLIPSE:
				{
					CCadElipse *pE = new CCadElipse;
					*pE = *(CCadElipse *)pLobj;
					AddObjectToEnd(pE);
				}
				break;
			case OBJECT_TYPE_RNDRECT:
				{
					CCadRoundRect *pR = new CCadRoundRect;
					*pR = *(CCadRoundRect *)pLobj;
					AddObjectToEnd(pR);
				}
				break;
			case OBJECT_TYPE_POLY:
				{
					CCadPolygon *pP = new CCadPolygon;
					*pP = *(CCadPolygon *)pLobj;
					AddObjectToEnd(pP);
				}
				break;
			case OBJECT_TYPE_LIBCOMP:
				{
				}
				break;
			case OBJECT_TYPE_HOLEROUND:
				{
					CCadHoleRound *pH = new CCadHoleRound;
					*pH = *(CCadHoleRound *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_HOLERECT:
				{
					CCadRectHole *pH = new CCadRectHole;
					*pH = *(CCadRectHole *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_HOLERND1FLAT:
				{
					CCadHoleRnd1Flat *pH = new CCadHoleRnd1Flat;
					*pH = *(CCadHoleRnd1Flat *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_HOLERND2FLAT:
				{
					CCadHoleRnd2Flat *pH = new CCadHoleRnd2Flat;
					*pH = *(CCadHoleRnd2Flat *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_TEXT:
				{
					CCadText *pT = new CCadText;
					*pT = *(CCadText *)pLobj;
					AddObjectToEnd(pT);
				}
				break;
			case OBJECT_TYPE_ARC:
				{
					CCadArc *pH = new CCadArc;
					*pH = *(CCadArc *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_ARCCENTERED:
				{
					CCadArcCentered *pH = new CCadArcCentered;
					*pH = *(CCadArcCentered *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_ARROW:
				{

				}
				break;
		}
		pLobj = pLobj->GetNext();
	}
}

CCadLibObject::CCadLibObject(CCadLibObject &LibObj):CCadObject(OBJECT_TYPE_LIBCOMP)
{
	GetAttributes()->CopyFrom(LibObj.GetAttributes());
	//copy from this object
	CCadObject *pLobj = LibObj.GetHead();
	while(pLobj)
	{
		switch(pLobj->GetType())
		{
			case OBJECT_TYPE_LINE:
				{
					CCadLine *pL = new CCadLine;
					*pL = *(CCadLine *)pLobj;
					AddObjectToEnd(pL);
				}
				break;
			case OBJECT_TYPE_RECT:
				{
					CCadRect *pR = new CCadRect;
					*pR = *(CCadRect *)pLobj;
					AddObjectToEnd(pR);
				}
				break;
			case OBJECT_TYPE_ELLIPSE:
				{
					CCadElipse *pE = new CCadElipse;
					*pE = *(CCadElipse *)pLobj;
					AddObjectToEnd(pE);
				}
				break;
			case OBJECT_TYPE_POLY:
				{
					CCadPolygon *pP = new CCadPolygon;
					*pP = *(CCadPolygon *)pLobj;
					AddObjectToEnd(pP);
				}
				break;
			case OBJECT_TYPE_LIBCOMP:
				{
				}
				break;
			case OBJECT_TYPE_HOLEROUND:
				{
					CCadHoleRound *pH = new CCadHoleRound;
					*pH = *(CCadHoleRound *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_HOLERECT:
				{
					CCadRectHole *pH = new CCadRectHole;
					*pH = *(CCadRectHole *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_HOLERND1FLAT:
				{
					CCadHoleRnd1Flat *pH = new CCadHoleRnd1Flat;
					*pH = *(CCadHoleRnd1Flat *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_HOLERND2FLAT:
				{
					CCadHoleRnd2Flat *pH = new CCadHoleRnd2Flat;
					*pH = *(CCadHoleRnd2Flat *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_TEXT:
				{
					CCadText *pT = new CCadText;
					*pT = *(CCadText *)pLobj;
					AddObjectToEnd(pT);
				}
				break;
			case OBJECT_TYPE_ARC:
				{
					CCadArc *pH = new CCadArc;
					*pH = *(CCadArc *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_ARCCENTERED:
				{
					CCadArcCentered *pH = new CCadArcCentered;
					*pH = *(CCadArcCentered *)pLobj;
					AddObjectToEnd(pH);
				}
				break;
			case OBJECT_TYPE_ARROW:
				{

				}
				break;

		}
		pLobj = pLobj->GetNext();
	}
}

CCadLibObject::~CCadLibObject()
{
	CCadObject *pO,*pNO;

	pO = m_pStart;
	while(pO)
	{
		pNO = pO->GetNext();
		delete pO;
		pO = pNO;
	}
	if(m_pName) delete[] m_pName;
	if(m_pRefPen) delete m_pRefPen;
}

void CCadLibObject::Draw(CDC *pDC, ObjectMode mode,CPoint Offset,CScale Scale)
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
	if (CCadLibObject::m_RenderEnable)
	{
		CCadObject *pO = m_pStart;
		CPoint p1;
		p1 = Scale * GetP1();
		CPoint Doff = p1 + Offset;
		while (pO)
		{
			pO->Draw(pDC, mode, Doff, Scale);
			pO = pO->GetNext();
		}
		//--------------------------
		// mark the reference point
		//--------------------------
		if (m_pRefPen == 0)
		{
			m_pRefPen = new CPen;
			m_pRefPen->CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		}
		CPen *pOldPen;
		CPoint Ref = m_Ref + Offset + GetP1();
		pOldPen = pDC->SelectObject(m_pRefPen);
		pDC->MoveTo(Ref.x - 2, Ref.y);
		pDC->LineTo(Ref.x + 2, Ref.y);
		pDC->MoveTo(Ref.x, Ref.y - 2);
		pDC->LineTo(Ref.x, Ref.y + 2);
		pDC->SelectObject(pOldPen);
	}
}

int CCadLibObject::CheckSelected(CPoint p, CSize Offset)
{
	int rV = 0;
	CCadObject *pO = GetHead();
	Offset = GetP1() + Offset;
	while(pO && !rV)
	{
		if(pO->CheckSelected(p,Offset)) rV = 1;
		else
			pO = pO->GetNext();
	}
	return rV;
}

//void CCadLibObject::AddObject(CCadObject *pObj)
//{
//	if(m_pStart)
//	{
//		//--------------------------
//		//add object to end of list
//		//--------------------------
//		m_pEnd->SetNext(pObj);
//		pObj->SetPrev(m_pEnd);
//		m_pEnd = pObj;
//	}
//	else	//first object
//	{
//		m_pStart = pObj;
//		m_pEnd = pObj;
//	}
//	if(pObj->GetType() == OBJECT_TYPE_ARCCENTERED)
//	{
//		CCadArcCentered *pA = (CCadArcCentered *)pObj;
//		SetP2(CPoint(pA->GetP2()));
//	}
//}

//void CCadLibObject::RemoveObject(CCadObject *pO)
//{
//}

//void CCadLibObject::SetName(const char *pName)
//{
//	if(m_pName) delete[] m_pName;
//	int len = strlen(pName) + 1;
//	m_pName = new char[len];
//	strcpy_s(m_pName,len,pName);
//}

void CCadLibObject::Move(CPoint p)
{
	SetP1(p);
}

int CCadLibObject::GrabVertex(CPoint point)
{
	return -1;
}

Tokens CCadLibObject::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
	CCadLibObject* pCLO = this;
	BOOL Loop = TRUE;

	LookAHeadToken = pParser->Expect(Tokens::LIBPART, LookAHeadToken, pIN);
	while (Loop)
	{
		switch (LookAHeadToken)
		{
		case Tokens::STRING:
			SetName(pParser->GetLexBuff());
			LookAHeadToken = pParser->Expect(Tokens::STRING, LookAHeadToken, pIN);
			break;
		case Tokens::LIBPART:
			break;
		case Tokens('('):
			LookAHeadToken = pParser->Expect(Tokens('('), LookAHeadToken, pIN);
			break;
		case Tokens::REFERENCE:
			LookAHeadToken = pParser->Point(Tokens::REFERENCE, pIN, GetRef(), LookAHeadToken);
			break;
		case Tokens::POINT:
			LookAHeadToken = pParser->Point(Tokens::POINT, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens::POINT_1:
			LookAHeadToken = pParser->Point(Tokens::POINT_1, pIN, GetP1(), LookAHeadToken);
			break;
		case Tokens(','):
			LookAHeadToken = pParser->Expect(Tokens(','), LookAHeadToken, pIN);
			break;
		case Tokens('{'):
			LookAHeadToken = pParser->Expect(Tokens('{'), LookAHeadToken, pIN);
			LookAHeadToken = pParser->DrawObjects(pIN, LookAHeadToken, this);
			break;
		case Tokens('}'):
			LookAHeadToken = pParser->Expect(Tokens('}'), LookAHeadToken, pIN);
			Loop = FALSE;
			break;
		case Tokens(')'):
			LookAHeadToken = pParser->Expect(Tokens(')'), LookAHeadToken, pIN);
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

void CCadLibObject::Save(FILE* pO, int Indent)
{
	char* s = new char[256];
	char* pPointString = new char[64];
	char* pRefString = new char[64];

	fprintf(pO, "%s%s(\"%s\",%s,%s ){\n",
		theApp.IndentString(s, 256, Indent),
		CFileParser::LookupKeyword(Tokens::LIBPART),
		m_pName,
		CFileParser::SavePoint(pRefString, 64, Tokens::REFERENCE, m_Ref),
		CFileParser::SavePoint(pPointString, 64, Tokens::POINT_1, GetP1())
	);
	CCadObject* pOb = m_pStart;
	while (pOb)
	{
		pOb->Save(pO, Indent + 4);
		pOb = pOb->GetNext();
	}
	fprintf(pO, "%s}\n", s);
	delete[] pPointString;
	delete[] s;
}

void CCadLibObject::SetVertex(int Vi, CPoint p)
{

}

CPoint CCadLibObject::GetReference()
{
	return GetP1() + m_Ref;
}

void CCadLibObject::AdjustRefernce(CPoint Ref)
{
	GetP1() -= Ref;
}

CRect CCadLibObject::GetRect()
{
	CRect rect;
	CSize d = GetP2();
	rect.SetRect(GetP1() + d, GetP1() - d);
	rect.NormalizeRect();
	return rect;
}

void CCadLibObject::RenderEnable(int e)
{
	CCadLibObject::m_RenderEnable = e;
}

CPoint CCadLibObject::GetCenter()
{
	CRect rect = this->GetRect();
	return rect.CenterPoint();
}

// Moves the center of the object to the spcified point
void CCadLibObject::ChangeCenter(CSize p)
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
}



CSize CCadLibObject::GetSize()
{
	CRect rect = GetRect();
	return rect.Size();
}


void CCadLibObject::ChangeSize(CSize Sz)
{
}
