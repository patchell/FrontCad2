#pragma once


struct ArrowAttributes {
	COLORREF m_LineColor;
	COLORREF m_FillColor;
	int m_LineWidth;
	int m_Len;
	int m_ArrowWidth;
	BOOL m_bTransparent;
	ArrowAttributes() {
		m_LineWidth = 1;
		m_LineColor = RGB(0, 0, 0);
		m_FillColor = RGB(255, 255, 255);
		m_Len = 20;
		m_ArrowWidth = 10;
		m_bTransparent = FALSE;
	}
	void CopyFrom(ArrowAttributes* pA) {
		m_LineWidth = pA->m_LineWidth;
		m_LineColor = pA->m_LineColor;
		m_FillColor = pA->m_FillColor;
		m_Len = pA->m_Len;
		m_ArrowWidth = pA->m_ArrowWidth;
		m_bTransparent = pA->m_bTransparent;
	}
	void CopyTo(ArrowAttributes* pA) {
		pA->m_LineWidth = m_LineWidth;
		pA->m_LineColor = m_LineColor;
		pA->m_FillColor = m_FillColor;
		pA->m_Len = m_Len;
		pA->m_ArrowWidth = m_ArrowWidth;
		pA->m_bTransparent = m_bTransparent;
	}
};

class CFileParser;

class CCadArrow :public CCadObject
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
private:
	ArrowAttributes m_Attrib;
	CPoint m_P3, m_P4;
private:	//methodes
	void CalcPoints(CPoint & a, CPoint & b, CPoint Offset, CScale Scale);
public:
	CCadArrow();
	CCadArrow(CCadArrow &ca);
	virtual ~CCadArrow();
	BOOL Create(CPoint ptPos, ArrowAttributes* pArrowAttributes);	
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual void Move(CPoint p);
	virtual void Save(FILE *pO,  int Indent);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void SetVertex(int Vi, CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void Draw(CDC *pDC, ObjectMode mode, CPoint Offset = CPoint(0, 0), CScale Scale = CScale(0.1, 0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual CPoint GetReference();
	virtual void AddObject(CCadObject *pO);
	virtual void RemoveObject(CCadObject *pO);
	virtual CCadObject *GetHead(void);
	virtual void AdjustRefernce(CPoint Ref);
	virtual CRect GetRect(void);
	COLORREF GetLineColor(void) const { return m_Attrib.m_LineColor; }
	void SetLineColor(COLORREF c) { m_Attrib.m_LineColor = c; }
	COLORREF GetFillColor(void) const { return m_Attrib.m_FillColor; }
	void SetFillColor(COLORREF c) { m_Attrib.m_FillColor = c; }	
	int GetArrowWidth(void) { return m_Attrib.m_ArrowWidth; }
	void SetArrowWidth(int w) { m_Attrib.m_ArrowWidth = w; }
	int GetArrowLegnth(void) { return m_Attrib.m_Len; }
	BOOL IsTransparent(void) { return m_Attrib.m_bTransparent; }
	void SetTransparent(BOOL b) { m_Attrib.m_bTransparent = b; }
	void SetLegnth(int l) { m_Attrib.m_Len = l; }
	int GetLineWidth(void) { return m_Attrib.m_LineWidth; }
	void SetLineWidth(int w) { m_Attrib.m_LineWidth = w; }
	CCadArrow operator=(CCadArrow & Ca);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	ArrowAttributes* GetAttributes() { return &m_Attrib; }
};

