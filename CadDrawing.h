// CadDrawing.h: interface for the CCadDrawing class.
//
///////////////////////////////////////////////

#if !defined(AFX_CADDRAWING_H__158D9EB0_BE4F_471A_B22E_2423339E764A__INCLUDED_)
#define AFX_CADDRAWING_H__158D9EB0_BE4F_471A_B22E_2423339E764A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#define CADDRAWUBG_CHECKSEL_FLAG_ALL	0
#define CADDRAWUBG_CHECKSEL_FLAG_UNSEL	1
#define CADDRAWUBG_CHECKSEL_FLAG_SEL	2


class CFileParser;
class CCadPrintRect;

class CCadDrawing : public CCadObject  
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
	CCadObject *m_pHead;
	CCadObject *m_pTail;
	COLORREF m_BkColor;
public:
	int m_Error;
	CCadDrawing();
	virtual ~CCadDrawing();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	void CheckPrev(void);
	CCadLibObject * CreatePartFromSelected(char *name);
	int CheckSelected(CPoint p,CCadObject **ppSelList,int n,int flag= CADDRAWUBG_CHECKSEL_FLAG_ALL);
	void Print(CDC* pDC, ObjectMode mode,CPoint Offset,CScale Scale);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset,CScale Scale);
	virtual void AddObject(CCadObject *pO);
	virtual void RemoveObject(CCadObject *pO);
	virtual void InsertObject(CCadObject *pObj);
	virtual CCadObject *GetHead(void){return m_pHead;}
	void SetBkColor(COLORREF c){m_BkColor = c;}
	COLORREF GetBkColor(void){return m_BkColor;}
	CCadPrintRect *GetPrintRect();
};

#endif // !defined(AFX_CADDRAWING_H__158D9EB0_BE4F_471A_B22E_2423339E764A__INCLUDED_)
