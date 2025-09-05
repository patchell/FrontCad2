// CadLibObject.h: interface for the CCadLibObject class.
//
///////////////////////////////////////////////

#pragma once

struct StPartAttributes {
	int m_bTransparent;
	COLORREF m_LineColor;
	COLORREF m_FillColor;
	CPoint m_Ref;	// Reference point for part insertion
	int m_LineWidth;
	char* m_pName;
	StPartAttributes() {
		m_pName = 0;
		m_bTransparent = 1;
		m_LineColor = RGB(0, 0, 0);
		m_FillColor = RGB(255, 255, 255);
		m_LineWidth = 1;
	}
	~StPartAttributes() {
		if (m_pName)
			delete[] m_pName;
	}
	void SetName(const char* pN) {
		if (m_pName)
			delete[] m_pName;
		if (pN) {
			m_pName = new char[strlen(pN) + 1];
			strcpy_s(m_pName, strlen(pN) + 1, pN);
		}
		else
			m_pName = 0;
	}
	void ChangeName(const char* pN) {
		if (m_pName)
			delete[] m_pName;
		if (pN) {
			m_pName = new char[strlen(pN) + 1];
			strcpy_s(m_pName, strlen(pN) + 1, pN);
		}
		else
			m_pName = 0;
	}
	void CopyTo(StPartAttributes* pAttr) {
		if (pAttr->m_pName)
			delete[] pAttr->m_pName;
		if (m_pName) {
			pAttr->m_pName = new char[strlen(m_pName) + 1];
			strcpy_s(pAttr->m_pName, strlen(m_pName) + 1, m_pName);
		}
		else
			pAttr->m_pName = 0;
		pAttr->m_bTransparent = m_bTransparent;
		pAttr->m_LineColor = m_LineColor;
		pAttr->m_FillColor = m_FillColor;
		pAttr->m_Ref = m_Ref;
		pAttr->m_LineWidth = m_LineWidth;
	}
	void CopyFrom(StPartAttributes* pAttr) {
		if (m_pName)
			delete[] m_pName;
		if (pAttr->m_pName) {
			m_pName = new char[strlen(pAttr->m_pName) + 1];
			strcpy_s(m_pName, strlen(pAttr->m_pName) + 1, pAttr->m_pName);
		}
		else
			m_pName = 0;
		m_bTransparent = pAttr->m_bTransparent;
		m_LineColor = pAttr->m_LineColor;
		m_FillColor = pAttr->m_FillColor;
		m_Ref = pAttr->m_Ref;
		m_LineWidth = pAttr->m_LineWidth;
	}

};

class CCadLibObject : public CCadObject  
{
	inline static int m_RenderEnable = 1;
	StPartAttributes m_Attrib;
public:
	CCadLibObject();
	CCadLibObject(CCadObject* pChain);
	CCadLibObject(CCadLibObject& LibObj);
	virtual ~CCadLibObject();
	static void SetRenderEnable(int e) { m_RenderEnable = e; }
	static int IsRenderEnabled() { return m_RenderEnable; }
	virtual CRect GetRect(void);
	void AdjustRefernce(CPoint Ref);
	virtual CPoint GetReference();
	virtual void Move(CPoint p);
	virtual void SetVertex(int Vi,CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE *pO,  int Indent);
	virtual void Draw(CDC* pDC, ObjectMode mode,CPoint Offset=CPoint(0,0),CScale Scale=CScale(0.1,0.1));
	virtual void SetName(const char *pName){ GetAttributes()->SetName(pName); }
	virtual void ChangeName(const char* pName) { GetAttributes()->ChangeName(pName); }
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual void RenderEnable(int e);
	virtual CPoint GetCenter();
	CPoint& GetRef() { return m_Attrib.m_Ref; }
	char* GetPartName() { return GetAttributes()->m_pName; }
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	StPartAttributes* GetAttributes() { return &m_Attrib; }
};
