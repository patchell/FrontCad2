// Polygon.h: interface for the CPolygon class.
//
///////////////////////////////////////////////

#pragma once

class CFileParser;
//class CCadText;

constexpr auto POLY_MAX_VERTECIES = 512;

struct PolyAttributes
{
	int m_LineWidth;
	COLORREF m_LineColor;
	COLORREF m_FillColor;
	BOOL m_Transparent;
	int m_Size;		//size of the array that holds vertex points
	int m_Count;	//total numbeer of verticies
	CPoint* m_pVertex;	//array of vertex points
	PolyAttributes()
	{
		m_LineWidth = 1;
		m_LineColor = RGB(0, 0, 0);
		m_FillColor = RGB(255, 255, 255);
		m_Transparent = 0;
		m_Size = 0;
		m_Count = 0;
		m_pVertex = new CPoint[POLY_MAX_VERTECIES];		//pointer to array of vertexes;
		for(int i=0;i<POLY_MAX_VERTECIES;++i)
			m_pVertex[i] = CPoint(0, 0);
	}
	virtual ~PolyAttributes() {
		if (m_pVertex)
			delete[] m_pVertex;
		m_pVertex = 0;
	}
	void Rest() {
		m_Size = 0;
		m_Count = 0;
		if (m_pVertex)
			delete[] m_pVertex;
		m_pVertex = new CPoint[POLY_MAX_VERTECIES];		//pointer to array of vertexes;
		for (int i = 0; i < POLY_MAX_VERTECIES; ++i)
			m_pVertex[i] = CPoint(0, 0);
	}
	void SetPoint(CPoint p) {
		m_pVertex[m_Count] = p;
	}
	BOOL AddPoint(CPoint p, BOOL bInc , BOOL bIncSizeToo);
};


class CCadPolygon:public CCadObject
{
//	friend CCadText;
//	friend CFileParser;
	inline static int m_RenderEnable = 1;
	PolyAttributes m_atrb;
	int m_MaxY;
	int m_MinY;
	int m_MaxX;
	int m_MinX;
public:
	CCadPolygon();
	CCadPolygon(CCadPolygon &v);
	virtual ~CCadPolygon();
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual void Draw(CDC* pDC,  ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
    virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	Tokens PolyParams(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	Tokens Vertex(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	Tokens VertexList(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint Ref);
	virtual CRect GetRect(void);
	void UpdateMinMax(void);
	void SetCurPoint(CPoint p);
	void Reset(void);
	inline void SetCount(int cnt){ GetAttributes()->m_Count = cnt;}
	inline void SetPolySize(int sz){ GetAttributes()->m_Size = sz;}
	inline int GetPolySize(void){return GetAttributes()->m_Size;}
	inline void SetLineWidth(int w) { GetAttributes()->m_LineWidth = w; }
	inline int GetLineWidth(void) { return GetAttributes()->m_LineWidth; }
	inline void SetLineColor(COLORREF c) { GetAttributes()->m_LineColor = c; }
	inline COLORREF GetLineColor(void) { return GetAttributes()->m_LineColor; }
	BOOL IsTransparent(void) { return GetAttributes()->m_Transparent; }
	BOOL GetTransparent(void) { return GetAttributes()->m_Transparent; }
	void SetTransparent(BOOL t) { GetAttributes()->m_Transparent = t; }
	COLORREF GetFillColor(void) { return GetAttributes()->m_FillColor; }	
	void SetFillColor(COLORREF c) { GetAttributes()->m_FillColor = c; }	
	void Copy(CCadPolygon *pP);
	BOOL AddPoint(CPoint ptNewPoint, BOOL bInc, BOOL bIncSize);
	CPoint * GetPoints(void);
	int CompareToLast(CPoint nP);
	int DeleteLastPoint(void);
	int GetCount(void);
	BOOL PointEnclosed(CPoint,CSize Offset=CSize(0,0));
	void Create(CPoint *);
	CCadPolygon operator=(CCadPolygon &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	PolyAttributes* GetAttributes(void) { return &m_atrb; }	
};
