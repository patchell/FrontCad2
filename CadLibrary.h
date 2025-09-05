// CadLibrary.h: interface for the CCadLibrary class.
//
///////////////////////////////////////////////

#if !defined(AFX_CADLIBRARY_H__F7C7788A_44D0_4810_AAFB_4C5053AF21FE__INCLUDED_)
#define AFX_CADLIBRARY_H__F7C7788A_44D0_4810_AAFB_4C5053AF21FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CadLibObject.h"


class CCadLibrary  
{
	CCadLibObject *m_pHead;
	CCadLibObject *m_pTail;
	CCadLibrary *m_pNext;
	CCadLibrary *m_pPrev;
	char *m_pName;	//name of library
public:
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	void SetName(char *pN);
	void DeletePart(CCadLibObject *pLO);
	void AddPart(CCadLibObject *pLO);
	CCadLibrary();
	virtual ~CCadLibrary();
	CCadLibObject *GetHeadObj(void){return m_pHead;}
	CCadLibObject *GetTailObj(void){return m_pTail;}
	CCadLibrary *GetPrev(void){return m_pPrev;}
	CCadLibrary *GetNext(void){return m_pNext;}
	void SetPrev(CCadLibrary *pP){m_pPrev = pP;}
	void SetNext(CCadLibrary *pN){m_pNext = pN;}
	char *GetName(void){return m_pName;}
};

#endif // !defined(AFX_CADLIBRARY_H__F7C7788A_44D0_4810_AAFB_4C5053AF21FE__INCLUDED_)
