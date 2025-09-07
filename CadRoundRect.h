// CadRoundRect.h: interface for the CCadRoundRect class.
//
///////////////////////////////////////////////

#pragma once

struct RndRectAttb {
	COLORREF m_FillColor;
	COLORREF m_LineColor;
	int m_LineWidth;
	CPoint m_P3;
	BOOL m_bTransparent;
	RndRectAttb() {
		m_FillColor = RGB(0, 0, 0);
		m_LineColor = RGB(0, 0, 0);
		m_LineWidth = 1;
		m_P3 = { 0,0 };
		m_bTransparent = FALSE;
	}
	~RndRectAttb() {
	}
	void CopyTo(RndRectAttb* pA) {
		if (pA) {
			pA->m_FillColor = m_FillColor;
			pA->m_LineColor = m_LineColor;
			pA->m_LineWidth = m_LineWidth;
			pA->m_P3 = m_P3;
			pA->m_bTransparent = m_bTransparent;
		}
	}
	void CopyFrom(RndRectAttb* pA) {
		if (pA) {
			m_FillColor = pA->m_FillColor;
			m_LineColor = pA->m_LineColor;
			m_LineWidth = pA->m_LineWidth;
			m_P3 = pA->m_P3;
			m_bTransparent = pA->m_bTransparent;
		}
	}
} ;

class CFileParser;

class CCadRoundRect : public CCadObject
{
	inline static int m_RenderEnable = 1;
	RndRectAttb m_attrib;
public:
	CCadRoundRect(CCadRoundRect &r);
	CCadRoundRect();
	virtual ~CCadRoundRect();
	BOOL Create(CPoint ptPos, RndRectAttb* pRndRectAttributes);
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint Ref);
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	//------------------------------
	COLORREF GetFillColor(void) {return GetAttributes()->m_FillColor;}
	COLORREF GetLineColor(void) {return GetAttributes()->m_LineColor;}
	int GetLineWidth(void)  {return GetAttributes()->m_LineWidth;}
	void SetFillColor(COLORREF nC){ GetAttributes()->m_FillColor = nC;}
	void SetLineColor(COLORREF nC){ GetAttributes()->m_LineColor = nC;}
	void SetLineWidth(int nW){ GetAttributes()->m_LineWidth = nW;}
	void SetArc(CPoint p){ GetAttributes()->m_P3 = p;}
	CPoint GetArc(void){return GetAttributes()->m_P3;}
	void SetTransparent(BOOL T) { GetAttributes()->m_bTransparent = T; }
	BOOL IsTransparent() { return GetAttributes()->m_bTransparent; }
	CCadRoundRect operator=(CCadRoundRect &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	RndRectAttb* GetAttributes() { return &m_attrib; }
};
