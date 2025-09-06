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
		AddObjectToEnd(pLobj->Copy());
		pLobj = pLobj->GetNext();
	}
}

CCadObject* CCadLibObject::Copy()
{
	CCadLibObject *pNew = new CCadLibObject(*this);
	return (CCadObject *)pNew;
}

CCadLibObject::CCadLibObject(CCadLibObject &LibObj):CCadObject(OBJECT_TYPE_LIBCOMP)
{
	GetAttributes()->CopyFrom(LibObj.GetAttributes());
	//copy from this object
	CCadObject *pLobj = LibObj.GetHead();
	while(pLobj)
	{
		AddObjectToEnd(pLobj->Copy());
		pLobj = pLobj->GetNext();
	}
}

CCadLibObject::~CCadLibObject()
{
	CCadObject *pO,*pNO;

	pO = GetHead();
	while(pO)
	{
		pNO = pO->GetNext();
		delete pO;
		pO = pNO;
	}
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
		CCadObject *pO = GetHead();
		CPoint p1;
		CPen RefPen;
		RefPen.CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
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
		CPen *pOldPen;
		CPoint Ref = GetAttributes()->m_Ref + Offset + GetP1();
		pOldPen = pDC->SelectObject(&RefPen);
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
		GetAttributes()->m_pName,
		CFileParser::SavePoint(pRefString, 64, Tokens::REFERENCE, GetAttributes()->m_Ref),
		CFileParser::SavePoint(pPointString, 64, Tokens::POINT_1, GetP1())
	);
	CCadObject* pOb = GetHead();
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
	return GetP1() + GetAttributes()->m_Ref;
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
