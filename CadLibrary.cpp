// CadLibrary.cpp: implementation of the CCadLibrary class.
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

CCadLibrary::CCadLibrary()
{
	m_pHead = 0;
	m_pTail = 0;
	m_pNext = 0;
	m_pPrev = 0;
	m_pName = 0;
}

CCadLibrary::~CCadLibrary()
{
	if(m_pName) delete[] m_pName;
}

void CCadLibrary::AddPart(CCadLibObject *pLO)
{
	if(m_pHead == 0)	//nothing in library
	{
		m_pHead = pLO;
		m_pTail = pLO;
	}
	else				//add part to library
	{
		m_pTail->SetNext(pLO);
		pLO->SetPrev(m_pTail);
		m_pTail = pLO;
	}
}

void CCadLibrary::DeletePart(CCadLibObject *pLO)
{
	if(pLO == m_pHead)
	{
		m_pHead = (CCadLibObject *)m_pHead->GetNext();
		m_pHead->SetPrev(0);
	}
	else if (pLO == m_pTail)
	{
		m_pTail = (CCadLibObject*)m_pTail->GetPrev();
		m_pTail->SetNext(0);
	}
	else
	{
		pLO->GetPrev()->SetNext(pLO->GetNext());
		pLO->GetNext()->SetPrev(pLO->GetPrev());
	}
	delete pLO;
}

void CCadLibrary::SetName(char *pN)
{
	if(m_pName) delete[] m_pName;
	m_pName = new char[strlen(pN)+1];
	strcpy_s(m_pName, strlen(pN) + 1,pN);
}

Tokens CCadLibrary::Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser)
{
    return Tokens(0);
}

void CCadLibrary::Save(FILE *pO,  int Indent)
{
	fprintf(pO,"LIBRARY(\"%s\"){\n",this->m_pName);
	CCadObject *pOb = m_pHead;
	while(pOb)
	{
		pOb->Save(pO, Indent+4);
		pOb = pOb->GetNext();
	}
	fprintf(pO,"}\n");
}
