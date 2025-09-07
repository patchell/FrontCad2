// CadHoleRnd1Flat.h: interface for the CCadHoleRnd1Flat class.
//
///////////////////////////////////////////////

#pragma once

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
	~HoleRnd1FlatAttributes() {}
	void CopyTo(HoleRnd1FlatAttributes* pAttrDest) {
		if (pAttrDest) {
			pAttrDest->m_LineWidth = m_LineWidth;
			pAttrDest->m_FlatDist = m_FlatDist;
			pAttrDest->m_LineColor = m_LineColor;
			pAttrDest->m_Radius = m_Radius;
		}
	}
	void CopyFrom(HoleRnd1FlatAttributes* pAttrSrc) {
		if (pAttrSrc) {
			m_LineWidth = pAttrSrc->m_LineWidth;
			m_FlatDist = pAttrSrc->m_FlatDist;
			m_LineColor = pAttrSrc->m_LineColor;
			m_Radius = pAttrSrc->m_Radius;
		}
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
	BOOL Create(CPoint ptPos, HoleRnd1FlatAttributes* pHoleRnd1FlatAttributes);	
	virtual CCadObject* Copy();
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

