#pragma once

struct DimAttrib {
	int m_LineWidth;
	COLORREF m_Color;
	CCadText* m_pText;
	DimAttrib() {
		m_LineWidth = 0;
		m_Color = RGB(0, 0, 0);
		m_pText = new CCadText;
	}
	virtual ~DimAttrib() {
		if (m_pText)
			delete m_pText;
		m_pText = 0;
	}
	void SetText(const char* s) {
		if (!m_pText)
			m_pText = new CCadText;;
		m_pText->SetText((char*)s);
	}
	void CopyFrom(DimAttrib* s) {
		m_LineWidth = s->m_LineWidth;
		m_Color = s->m_Color;
		if (!m_pText)
			m_pText = new CCadText;
		*m_pText = *(s->m_pText);
	}
	void CopyTo(DimAttrib* s) {
		s->m_LineWidth = m_LineWidth;
		s->m_Color = m_Color;
		if (!s->m_pText)
			s->m_pText = new CCadText;
		*(s->m_pText) = *m_pText;
	}
};

class CCadDimension :public CCadObject
{
	inline static int m_RenderEnable = 1;
	DimAttrib m_Atrib;
public:
	CCadDimension();
	CCadDimension(CCadDimension &cd);
	virtual ~CCadDimension();
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	CCadDimension operator=(CCadDimension &cd);
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void SetVertex(int Vi, CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void Draw(CDC *pDC, ObjectMode mode , CPoint Offset = CPoint(0, 0), CScale Scale = CScale(0.1, 0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual CPoint GetReference();
	virtual void AddObject(CCadObject *pO);
	virtual void RemoveObject(CCadObject *pO);
	virtual CCadObject *GetHead(void) { return (CCadObject *)GetAttributes()->m_pText; }
	virtual void SetSelected(int Flag = 0);
	virtual void AdjustRefernce(CPoint Ref);
	virtual CRect GetRect(void);
	void UpdateText(CPoint Org);
	void SetValue(int v, int dp);
	inline void SetColor(COLORREF c) { m_Atrib.m_Color = c; }
	inline COLORREF GetColor(void) { return m_Atrib.m_Color; }
	inline void SetLineWidth(int w) { m_Atrib.m_LineWidth = w; }
	inline int GetLineWidth(void) { return m_Atrib.m_LineWidth; }
	inline CCadText *GetText(void) { 
		return GetAttributes()->m_pText; 
	}
	DimAttrib* GetAttributes(void) { return &m_Atrib; }
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	void AlignToPoint(CPoint p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	void SetFontName(char * pN);
	char * GetFontName();
};

