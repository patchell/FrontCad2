// CadObject.h: interface for the CCadObject class.
//
///////////////////////////////////////////////

#pragma once


struct ObjectTypeMembers {
	const char* m_pName;
	int m_Type;
	ObjectTypeMembers()
	{
		m_pName = 0;
		m_Type = 0;
	}
	ObjectTypeMembers(const char* s, int T)
	{
		m_pName = s;
		m_Type = T;
	}
	BOOL Is(int Type) const {
		BOOL rV = FALSE;
		if (m_Type == Type)
			rV = TRUE;
		return rV;
	}
};
class CCadDrawing;
class CFileParser;

class CCadObject
{

	int m_Type;
	CPoint m_P2;
	CPoint m_P1;
	int m_Selected;
	CCadObject* m_pPrev;
	CCadObject* m_pNext;
	CCadObject* m_pHead; // Used for library parts and groups of objects
	CCadObject* m_pTail;
	CCadObject* m_pSelNext;
	inline static BOOL RenderObjectFillsEnable = TRUE;
public:
	CCadObject();
	CCadObject(int type);
	virtual ~CCadObject();
	//----------------------------------
	// Private Data Member Access
	//----------------------------------
	void SetP1(CPoint p) { m_P1 = p; }
	void SetP1X(int x) { m_P1.x = x; }
	void SetP1Y(int y) { m_P1.y = y; }
	CPoint& GetP1() { return m_P1; }
	virtual void SetP2(CPoint p) { m_P2 = p; }
	void SetP2X(int x) { m_P2.x = x; }
	void SetP2Y(int y) { m_P2.y = y; }
	CPoint& GetP2() { return m_P2; }
	virtual void SetSelected(int Sel = 0) { m_Selected = Sel; }
	int GetSelected() const { return m_Selected; }
	void SetNext(CCadObject* pN) { m_pNext = pN; }
	CCadObject* GetNext() { return m_pNext; }
	void SetPrev(CCadObject* pP) { m_pPrev = pP; }
	CCadObject* GetPrev() { return m_pPrev; }
	void SetNextSelection(CCadObject* pNS) { m_pSelNext = pNS; }
	CCadObject* GetNextSelection() { return m_pSelNext; }
	//----------------------------------
	virtual void Move(CPoint p);
	virtual Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CCadDrawing** ppDrawing, CFileParser* pParser);
	virtual void Save(FILE* pO, int Indent);
	virtual void SetVertex(int Vi, CPoint p);
	virtual int GrabVertex(CPoint p);
	virtual void Draw(CDC* pDC, ObjectMode mode, CPoint Offset = CPoint(0, 0), CScale Scale = CScale(0.1, 0.1));
	virtual int CheckSelected(CPoint p, CSize Offset = CSize(0, 0));
	virtual CPoint GetReference();
	virtual void AdjustRefernce(CPoint Ref);
	virtual CRect GetRect(void);
	virtual const char* GetTypeString(void);
	void SetType(int t) { m_Type = t; }
	int GetType(void) const { return m_Type; }
	virtual CCadObject operator=(CCadObject& v) = 0;
	CPoint ScalePoint(CPoint p, int Scale, int ScaleDiv);
	virtual CCadObject* Copy() = 0;
	void SetRect(CRect& rect, CPoint P1, CPoint P2, CSize Lw);
	virtual void RenderEnable(int e);
	CCadObject* PopHead();
	CCadObject* PopTail();
	// Moves the center of the object to the spcified point
	virtual void ChangeCenter(CSize p);
	virtual CSize GetSize();
	virtual void ChangeSize(CSize Sz);
	static const char* LookupTypeName(int TypeToken);
	//-------------------------------------------------
	// Alignment
	//-------------------------------------------------
	virtual int GetTop();
	virtual int GetBottom();
	virtual int GetLeft();
	virtual int GetRight();
	virtual CPoint GetCenter();
	virtual CPoint GetUpperLeftPoint();
	virtual CPoint GetLowerRightPoint();
	static void EnableRenderFills() {
		RenderObjectFillsEnable = TRUE;
	}
	static void DisableRenderFills() {
		RenderObjectFillsEnable = FALSE;
	}
	static BOOL AreShapeFillsEnable() {
		return RenderObjectFillsEnable;
	}
	static BOOL AreShapeFillsDisabled() {
		return !RenderObjectFillsEnable;
	}
	virtual void SetHead(CCadObject* pH) {
		m_pHead = pH;
	}
	virtual void SetTail(CCadObject* pT) {
		m_pTail = pT;
	}
	virtual CCadObject* GetTail() {
		return m_pTail;
	}
	virtual CCadObject* GetHead() {
		return m_pHead;
	}
	virtual void AddObjectToEnd(CCadObject* pO) {
		if (m_pTail) {
			m_pTail->SetNext(pO);
			pO->SetPrev(m_pTail);
		}
		m_pTail = pO;
		if (!m_pHead) {
			m_pHead = pO;
		}
	}
	virtual void AddObjectToStart(CCadObject* pO) {
		if (m_pHead) {
			m_pHead->SetPrev(pO);
			pO->SetNext(m_pHead);
		}
		m_pHead = pO;
		if (!m_pTail) {
			m_pTail = pO;
		}
	}
	virtual void RemoveObject(CCadObject* pO) {
		if (pO == m_pHead) {
			m_pHead = pO->GetNext();
			if (m_pHead) {
				m_pHead->SetPrev(0);
			}
			else {
				m_pTail = 0;
			}
		}
		else if (pO == m_pTail) {
			m_pTail = pO->GetPrev();
			if (m_pTail) {
				m_pTail->SetNext(0);
			}
			else {
				m_pHead = 0;
			}
		}
		else {
			if (pO->GetPrev()) {
				pO->GetPrev()->SetNext(pO->GetNext());
			}
			if (pO->GetNext()) {
				pO->GetNext()->SetPrev(pO->GetPrev());
			}
		}
		pO->SetNext(0);
		pO->SetPrev(0);
	}
};
