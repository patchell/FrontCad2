// MoveObjects.cpp: implementation of the CMoveObjects class.
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

CMoveObjects::CMoveObjects()
{
	m_pHead = 0;
	m_pTail = 0;
	m_Ref = CPoint(0, 0);
}

CMoveObjects::~CMoveObjects()
{

}

void CMoveObjects::AddObject(CCadObject *pObj)
{
	if(GetHead())
	{
		//--------------------------
		//add object to end of list
		//--------------------------
		GetTail()->SetNext(pObj);
		pObj->SetPrev(GetTail());
		SetTail(pObj);
	}
	else	//first object
	{
		SetHead(pObj);
		SetTail(pObj);
	}
}

CCadObject * CMoveObjects::RemoveObject(CCadObject *pLO)
{
	//------------------------------------------
	// RemoveObject
	//			This function removes an object
	// from the move buffer.  This is a DELETE
	//
	//	parameters:
	//		pLO.....pointer to object to remove
	//------------------------------------------
	if(pLO == GetHead())
	{
		SetHead(GetHead()->GetNext());
		if(GetHead()) GetHead()->SetPrev(0);
	}
	else if (pLO == GetTail())
	{
		SetTail(GetTail()->GetPrev());
		if (GetTail()) 
			GetTail()->SetNext(0);
	}
	else
	{
		pLO->GetPrev()->SetNext(pLO->GetNext());
		pLO->GetNext()->SetPrev(pLO->GetPrev());
	}
	pLO->SetPrev(0);
	pLO->SetNext(0);
	return pLO;
}

void CMoveObjects::Draw(CDC *pDC, CPoint Off, CScale Scale)
{
	CCadObject *pCO = m_pHead;
	while(pCO)
	{
		pCO->Draw(pDC,ObjectMode::Selected,Off,Scale);
		pCO = pCO->GetNext();
	}

}

void CMoveObjects::SetRef(CPoint Ref)
{
	CCadObject *pCO = GetHead();
	while(pCO)
	{
		pCO->AdjustRefernce(Ref);
		pCO = pCO->GetNext();
	}
	m_Ref = Ref;
}

void CMoveObjects::Clear(int nDeleteFlag)
{
	CCadObject *pCO = GetHead();
	CCadObject *pNext;
	while(pCO && nDeleteFlag)
	{
		pNext = pCO->GetNext();
		delete pCO;
		pCO = pNext;
	}
	SetHead(0);
	SetTail(0);
}

// Copy a MoveObjects class
void CMoveObjects::Copy(CMoveObjects & Src)
{
	CCadObject *pObj = Src.GetHead();
	while (pObj)
	{
		AddObject(pObj->Copy());
		pObj = pObj->GetNext();
	}
}


// Removes object from front of list
CCadObject * CMoveObjects::RemoveFromHead()
{
	CCadObject *pObj;

	pObj = GetHead();
	if (pObj)
	{
		SetHead(pObj->GetNext());
		if (GetHead())
			GetHead()->SetPrev(0);
		pObj->SetNext(0);
	}
	return pObj;
}


CCadObject * CMoveObjects::RemoveFromTail()
{
	CCadObject *pObj;

	pObj = m_pTail;
	if (pObj)
	{
		SetTail(pObj->GetPrev());
		if (GetTail())
			GetTail()->SetNext(0);
		pObj->SetPrev(0);
	}
	return pObj;
}
