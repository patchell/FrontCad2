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
	COLORREF m_BkColor;
	int m_Error;
public:
	CCadDrawing();
	virtual ~CCadDrawing();
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	CCadLibObject * CreatePartFromSelected(char *name);
	int CheckSelected(CPoint p,CCadObject **ppSelList,int n,int flag= CADDRAWUBG_CHECKSEL_FLAG_ALL);
	void Print(CDC* pDC, ObjectMode mode,CPoint Offset,CScale Scale);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset,CScale Scale);
	void SetBkColor(COLORREF c){m_BkColor = c;}
	COLORREF GetBkColor(void){return m_BkColor;}
	CCadPrintRect *GetPrintRect();
};

#endif // !defined(AFX_CADDRAWING_H__158D9EB0_BE4F_471A_B22E_2423339E764A__INCLUDED_)
