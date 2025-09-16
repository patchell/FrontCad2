#pragma once

class CCadText;

struct DimAttrib {
	int m_LineWidth;
	COLORREF m_Color;
	TextAttributes m_TextAtrib;
	DimAttrib() {
		m_LineWidth = 0;
		m_Color = RGB(0, 0, 0);
	}
	virtual ~DimAttrib() {
	}
	BOOL Create(DimAttrib* pDimAttributes) {
		BOOL rV = TRUE;

		if (pDimAttributes)
		{
			CopyFrom(pDimAttributes);
		}
		else
		{
			rV = FALSE;
		}
		return rV;
	}
	void CopyFrom(DimAttrib* s) {
		m_LineWidth = s->m_LineWidth;
		m_Color = s->m_Color;
		m_TextAtrib.CopyFrom(&s->m_TextAtrib);
	}
	void CopyTo(DimAttrib* s) {
		s->m_LineWidth = m_LineWidth;
		s->m_Color = m_Color;
		m_TextAtrib.CopyTo(&s->m_TextAtrib);
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
	BOOL Create(CPoint ptPos, DimAttrib* pDimAttributes);
	BOOL IsVertical();
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	CCadDimension operator=(CCadDimension &cd);
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void SetVertex(int Vi, CPoint p);
	virtual int GrabVertex(CPoint p);
	CCadText* CalculateDimensionTextPosition(CDC*pDC, ObjectMode mode, CPoint Offset, CScale Scale);
	virtual void Draw(CDC *pDC, ObjectMode mode , CPoint Offset = CPoint(0, 0), CScale Scale = CScale(0.1, 0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual CPoint GetReference();
	virtual void RemoveObject(CCadObject *pO);
	virtual void AdjustRefernce(CPoint Ref);
	virtual CRect GetRect(void);
	void AddText(CPoint Org);
	void UpdateText(CPoint Org);
	char* SetValue(int v, int dp, char* pS, int n);
	inline void SetColor(COLORREF c) { m_Atrib.m_Color = c; }
	inline COLORREF GetColor(void) { return m_Atrib.m_Color; }
	inline void SetLineWidth(int w) { m_Atrib.m_LineWidth = w; }
	inline int GetLineWidth(void) { return m_Atrib.m_LineWidth; }
	CCadText *GetTextObject(void);
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

