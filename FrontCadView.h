// FrontCadView.h : interface of the CFrontCadView class
//
////////////////////////////////////////////////////
#pragma once

class CFrontCadApp;
class CMainFrame;
class CUtilView;
class CLibFormView;
class CFrontCadDoc;
class CMoveObjects;

class CFrontCadView : public CView
{
	inline static int ZoomScale[MAX_ZOOM] = {
		1,
		1,
		1,
		1,
		1,
		1
	};

	inline static int ZoomScaleDiv[MAX_ZOOM] = {
		1,
		2,
		5,
		10,
		20,
		50,
	};

	inline static double ZF[MAX_ZOOM] = {
		1.0,		//1000 pixels per inch
		0.50,		// 500 pixels per inch
		0.20,		// 200 pixels per inch
		0.10,		// 100 pixels per inch
		0.05,		//  50 pixels per inch
		0.02		//	20 pixels per inch
	};
public:

	enum DrawMode {
		NONE,
		LINE,
		RECTANGLE,
		ELIPSE,
		SELECT,
		RNDRECT,
		ARC,
		POLYGON,
		POLYFILL,
		ARC_CENTER,
		HOLE_ROUND,
		HOLE_RECT,
		HOLE_RND1F,
		HOLE_RND2F,
		TEXT,
		LIBPART,
		GETREF,
		MOVE,
		COPY,
		CUT,
		PASTE,
		SELECTREGION,
		BITMAPIMAGE,
		ARROW,
		ORIGIN,
		DIMENSION,
		ALIGN_DIM_TO_HOLE,
		PRINTRECT,
		CIRCLE
	};
	struct DrawModeName {
		DrawMode mode;
		const char* name;
		DrawModeName() {
			mode = DrawMode::NONE;
			name = "";
		}
		DrawModeName(DrawMode m, const char* n) {
			mode = m;
			name = n;
		}
	};
private:
	inline static DrawModeName DrawModeNames[] = {
		{DrawMode::NONE, "None"},
		{DrawMode::LINE, "Line"},
		{DrawMode::RECTANGLE, "Rectangle"},
		{DrawMode::ELIPSE, "Ellipse"},
		{DrawMode::SELECT, "Select"},
		{DrawMode::RNDRECT, "Rounded Rectangle"},
		{DrawMode::ARC, "Arc"},
		{DrawMode::POLYGON, "Polygon"},
		{DrawMode::POLYFILL, "Filled Polygon"},
		{DrawMode::ARC_CENTER, "Centered Arc"},
		{DrawMode::HOLE_ROUND, "Round Hole"},
		{DrawMode::HOLE_RECT, "Rectangular Hole"},
		{DrawMode::HOLE_RND1F, "1 Flat Round Hole"},
		{DrawMode::HOLE_RND2F, "2 Flat Round Hole"},
		{DrawMode::TEXT, "Text"},
		{DrawMode::LIBPART, "Library Part"},
		{DrawMode::GETREF, "Get Reference"},
		{DrawMode::MOVE, "Move"},
		{DrawMode::COPY, "Copy"},
		{DrawMode::CUT, "Cut"},
		{DrawMode::PASTE, "Paste"},
		{DrawMode::SELECTREGION, "Select Region"},
		{DrawMode::BITMAPIMAGE, "Bitmap Image"},
		{DrawMode::ARROW, "Arrow"},
		{DrawMode::ORIGIN, "Origin"},
		{DrawMode::DIMENSION, "Dimension"},
		{DrawMode::ALIGN_DIM_TO_HOLE, "Align Dimension to Hole"},
		{DrawMode::PRINTRECT, "Print Rectangle"},
		{DrawMode::CIRCLE, "Circle"},
		{DrawMode::NONE, 0}
	};

