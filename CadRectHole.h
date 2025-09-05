// CadRectHole.h: interface for the CCadRectHole class.
//
///////////////////////////////////////////////

#if !defined(AFX_CADRECTHOLE_H__7D533B79_BB3B_4DFF_8AD2_D368D3DD1871__INCLUDED_)
#define AFX_CADRECTHOLE_H__7D533B79_BB3B_4DFF_8AD2_D368D3DD1871__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



struct RectHoleAttributes {
	int m_LineWidth;
	COLORREF m_LineColor;
	int m_W;
	int m_H;
	RectHoleAttributes() {
		m_LineWidth = 1;
		m_LineColor = RGB(0, 0, 0);
		m_W = 100;
		m_H = 100;
	}
};

class CFileParser;

class CCadRectHole : public CCadObject  
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
	RectHoleAttributes m_Attr;
public:
	CCadRectHole();
	virtual ~CCadRectHole();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CRect GetRect(void);
	CCadRectHole(CCadRectHole &r);
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint p);
	void SetLineWidth(int w){GetAttributes()->m_LineWidth = w;}
	int GetLineWidth(void) {return GetAttributes()->m_LineWidth;}
	void SetLineColor(COLORREF c){ GetAttributes()->m_LineColor = c;}
	COLORREF GetLineColor(void) {return GetAttributes()->m_LineColor;}
	void SetHieghtWidth(int h, int w){ GetAttributes()->m_H = h; GetAttributes()->m_W=w;}
	int GetHieght(void) {return GetAttributes()->m_H;}
	CCadRectHole operator=(CCadRectHole &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	virtual CPoint GetLowerRightPoint();
	virtual CPoint GetUpperLeftPoint();
	virtual int GetTop();
	virtual int GetBottom();
	virtual int GetLeft();
	virtual int GetRight();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	RectHoleAttributes* GetAttributes() { return &m_Attr; }
};
#endif // !defined(AFX_CADRECTHOLE_H__7D533B79_BB3B_4DFF_8AD2_D368D3DD1871__INCLUDED_)
