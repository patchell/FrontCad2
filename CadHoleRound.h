// CadHoleRound.h: interface for the CCadHoleRound class.
//
///////////////////////////////////////////////

#if !defined(AFX_CADHOLEROUND_H__14A455ED_1405_4CBA_BD0F_79D1203DB952__INCLUDED_)
#define AFX_CADHOLEROUND_H__14A455ED_1405_4CBA_BD0F_79D1203DB952__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFileParser;

struct HoleRoundAttributes {
	int m_Radius;
	int m_LineWidth;
	COLORREF m_LineColor;
	HoleRoundAttributes() {
		m_LineWidth = 1;
		m_LineColor = RGB(0, 0, 0);
		m_Radius = 50;
	}
	~HoleRoundAttributes() {}
	void CopyTo(HoleRoundAttributes* pAttrDest) {
		if (pAttrDest) {
			pAttrDest->m_LineWidth = m_LineWidth;
			pAttrDest->m_LineColor = m_LineColor;
			pAttrDest->m_Radius = m_Radius;
		}
	}
	void CopyFrom(HoleRoundAttributes* pAttrSrc) {
		if (pAttrSrc) {
			m_LineWidth = pAttrSrc->m_LineWidth;
			m_LineColor = pAttrSrc->m_LineColor;
			m_Radius = pAttrSrc->m_Radius;
		}
	}
};

class CCadHoleRound : public CCadObject
{
	friend CFileParser;
	inline static int m_RenderEnable = 1;
	HoleRoundAttributes m_atrb;
	int m_GrabVertex;
	int m_HighlightVertex;
	int m_VtxSize;
	int m_VtxSize2;
	int m_VtxGrabSize;
	int m_VtxGrabSize2;
public:
	CCadHoleRound(CCadHoleRound &h);
	CCadHoleRound();
	virtual ~CCadHoleRound();
	BOOL Create(CPoint m_Pos, HoleRoundAttributes* pHoleRoundAttributes);	
	virtual CCadObject* Copy();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CRect GetRect(void);
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void AdjustRefernce(CPoint Ref);
	virtual void Draw(CDC *pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	void SetLineColor(COLORREF c){GetAttributes()->m_LineColor = c;}
	COLORREF GetLineColor(void){return GetAttributes()->m_LineColor;}
	void SetLineWidth(int w){ GetAttributes()->m_LineWidth = w;}
	int GetLineWidth(void){return GetAttributes()->m_LineWidth;}
	void SetRadius(int r){ GetAttributes()->m_Radius = r;}
	int GetRadius(void){return GetAttributes()->m_Radius;}
	CCadHoleRound operator=(CCadHoleRound &v);
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	HoleRoundAttributes* GetAttributes() { return &m_atrb; }
};

#endif // !defined(AFX_CADHOLEROUND_H__14A455ED_1405_4CBA_BD0F_79D1203DB952__INCLUDED_)
