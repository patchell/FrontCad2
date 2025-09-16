// FrontCadDoc.h : interface of the CFrontCadDoc class
//
////////////////////////////////////////////////////

#pragma once

class CFrontCadView;
class CFileParser;

class CFrontCadDoc : public CDocument
{
	CCadDrawing* m_pDrawing;
	CFrontCadView* m_pDocView;
	CFileParser* m_pParser;
protected: // create from serialization only
	CFrontCadDoc();
	DECLARE_DYNCREATE(CFrontCadDoc)
public:
	virtual ~CFrontCadDoc();
	CFrontCadView* GetDocView() { return m_pDocView; }
	void SetDocViedw(CFrontCadView* pDV) { m_pDocView = pDV; }
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	void InsertObject(CCadObject* pObj);
	void AddObject(CCadObject* pObj);
	void RemoveObject(CCadObject* pObj);
	CCadPrintRect* GetPrintRect();
	COLORREF GetBkColor();
	void SetBkColor(COLORREF color);
	int CheckSelected(CPoint p, CCadObject** ppSelList, int n, int flag = 0) { return m_pDrawing->CheckSelected(p, ppSelList, n, flag); }
	CCadObject* GetHead(void) { return m_pDrawing->GetHead(); }
	void Print(CDC* pDC, ObjectMode mode, CPoint Offset, CScale Scale) { m_pDrawing->Print(pDC, mode, Offset, Scale); }
	CCadDrawing* GetDrawing() { return m_pDrawing; }
	CFileParser* GetParser() { return m_pParser; }
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};
