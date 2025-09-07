
// CadArc.h: interface for the CCadArc class.
//
///////////////////////////////////////////////

#pragma once


// Arc Attributes

struct ArcAttributes {
	int m_LineWidth;
	COLORREF m_LineColor;
	CPoint m_Start;
	CPoint m_End;
	int m_StartAngle;
	int m_EndAngle;
	ArcAttributes() {
		m_LineWidth = 0;
		m_LineColor = RGB(0,0,0);
		m_Start = CPoint(0,0);
		m_End = CPoint(0, 0);
		m_StartAngle = 0;
		m_EndAngle = 0;
	}
	BOOL Create(ArcAttributes* pA) {
		BOOL rV = TRUE;

		if (pA) {
			CopyFrom(pA);
		}
		else
			rV = FALSE;
		return rV;
	}
	void CopyFrom(ArcAttributes* pA) {
		m_LineWidth = pA->m_LineWidth;
		m_LineColor = pA->m_LineColor;
		m_Start = pA->m_Start;
		m_End = pA->m_End;
		m_StartAngle = pA->m_StartAngle;
		m_EndAngle = pA->m_EndAngle;
	}
	void CopyTo(ArcAttributes* pA) {
		pA->m_LineWidth = m_LineWidth;
		pA->m_LineColor = m_LineColor;
		pA->m_Start = m_Start;
		pA->m_End = m_End;
		pA->m_StartAngle = m_StartAngle;
		pA->m_EndAngle = m_EndAngle;
	}
};

class CFileParser;

class CCadArc : public CCadObject
{
	inline static int m_RenderEnable = 1;
	ArcAttributes m_atrb;
public:
	CCadArc();
	CCadArc(CCadArc& arc);
	virtual ~CCadArc();
	BOOL Create(CPoint ptPos, ArcAttributes* pArcAttributes);
	virtual CCadObject* Copy();
	virtual CPoint GetReference();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE* pO, int Indent);
	virtual void SetVertex(int Vi, CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void Draw(CDC* pDC, ObjectMode mode, CPoint Offset = CPoint(0, 0), CScale Scale = CScale(0.1, 0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void AdjustRefernce(CPoint Ref);
	void SetLineWidth(int w) { m_atrb.m_LineWidth = w; }
	int GetLineWidth(void) { return m_atrb.m_LineWidth; }
	void SetLineColor(COLORREF c) { m_atrb.m_LineColor = c; }
	COLORREF GetLineColor(void) { return m_atrb.m_LineColor; }
	void SetEndAngle(int Angle);
	int GetEndAngle(void) { return m_atrb.m_EndAngle; }
	void SetStartAngle(int Angle);
	int GetStartAngle(void) { return m_atrb.m_StartAngle; }
	void SetEndPoint(CPoint p);
	CPoint GetEndPoint(void) { return m_atrb.m_End; }
	void SetStartPoint(CPoint p);
	CPoint GetStartPoint(void) { return m_atrb.m_Start; }
	CCadArc operator=(CCadArc& v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	void ChangeSize(CSize Sz);
	ArcAttributes* GetAttributes(void) {
		return &m_atrb;
	}
};
