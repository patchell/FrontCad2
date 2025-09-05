// CadHoleRnd1Flat.h: interface for the CCadHoleRnd1Flat class.
//
///////////////////////////////////////////////

#if !defined(AFX_CADHOLERND1FLAT_H__A9C94EAC_1F36_421C_A9F3_8B94ED066B9B__INCLUDED_)
#define AFX_CADHOLERND1FLAT_H__A9C94EAC_1F36_421C_A9F3_8B94ED066B9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileParser;

struct HoleRnd1FlatAttributes {
	int m_LineWidth;
	int m_FlatDist;	//distance from flat to center point
	COLORREF m_LineColor;
	int m_Radius;
	HoleRnd1FlatAttributes() {
		m_LineWidth = 1;
		m_LineColor = RGB(0, 0, 0);
		m_FlatDist = 50;
		m_Radius = 50;
	}
} ;

class CCadHoleRnd1Flat : public CCadObject
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
	HoleRnd1FlatAttributes atrb;
public:
	CCadHoleRnd1Flat();
	virtual ~CCadHoleRnd1Flat();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CRect GetRect(void);
	CCadHoleRnd1Flat(CCadHoleRnd1Flat &h);
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint Ref);
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	void SetLineColor(COLORREF c){ GetAttributes()->m_LineColor = c;}
	COLORREF GetLineColor(void){return GetAttributes()->m_LineColor;}
	double SolveIntersection(int m,CPoint P,int FlatDist,int Radius);
	void SetFlatDist(int d){GetAttributes()->m_FlatDist = d; }
	int GetFlatDist(void){return GetAttributes()->m_FlatDist;}
	void SetRadius(int r){ GetAttributes()->m_Radius = r;}
	int GetRadius(void){return GetAttributes()->m_Radius;}
	void SetLineWidth(int w){ GetAttributes()->m_LineWidth = w;}
	int GetLineWidth(void){return GetAttributes()->m_LineWidth;}
	CCadHoleRnd1Flat operator=(CCadHoleRnd1Flat &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	HoleRnd1FlatAttributes* GetAttributes() { return &atrb; }
};

#endif // !defined(AFX_CADHOLERND1FLAT_H__A9C94EAC_1F36_421C_A9F3_8B94ED066B9B__INCLUDED_)
