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
	BOOL Create(ElipseAttributes* pA) {
		BOOL rV = TRUE;
		if (pA) {
			CopyFrom(pA);
		}
		else
			rV = FALSE;
		return rV;
	}
	void CopyFrom(ElipseAttributes* pA) {
		if (pA)
		{
			m_LineWidth = pA->m_LineWidth;
			m_LineColor = pA->m_LineColor;
			m_FillColor = pA->m_FillColor;
			m_Transparent = pA->m_Transparent;
		}
	}
	void CopyTo(ElipseAttributes* pA) {
		if(pA)
		{
			pA->m_LineWidth = m_LineWidth;
			pA->m_LineColor = m_LineColor;
			pA->m_FillColor = m_FillColor;
			pA->m_Transparent = m_Transparent;
		}
	}

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
	BOOL Create(CPoint ptPos, ElipseAttributes* pElipseAttributes);	
	virtual CCadObject* Copy();
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
	int GetLineWidth(void) { return m_atrb.m_LineWidth; }
	void SetLineWidth(int w) { m_atrb.m_LineWidth = w; }
	void SetLineColor(COLORREF c) {
		m_atrb.m_LineColor = c;
	}
	COLORREF GetLineColor(void) { return m_atrb.m_LineColor; }	
	void SetFillColor(COLORREF c) {
		m_atrb.m_FillColor = c;
	}	
	COLORREF GetFillColor(void) { return m_atrb.m_FillColor; }	
	void SetTransparent(BOOL bT) { m_atrb.m_Transparent = bT; }
	BOOL GetTransparent() { return m_atrb.m_Transparent; }	
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	ElipseAttributes* GetAttributes() { return &m_atrb; }
};

#endif // !defined(AFX_CADELIPSE_H__7652BDAC_7D47_420B_92E2_5F93D2617B54__INCLUDED_)
