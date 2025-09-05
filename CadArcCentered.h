// CadArcCentered.h: interface for the CCadArcCentered class.
//
///////////////////////////////////////////////

#pragma once



//----------------------------------
// It should be noted that point mP1
// is used as the center poiot, and
// m_P2 is used as the radius
//----------------------------------

class CFileParser;

class CCadArcCentered : public CCadObject
{
	inline static int m_RenderEnable = 1;
	friend CFileParser;
public:
	CCadArcCentered(CCadArcCentered &arc);
	CCadArcCentered();
	virtual ~CCadArcCentered();
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint Ref);
	void SetLineWidth(int w){m_atrb.m_LineWidth = w;}
	int GetLineWidth(void){return m_atrb.m_LineWidth;}
	void SetLineColor(COLORREF c){m_atrb.m_LineColor = c;}
	COLORREF GetLineColor(void){return m_atrb.m_LineColor;}
	void SetEndAngle(int Angle);
	int GetEndAngle(void){return m_atrb.m_EndAngle;}
	void SetStartAngle(int Angle);
	int GetStartAngle(void){return m_atrb.m_StartAngle;}
	void SetEndPoint(CPoint p);
	CPoint GetEndPoint(void){return m_atrb.m_End;}
	void SetStartPoint(CPoint p);
	CPoint GetStartPoint(void){return m_atrb.m_Start;}
	CCadArcCentered operator=(CCadArcCentered &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
private:
	ArcAttributes m_atrb;
public:
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
};
