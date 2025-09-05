// CadElipse.h: interface for the CCadElipse class.
//
///////////////////////////////////////////////

#if !defined(AFX_CADELIPSE_H__7652BDAC_7D47_420B_92E2_5F93D2617B54__INCLUDED_)
#define AFX_CADELIPSE_H__7652BDAC_7D47_420B_92E2_5F93D2617B54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct ElipseAttributes {
	int m_LineWidth;
	COLORREF m_LineColor;
	COLORREF m_FillColor;
	BOOL m_Transparent;
	ElipseAttributes() {
		m_LineWidth = 1;
		m_LineColor = RGB(0, 0, 0);
		m_FillColor = RGB(192, 192, 192);
		m_Transparent = 0;
	}
	BOOL GetTransparent() const { return m_Transparent; }
	void SetTransparent(BOOL t) { m_Transparent = t; }
	BOOL& GetTransparentRef() { return m_Transparent; }
	int GetLineWidth() const { return m_LineWidth; }
	void SetLineWidth(int w) { m_LineWidth = w; }
	int& GetLineWidthRef() { return m_LineWidth; }
	COLORREF GetLineColor() const { return m_LineColor; }
	void SetLineColor(COLORREF c) { m_LineColor = c; }
	COLORREF& GetLineColorRef() { return m_LineColor; }	
	COLORREF GetFillColor() const { return m_FillColor; }
	void SetFillColor(COLORREF c) { m_FillColor = c; }
	COLORREF& GetFillColorRef() { return m_FillColor; }	
};

class CFileParser;

class CCadElipse : public CCadObject
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
	ElipseAttributes m_atrb;
public:
	CCadElipse(CCadElipse &e);
	CCadElipse();
	virtual ~CCadElipse();
	CCadElipse operator=(CCadElipse& v);
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint Ref);
	int GetLineWidth(void) { return m_atrb.GetLineWidth(); }
	void SetLineWidth(int w) { m_atrb.SetLineWidth(w); }
	void SetLineColor(COLORREF c) {
		m_atrb.SetLineColor(c);
	}
	COLORREF GetLineColor(void) { return m_atrb.GetLineColor(); }	
	void SetFillColor(COLORREF c) {
		m_atrb.SetFillColor(c);
	}	
	COLORREF GetFillColor(void) { return m_atrb.GetFillColor(); }	
	void SetTransparent(BOOL bT) { m_atrb.SetTransparent(bT); }
	BOOL GetTransparent() { return m_atrb.GetTransparent(); }	
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	ElipseAttributes* GetAttributes() { return &m_atrb; }
};

#endif // !defined(AFX_CADELIPSE_H__7652BDAC_7D47_420B_92E2_5F93D2617B54__INCLUDED_)