	int m_nSelRegionLock;
	CCadBitmap* m_pTempCadBitmap;
	CMoveObjects* m_pClipBoard;;
	CMoveObjects* m_pMoveObj;
	CPoint m_MouseUpPoint;
	CPoint m_MouseDownPoint;
	CPoint m_RefPoint;
	CMainFrame* m_pParent;
	CPoint       m_RefScroll;
	BOOL         m_bMoveImage;
	float 	     m_fZoomFactor;
	BOOL         m_bShowRulers;
	int m_SelectionCount;
	int m_VPageSize;
	int m_HPageSize;
	int m_VScrollPos;
	int m_HScrollPos;
	//------------------------------------
	// Drawing Variables
	//------------------------------------
	CCadObject* m_pDrawObject;
	CCadObject* m_pSelObjList, * m_pSelObjEnd;
	int m_Drawmode;
	int m_MouseState;
	int m_DrawState;
	//	CPoint m_CurPos;
	CPoint m_SnapPos;	//this is the real poisition in real units
	CPoint m_MousePos;	//virtual mouse position (corrected for scroll)
	CPoint m_SelRegion_P2;
	CPoint m_SelRegion_P1;
	COLORREF m_GridColor;
	int m_GridOn;
	int m_Grid;
	CSize m_DocSize;
	CSize m_ImageSize;
	int m_ZoomLevel;
	int m_DragState;
	int m_SnapOff;
	int m_DragObject;
	int m_GrabbedVertex;
	CPoint m_PolyStart;
	CBitmap* m_pDCbm;
	CDC* m_pMemDC;
	int m_SnapGrid;
protected: // create from serialization only
	CFrontCadView();
	virtual ~CFrontCadView();
	DECLARE_DYNCREATE(CFrontCadView)
	void DrawCrosshairs(CDC *pDC,CRect *pRect,CPoint pos);
	void DrawGrid(CDC *pDC, ObjectMode mode,CRect rect);
    void UpdateRulerInfo(int nMessage, CPoint ScrollPos, CPoint Pos = CPoint(0, 0)); 

public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL DestroyWindow();
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	CPoint GetOrigin(void);
	void NextSnap(int mode,int SnapUnits);
	BOOL SetCursorPos(CPoint pos);
	CPoint GetCursorPos(void);
	void UpdateScrollbarInfo(void);
	CPoint CorrectMousePosition(CPoint point);
	CPoint GetScrollPosition(void);
	CLibFormView *GetLibFormView(void);
	void ChangeObject(CUtilView *pUV,CCadObject *pO);
	//------------------------------------------
	// Object Selection Management Functions
	//------------------------------------------
	void ClearSelList(void);
	CCadObject *PopSelList(void);
	void RemoveObject(CCadObject *pO);
	void RemoveUnselected(void);
	CCadObject * GetTopSelection(void);
	void AddToSelList(CCadObject *pO);
	int IncSelectionCount(BOOL PreInc = TRUE) {
		int Count;
		if (PreInc)
			Count = ++m_SelectionCount;
		else
			Count = m_SelectionCount++;
		return Count;
	}
	int DecSelectionCount(BOOL PreDec = TRUE) {
		int Count;

		if (PreDec)
			Count = --m_SelectionCount;
		else
			Count = m_SelectionCount--;
		return Count;
	}
	//-------------------------------------------
	void FillInUtilView(CUtilView *pUV, CCadObject *pSel);
	CPoint Snap(CPoint nP,int SnapUnits);
	CUtilView * GetUtilityView(void);
	CCadObject* FindHole(CCadObject* pHead, CPoint p);
	int IsHole(CCadObject* pObj);
	CPoint SnapToScreen(CPoint npSnap);
	CPoint Scale(CPoint p);
	void PrintToDC(CDC* pDC);
	void FixDimensions(void);
	CScale GetScale(void) const {
		return CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]);
	}
#ifdef _DEBUG
	CFrontCadDoc* GetDocument();
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:
	LRESULT OnLibViewRequestReferencePoint(WPARAM wP,LPARAM lP);
	LRESULT OnUtilMessage(WPARAM wP, LPARAM lP);
	afx_msg LRESULT OnUpdatedimensions(WPARAM wParam, LPARAM lParam);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnToolbarZoomout();
	afx_msg void OnUpdateToolbarZoomout(CCmdUI* pCmdUI);
	afx_msg void OnToolbarZoomin();
	afx_msg void OnUpdateToolbarZoomin(CCmdUI* pCmdUI);
	afx_msg void OnToolbarToggleruler();
	afx_msg void OnToolbarSelect();
	afx_msg void OnToolbarRect();
	afx_msg void OnToolbarLine();
	afx_msg void OnToolbarEllipse();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnToolbarRndrect();
	afx_msg void OnToolbarGridonoff();
	afx_msg void OnToolbarGridsettings();
	afx_msg void OnToolbarLibpart();
	afx_msg void OnToolbarPolygon();
	afx_msg void OnToolbarScalewiz();
	afx_msg void OnToolbarArc();
	afx_msg void OnToolbarArcCenter();
	afx_msg void OnToolbarHolernd();
	afx_msg void OnToolbarRecthole();
	afx_msg void OnToolbarRnd1flat();
	afx_msg void OnToolbarTwoflats();
	afx_msg void OnToolbarDrawtext();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnToolbarSelectregion();
	afx_msg void OnToolbarBitmap();
	afx_msg void OnFilePrinttoclipboard();
	afx_msg void OnButtonArrowobj();
	afx_msg void OnButtonDimension();
	afx_msg void OnButtonOrigin();
	afx_msg void OnViewRenderenable();
	afx_msg void OnAlignCentersvertical();
	afx_msg void OnAlignCentershorizontal();
	afx_msg void OnAlignCenters();
	afx_msg void OnUpdateAlignCentersUI(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignCentershorizontal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignCentersvertical(CCmdUI* pCmdUI);
	afx_msg void OnAlignBottom();
	afx_msg void OnAlignLeft();
	afx_msg void OnAlignRight();
	afx_msg void OnAlignSizeboth();
	afx_msg void OnAlignSizex();
	afx_msg void OnAlignSizey();
	afx_msg void OnAlignTop();
	afx_msg void OnUpdateAlignBottom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignRight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignSizeboth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignSizex(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignSizey(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignTop(CCmdUI* pCmdUI);
	afx_msg void OnButtonPrintRectangle();
	afx_msg void OnToolbarCircle();
	//    afx_msg void OnUpdateToolbarCircle(CCmdUI* pCmdUI);
	afx_msg void OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FrontCadView.cpp
inline CFrontCadDoc* CFrontCadView::GetDocument()
   { return (CFrontCadDoc*)m_pDocument; }
#endif
