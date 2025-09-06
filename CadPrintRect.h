#pragma once

struct PrintRectAttributes {
	int m_LineWidth;
	COLORREF m_LineColor;
	CSize m_Size;
	PrintRectAttributes() {
		m_LineWidth = 0;
		m_LineColor = RGB(0, 0, 0);
		m_Size = CSize(0, 0);
	}
};

class CFileParser;

class CCadPrintRect :public CCadObject
{
	friend CFileParser;
	PrintRectAttributes m_Attrib;
	inline static int m_RenderEnable = 1;
public:
	CCadPrintRect();
	CCadPrintRect(CCadPrintRect &PR);
	virtual ~CCadPrintRect();
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual void Draw(CDC *pDC, ObjectMode mode , CPoint Offset = CPoint(0, 0), CScale Scale = CScale(0.1, 0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void AdjustRefernce(CPoint Ref);
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void SetVertex(int Vi, CPoint p);
	virtual int GrabVertex(CPoint p);
	void SetLineWidth(int w) { m_Attrib.m_LineWidth = w; }
	int GetLineWidth(void) { return m_Attrib.m_LineWidth; }
	void SetLineColor(COLORREF c) { m_Attrib.m_LineColor = c; }
	COLORREF GetLineColor(void) { return m_Attrib.m_LineColor; }
	CPoint GetReference();
	CCadPrintRect operator=(CCadPrintRect &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	void SetSize(CSize s) { GetAttributes()->m_Size = s; }
	virtual CSize GetSize(void) { return GetAttributes()->m_Size; }
	virtual CRect GetRect(void);
	virtual void ChangeSize(CSize Sz);
	PrintRectAttributes* GetAttributes() { return &m_Attrib; }
};

