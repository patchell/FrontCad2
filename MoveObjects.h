// MoveObjects.h: interface for the CMoveObjects class.
//
///////////////////////////////////////////////

#if !defined(AFX_MOVEOBJECTS_H__9FAA8A52_F3DA_461E_BBF4_DCF31FF02BAA__INCLUDED_)
#define AFX_MOVEOBJECTS_H__9FAA8A52_F3DA_461E_BBF4_DCF31FF02BAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCadObject;

class CMoveObjects  
{
	CPoint m_Ref;
	CCadObject* m_pHead;
	CCadObject* m_pTail;
public:
	void Clear(int nDeleteFlag=0);
	void SetRef(CPoint Ref);
	void Draw(CDC *pDC,CPoint Off,CScale Scale);
	CMoveObjects();
	virtual ~CMoveObjects();
	CCadObject *GetHead(){return m_pHead;}
	void SetHead(CCadObject* pH) { m_pHead = pH; }
	CCadObject* GetTail() { return m_pTail; }
	void SetTail(CCadObject* pT) { m_pTail = pT; }
	CCadObject * RemoveObject(CCadObject *pO);
	void AddObject(CCadObject *pO);
public:
	// Copy a MoveObjects class
	void Copy(CMoveObjects & Src);
	// Removes object from front of list
	CCadObject * RemoveFromHead();
	CCadObject * RemoveFromTail();
};

#endif // !defined(AFX_MOVEOBJECTS_H__9FAA8A52_F3DA_461E_BBF4_DCF31FF02BAA__INCLUDED_)
