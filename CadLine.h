// CadLine.h: interface for the CCadLine class.
//
///////////////////////////////////////////////

#pragma once

class CFileParser;

struct LineAttrib {
	int m_LineWidth;
	COLORREF m_LineColor;
	LineAttrib() {
		m_LineWidth = 1;
		m_LineColor = RGB(0, 0, 0);
	}
} ;

class CCadLine : public CCadObject
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
	LineAttrib m_atrb;
	CCadPolygon* m_pPoly;	//encloses like a polygon for selection purposes
public:
	CCadLine();
	CCadLine(CCadLine &line);
	virtual ~CCadLine();
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CPoint GetReference(void);
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual void AdjustRefernce(CPoint Ref);
	void SetLineWidth(int w){GetAttributes()->m_LineWidth = w;}
	int GetLineWidth(void){return GetAttributes()->m_LineWidth;}
	void SetLineColor(COLORREF c){ GetAttributes()->m_LineColor = c;}
	COLORREF GetLineColor(void){return GetAttributes()->m_LineColor;}
	CCadLine operator=(CCadLine &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	LineAttrib* GetAttributes(void) { return &m_atrb; }
};
