// CadText.h: interface for the CCadText class.
//
///////////////////////////////////////////////

#if !defined(AFX_CADTEXT_H__3158CE29_1A32_4EBA_941D_92BA4FD81C1B__INCLUDED_)
#define AFX_CADTEXT_H__3158CE29_1A32_4EBA_941D_92BA4FD81C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


struct TextAttributes {
	COLORREF m_Color;
	COLORREF m_BkColor;
	int m_FontHeight;
	int m_FontWidth;
	int m_Angle;
	int m_Transparent;
	int m_Weight;
	UINT m_Format;
	char *m_pFontName;
	char *m_pText;
	TextAttributes() {
		m_Color = RGB(0,0,0);
		m_BkColor = RGB(0, 0, 0);
		m_FontHeight = 0;
		m_FontWidth = 0;
		m_Angle = 0;
		m_Transparent = 0;
		m_Weight = 0;
		m_Format = 0;
		m_pFontName = 0;
		m_pText = 0;
	}
};


class CCadText : public CCadObject
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
	TextAttributes m_atrb;
	CCadPolygon m_SelRect;
public:
	CCadText();
	CCadText(CCadText& v);
	virtual ~CCadText();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CRect GetRect(void);
	CRect GetTextRectangle(CDC* pDC, CScale Scale);
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint Ref);
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	CRect GetTextRectangle(void);
	void CopyAttributes(TextAttributes *d,TextAttributes *s);
	void Rotate(int Angle,CRect rect,CCadPolygon &Poly);
	TextAttributes * GetAttributes(void);
	void SettAttrib(TextAttributes &atrb);
	void SetColor(COLORREF c){m_atrb.m_Color = c;}
	COLORREF GetColor(void){return m_atrb.m_Color;}
	void SetBkColor(COLORREF c){m_atrb.m_BkColor = c;}
	COLORREF GetBkColor(void){return m_atrb.m_BkColor;}
	void SetText(char *s);
	void GetText(char *s,int n);
	void SetFormat(UINT f){m_atrb.m_Format = f;}
	UINT GetFormat(void){return m_atrb.m_Format;}
	void SetFontName(char *s);
	char *GetFontName(void){return m_atrb.m_pFontName;}
	void SetAngle(int e);
	int GetAngle(void){return m_atrb.m_Angle;}
	void SetFontHeight(int h){m_atrb.m_FontHeight = h;}
	int GetFontHeight(void){return m_atrb.m_FontHeight;}
	void SetFontWidth(int w){m_atrb.m_FontWidth = w;}
	int GetFontWidth(void){return m_atrb.m_FontWidth;}
	void SetTransparent(int o){m_atrb.m_Transparent = o;}
	int GetTransparent(void){return m_atrb.m_Transparent;}
	void SetWeight(int w){m_atrb.m_Weight = w;}
	int GetWeight(void){return m_atrb.m_Weight;}
	CPoint CalcTextShiftonRotation(CPoint p1,CPoint Center,double angle);
	char * GetText(void);
	CCadText operator=(CCadText &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
};

#endif // !defined(AFX_CADTEXT_H__3158CE29_1A32_4EBA_941D_92BA4FD81C1B__INCLUDED_)
