// FrontCadView.cpp : implementation of the CFrontCadView class
//

#include "stdafx.h"

constexpr auto ID_OBJECTSEL = 3120;
constexpr auto ZOOM_NORMAL = 1;
constexpr auto INCHES_DECPLACE = 3;
constexpr auto DEGREE_DECPLACE = 1;

double ZF[MAX_ZOOM] = {
	1.0,		//1000 pixels per inch
	0.50,		// 500 pixels per inch
	0.20,		// 200 pixels per inch
	0.10,		// 100 pixels per inch
	0.05,		//  50 pixels per inch
	0.02		//	20 pixels per inch
};

int ZoomScale[MAX_ZOOM] = {
	1,
	1,
	1,
	1,
	1,
	1
};

int ZoomScaleDiv[MAX_ZOOM] = {
	1,
	2,
	5,
	10,
	20,
	50,
};



///////////////////////////////////
// CFrontCadView

IMPLEMENT_DYNCREATE(CFrontCadView, CView)

BEGIN_MESSAGE_MAP(CFrontCadView, CView)
	//{{AFX_MSG_MAP(CFrontCadView)
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_TOOLBAR_ZOOMOUT, OnToolbarZoomout)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_ZOOMOUT, OnUpdateToolbarZoomout)
	ON_COMMAND(ID_TOOLBAR_ZOOMIN, OnToolbarZoomin)
	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_ZOOMIN, OnUpdateToolbarZoomin)
	ON_COMMAND(ID_TOOLBAR_TOGGLERULER, OnToolbarToggleruler)
	ON_COMMAND(ID_TOOLBAR_SELECT, OnToolbarSelect)
	ON_COMMAND(ID_TOOLBAR_RECT, OnToolbarRect)
	ON_COMMAND(ID_TOOLBAR_LINE, OnToolbarLine)
	ON_COMMAND(ID_TOOLBAR_ELLIPSE, OnToolbarEllipse)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TOOLBAR_RNDRECT, OnToolbarRndrect)
	ON_COMMAND(ID_TOOLBAR_GRIDONOFF, OnToolbarGridonoff)
	ON_COMMAND(ID_TOOLBAR_GRIDSETTINGS, OnToolbarGridsettings)
	ON_COMMAND(ID_TOOLBAR_LIBPART, OnToolbarLibpart)
	ON_COMMAND(ID_TOOLBAR_POLYGON, OnToolbarPolygon)
	ON_COMMAND(ID_TOOLBAR_SCALEWIZ, OnToolbarScalewiz)
	ON_COMMAND(ID_TOOLBAR_ARC, OnToolbarArc)
	ON_COMMAND(ID_TOOLBAR_ARC_CENTER, OnToolbarArcCenter)
	ON_COMMAND(ID_TOOLBAR_HOLERND, OnToolbarHolernd)
	ON_COMMAND(ID_TOOLBAR_RECTHOLE, OnToolbarRecthole)
	ON_COMMAND(ID_TOOLBAR_RND_1FLAT, OnToolbarRnd1flat)
	ON_COMMAND(ID_TOOLBAR_TWOFLATS, OnToolbarTwoflats)
	ON_COMMAND(ID_TOOLBAR_DRAWTEXT, OnToolbarDrawtext)
	ON_WM_KILLFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_TOOLBAR_SELECTREGION, OnToolbarSelectregion)
	ON_COMMAND(ID_TOOLBAR_BITMAP, OnToolbarBitmap)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_MESSAGE(WM_UTILMESSAGE,OnUtilMessage)
	ON_MESSAGE(WM_LIBVIEW_GETREF,OnLibViewRequestReferencePoint)
	ON_COMMAND(ID_FILE_PRINTTOCLIPBOARD, &CFrontCadView::OnFilePrinttoclipboard)
	ON_COMMAND(ID_BUTTON_ARROWOBJ, &CFrontCadView::OnButtonArrowobj)
	ON_COMMAND(ID_BUTTON_DIMENSION, &CFrontCadView::OnButtonDimension)
	ON_COMMAND(ID_BUTTON_ORIGIN, &CFrontCadView::OnButtonOrigin)
	ON_MESSAGE(WM_UPDATEDIMENSIONS, &CFrontCadView::OnUpdatedimensions)
	ON_COMMAND(ID_VIEW_RENDERENABLE, &CFrontCadView::OnViewRenderenable)
	ON_COMMAND(ID_ALIGN_CENTERSVERTICAL, &CFrontCadView::OnAlignCentersvertical)
	ON_COMMAND(ID_ALIGN_CENTERSHORIZONTAL, &CFrontCadView::OnAlignCentershorizontal)
	ON_COMMAND(ID_ALIGN_CENTERS, &CFrontCadView::OnAlignCenters)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_CENTERS, &CFrontCadView::OnUpdateAlignCentersUI)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_CENTERSHORIZONTAL, &CFrontCadView::OnUpdateAlignCentershorizontal)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_CENTERSVERTICAL, &CFrontCadView::OnUpdateAlignCentersvertical)
	ON_COMMAND(ID_ALIGN_BOTTOM, &CFrontCadView::OnAlignBottom)
	ON_COMMAND(ID_ALIGN_LEFT, &CFrontCadView::OnAlignLeft)
	ON_COMMAND(ID_ALIGN_RIGHT, &CFrontCadView::OnAlignRight)
	ON_COMMAND(ID_ALIGN_SIZEBOTH, &CFrontCadView::OnAlignSizeboth)
	ON_COMMAND(ID_ALIGN_SIZEX, &CFrontCadView::OnAlignSizex)
	ON_COMMAND(ID_ALIGN_SIZEY, &CFrontCadView::OnAlignSizey)
	ON_COMMAND(ID_ALIGN_TOP, &CFrontCadView::OnAlignTop)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BOTTOM, &CFrontCadView::OnUpdateAlignBottom)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_LEFT, &CFrontCadView::OnUpdateAlignLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_RIGHT, &CFrontCadView::OnUpdateAlignRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_SIZEBOTH, &CFrontCadView::OnUpdateAlignSizeboth)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_SIZEX, &CFrontCadView::OnUpdateAlignSizex)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_SIZEY, &CFrontCadView::OnUpdateAlignSizey)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_TOP, &CFrontCadView::OnUpdateAlignTop)
	ON_COMMAND(ID_BUTTON_PRINT_RECTANGLE, &CFrontCadView::OnButtonPrintRectangle)
	ON_COMMAND(ID_TOOLBAR_CIRCLE, &CFrontCadView::OnToolbarCircle)
//	ON_UPDATE_COMMAND_UI(ID_TOOLBAR_CIRCLE, &CFrontCadView::OnUpdateToolbarCircle)
ON_WM_SYSCHAR()
ON_WM_SYSKEYDOWN()
ON_WM_SYSKEYUP()
END_MESSAGE_MAP()

///////////////////////////////////
// CFrontCadView construction/destruction

CFrontCadView::CFrontCadView()
{
	m_VScrollPos = 0;
	m_HScrollPos = 0;
	m_HPageSize = 0;
	m_VPageSize = 0;
	m_pClipBoard = 0;
	m_pParent = NULL;
	m_bMoveImage = FALSE;
	m_fZoomFactor = 1.0;
	m_bShowRulers = TRUE;
	m_pMemDC = NULL;
	m_pDCbm = NULL;
	m_SelRegion_P1 = CPoint(0, 0);
	m_SelRegion_P2 = CPoint(0, 0);
	m_pMoveObj = 0;
	m_ZoomLevel = 3;
	m_GrabbedVertex = -1;
	m_DragObject = 0;
	m_Drawmode = 0;
	m_DrawState = 0;
	m_pDrawObject = 0;
	m_SnapOff = 0;		//snap grid is on
	m_Grid = 1000;		//1 inch grid
	m_GridColor = RGB(128, 255, 255);
	m_GridOn = 1;		//grid is on
	m_SnapGrid = 250;	//1/4 inch grid
	m_DragState = 0;
	m_DocSize = CSize(24000, 24000);
	m_pTempCadBitmap = 0;
	m_MouseState = 0;
	//Selected Object List
	m_pSelObjList = 0;
	m_pSelObjEnd = 0;
	m_nSelRegionLock = 0;
	m_SelectionCount = 0;
}

CFrontCadView::~CFrontCadView()
{
}

BOOL CFrontCadView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

///////////////////////////////////
// CFrontCadView drawing

void CFrontCadView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
//------------------------------------------
//	OnPrint
//		This is the draw function that is
// called when the device context is
// the printer.
//
//	parameters:
//		pDC....pointer to the device context
//		pInfo..poointer to printer information
//------------------------------------------
	int HPix = pDC->GetDeviceCaps(HORZRES);
	int VPix = pDC->GetDeviceCaps(VERTRES);
	int DpiX = pDC->GetDeviceCaps(LOGPIXELSX);
	int DpiY = pDC->GetDeviceCaps(LOGPIXELSY);
	int OffX = pDC->GetDeviceCaps(PHYSICALOFFSETX);
	int OffY = pDC->GetDeviceCaps(PHYSICALOFFSETY);
	pDC->SetMapMode(MM_HIENGLISH);
	CFrontCadDoc* pDoc = GetDocument();
	CPoint offset;
	CBrush br;
	CRect rect;
	CCadPrintRect *pagerect;
	if ((pagerect = pDoc->GetPrintRect()) == NULL)
	{
		offset.SetPoint(0, 0);
	}
	else
	{
		offset = pagerect->GetRect().TopLeft();
		pagerect->RenderEnable(0);
	}
	rect.SetRect(0,0,HPix-1,VPix-1);
	br.CreateSolidBrush(pDoc->GetBkColor());
	pDC->FillRect(&rect,&br);
	//----------------------------------
	// Print the document
	//----------------------------------
	offset.x = -offset.x;
	pDoc->Print(pDC,ObjectMode::Final,offset,CScale(1.0,-1.0));
	//make dirty all over again.
	if (pagerect)pagerect->RenderEnable(1);


	CView::OnPrint(pDC, pInfo);
}

void CFrontCadView::OnDraw(CDC* pDC)
{
	//----------------------------------------
	// OnDraw
	//		This is the function that is called
	// when the screen needs to be redrawn.
	// To minimize screen flicker, all drawing
	// is done to a Memory DC, and then it is
	// blt to the screen.
	//
	//	parameters:
	//		pDC....pointer to the device context
	//----------------------------------------
	ObjectMode mode;
	CDC DCm;
	CBitmap bm,*oldBM = 0;
	CFrontCadDoc* pDoc = GetDocument();
	CCadObject *pCO = pDoc->GetDrawing();
	CRect rect;
	CBrush brushBackground;
	COLORREF colorOldBk;

	//Create memory DC
	GetClientRect(&rect);
	DCm.CreateCompatibleDC(pDC);
	bm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	oldBM = DCm.SelectObject(&bm);
	// erase background
	colorOldBk = DCm.SetBkColor(((CCadDrawing*)pCO)->GetBkColor());
	brushBackground.CreateSolidBrush(((CCadDrawing *)pCO)->GetBkColor());
	DCm.FillRect(&rect, &brushBackground);
	//draw the grid
	DrawGrid(&DCm, ObjectMode::None, rect);
	// Create an offet point based on the scroll position
	CPoint Off = CPoint(m_HScrollPos, m_VScrollPos);
	// Draw the objects
	pCO->Draw(&DCm, ObjectMode::Final, -Off, CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]));
	if (m_DrawState == DRAWSTATE_MOVE  && m_pDrawObject)
	{
		mode = ObjectMode::Sketch;
		m_pDrawObject->Draw(&DCm, mode, -Off, CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]));
	}
	else if ( m_DrawState == DRAWSTATE_ARCSTART)
	{
		mode = ObjectMode::ArcStart;
		m_pDrawObject->Draw(&DCm, mode, -Off, CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]));
	}
	else if (m_DrawState == DRAWSTATE_ARCEND)
	{
		mode = ObjectMode::ArcEnd;
		m_pDrawObject->Draw(&DCm, mode, -Off, CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]));
	}
	if (m_pMoveObj)
	{
		m_pMoveObj->Draw(&DCm, SnapToScreen(m_SnapPos) - Off, CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]));
	}
	if ((m_Drawmode == DrawMode::SELECTREGION) && ((m_MouseState == MOUSESTATE_DOWN)|| (m_nSelRegionLock) ) )
	{
		int bkm = DCm.SetBkMode(TRANSPARENT);
		CRect RRect;
		CSize Offset;
		CPoint P1, P2;
		P1 = CScale(ZF[m_ZoomLevel],ZF[m_ZoomLevel]) * m_SelRegion_P1;
		P2 = CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]) * m_SelRegion_P2;
		Offset.cx = -m_HScrollPos;
		Offset.cy = -m_VScrollPos;
		RRect.SetRect(P1 +Offset,P2 +Offset);
		CPen DotPen;
		DotPen.CreatePen(PS_DOT,1,RGB(0,0,0));
		CPen *oP;
		oP = DCm.SelectObject(&DotPen);
		DCm.DrawDragRect(&RRect,CSize(1,1),NULL,CSize(1,1));
		DCm.SelectObject(oP);
		DCm.SetBkMode(bkm);
	}
	DrawCrosshairs(&DCm,&rect, SnapToScreen(m_SnapPos));
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&DCm,0,0,SRCCOPY);
	DCm.SetBkColor(colorOldBk);
	if (oldBM)DCm.SelectObject(oldBM);
}

void CFrontCadView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

    m_pParent = ((CMainFrame*)GetParentFrame());
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
    m_pParent->ShowRulers(TRUE);
	CRect clientrect;
	GetClientRect(&clientrect);
	m_DocSize = CSize(24000,24000);	//document size is in mils
	m_ImageSize = clientrect.Size();
	((CFrontCadApp *)AfxGetApp())->SetMainView(this);
	ShowScrollBar(SB_BOTH,TRUE);
	UpdateScrollbarInfo();
	EnableScrollBarCtrl(SB_VERT,TRUE);
	EnableScrollBarCtrl(SB_HORZ,TRUE);
	OnToolbarSelect();
	//----------------------------------
	// Create a memory device context
	// so we can get rid of the flicker
	//----------------------------------
	CDC *pDC = GetDC();
	if(m_pMemDC) delete m_pMemDC;
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(pDC);
	if(m_pDCbm) delete m_pDCbm;
	m_pDCbm = new CBitmap;
	m_pDCbm->CreateBitmap(clientrect.Width(),clientrect.Height(),1,32,NULL);
	m_pMemDC->SelectObject(m_pDCbm);
	CBrush br;
	br.CreateSolidBrush(RGB(255,255,255));
	m_pMemDC->FillRect(&clientrect,&br);
	//-----------------------------------------
	CUtilView *pUV = GetUtilityView();
	pUV->ShowHide(0);
	pUV->SetCadView(this);

	CFrontCadDoc *pDoc = GetDocument();
	pUV->m_Static_Background.SetColor(pDoc->GetBkColor());
	pUV->m_Static_Background.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::BACKGROUND);

	pUV->m_Edit_X3.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::X3);
	pUV->m_Edit_X3.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_Y3.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::Y3);
	pUV->m_Edit_Y3.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_X2.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::X2);
	pUV->m_Edit_X2.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_Y2.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::Y2);
	pUV->m_Edit_Y2.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_X1.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::X1);
	pUV->m_Edit_X1.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_Y1.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::Y1);
	pUV->m_Edit_Y1.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_LineThickness.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::LINEWIDTH);
	pUV->m_Edit_LineThickness.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Static_LineColor.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::LINECOLOR);
	pUV->m_Static_FillColor.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::FILLCOLOR);
	pUV->m_Static_TextColor.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::TEXTCOLOR);
	pUV->m_Static_BkGrndColor.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::TEXTBKCOLOR);
	pUV->m_Edit_FlatToCenterDist.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::FLATDIST);
	pUV->m_Edit_FlatToCenterDist.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_HoleRadius.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::HOLERADIUS);
	pUV->m_Edit_HoleRadius.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_Text.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::_TEXT);
	pUV->m_Edit_FontHeight.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::FONTHEIGHT);
	pUV->m_Edit_FontHeight.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_FontWidth.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::FONTWIDTH);
	pUV->m_Edit_FontWidth.SetDecimalPlaces(INCHES_DECPLACE);
	pUV->m_Edit_TextAngle.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::TEXTANGLE);
	pUV->m_Edit_TextAngle.SetDecimalPlaces(DEGREE_DECPLACE);
	pUV->m_Check_TransparentFont.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::TEXTTRANSPARENT);
	pUV->m_Check_TransparentFill.SetupMessaging(this, WM_UTILMESSAGE, UtilMsg::TRANSPARENT_FILL);

	pUV->m_Combo_PrintRect.SetupMessaging(this, WM_UTILMESSAGE, UtilMsg::_PRINTRECT);
	pUV->m_Combo_FontWeight.SetupMessaging(this,WM_UTILMESSAGE,UtilMsg::FONTWEIGHT);
	pUV->m_Button_Font.SetWindowText(pA->m_TextAttributes.m_pFontName);

	pDoc->SetDocViedw(this);

    OnUpdate(NULL, 0, NULL);
}

///////////////////////////////////
// CFrontCadView printing

BOOL CFrontCadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFrontCadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void CFrontCadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

///////////////////////////////////
// CFrontCadView diagnostics

#ifdef _DEBUG
void CFrontCadView::AssertValid() const
{
	CView::AssertValid();
}

void CFrontCadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFrontCadDoc* CFrontCadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFrontCadDoc)));
	return (CFrontCadDoc*)m_pDocument;
}
#endif //_DEBUG

///////////////////////////////////
// CFrontCadView message handlers

BOOL CFrontCadView::OnEraseBkgnd(CDC* pDC)
{
	//--------------------------------------
	//	OnEraseBkgnd
	//		We override this function so that
	//	the window is not erased.
	//--------------------------------------
	return TRUE;
}

void CFrontCadView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//----------------------------------------
	// OnKeyDown
	//		This function is used to intercept
	// key presses, looking for  HHotkeys
	// that do certain funcrtions
	//----------------------------------------
	//if(theApp.HasConsol()) p

	switch(nChar)	//check the key press
	{
	case VK_CONTROL:	//control key
		m_SnapOff = 1;	//turn of snapo grid
			break;
		case VK_DELETE:
			break;
		case VK_LEFT:
			break;
		case VK_RIGHT:
			break;
		case VK_UP:
			break;
		case VK_DOWN:
			break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFrontCadView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//--------------------------------------------
	// OnKeyUp
	//		This function intercepts key releases.
	//--------------------------------------------
	int id;

//	if (theApp.HasConsol()) 
	switch(nChar)	//check released character
	{
		case VK_CONTROL:	//control key
			m_SnapOff = 0;	//turn snap back on
			break;
		case VK_DELETE:	//delete selected objects
			{
				id = MessageBox("Delete Selected Objects?","DELETE OBJECTS",MB_YESNO);
				if(id == IDYES)
				{
					CCadObject *pObj = GetTopSelection();
					CFrontCadDoc *pDoc = GetDocument();
					while(pObj)
					{
						RemoveObject(pObj);
						pDoc->RemoveObject(pObj);
						delete pObj;
						pObj = GetTopSelection();
					}
				}
			}
			break;
		case VK_LEFT:	//left arrow, move cursor
			NextSnap(VK_LEFT,m_SnapGrid);
			SetCursorPos(m_MousePos);
			Invalidate();
			break;
		case VK_RIGHT:	//right arrow, move cursor
			NextSnap(VK_RIGHT,m_SnapGrid);
			SetCursorPos(m_MousePos);
			Invalidate();
			break;
		case VK_UP:	//up arrow, move cursor
			NextSnap(VK_UP,m_SnapGrid);
			SetCursorPos(m_MousePos);
			Invalidate();
			break;
		case VK_DOWN:	//down arrow,movecursor
			NextSnap(VK_DOWN,m_SnapGrid);
			SetCursorPos(m_MousePos);
			Invalidate();
			break;
		case 'A':	//A key, draw arc
			OnToolbarArc();
			break;
		case 'E':	// E key, draw Ellipse
			OnToolbarEllipse();
			break;
		case 'G':	//G key, toggle grid
			this->m_GridOn ^= 1;
			break;
		case 'L':	//L key, draw line
			OnToolbarLine();
			break;
		case 'P':	//P key, draw polygon
			OnToolbarPolygon();
			break;
		case 'R':	//R key, draw rectangle
			OnToolbarRect();
			break;
		case 'S':	//S key, toggle Snap Grid
			this->m_SnapOff ^= 1;
			break;
		case VK_ESCAPE:	//escape key
			m_Drawmode = DrawMode::SELECT;
			break;
		case VK_MENU: //alt key
			m_SnapOff = 0; //turn off snap grid
			break;
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CFrontCadView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//-------------------------------------------
	// OnLButtonDown
	//		This function perfroms the functions
	// when the mouse button is presses.
	//
	//	parameters:
	//		nFlags.....status flaGs of mouse press
	//		point......point where mouse was pressed
	//-------------------------------------------
	CCadRoundRect* pRRect = 0;
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	CFrontCadDoc *pDoc = GetDocument();
	CUtilView *pUV = this->GetUtilityView();

	// correct mouse position for scrolling, etc
	m_MousePos = CorrectMousePosition(point);
	// Snap the mouse posiition
	m_SnapPos = Snap(m_MousePos,m_SnapGrid);
	this->m_MouseState = MOUSESTATE_DOWN;
	//do actions depending of Drawmode state
	switch(m_Drawmode)
	{
		case DrawMode::NONE:
			break;
		case DrawMode::LINE:
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					{
						CCadLine *pLine;

						pA->UpdateLineAttrib(pUV);
						pLine = new CCadLine;
						pLine->Create(m_SnapPos, &pA->m_LineAttrib);
						m_pDrawObject = (CCadObject *)pLine;
					}
					break;
				case DRAWSTATE_MOVE:
					break;
			}
			break;
		case DrawMode::RECTANGLE:	//Button Down
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					{
						CCadRect *pCR = new CCadRect();
						//update rectangle attributes
						pA->UpdateRectAttributes(pUV);
						pCR->Create(m_SnapPos, &pA->m_RectAttributes);
						m_pDrawObject = (CCadObject *)pCR;
					}
					break;
				case DRAWSTATE_MOVE:
					break;
			}
			break;
		case DrawMode::CIRCLE:		//Button Down
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
			{
				CUtilView* pUV = GetUtilityView();
				CCadCircle* pCC = new CCadCircle;
				pA->UpdateCircleAttributes(pUV);
				pCC->Create(m_SnapPos, &pA->m_CircleAttributs);
				m_pDrawObject = (CCadObject*)pCC;
			}
			break;
			case DRAWSTATE_MOVE:
				break;
			}
			break;
		case DrawMode::ELIPSE:
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					{
						CUtilView *pUV = GetUtilityView();
						CCadElipse *pCE = new CCadElipse();
						//update ellipse attributes
						pA->UpdateEllipseAttributes(pUV);
						//create the ellipse
						pCE->Create(m_SnapPos, &pA->m_EllipseAttributes);
						m_pDrawObject = (CCadObject *)pCE;
				}
					break;
				case DRAWSTATE_MOVE:
					break;
			}
			break;
		case DrawMode::SELECT://MOUSE DOWN
			//----------------------------------
			// Now we are getting complicated.
			// We do not know, at this junksure
			// if the user is just selecting an
			// object, or wants to maybe drag
			// something.
			//----------------------------------
			if(m_pSelObjList)	//object selected?
			{
				CCadObject *pOb = m_pSelObjList;
				m_GrabbedVertex = pOb->GrabVertex(m_SnapPos);
				if(m_GrabbedVertex < 0)
				{
					if(pOb->CheckSelected(Scale(m_MousePos)))
						m_DragObject = 1;
				}
			}
			break;
		case DrawMode::RNDRECT:	//MOUSE DOWN
		{
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					//update rounded rect paramters
					pA->UpdateRndRectAttributes(pUV);
					//------------------------------------------------------------
					pRRect = new CCadRoundRect;
					pRRect->Create(m_SnapPos, &pA->m_RndRectAttributes);
					//--------------------------------------
					m_pDrawObject = (CCadObject *)pRRect;
					break;
				case DRAWSTATE_MOVE:
					break;
			}
		}
		break;
		case DrawMode::POLYGON://MOUSE DOWN
			{
				CCadPolygon* pCP = new CCadPolygon;
				pCP->Create(m_SnapPos, &pA->m_PolyAttributes);
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:	//This is where we start
						//update polygon attributes
						pA->UpdatePolyAttributes(pUV);
						pCP->Create(m_SnapPos, &pA->m_PolyAttributes);
						pCP->AddPoint(m_SnapPos, FALSE, TRUE);
						m_pDrawObject = (CCadObject *)pCP;
						m_PolyStart = m_SnapPos;
						break;
					case DRAWSTATE_MOVE:
						if (!((m_SnapPos.x == m_PolyStart.x) && (m_SnapPos.y == m_PolyStart.y)))
						{

							pCP = (CCadPolygon*)m_pDrawObject;
							pCP->AddPoint(m_SnapPos, FALSE, TRUE);
						}
						break;
				}
			}
			break;
		case DrawMode::ARC:	//mouse down
			{
				CCadArc *pCA;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						pA->UpdateArcAttributes(pUV);
						pCA = new CCadArc;
						pCA->Create(m_SnapPos, &pA->m_ArcAttributes);
						m_pDrawObject = (CCadObject *)pCA;
						break;
					case DRAWSTATE_MOVE:
						break;
					case DRAWSTATE_ARCSTART:
						pCA = (CCadArc *)m_pDrawObject;
						pCA->SetStartPoint(m_SnapPos);
						break;
					case DRAWSTATE_ARCEND:
						break;
				}
			}
			break;
		case DrawMode::ARC_CENTER:	//Mouse Down
			{
				CCadArcCentered* pCA = 0;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						//update arc attributes
						pA->UpdateArcAttributes(pUV);
						pCA = new CCadArcCentered;
						pCA->Create(m_SnapPos, &pA->m_ArcAttributes);
						m_pDrawObject = (CCadObject *)pCA;
						break;
					case DRAWSTATE_MOVE:
						break;
					case DRAWSTATE_ARCSTART:
						pCA = (CCadArcCentered *)m_pDrawObject;
						pCA->SetStartPoint(m_SnapPos);
						break;
					case DRAWSTATE_ARCEND:
						pCA = (CCadArcCentered *)m_pDrawObject;
						pCA->SetEndPoint(m_SnapPos);
						break;
				}
			}
			break;
		case DrawMode::HOLE_ROUND:	//Mouse Down
			{
				CCadHoleRound *pHR;
				switch (m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						pA->UpdateHoleRoundAttributes(pUV);
						pHR = new CCadHoleRound;
						pHR->Create(m_SnapPos, &pA->m_HoleRoundAttributes);
						m_pDrawObject = (CCadObject *)pHR;
						Invalidate();
						break;
					case DRAWSTATE_MOVE:
						Invalidate();
						break;
				}
			}
			break;
		case DrawMode::HOLE_RECT:
			{
				CCadRectHole *pRH;

				switch (m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						pRH = new CCadRectHole;
						pA->UpdateRectHoleAttributes(pUV);
						pRH->Create(m_SnapPos, &pA->m_RectHoleAttributes);
						m_pDrawObject = (CCadObject*)pRH;
						Invalidate();
						break;
					case DRAWSTATE_MOVE:
						Invalidate();
						break;
				}
			}
			break;
		case DrawMode::HOLE_RND1F:
			{
				CCadHoleRnd1Flat *pHR;

				switch (m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						pA->UpdateHoleRnd1FlatAttributes(pUV);
						pHR = new CCadHoleRnd1Flat;
						pHR->Create(m_SnapPos, &pA->m_HoleRnd1FlatAttributes);
						m_pDrawObject = (CCadObject *)pHR;
						Invalidate();
						break;
					case DRAWSTATE_MOVE:
						break;
				}
			}
			break;
		case DrawMode::HOLE_RND2F:
			{
				CCadHoleRnd2Flat *pHR;

				switch (m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						//update hole rnd2flat attributes
						pA->UpdateHoleRnd2FlatAttributes(pUV);
						pHR = new CCadHoleRnd2Flat;
						pHR->Create(m_SnapPos, &pA->m_HoleRnd2FlatAttributes);
						m_pDrawObject = (CCadObject *)pHR;
						Invalidate();
						break;
					case DRAWSTATE_MOVE:
						Invalidate();
						break;
				}
			}
			break;
		case DrawMode::TEXT:	//Mouse Down
			{
				char *s = new char[256];
				CCadText* pCT = new CCadText;
				//update text attributes
				pA->UpdateTextAttributes(pUV);
				pCT->Create(m_SnapPos, &pA->m_TextAttributes);
				pUV->m_Edit_Text.GetWindowText(s, 256);
				pCT->SetText(s);
				pDoc->AddObject(pCT);
				delete[] s;
				Invalidate();
			}
			break;
		case DrawMode::LIBPART:
			{
				CLibFormView *pLFV = ((CFrontCadApp *)AfxGetApp())->GetLibView();
				CCadLibObject *pLO = pLFV->GetCurrentPart();
				if(pLO)
				{
					CCadLibObject *pPart = new CCadLibObject(pLO->GetHead());
					pPart->SetName(pLO->GetPartName());
					pPart->SetP1(m_SnapPos);
					pDoc->AddObject(pPart);
					Invalidate();
				}
				else
				{
					m_Drawmode = DrawMode::SELECT;
					MessageBox("No Libraries or Parts Selected","Oppsie",MB_OK | MB_ICONHAND);
				}
			}
			break;
		case DrawMode::GETREF:
			break;
		case DrawMode::MOVE:		// mouse down
			switch(this->m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					{
						m_RefPoint = m_SnapPos;
						CCadObject *pObj = GetTopSelection();
						m_pMoveObj = new CMoveObjects;
						while(pObj)
						{
							pDoc->RemoveObject(pObj);
							RemoveObject(pObj);
							m_pMoveObj->AddObject(pObj);
							pObj = GetTopSelection();
						}
					}
					m_pMoveObj->SetRef(m_SnapPos);
//					m_pMoveObj = &m_MoveObj;
					Invalidate();
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			break;
		case DrawMode::COPY:	//mouse button down
			switch(m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					{
						//----------------------------------------------
						//for copy, leave the objects behind in the
						//drawing, but make a new copy of the objects
						//to put into the "clipboard"
						//----------------------------------------------
//						m_RefPoint = m_SnapPos;
						CCadObject *pObj = this->GetTopSelection();
						CCadObject *newObj;
						if (m_pClipBoard == NULL) m_pClipBoard = new CMoveObjects;
						m_pClipBoard->Clear(1);
						while(pObj)
						{
							newObj = pObj->Copy();
							m_pClipBoard->AddObject(newObj);
							RemoveObject(pObj);
							pObj->SetSelected(0);
							pObj = GetTopSelection();
						}
						m_pClipBoard->SetRef(m_SnapPos);
						Invalidate();
					}
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			break;
		case DrawMode::PASTE:		//mouse down
			switch (m_DrawState)
			{
				case DRAWSTATE_PLACE:
					if (m_pClipBoard)
					{
						m_pMoveObj = new CMoveObjects;
						m_pMoveObj->Copy(*m_pClipBoard);
						Invalidate();
					}
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			break;
		case DrawMode::CUT:		//Mouse Down
			switch(m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					{
						//----------------------------------------------
						//for copy, leave the objects behind in the
						//drawing, but make a new copy of the objects
						//to put into the "clipboard"
						//----------------------------------------------
						CCadObject *pObj = this->GetTopSelection();
						if (m_pClipBoard == 0) m_pClipBoard = new CMoveObjects;
						m_pClipBoard->Clear(1);	//delete objects in clipboard
						while(pObj)
						{
							RemoveObject(pObj);	//remove from sel list
							//remove from drawing
							pDoc->RemoveObject(pObj);
							//add to clipboard
							m_pClipBoard->AddObject(pObj);
							//get next obje3ct
							pObj = GetTopSelection();
						}
						m_pClipBoard->SetRef(m_SnapPos);
						Invalidate();
					}
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			break;
		case DrawMode::SELECTREGION:	//Button Down
			if (m_nSelRegionLock)
			{
				m_nSelRegionLock = 0;
				m_Drawmode = DrawMode::SELECT;
			}
			else
			{
				m_nSelRegionLock = 1;
				m_SelRegion_P1 = m_SnapPos;
				m_SelRegion_P2 = m_SnapPos;
				ClearSelList();
			}
			break;
		case DrawMode::BITMAPIMAGE:
			m_pDrawObject = m_pTempCadBitmap;
			m_pDrawObject->SetP1(m_SnapPos);
			break;
		case DrawMode::ARROW:	//Button Down
			{
				CCadArrow* pArrow = 0;
				switch (m_DrawState)
				{
				case DRAWSTATE_WAITMOUSE_DOWN:
				{
					pArrow = new CCadArrow;
					pA->UpdateArcAttributes(pUV);
					//-------------------------------
					pArrow->Create(m_SnapPos, &pA->m_ArrowAttrib);
					//-------------------------------
					m_pDrawObject = (CCadObject*)pArrow;
				}
				break;
				case DRAWSTATE_MOVE:
					break;
				}
			}
			Invalidate();
			break;
		case DrawMode::ORIGIN:	//button down
			{
			CCadOrigin* pOrg = 0;
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
				pA->UpdateOriginAttrib(pUV);
				pOrg = new CCadOrigin;
				pOrg->Create(m_SnapPos, &pA->m_OriginAttrib);
				pOrg->SetParent(this);
				m_pDrawObject = (CCadObject*)pOrg;
				break;
			case DRAWSTATE_MOVE:
				break;
			case DRAWSTATE_PLACE:
				break;
			}
			Invalidate();
		}
			break;
		case DrawMode::DIMENSION:	//mouse button down
			{
				CCadDimension *pCD;
				char *s = new char[256];
				switch (m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						//---------------------------------
						// Update Dimension Settings
						//---------------------------------
						pA->UpdateDimAttributes(pUV);
						//---------------------------------
						pCD = new CCadDimension;
						pCD->Create(m_SnapPos, &pA->m_DimAttrib);
						m_pDrawObject = (CCadObject *)pCD;
						Invalidate();
						break;
					case DRAWSTATE_MOVE:
						Invalidate();
						break;
				}
				delete[] s;
			}
			break;
		case DrawMode::ALIGN_DIM_TO_HOLE:	//Mouse button down
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					Invalidate();
					break;
			}
			break;
		case DrawMode::PRINTRECT:	//Mouse Button Down
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
			{
				CCadPrintRect *pPR = new CCadPrintRect;
				pPR->SetP1(m_SnapPos);
				pPR->SetLineWidth(40);
				pPR->SetLineColor(RGB(0, 0, 0));
				pPR->SetSize(pUV->m_Combo_PrintRect.GetPrintRectSize());
				m_pDrawObject = (CCadObject *)pPR;
				Invalidate();
			}
				break;
			case DRAWSTATE_MOVE:
				break;
			}
			break;
	}		 
	CView::OnLButtonDown(nFlags, point);
}

void CFrontCadView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//-----------------------------------------------
	// OnLButtonUp
	//		This function is used to perfrom functions
	// when the mouse button is released.
	//	parameters:
	//		nFlags.....Mouse flags
	//		point......point where mouse button released
	//-----------------------------------------------

	m_MousePos = CorrectMousePosition(point);
	m_SnapPos = Snap(m_MousePos,m_SnapGrid);
	CFrontCadDoc *pDoc = GetDocument();
	m_MouseState = MOUSESTATE_UP;
	switch(m_Drawmode)
	{
		case DrawMode::NONE:	//L Button Up
			theApp.GetMainFrame()->UpdateStatusBar("Select Object");
			break;
		case DrawMode::LINE:		//L Button Up
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					theApp.GetMainFrame()->UpdateStatusBar("Line:Place Second Point");
					m_DrawState = DRAWSTATE_MOVE;
					break;
				case DRAWSTATE_MOVE:
					theApp.GetMainFrame()->UpdateStatusBar("Line:Place First Point");
					if (m_pDrawObject)
					{
						m_pDrawObject->SetP2(m_SnapPos);
						pDoc->AddObject(m_pDrawObject);
						m_pDrawObject = 0;
						m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
					}
					break;
			}
			Invalidate();
			break;
		case DrawMode::CIRCLE:		//L Button Up
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
				theApp.GetMainFrame()->UpdateStatusBar("Place Radial Point");
				m_DrawState = DRAWSTATE_MOVE;
				break;
			case DRAWSTATE_MOVE:
				if (m_pDrawObject)
				{
					CCadCircle* pCC = (CCadCircle*)m_pDrawObject;
					pCC->SetP2(m_SnapPos);
					pCC->CalculateRadius();
					pDoc->AddObject(m_pDrawObject);
					m_pDrawObject = 0;
					m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
					theApp.GetMainFrame()->UpdateStatusBar("Place Center Point");
				}
				Invalidate();
				break;
			}
			break;
		case DrawMode::RECTANGLE:	//Button Up
		case DrawMode::ELIPSE:
		case DrawMode::RNDRECT:
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					theApp.GetMainFrame()->UpdateStatusBar("Place Second Corner");
					m_DrawState = DRAWSTATE_MOVE;
					break;
				case DRAWSTATE_MOVE:
					if (m_pDrawObject)
					{
						m_pDrawObject->SetP2(m_SnapPos);
						pDoc->AddObject(m_pDrawObject);
						m_pDrawObject = 0;
						m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
						theApp.GetMainFrame()->UpdateStatusBar("Place First Corner");
					}
					Invalidate();
					break;
			}
			break;
		case DrawMode::POLYGON:	//mouse up.
			{
				CCadPolygon *pCP = (CCadPolygon *)m_pDrawObject;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						// 
						m_DrawState = DRAWSTATE_MOVE;
						pCP->AddPoint(m_SnapPos, TRUE, TRUE);	// first point
						pCP->AddPoint(m_SnapPos, FALSE, FALSE); //rubber band point
						theApp.GetMainFrame()->UpdateStatusBar("PolyGon:Place Next Point");
						break;
					case DRAWSTATE_MOVE:
						{
							if ((m_SnapPos.x == m_PolyStart.x) && (m_SnapPos.y == m_PolyStart.y))
							{
								//-----------------------------------------------
								// So, at this point, this poloyggon is finished
								//-----------------------------------------------
								//we are back at the start point, terminate
								pCP->GetAttributes()->m_Size--;	//remove rubber band point from count
								pCP->GetAttributes()->m_Count--;
								pDoc->AddObject(m_pDrawObject);
								m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
								m_pDrawObject = 0;
							}
							else
							{
								pCP->AddPoint(m_SnapPos, TRUE, FALSE);
								pCP->AddPoint(m_SnapPos, FALSE, FALSE);
							}
						}
						Invalidate();
						break;
				}
			}
			Invalidate();
			break;
		case DrawMode::ARC:	//Mouse Up
			{
				CCadArc *pCA = (CCadArc *)m_pDrawObject;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						pCA->SetP1(m_SnapPos);
						pCA->SetP2(m_SnapPos);
						m_DrawState = DRAWSTATE_MOVE;
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place Second Corner");
						break;
					case DRAWSTATE_MOVE:
						m_pDrawObject->SetP2(m_SnapPos);
						m_DrawState = DRAWSTATE_ARCSTART;
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place Start of Arc");
						break;
					case DRAWSTATE_ARCSTART:
						pCA->SetStartPoint(m_SnapPos);
						m_DrawState = DRAWSTATE_ARCEND;
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place End of Arc");
						break;
					case DRAWSTATE_ARCEND:
						pCA->SetEndPoint(m_SnapPos);
						pDoc->AddObject(m_pDrawObject);
						m_pDrawObject = 0;
						m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place First Corner");
						break;
				}
			}
			Invalidate();
			break;
		case DrawMode::ARC_CENTER:	//Mouse Up	
			{
				CCadArcCentered *pCA = (CCadArcCentered *)m_pDrawObject;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						pCA->SetP1(m_SnapPos);
						m_DrawState = DRAWSTATE_MOVE;
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place Defining Rectangle");
						break;
					case DRAWSTATE_MOVE:
						m_pDrawObject->SetP2(m_SnapPos);
						m_DrawState = DRAWSTATE_ARCSTART;
						pCA->SetStartPoint(pCA->GetP2());
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place Start of Arc");
						break;
					case DRAWSTATE_ARCSTART:
						pCA->SetStartPoint(m_SnapPos);
						m_DrawState = DRAWSTATE_ARCEND;
						pCA->SetEndPoint(pCA->GetStartPoint());
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place End of Arc");
						break;
					case DRAWSTATE_ARCEND:
						pCA->SetEndPoint(m_SnapPos);
						m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
						pDoc->AddObject(m_pDrawObject);
						theApp.GetMainFrame()->UpdateStatusBar("Arc:Place Center of Arc");
						m_pDrawObject = 0;
						break;
				}
			}
			Invalidate();
			break;
		case DrawMode::SELECT:	//MOUSE UP
			m_pDrawObject = 0;
			if(m_pSelObjList && (( 0 <= m_GrabbedVertex) || m_DragObject))	//a part is selected
			{
				CCadObject *pOb = m_pSelObjList;
				if(pOb->GetSelected())
				{
					pOb->SetSelected(0);
					this->RemoveObject(pOb);
					CUtilView *pUV = GetUtilityView();
					if(this->m_pSelObjList)
					{
						FillInUtilView(pUV,m_pSelObjList);
						pUV->ShowHideForSelected(m_pSelObjList->GetType());
					}
					else
						pUV->ShowHideForSelected(0);

					Invalidate();
				}
				m_GrabbedVertex = -1;
				m_DragObject = 0;
			}
			else
			{
				CCadObject **selObjs = new CCadObject*[8];
				int c;
				c = pDoc->CheckSelected(Scale(m_MousePos),selObjs,8);
				if(c > 1)
				{
					CMenu Menu;
					Menu.CreatePopupMenu();
					int i;
					char *s = new char[256];
					for(i=0;i<c;++i)
					{
						sprintf_s(s,256,"%s:(%d,%d)",selObjs[i]->GetTypeString(),selObjs[i]->GetP1().x,selObjs[i]->GetP1().y);
						Menu.AppendMenu(MF_STRING,ID_OBJECTSEL+i,s);
					}
					for(i=0;i<c;++i)
						Menu.EnableMenuItem(ID_OBJECTSEL+i,MF_ENABLED);
					CRect rect;
					GetWindowRect(&rect);
					CPoint Offset = point + rect.TopLeft();
					int id = Menu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, Offset.x, Offset.y,this);
					if(id > 0)
					{
						int sel;
						sel = selObjs[id - ID_OBJECTSEL]->GetSelected() ^ 1;
						selObjs[id - ID_OBJECTSEL]->SetSelected(sel);
						if(selObjs[id-ID_OBJECTSEL]->GetSelected())
						{
							this->AddToSelList(selObjs[id-ID_OBJECTSEL]);
							CUtilView *pUV = GetUtilityView();
							FillInUtilView(pUV,selObjs[id-ID_OBJECTSEL]);
							pUV->ShowHideForSelected(selObjs[id-ID_OBJECTSEL]->GetType());
							pUV->SetupTextSelected(selObjs[id-ID_OBJECTSEL]->GetType());
							Invalidate();
						}
					}
					delete[] s;
				}
				else if(c==1)
				{
					selObjs[0]->SetSelected(selObjs[0]->GetSelected() ^ 1);
					if(selObjs[0]->GetSelected())
					{
						this->AddToSelList(selObjs[0]);
						CUtilView *pUV = GetUtilityView();
						FillInUtilView(pUV,selObjs[0]);
						pUV->ShowHideForSelected(selObjs[0]->GetType());
						pUV->SetupTextSelected(selObjs[0]->GetType());

					}
					Invalidate();
				}
				//don't do anything if c==0
				delete[] selObjs;
			}
			break;
		case DrawMode::HOLE_ROUND:	//Mouse Up
		case DrawMode::HOLE_RECT:
		case DrawMode::HOLE_RND1F:
		case DrawMode::HOLE_RND2F:
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					m_DrawState = DRAWSTATE_MOVE;
					m_pDrawObject->SetP1(m_SnapPos);
					Invalidate();
					theApp.GetMainFrame()->UpdateStatusBar("Hole:Place Center of Hole");
					break;
				case DRAWSTATE_MOVE:
					m_pDrawObject->SetP1(m_SnapPos);
					pDoc->AddObject(m_pDrawObject);
					m_pDrawObject = 0;
					m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
					theApp.GetMainFrame()->UpdateStatusBar("Hole:Locate Center of Hole");
					Invalidate();
					break;
			}
			break;
		case DrawMode::TEXT:		//mouse up
			m_pDrawObject = 0;
			break;
		case DrawMode::LIBPART:	//mouse up
			m_pDrawObject = 0;
			break;
		case DrawMode::GETREF:
			m_Drawmode = 0;	// no draw mode
			{
				CPoint Ref = m_SnapPos;
				((CFrontCadApp *)AfxGetApp())->GetLibView()->PostMessageA(WM_MAINVIEW_GOTREF, Ref.x, Ref.y);
			}
			break;
		case DrawMode::MOVE:		//mouse up
			switch(m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					m_DrawState = DRAWSTATE_DRAG;
					break;
					theApp.GetMainFrame()->UpdateStatusBar("Move:Drag Objects");
				case DRAWSTATE_DRAG:
					{
						CCadObject *pO = m_pMoveObj->GetHead();
						while(pO)
						{
							pO->SetSelected(0);
							m_pMoveObj->RemoveObject(pO);
							pDoc->AddObject(pO);
							pO->AdjustRefernce(-m_SnapPos);
							pO = m_pMoveObj->GetHead();
						}
					}
					delete m_pMoveObj;
					m_pMoveObj = 0;
					m_Drawmode = DrawMode::SELECT;
					theApp.GetMainFrame()->UpdateStatusBar("Select Object");
					Invalidate();
					break;
			}
			break;
		case DrawMode::COPY:	//mouse button up
			switch(this->m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					m_Drawmode = DrawMode::SELECT;
					theApp.GetMainFrame()->UpdateStatusBar("Select Object");
					Invalidate();
					break;
				case DRAWSTATE_DRAG:
					Invalidate();
					break;
			}
			break;
		case DrawMode::PASTE:	//mouse button up
			switch (m_DrawState)
			{
				case DRAWSTATE_PLACE:
					m_DrawState = DRAWSTATE_DRAG;
					theApp.GetMainFrame()->UpdateStatusBar("Drag Object(s)");
					break;
				case DRAWSTATE_DRAG:
					{
						CCadObject *pObj;
						do
						{
							pObj = m_pMoveObj->RemoveFromHead();
							if (pObj)
							{
								pObj->SetSelected(0);
								pObj->AdjustRefernce(-m_SnapPos);
								pDoc->AddObject(pObj);
							}
						} while (pObj);
						delete m_pMoveObj;
						m_pMoveObj = 0;
						Invalidate();
					}
					m_Drawmode = DrawMode::SELECT;
					m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
					theApp.GetMainFrame()->UpdateStatusBar("Select Object");
					break;
			}
			break;
		case DrawMode::CUT:		//mouse up
			switch (m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					m_Drawmode = DrawMode::SELECT;
					theApp.GetMainFrame()->UpdateStatusBar("Select Object");
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			Invalidate();
			break;
		case DrawMode::SELECTREGION:		//Mouse Button UP
			m_SelRegion_P2 = m_SnapPos;
			{
				CRect Rsel,rect;
				Rsel.SetRect(m_SelRegion_P1,m_SelRegion_P2);
				Rsel.NormalizeRect();
				CCadDrawing *pD = pDoc->GetDrawing();
				CCadObject *pObj = pD->GetHead();
				CScale sf = CScale(1.0, 1.0);
				while(pObj)
				{
					rect = pObj->GetRect();
					if (Rsel.PtInRect(sf * rect.TopLeft()) && Rsel.PtInRect(sf * rect.BottomRight()))
					{
						if (OBJECT_TYPE_ORIGIN != pObj->GetType())
						{
							pObj->SetSelected(1);
							this->AddToSelList(pObj);
						}
					}
					pObj = pObj->GetNext();
				}
			}
			m_nSelRegionLock = 0;
			m_Drawmode = DrawMode::SELECT;
			Invalidate();
//			m_Drawmode = DrawMode::SELECT;
			break;
		case DrawMode::BITMAPIMAGE:
			if(m_pDrawObject)
			{
				m_pDrawObject->SetP2(m_SnapPos); ;
				if(m_pDrawObject->GetP1() != m_pDrawObject->GetP2())
				{
					pDoc->AddObject(m_pDrawObject);
					m_pDrawObject = 0;
					m_pTempCadBitmap = 0;
				}
				else
				{
					delete m_pTempCadBitmap;
					m_pDrawObject = 0;
					m_pTempCadBitmap = 0;
				}
			}
			Invalidate();
			break;
		case DrawMode::ARROW:	//Button Up
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
				m_pDrawObject->SetP1(m_SnapPos); ;
				m_DrawState = DRAWSTATE_MOVE;
				Invalidate();
				theApp.GetMainFrame()->UpdateStatusBar("Arrow:Set Direction Arrow Points");
				break;
			case DRAWSTATE_MOVE:
				if (m_pDrawObject)
				{
					m_pDrawObject->SetP2(m_SnapPos);
					if (m_pDrawObject->GetP1() != m_pDrawObject->GetP2())
					{
						pDoc->AddObject(m_pDrawObject);
						m_pDrawObject = 0;
						m_pTempCadBitmap = 0;
					}
					m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
					Invalidate();
					theApp.GetMainFrame()->UpdateStatusBar("Arrow:Place Location of Point");
				}
				break;
			}


			break;
		case DrawMode::ORIGIN:	//Left Button Up
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					m_DrawState = DRAWSTATE_MOVE;
					theApp.GetMainFrame()->UpdateStatusBar("Origin:Place Location");
					break;
				case DRAWSTATE_MOVE:
					m_pDrawObject->SetP1(m_SnapPos);
					pDoc->AddObject(m_pDrawObject);
					m_pDrawObject = 0;
					m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
					break;
			}
			Invalidate();
			break;
		case DrawMode::DIMENSION:	//Mouse Up
		{
			CCadDimension *pCD;

			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					pCD = (CCadDimension *)m_pDrawObject;
					pCD->SetP2(m_SnapPos);
					pCD->SetP1(m_SnapPos);
					m_DrawState = DRAWSTATE_MOVE;
					theApp.GetMainFrame()->UpdateStatusBar("Dimension:Place Second Point of Dimension");
					Invalidate();
					break;
				case DRAWSTATE_MOVE:
					pCD = (CCadDimension *)m_pDrawObject;
					{
						CPoint NewPos, UpdatedPos;
						NewPos = m_SnapPos;
						int diffx, diffy;
						diffx = abs(NewPos.x - pCD->GetP1().x);
						diffy = abs(NewPos.y - pCD->GetP1().y);
						if (diffx > diffy)
						{
							NewPos = CPoint(NewPos.x, pCD->GetP1().y);
						}
						else
						{
							NewPos = CPoint(pCD->GetP1().x, NewPos.y);
						}
						pCD->SetP2(NewPos); ;

					}
					pCD->UpdateText(GetOrigin());
					pDoc->AddObject(pCD);
					m_pDrawObject = 0;
					m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
					theApp.GetMainFrame()->UpdateStatusBar("Dimension:Place First Point of Dimension");
					Invalidate();
					break;
			}
		}
		break;
		case DrawMode::ALIGN_DIM_TO_HOLE:	//Mouse button up.
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					{
						CCadObject *pHole,*pHead;
						pHead = pDoc->GetHead();
						pHole = FindHole(pHead, m_SnapPos);
						if (pHole)
						{
							CCadDimension *pDim;
							if (GetTopSelection()->GetType() == OBJECT_TYPE_DIMENSION)
							{
								pDim = (CCadDimension *)GetTopSelection();
								pDim->AlignToPoint(pHole->GetReference());
								pDim->UpdateText(GetOrigin());
								
							}
							Invalidate();
							m_Drawmode = DrawMode::SELECT;
							theApp.GetMainFrame()->UpdateStatusBar("Select Object");
						}
					}
					break;
			}
			break;
		case DrawMode::PRINTRECT:	//Mouse button up.
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
//				m_DrawState = DRAWSTATE_MOVE;
//				theApp.GetMainFrame()->UpdateStatusBar("Print Rectangle:Place Second Corner");
//				break;
//			case DRAWSTATE_MOVE:
				m_pDrawObject->SetP1(m_SnapPos);
				pDoc->InsertObject(m_pDrawObject);
				m_pDrawObject = 0;
				m_Drawmode = DrawMode::SELECT;
				m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
				theApp.GetMainFrame()->UpdateStatusBar("Select::Select an Object");
				Invalidate();
				break;
			}
			break;
	}

	CView::OnLButtonUp(nFlags, point);
}

void CFrontCadView::OnMouseMove(UINT nFlags, CPoint point)
{
	//-----------------------------------------------
	// OnMouseMove
	//		This function handles the functionality
	// when the mouse is moved.
	//-----------------------------------------------
	CPoint LastPosition = m_SnapPos;
	m_MousePos = CorrectMousePosition(point);
	m_SnapPos = Snap(m_MousePos,m_SnapGrid);
	CMainFrame *pMF = (CMainFrame *)((CFrontCadApp *)AfxGetApp())->m_pMainWnd;
	pMF->SetXYPos(m_SnapPos.x,m_SnapPos.y);
    UpdateRulerInfo(RW_POSITION, CPoint(m_HScrollPos,m_VScrollPos), SnapToScreen(m_SnapPos));
	switch(m_Drawmode)
	{
		case DrawMode::NONE:	// OnMouseMove
			break;
		case DrawMode::LINE:	// OnMouseMove
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					break;
				case DRAWSTATE_MOVE:
					if (m_pDrawObject)
						m_pDrawObject->SetP2(m_SnapPos);
					break;
			}
			break;
		case DrawMode::CIRCLE:	// OnMouseMove
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
				break;
			case DRAWSTATE_MOVE:
				if (m_pDrawObject)
					m_pDrawObject->SetP2(m_SnapPos);
				break;
			}
			break;
		case DrawMode::RECTANGLE:
		case DrawMode::ELIPSE:
		case DrawMode::RNDRECT:
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					break;
				case DRAWSTATE_MOVE:
					if (m_pDrawObject)
						m_pDrawObject->SetP2(m_SnapPos);
					break;
			}
			break;
		case DrawMode::POLYGON:	//mouse move
			{
				CCadPolygon *pCP = (CCadPolygon *)m_pDrawObject;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						break;
					case DRAWSTATE_MOVE:
						pCP->AddPoint(m_SnapPos,FALSE,FALSE);
						break;
				}
			}
			break;
		case DrawMode::ARC:	//mouse move
			{
				CCadArc *pCA = (CCadArc *)m_pDrawObject;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						if (pCA) {
							pCA->SetP1(m_SnapPos);
							pCA->SetP2(m_SnapPos);
						}
						break;
					case DRAWSTATE_MOVE:
						{
							pCA->SetP2(m_SnapPos);
						}
						break;
					case DRAWSTATE_ARCSTART:
						pCA->SetStartPoint(m_SnapPos);
						break;
					case DRAWSTATE_ARCEND:
						pCA->SetEndPoint(m_SnapPos);
					break;
				}
			}
			break;
		case DrawMode::ARC_CENTER:	//Mouse Move
			{
				CCadArcCentered *pCA = (CCadArcCentered *)m_pDrawObject;
				switch(m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						break;
					case DRAWSTATE_MOVE:
						pCA->SetP2(m_SnapPos);
						break;
					case DRAWSTATE_ARCSTART:
						pCA->SetStartPoint(m_SnapPos);
						break;
					case DRAWSTATE_ARCEND:
						pCA->SetEndPoint(m_SnapPos);
						Invalidate();
					break;
				}
			}
			break;
		case DrawMode::SELECT:	//MOUSE MOVE
			if(m_DragObject && m_pSelObjList)
			{
				CPoint Diff = m_SnapPos - LastPosition;
				m_pSelObjList->Move(m_pSelObjList->GetReference()+Diff);
			}
			else if(m_pSelObjList && (0 <= m_GrabbedVertex))	//object selected?
			{
				m_pSelObjList->SetVertex(m_GrabbedVertex,m_SnapPos);
			}
			break;
		case DrawMode::HOLE_ROUND:	//Mouse Move
		case DrawMode::HOLE_RECT:
		case DrawMode::HOLE_RND1F:
		case DrawMode::HOLE_RND2F:
			if (m_pDrawObject)
			{
				switch (m_DrawState)
				{
					case DRAWSTATE_WAITMOUSE_DOWN:
						m_pDrawObject->SetP1(m_SnapPos);
						break;
					case DRAWSTATE_MOVE:
						m_pDrawObject->SetP1(m_SnapPos); 
						break;
				}
			}
			break;
		case DrawMode::MOVE:	//mouse move
			switch (m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			break;
		case DrawMode::COPY:
		case DrawMode::CUT:
			switch (m_DrawState)
			{
				case DRAWSTATE_GETREFEREMCE:
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			break;
		case DrawMode::PASTE:	//mouse move
			switch (m_DrawState)
			{
				case DRAWSTATE_PLACE:
					break;
				case DRAWSTATE_DRAG:
					break;
			}
			break;
		case DrawMode::TEXT:
		case DrawMode::LIBPART:
		case DrawMode::GETREF:
			break;
		case DrawMode::SELECTREGION:
			if(m_MouseState == MOUSESTATE_DOWN)
				m_SelRegion_P2 = m_SnapPos;
			break;
		case DrawMode::BITMAPIMAGE:
			if(m_pDrawObject)
			{
				m_pDrawObject->SetP2(m_SnapPos);
			}
			break;
		case DrawMode::ARROW:	//mouse move
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
				if(m_pDrawObject)
					m_pDrawObject->SetP1(m_SnapPos);
				break;
			case DRAWSTATE_MOVE:
				m_pDrawObject->SetP2(m_SnapPos);
				break;
			}
			break;
		case DrawMode::ORIGIN:	//OnMouseMove
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
				break;
				case DRAWSTATE_MOVE:
					if (m_pDrawObject)
						m_pDrawObject->SetP1(m_SnapPos);
					break;
				case DRAWSTATE_PLACE:
					break;
			}
			break;
		case DrawMode::DIMENSION:	//Mouse Move
		{
			CCadDimension *pCD;

			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					if (m_MouseState == MOUSESTATE_DOWN)
					{
						pCD = (CCadDimension *)m_pDrawObject;
						pCD->SetP2(m_SnapPos);
						pCD->SetP1(m_SnapPos);
					}
					break;
				case DRAWSTATE_MOVE:
					if (m_MouseState == MOUSESTATE_DOWN)
					{
						pCD = (CCadDimension *)m_pDrawObject;
						CPoint NewPos, UpdatedPos;
						NewPos = m_SnapPos;
						int diffx, diffy;
						diffx = abs(NewPos.x - pCD->GetP1().x);
						diffy = abs(NewPos.y - pCD->GetP1().y);
						if (diffx > diffy)
						{
							NewPos = CPoint(NewPos.x, pCD->GetP1().y);
						}
						else
						{
							NewPos = CPoint(pCD->GetP1().x, NewPos.y);
						}
						pCD->SetP2(NewPos);
					}
					break;
			}
		}
		break;
		case DrawMode::ALIGN_DIM_TO_HOLE:
			switch (m_DrawState)
			{
				case DRAWSTATE_WAITMOUSE_DOWN:
					break;
			}
			break;
		case DrawMode::PRINTRECT:
			switch (m_DrawState)
			{
			case DRAWSTATE_WAITMOUSE_DOWN:
				break;
			case DRAWSTATE_MOVE:
				m_pDrawObject->SetP1(m_SnapPos);
				break;
			}
			break;
	}
	Invalidate();
	CView::OnMouseMove(nFlags, point);
}

void CFrontCadView::OnSize(UINT nType, int cx, int cy)
{
	//-----------------------------------------
	// OnSize
	//		This function is called whenever the
	// window has been resized.
	//
	//	parameters:
	// 	pType......Specifies type of resizing requested
	//		cx.........X size
	//		cy.........Y size
	//-----------------------------------------
	CView::OnSize(nType, cx, cy);

	int HScrollMax = 0;
	m_HScrollPos = 0;
	m_HPageSize = 0;
   if (cx < (m_DocSize.cx / ZoomScaleDiv[m_ZoomLevel])) {
        HScrollMax = (m_DocSize.cx / ZoomScaleDiv[m_ZoomLevel])- 1;
        m_HPageSize = cx;
        m_HScrollPos = min (m_HScrollPos, (m_DocSize.cx/ ZoomScaleDiv[m_ZoomLevel]) - m_HPageSize - 1);
    }
	SCROLLINFO si;
    si.nMin = 0;
    si.nMax = HScrollMax;
    si.nPos = m_HScrollPos;
    si.nPage = m_HPageSize;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nTrackPos = 0;
	SetScrollInfo (SB_HORZ, &si, TRUE);
	int VScrollMax=0;
	m_VScrollPos = 0;
	m_VPageSize = 0;

    if (cy < (m_DocSize.cy/ ZoomScaleDiv[m_ZoomLevel]) ) {
        VScrollMax = (m_DocSize.cy/ ZoomScaleDiv[m_ZoomLevel]) - 1;
        m_VPageSize = cy;
        m_VScrollPos = min (m_VScrollPos, (m_DocSize.cy/ ZoomScaleDiv[m_ZoomLevel]) - m_VPageSize - 1);
    }
    si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
    si.nMin = 0;
    si.nMax = VScrollMax;
    si.nPos = m_VScrollPos;
    si.nPage = m_VPageSize;

    SetScrollInfo (SB_VERT, &si, TRUE);

}

void CFrontCadView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//------------------------------------------------
	// OnHScroll
	//		This is the function that is called when
	// the user presses the horizonalscroll bar in
	// the view.
	//
	// parameters:
	//		nSBCode.....part of the scrollbar clicked
	//		nPos........Position of the scrollbar
	//		pScrollBar..pointer to the scrollbar object
	//------------------------------------------------
	int Delta = 0;

	switch(nSBCode)
	{
		case SB_LINELEFT:
			Delta = -1;
			break;
		case SB_PAGELEFT:
			Delta = -50;
			break;
		case SB_THUMBTRACK:
			Delta = nPos - m_HScrollPos;
			break;
		case SB_LINERIGHT:
			Delta = 1;
			break;
		case SB_PAGERIGHT:
			Delta = 50;
			break;
	}
    int ScrollPos = m_HScrollPos + Delta;
    int MaxPos = m_DocSize.cx - m_HPageSize;
    if (ScrollPos < 0)
        Delta = -m_VScrollPos;
    else if (ScrollPos > MaxPos)
        Delta = MaxPos - m_HScrollPos;

	if(Delta)
	{
        m_HScrollPos += Delta;
        SetScrollPos (SB_HORZ, m_HScrollPos, TRUE);
	}

    UpdateRulerInfo(RW_HSCROLL, CPoint(m_HScrollPos,m_VScrollPos));
	CView::OnHScroll(nSBCode, nPos, pScrollBar);
	Invalidate(FALSE);
}

void CFrontCadView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	//------------------------------------------------
	// OnVScroll
	//		This is the function that is called when
	// the user presses the VerticalScroll bar in
	// the view.
	//
	// parameters:
	//		nSBCode.....part of the scrollbar clicked
	//		nPos........Position of the scrollbar
	//		pScrollBar..pointer to the scrollbar object
	//------------------------------------------------
	int Delta=0;
	switch(nSBCode)
	{
		case SB_LINEUP:
			Delta = -1;
			break;
		case SB_PAGEUP:
			Delta = -50;
			break;
		case SB_THUMBTRACK:
			Delta = nPos - m_VScrollPos;
			break;
		case SB_LINEDOWN:
			Delta = 1;
			break;
		case SB_PAGEDOWN:
			Delta = 50;
			break;
		default:
			return;
	}
    int ScrollPos = m_VScrollPos + Delta;
    int MaxPos = m_DocSize.cy - m_VPageSize;
    if (ScrollPos < 0)
        Delta = -m_VScrollPos;
    else if (ScrollPos > MaxPos)
        Delta = MaxPos - m_VScrollPos;

	if(Delta)
	{
        m_VScrollPos += Delta;
        SetScrollPos (SB_VERT, m_VScrollPos, TRUE);
	}
    UpdateRulerInfo(RW_VSCROLL, CPoint(m_HScrollPos,m_VScrollPos));

	CView::OnVScroll(nSBCode, nPos, pScrollBar);
	Invalidate(FALSE);
}

void CFrontCadView::OnToolbarZoomout()
{
	//--------------------------------------------
	// OnToolbarZoomout
	//		This function is called when the user
	// clicks the ZoomOut command
	//--------------------------------------------
	m_ZoomLevel++;
	if(m_ZoomLevel >= MAX_ZOOM)
		m_ZoomLevel = MAX_ZOOM-1;
	this->m_fZoomFactor = (float)(ZF[m_ZoomLevel] * 10.0);
	UpdateRulerInfo(RW_ZOOM, CPoint(m_HScrollPos,m_VScrollPos), SnapToScreen(m_SnapPos));
	UpdateScrollbarInfo();
	CFrontCadDoc *pDoc = GetDocument();
	Invalidate();
}

void CFrontCadView::OnUpdateToolbarZoomout(CCmdUI* pCmdUI)
{
	//--------------------------------------------
	// OnUpdateToolbarZoomout
	//		This function is called to see if the
	// Zoomout command should be enabled or not.
	//--------------------------------------------
	if(m_ZoomLevel >= (MAX_ZOOM-1))
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);
}

void CFrontCadView::OnToolbarZoomin()
{
	//--------------------------------------------
	// OnToolbarZoomin
	//		This function is called when the useer
	// user presses the ZoomIn button.
	//--------------------------------------------
	m_ZoomLevel--;
	if(m_ZoomLevel < 0)
		m_ZoomLevel = 0;
	this->m_fZoomFactor = (float)(ZF[m_ZoomLevel] * 10.0);
	UpdateRulerInfo(RW_ZOOM,CPoint(m_HScrollPos,m_VScrollPos), SnapToScreen(m_SnapPos));
	UpdateScrollbarInfo();
	CFrontCadDoc *pDoc = GetDocument();
	Invalidate();
}

void CFrontCadView::OnUpdateToolbarZoomin(CCmdUI* pCmdUI)
{
	//--------------------------------------------
	// OnUpdateToolbarZoomIn
	//		This function is called to see if the
	// Zoomin command should be enabled or not.
	//--------------------------------------------
	if(m_ZoomLevel <= 0)
		pCmdUI->Enable(FALSE);
	else
		pCmdUI->Enable(TRUE);

}

void CFrontCadView::OnToolbarToggleruler()
{
	m_bShowRulers ^= 1;
	m_pParent->ShowRulers(this->m_bShowRulers);
}

//----------------------------------------------
// Drawing Functions
//----------------------------------------------

void CFrontCadView::OnToolbarSelect()
{
	//--------------------------------
	// OnToolbarSelect
	//		This function put us into
	// the Select Mode
	//--------------------------------
	m_Drawmode = DrawMode::SELECT;
	theApp.GetMainFrame()->UpdateStatusBar("Select Object");
}


void CFrontCadView::OnButtonDimension()
{
	CUtilView *pUV = GetUtilityView();
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	//------------------------------------------------
	// Line attributes
	//------------------------------------------------
	pUV->m_Edit_LineThickness.SetValue(pA->m_DimAttrib.m_LineWidth);
	pUV->m_Static_LineColor.SetColor(pA->m_DimAttrib.m_Color);
	//------------------------------------------------
	// Text Attributes
	//-------------------------------------------------
	pUV->m_Edit_TextAngle.SetValue(pA->m_DimAttrib.m_TextAtrib.m_Angle);
	pUV->m_Edit_FontHeight.SetValue(pA->m_DimAttrib.m_TextAtrib.m_FontHeight);
	pUV->m_Edit_FontWidth.SetValue(pA->m_DimAttrib.m_TextAtrib.m_FontWidth);
	pUV->m_Check_TransparentFont.SetCheck(pA->m_DimAttrib.m_TextAtrib.m_Transparent, 0);
	pUV->m_Static_TextColor.SetColor(pA->m_DimAttrib.m_TextAtrib.m_Color);
	pUV->m_Static_BkGrndColor.SetColor(pA->m_DimAttrib.m_TextAtrib.m_BkColor);
	pUV->m_Button_Font.SetWindowText(pA->m_DimAttrib.m_TextAtrib.m_pFontName);
	pUV->m_Combo_FontWeight.SetFontWeight(pA->m_DimAttrib.m_TextAtrib.m_Weight);

	m_Drawmode = DrawMode::DIMENSION;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;

	pUV->ShowHide(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Dimension:Place First Point");
}


void CFrontCadView::OnButtonOrigin()
{
	CUtilView *pUV = GetUtilityView();
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	m_Drawmode = DrawMode::ORIGIN;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	pUV->m_Edit_LineThickness.SetValue(pA->m_OriginAttrib.m_LineWidth);
	pUV->m_Static_LineColor.SetColor(pA->m_OriginAttrib.m_Color);
	pUV->ShowHide(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Origin:Place Location of Point");
}

void CFrontCadView::OnToolbarRect()
{
	//----------------------------------------
	// OnToolbarRect
	//		This function put the program into
	// the Draw rectangle mode
	//----------------------------------------
	CUtilView *pUV = GetUtilityView();
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	m_Drawmode = DrawMode::RECTANGLE;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	pUV->m_Edit_LineThickness.SetValue(pA->m_RectAttributes.m_LineWidth);
	pUV->m_Static_FillColor.SetColor(pA->m_RectAttributes.m_FillColor);
	pUV->m_Static_LineColor.SetColor(pA->m_RectAttributes.m_LineColor);
	pUV->m_Check_TransparentFill.SetCheck(pA->m_RectAttributes.m_bTransparentFill);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Rectangle:Place First Corner");
}

void CFrontCadView::OnToolbarBitmap()
{
	//----------------------------------------
	// OnToolbarBitmap
	//		This function is called when the
	// Draw Bitmap button is pressed and puts
	// the program into the Draw Bitmap mode.
	//----------------------------------------
	if(this->m_pTempCadBitmap) delete m_pTempCadBitmap;
	m_Drawmode = DrawMode::BITMAPIMAGE;
	CFileDialog dlg(TRUE);
	theApp.GetMainFrame()->UpdateStatusBar("Bitmap:Choose Bitmap File");

	dlg.DoModal();
	CString path = dlg.GetPathName();
	m_pTempCadBitmap = new CCadBitmap;
	m_pTempCadBitmap->LoadBitmapImage((char *)path.GetString());
	theApp.GetMainFrame()->UpdateStatusBar("Bitmap:Place Upper Left Corner");
}

void CFrontCadView::OnButtonArrowobj()
{
	// ------------------------------------------------------
	// OnButtonArrowobj
	// This function is called when we click on the Arrow
	// object in the tool bar.  We will put FrontCAD into
	// the mode fro drawing an arrow
	//-------------------------------------------------------
	m_Drawmode = DrawMode::ARROW;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	CUtilView *pUV = GetUtilityView();
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	//------------------------------------------------
	pUV->m_Edit_X3.SetValue(pA->m_ArrowAttrib.m_Len);
	pUV->m_Edit_Y3.SetValue(pA->m_ArrowAttrib.m_ArrowWidth);
	pUV->m_Static_FillColor.SetColor(pA->m_ArrowAttrib.m_FillColor);
	pUV->m_Static_LineColor.SetColor(pA->m_ArrowAttrib.m_LineColor);
	pUV->m_Check_TransparentFill.SetCheck(pA->m_ArrowAttrib.m_bTransparent, 0);
	pUV->m_Edit_LineThickness.SetValue(pA->m_ArrowAttrib.m_LineWidth);
	//------------------------------------------------
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Arrow:Place Location of Point");
}

void CFrontCadView::OnToolbarLine()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	m_Drawmode = DrawMode::LINE;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	CUtilView *pUV = GetUtilityView();
	pUV->m_Edit_LineThickness.SetValue(pA->m_LineAttrib.m_LineWidth);
	pUV->m_Static_LineColor.SetColor(pA->m_LineAttrib.m_LineColor );
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Line:Place First Point");
}

void CFrontCadView::OnToolbarEllipse()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	m_Drawmode = DrawMode::ELIPSE;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	CUtilView *pUV = GetUtilityView();
	pUV->m_Edit_LineThickness.SetValue(pA->m_EllipseAttributes.m_LineWidth);
	pUV->m_Static_FillColor.SetColor(pA->m_EllipseAttributes.m_FillColor);
	pUV->m_Static_LineColor.SetColor(pA->m_EllipseAttributes.m_LineColor);
	pUV->m_Check_TransparentFill.SetCheck(pA->m_EllipseAttributes.m_Transparent);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Ellipse:Place First Corner");
}


void CFrontCadView::OnToolbarCircle()
{
	CFrontCadApp* pA = (CFrontCadApp*)AfxGetApp();
	m_Drawmode = DrawMode::CIRCLE;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	CUtilView* pUV = GetUtilityView();
	pUV->m_Edit_LineThickness.SetValue(pA->m_CircleAttributs.m_LineWidth);
	pUV->m_Static_FillColor.SetColor(pA->m_CircleAttributs.m_FillColor);
	pUV->m_Static_LineColor.SetColor(pA->m_CircleAttributs.m_LineColor);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	pA->GetMainFrame()->UpdateStatusBar("Circle:Place Center Point");
}

void CFrontCadView::OnToolbarRndrect()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	CUtilView *pUV = GetUtilityView();
	pUV->m_Edit_X3.SetValue(pA->m_RndRectAttributes.m_P3.x);
	pUV->m_Edit_Y3.SetValue(pA->m_RndRectAttributes.m_P3.y);
	pUV->m_Edit_LineThickness.SetValue(pA->m_RndRectAttributes.m_LineWidth);
	pUV->m_Static_FillColor.SetColor(pA->m_RndRectAttributes.m_FillColor);
	pUV->m_Static_LineColor.SetColor(pA->m_RndRectAttributes.m_LineColor);
	pUV->m_Check_TransparentFill.SetCheck(pA->m_RndRectAttributes.m_bTransparent);
	m_Drawmode = DrawMode::RNDRECT;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Round Rect:Place First Corner");
}

#define ID_CM_FORWARD				3100
#define ID_CM_BACKWARD				3101
#define ID_CM_DELETE				3102
#define ID_CM_MOVE					3103
#define ID_CM_RESTOREASPECTRATIO	3104
#define ID_CM_ALIGHN_DIM_TO_HOLE	3105
#define ID_CM_REPEAT_SELECTED		3106
#define ID_CM_DESELECT				3107
#define ID_CM_DESELECT_ALL			3108

void CFrontCadView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CFrontCadDoc *pDoc = GetDocument();
	CMenu ConTexMenu;
	int id;
	m_MousePos = point;
	ScreenToClient(&m_MousePos);
	m_MousePos = CorrectMousePosition(m_MousePos);
	CCadObject *pObj = GetTopSelection();;
	ConTexMenu.CreatePopupMenu();
	ConTexMenu.AppendMenu(MF_STRING,ID_CM_FORWARD,"Send Obj Forward");
	ConTexMenu.AppendMenu(MF_STRING,ID_CM_BACKWARD,"Send Obj Back");
	ConTexMenu.AppendMenu(MF_STRING,ID_CM_DELETE,"Delete");
	ConTexMenu.AppendMenu(MF_SEPARATOR);
	ConTexMenu.AppendMenu(MF_STRING,ID_CM_MOVE,"Move");
	if(pObj)	//is anything slected?
	{
		ConTexMenu.EnableMenuItem(ID_CM_FORWARD,MF_ENABLED);
		ConTexMenu.EnableMenuItem(ID_CM_BACKWARD,MF_ENABLED);
		ConTexMenu.EnableMenuItem(ID_CM_DELETE,MF_ENABLED);
		ConTexMenu.EnableMenuItem(ID_CM_MOVE,MF_ENABLED);
		if(pObj->GetType() == OBJECT_TYPE_BITMAP)
		{
			ConTexMenu.AppendMenu(MF_STRING,ID_CM_RESTOREASPECTRATIO,"Restore Aspect Ratio");
			ConTexMenu.EnableMenuItem(ID_CM_RESTOREASPECTRATIO,MF_ENABLED);
		}
		if (pObj->GetType() == OBJECT_TYPE_DIMENSION) 
		{
			ConTexMenu.AppendMenuA(MF_STRING, ID_CM_ALIGHN_DIM_TO_HOLE, "Align Dim To Hole or Part");
			ConTexMenu.EnableMenuItem(ID_CM_ALIGHN_DIM_TO_HOLE, MF_ENABLED);
		}
		ConTexMenu.AppendMenuA(MF_STRING, ID_CM_REPEAT_SELECTED, "Place Array");
		ConTexMenu.EnableMenuItem(ID_CM_REPEAT_SELECTED, MF_ENABLED);
	}
	else
	{
		ConTexMenu.EnableMenuItem(ID_CM_FORWARD,MF_GRAYED);
		ConTexMenu.EnableMenuItem(ID_CM_BACKWARD,MF_GRAYED);
		ConTexMenu.EnableMenuItem(ID_CM_DELETE,MF_GRAYED);
		ConTexMenu.EnableMenuItem(ID_CM_MOVE,MF_GRAYED);
	}
	if (pObj)
	{
		ConTexMenu.AppendMenu(MF_SEPARATOR);
		if (pDoc->CheckSelected(m_SnapPos,0,0, CADDRAWUBG_CHECKSEL_FLAG_SEL) > 0 )
		{
			ConTexMenu.AppendMenu(MF_STRING, ID_CM_DESELECT, "Deselect Object");
			ConTexMenu.EnableMenuItem(ID_CM_DESELECT, MF_ENABLED);
		}
		ConTexMenu.AppendMenu(MF_STRING, ID_CM_DESELECT_ALL, "Deselect All");
		ConTexMenu.EnableMenuItem(ID_CM_DESELECT_ALL, MF_ENABLED);
	}

	id = ConTexMenu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,point.x,point.y, this);
	ConTexMenu.DestroyMenu();
	switch(id)
	{
		case ID_CM_FORWARD:
			pDoc->RemoveObject(pObj);
			pDoc->AddObject(pObj);
			Invalidate();
			break;
		case ID_CM_BACKWARD:
			pDoc->RemoveObject(pObj);
			pDoc->InsertObject(pObj);
			Invalidate();
			break;
		case ID_CM_DELETE:
			RemoveObject(pObj);
			pDoc->RemoveObject(pObj);
			delete pObj;
			Invalidate();
			break;
		case ID_CM_MOVE:
			m_Drawmode = DrawMode::MOVE;
			m_DrawState = DRAWSTATE_GETREFEREMCE;
			break;
		case ID_CM_RESTOREASPECTRATIO:
			((CCadBitmap *)pObj)->RestoreAspectRatio();
			break;
		case ID_CM_ALIGHN_DIM_TO_HOLE:
			m_Drawmode = DrawMode::ALIGN_DIM_TO_HOLE;
			m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
			theApp.GetMainFrame()->UpdateStatusBar("Align Dimension:Select Object To Align to");
			break;
		case ID_CM_REPEAT_SELECTED:
			{
				CRepeatDlg dlg;
				int dlgID;
				dlg.m_Xinc = 0;
				dlg.m_Yinc = 0;
				dlg.m_RepeatCountX = 0;
				dlg.m_RepeatCountY = 0;
				dlgID = dlg.DoModal();
				if (IDOK == dlgID)
				{
					int i, j;
					int flag = 1;
					CCadObject *pNewObj;
					for (j = 0; j < dlg.m_RepeatCountY; ++j)
					{
						for (i = 0; i < dlg.m_RepeatCountX; ++i)
						{
							if (flag)	//we need to skip creating the first object
							{
								flag = 0;
								i++;
							}
							pNewObj = pObj->Copy();
							pNewObj->SetP1(CPoint(pObj->GetP1() + CSize(dlg.m_Xinc * i, dlg.m_Yinc * j)));
							pDoc->AddObject(pNewObj);
						}
					}
				}
			}
			break;
		case ID_CM_DESELECT:
			{
				int c;
				CCadObject **ppObList = new CCadObject*[8];
				c = pDoc->CheckSelected(m_SnapPos, ppObList, 8, CADDRAWUBG_CHECKSEL_FLAG_SEL);
				if (c > 1)
				{
					CMenu SelMenu;
					SelMenu.CreatePopupMenu();
					int i;
					char *s = new char[256];
					for (i = 0; i < c; ++i)
					{
						sprintf_s(s, 256, "%s:(%d,%d)", ppObList[i]->GetTypeString(), ppObList[i]->GetP1().x, ppObList[i]->GetP1().y);
						SelMenu.AppendMenu(MF_STRING, ID_OBJECTSEL + i, s);
						SelMenu.EnableMenuItem(ID_OBJECTSEL + i, MF_ENABLED);
					}
					int id = SelMenu.TrackPopupMenu(TPM_RETURNCMD | TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, point.x, point.y, this);
					if (id > 0)
					{
						CCadObject *pObj = ppObList[id - ID_OBJECTSEL];
						pObj->SetSelected(0);
						RemoveObject(pObj);
					}
					delete[] s;
				}
				else if(c == 1)
				{
					ppObList[0]->SetSelected(0);
					RemoveObject(ppObList[0]);
				}
				Invalidate();
			}
			break;
		case ID_CM_DESELECT_ALL:
			ClearSelList();
			break;
	}
}

void CFrontCadView::UpdateRulerInfo(int nMessage, CPoint ScrollPos, CPoint Pos)
{
    if (!m_pParent)
        return;

 //   if (m_fZoomFactor < ZOOM_NORMAL) {
 //       m_bShowRulers = FALSE;
 //       m_pParent->ShowRulers(FALSE);
 //   }

    stRULER_INFO pRulerInfo;
    pRulerInfo.uMessage    = nMessage;
    pRulerInfo.ScrollPos   = ScrollPos;
    pRulerInfo.Pos         = Pos;
    pRulerInfo.DocSize     = m_DocSize;
    pRulerInfo.fZoomFactor = m_fZoomFactor;

    m_pParent->UpdateRulersInfo(pRulerInfo);

}

void CFrontCadView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
//	SetScrollSizes(MM_TEXT,
//                   CSize(int(m_DocSize.cx*m_fZoomFactor),
//                         int(m_DocSize.cy*m_fZoomFactor)));
    UpdateRulerInfo(RW_POSITION, CPoint(m_HScrollPos,m_VScrollPos));
    Invalidate();

}

CUtilView * CFrontCadView::GetUtilityView()
{
	return this->m_pParent->GetUtilityView();
}

void CFrontCadView::OnToolbarGridonoff()
{
	m_GridOn ^= 1;
	Invalidate();
}

void CFrontCadView::OnToolbarGridsettings()
{
	CDialogGridSettings dlg;
	dlg.m_Grid = this->m_Grid;
	dlg.m_Snap = this->m_SnapGrid;
	dlg.m_Color = this->m_GridColor;
	if(dlg.DoModal() == IDOK)
	{
		m_Grid = dlg.m_Grid;
		m_SnapGrid = dlg.m_Snap;
		m_GridColor = dlg.m_Color;
	}
}

void CFrontCadView::OnToolbarLibpart()
{
	m_Drawmode = DrawMode::LIBPART;
	theApp.GetMainFrame()->UpdateStatusBar("Library Part:Place");
}

void CFrontCadView::OnToolbarPolygon()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	this->m_Drawmode = DrawMode::POLYGON;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	CUtilView *pUV = GetUtilityView();
	pUV->m_Edit_LineThickness.SetValue(pA->m_PolyAttributes.m_LineWidth);
	pUV->m_Static_LineColor.SetColor(pA->m_PolyAttributes.m_LineColor);
	pUV->m_Static_FillColor.SetColor(pA->m_PolyAttributes.m_FillColor);
	pUV->m_Check_TransparentFill.SetCheck(pA->m_PolyAttributes.m_Transparent, 0);	
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Polygon:Place First Point");
}

void CFrontCadView::OnToolbarScalewiz()
{
	CFrontCadApp *pA = &theApp;
	CScaleWizDialog dlg;
	int Id;

	dlg.m_atrb.m_ArcEnd = pA->m_SCALEWIZattributes.m_ArcEnd;
	dlg.m_atrb.m_ArcLineWidth = pA->m_SCALEWIZattributes.m_ArcLineWidth;
	dlg.m_atrb.m_ArcRadius = pA->m_SCALEWIZattributes.m_ArcRadius;
	dlg.m_atrb.m_ArcStart = pA->m_SCALEWIZattributes.m_ArcStart;
	dlg.m_atrb.m_ArcColor = pA->m_SCALEWIZattributes.m_ArcColor;
	dlg.m_atrb.m_DivisionLineLegnth = pA->m_SCALEWIZattributes.m_DivisionLineLegnth;
	dlg.m_atrb.m_DivisionLineWidth = pA->m_SCALEWIZattributes.m_DivisionLineWidth;
	dlg.m_atrb.m_Divisions = pA->m_SCALEWIZattributes.m_Divisions;
	dlg.m_atrb.m_DivLineColor = pA->m_SCALEWIZattributes.m_DivLineColor;
	dlg.m_atrb.m_SubdivisionLengnth = pA->m_SCALEWIZattributes.m_SubdivisionLengnth;
	dlg.m_atrb.m_SubDivisionLineWidth = pA->m_SCALEWIZattributes.m_SubDivisionLineWidth;
	dlg.m_atrb.m_SubDivisions = pA->m_SCALEWIZattributes.m_SubDivisions;
	dlg.m_atrb.m_SubDivColor = pA->m_SCALEWIZattributes.m_SubDivColor;
	dlg.m_atrb.m_FlatDist = pA->m_SCALEWIZattributes.m_FlatDist;
	dlg.m_atrb.m_HoleSize = pA->m_SCALEWIZattributes.m_HoleSize;
	dlg.m_atrb.m_HoleType = pA->m_SCALEWIZattributes.m_HoleType;
	dlg.m_atrb.m_FontSize = pA->m_SCALEWIZattributes.m_FontSize;
	dlg.m_atrb.m_FontWeight = pA->m_SCALEWIZattributes.m_FontWeight;
	dlg.m_atrb.m_DistToTick = pA->m_SCALEWIZattributes.m_DistToTick;
	for(int i=0;i< pA->m_SCALEWIZattributes.m_Divisions+1;++i)
		strcpy_s(dlg.m_atrb.m_pLabels[i], SCALE_LABELS_STRING_SIZE,pA->m_SCALEWIZattributes.m_pLabels[i]);
	strcpy_s(dlg.m_atrb.m_pFont, LF_FACESIZE,pA->m_SCALEWIZattributes.m_pFont);
	dlg.m_atrb.m_BkColor = pA->m_SCALEWIZattributes.m_BkColor;
	dlg.m_atrb.m_TextColor = pA->m_SCALEWIZattributes.m_TextColor;
	Id = dlg.DoModal();
	if(IDOK == Id)
	{
		pA->m_SCALEWIZattributes.m_ArcEnd = dlg.m_atrb.m_ArcEnd;
		pA->m_SCALEWIZattributes.m_ArcLineWidth = dlg.m_atrb.m_ArcLineWidth;
		pA->m_SCALEWIZattributes.m_ArcRadius = dlg.m_atrb.m_ArcRadius;
		pA->m_SCALEWIZattributes.m_ArcStart = dlg.m_atrb.m_ArcStart;
		pA->m_SCALEWIZattributes.m_ArcColor = dlg.m_atrb.m_ArcColor;
		pA->m_SCALEWIZattributes.m_DivisionLineLegnth = dlg.m_atrb.m_DivisionLineLegnth;
		pA->m_SCALEWIZattributes.m_DivisionLineWidth = dlg.m_atrb.m_DivisionLineWidth;
		pA->m_SCALEWIZattributes.m_Divisions = dlg.m_atrb.m_Divisions;
		pA->m_SCALEWIZattributes.m_DivLineColor = dlg.m_atrb.m_DivLineColor;
		pA->m_SCALEWIZattributes.m_SubdivisionLengnth = dlg.m_atrb.m_SubdivisionLengnth;
		pA->m_SCALEWIZattributes.m_SubDivisionLineWidth = dlg.m_atrb.m_SubDivisionLineWidth;
		pA->m_SCALEWIZattributes.m_SubDivisions = dlg.m_atrb.m_SubDivisions;
		pA->m_SCALEWIZattributes.m_SubDivColor = dlg.m_atrb.m_SubDivColor;
		pA->m_SCALEWIZattributes.m_FlatDist = dlg.m_atrb.m_FlatDist;
		pA->m_SCALEWIZattributes.m_HoleSize = dlg.m_atrb.m_HoleSize;
		pA->m_SCALEWIZattributes.m_HoleType = dlg.m_atrb.m_HoleType;
		pA->m_SCALEWIZattributes.m_DistToTick = dlg.m_atrb.m_DistToTick;
		for(int i=0;i< pA->m_SCALEWIZattributes.m_Divisions+1;++i)
			strcpy_s(pA->m_SCALEWIZattributes.m_pLabels[i], SCALE_LABELS_STRING_SIZE,dlg.m_atrb.m_pLabels[i]);
		pA->m_SCALEWIZattributes.m_FontSize = dlg.m_atrb.m_FontSize;
		pA->m_SCALEWIZattributes.m_BkColor = dlg.m_atrb.m_BkColor;
		pA->m_SCALEWIZattributes.m_TextColor = dlg.m_atrb.m_TextColor;
	}
}

void CFrontCadView::DrawCrosshairs(CDC *pDC,CRect *pRect,CPoint pos)
{
	CPen pen,*pOldPen;
	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	pOldPen = pDC->SelectObject(&pen);
	int w,h;
	pos -= CPoint(m_HScrollPos,m_VScrollPos);
	w = pRect->Width();
	h = pRect->Height();
	pDC->MoveTo(0,pos.y);
	pDC->LineTo(w,pos.y);
	pDC->MoveTo(pos.x,0);
	pDC->LineTo(pos.x,h);
	pDC->SelectObject(pOldPen);
}

void CFrontCadView::OnToolbarArcCenter()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	m_Drawmode = DrawMode::ARC_CENTER;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	CUtilView *pUV = GetUtilityView();
	pUV->m_Edit_LineThickness.SetValue(pA->m_ArcAttributes.m_LineWidth);
	pUV->m_Static_LineColor.SetColor(pA->m_ArcAttributes.m_LineColor);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Arc:Place Center Point");

}

void CFrontCadView::OnToolbarArc()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	m_Drawmode = DrawMode::ARC;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	CUtilView *pUV = GetUtilityView();
	pUV->m_Edit_LineThickness.SetValue(pA->m_ArcAttributes.m_LineWidth);
	pUV->m_Static_LineColor.SetColor(pA->m_ArcAttributes.m_LineColor);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Arc:Place First Corner");
}

void CFrontCadView::OnToolbarHolernd()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	CUtilView *pUV = GetUtilityView();
	m_Drawmode = DrawMode::HOLE_ROUND;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	pUV->m_Static_LineColor.SetColor(pA->m_HoleRoundAttributes.m_LineColor);
	pUV->m_Edit_LineThickness.SetValue(pA->m_HoleRoundAttributes.m_LineWidth);
	pUV->m_Edit_HoleRadius.SetValue(pA->m_HoleRoundAttributes.m_Radius);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Round Hole:Place Center Point");
}

void CFrontCadView::OnToolbarRecthole()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	CUtilView *pUV = GetUtilityView();
	m_Drawmode = DrawMode::HOLE_RECT;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	pUV->m_Edit_X2.SetValue(pA->m_RectHoleAttributes.m_H);
	pUV->m_Edit_Y2.SetValue(pA->m_RectHoleAttributes.m_W);
	pUV->m_Edit_LineThickness.SetValue(pA->m_RectHoleAttributes.m_LineWidth);
	pUV->m_Static_LineColor.SetColor(pA->m_RectHoleAttributes.m_LineColor);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Rectangular Hole:Place Center Point");
}

void CFrontCadView::OnToolbarRnd1flat()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	CUtilView *pUV = GetUtilityView();
	m_Drawmode = DrawMode::HOLE_RND1F;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	pUV->m_Static_LineColor.SetColor(pA->m_HoleRnd1FlatAttributes.m_LineColor);
	pUV->m_Edit_LineThickness.SetValue(pA->m_HoleRnd1FlatAttributes.m_LineWidth);
	pUV->m_Edit_HoleRadius.SetValue(pA->m_HoleRnd1FlatAttributes.m_Radius);
	pUV->m_Edit_FlatToCenterDist.SetValue(pA->m_HoleRnd1FlatAttributes.m_FlatDist);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Round Hole one Flat Side:Place Center Point");
}

void CFrontCadView::OnToolbarTwoflats()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	CUtilView *pUV = GetUtilityView();
	m_Drawmode = DrawMode::HOLE_RND2F;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	pUV->m_Static_LineColor.SetColor(pA->m_HoleRnd2FlatAttributes.m_LineColor);
	pUV->m_Edit_LineThickness.SetValue(pA->m_HoleRnd2FlatAttributes.m_LineWidth);
	pUV->m_Edit_HoleRadius.SetValue(pA->m_HoleRnd2FlatAttributes.m_Radius);
	pUV->m_Edit_FlatToCenterDist.SetValue(pA->m_HoleRnd2FlatAttributes.m_FlatDist);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Round Hole two flat sides:Place Center Point");
}

void CFrontCadView::OnToolbarDrawtext()
{
	CFrontCadApp *pA = (CFrontCadApp *)AfxGetApp();
	CUtilView *pUV = GetUtilityView();
	m_Drawmode = DrawMode::TEXT;
	pUV->m_Edit_TextAngle.SetValue(pA->m_TextAttributes.m_Angle);
	pUV->m_Edit_FontHeight.SetValue(pA->m_TextAttributes.m_FontHeight);
	pUV->m_Edit_FontWidth.SetValue(pA->m_TextAttributes.m_FontWidth);
	pUV->m_Check_TransparentFont.SetCheck(pA->m_TextAttributes.m_Transparent,0);
	pUV->m_Static_TextColor.SetColor(pA->m_TextAttributes.m_Color);
	pUV->m_Static_BkGrndColor.SetColor(pA->m_TextAttributes.m_BkColor);
	pUV->m_Button_Font.SetWindowText(pA->m_TextAttributes.m_pFontName);
	pUV->m_Combo_FontWeight.SetFontWeight(pA->m_TextAttributes.m_Weight);
	pUV->ShowHide(m_Drawmode);
	pUV->SetUpText(m_Drawmode);
	theApp.GetMainFrame()->UpdateStatusBar("Text:Place Corner Point");
}

LRESULT CFrontCadView::OnUtilMessage(WPARAM wP, LPARAM lP)
{
	//----------------------------------------------
	// OnUtilMessage
	//		This function recieves a message from the
	//	controls in the Utility pane when the user updates
	//	one of the controls.  This is used to edit
	// an object in the drawing when that object
	// is selected
	//
	//	parameters:
	//		wP.....holds the sub message
	//				this identifies the object
	//				that the message came from
	//		lP.....resaerved
	//----------------------------------------------
	CFrontCadDoc *pDoc;

	switch(wP)
	{
		case UtilMsg::DEFAULT:
			MessageBox("Unknown Message","Debug");
			break;
		case UtilMsg::X1:
		case UtilMsg::Y1:
		case UtilMsg::X2:
		case UtilMsg::Y2:
		case UtilMsg::X3:
		case UtilMsg::Y3:
		case UtilMsg::_TEXT:
		case UtilMsg::FLATDIST:
		case UtilMsg::HOLERADIUS:
			if (GetTopSelection())
			{
				ChangeObject(this->GetUtilityView(), GetTopSelection());
				Invalidate();
			}
			break;
		case UtilMsg::LINEWIDTH:
		case UtilMsg::LINECOLOR:
		case UtilMsg::FILLCOLOR:
		case UtilMsg::FONTHEIGHT:
		case UtilMsg::FONTWIDTH:
		case UtilMsg::TEXTANGLE:
		case UtilMsg::TEXTCOLOR:
		case UtilMsg::FONT:
		case UtilMsg::TEXTBKCOLOR:
		case UtilMsg::FONTWEIGHT:
		case UtilMsg::_PRINTRECT:
			if(GetTopSelection())
			{
				ChangeObject(GetUtilityView(),GetTopSelection());
				Invalidate();
			}
			break;
		case UtilMsg::BACKGROUND:
			pDoc = GetDocument();
			pDoc->SetBkColor(lP);
			Invalidate();
			break;
		case UtilMsg::TEXTTRANSPARENT:
		case UtilMsg::TRANSPARENT_FILL:
			if(GetTopSelection())
			{
				ChangeObject(GetUtilityView(),GetTopSelection());
				Invalidate();
			}
			break;
	}
	this->SetForegroundWindow();
//	((CMainFrame *)GetParent())->FocusOnMainView();
//	SetFocus();
	return 0;
}

void CFrontCadView::FillInUtilView(CUtilView *pUV, CCadObject *pSel)
{
	switch(pSel->GetType())
	{
		case OBJECT_TYPE_NONE:
			break;
		case OBJECT_TYPE_LINE:
			pUV->m_Edit_X1.SetValue(((CCadLine *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadLine *)pSel)->GetP1().y);
			pUV->m_Edit_X2.SetValue(((CCadLine *)pSel)->GetP2().x);
			pUV->m_Edit_X2.SetValue(((CCadLine *)pSel)->GetP2().x);
			pUV->m_Edit_Y2.SetValue(((CCadLine *)pSel)->GetP2().y);
			pUV->m_Edit_LineThickness.SetValue(((CCadLine *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadLine *)pSel)->GetLineColor());
			break;
		case OBJECT_TYPE_RECT:
			pUV->m_Edit_X1.SetValue(((CCadRect *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadRect *)pSel)->GetP1().y);
			pUV->m_Edit_X2.SetValue(((CCadRect *)pSel)->GetP2().x);
			pUV->m_Edit_X2.SetValue(((CCadRect *)pSel)->GetP2().x);
			pUV->m_Edit_Y2.SetValue(((CCadRect *)pSel)->GetP2().y);
			pUV->m_Edit_LineThickness.SetValue(((CCadRect *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadRect *)pSel)->GetLineColor() );
			pUV->m_Static_FillColor.SetColor( ((CCadRect *)pSel)->GetFillColor() );
			break;
		case OBJECT_TYPE_ELLIPSE:
			pUV->m_Edit_X1.SetValue(((CCadElipse *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadElipse *)pSel)->GetP1().y);
			pUV->m_Edit_X2.SetValue(((CCadElipse *)pSel)->GetP2().x);
			pUV->m_Edit_X2.SetValue(((CCadElipse *)pSel)->GetP2().x);
			pUV->m_Edit_Y2.SetValue(((CCadElipse *)pSel)->GetP2().y);
			pUV->m_Edit_LineThickness.SetValue(((CCadElipse *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadElipse *)pSel)->GetLineColor() );
			pUV->m_Static_FillColor.SetColor( ((CCadElipse *)pSel)->GetFillColor() );
			break;
		case OBJECT_TYPE_RNDRECT:
			pUV->m_Edit_X1.SetValue(((CCadRoundRect *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadRoundRect *)pSel)->GetP1().y);
			pUV->m_Edit_X2.SetValue(((CCadRoundRect *)pSel)->GetP2().x);
			pUV->m_Edit_Y2.SetValue(((CCadRoundRect *)pSel)->GetP2().y);
			pUV->m_Edit_X3.SetValue(((CCadRoundRect *)pSel)->GetArc().x);
			pUV->m_Edit_Y3.SetValue(((CCadRoundRect *)pSel)->GetArc().y);
			pUV->m_Edit_LineThickness.SetValue(((CCadRoundRect *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadRoundRect *)pSel)->GetLineColor() );
			pUV->m_Static_FillColor.SetColor( ((CCadRoundRect *)pSel)->GetFillColor() );
			break;
		case OBJECT_TYPE_POLY:
			pUV->m_Edit_LineThickness.SetValue(((CCadPolygon *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadPolygon *)pSel)->GetLineColor() );
			pUV->m_Static_FillColor.SetColor(((CCadPolygon*)pSel)->GetFillColor());
			pUV->m_Check_TransparentFill.SetCheck(((CCadPolygon*)pSel)->GetTransparent(), 0);		
			break;
		case OBJECT_TYPE_LIBCOMP:
			break;
		case OBJECT_TYPE_HOLEROUND:
			pUV->m_Edit_X1.SetValue(((CCadHoleRound *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadHoleRound *)pSel)->GetP1().y);
			pUV->m_Edit_LineThickness.SetValue(((CCadHoleRound *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadHoleRound *)pSel)->GetLineColor() );
			pUV->m_Edit_HoleRadius.SetValue(((CCadHoleRound *)pSel)->GetRadius());
			break;
		case OBJECT_TYPE_HOLERECT:
			pUV->m_Edit_X1.SetValue(((CCadRectHole *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadRectHole *)pSel)->GetP1().y);
			pUV->m_Edit_X2.SetValue(((CCadRectHole *)pSel)->GetHieght());
			pUV->m_Edit_Y2.SetValue(((CCadRectHole *)pSel)->GetLineWidth());
			pUV->m_Edit_LineThickness.SetValue(((CCadRectHole *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadRectHole *)pSel)->GetLineColor() );
			break;
		case OBJECT_TYPE_HOLERND1FLAT:
			pUV->m_Edit_X1.SetValue(((CCadHoleRnd1Flat *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadHoleRnd1Flat *)pSel)->GetP1().y);
			pUV->m_Edit_LineThickness.SetValue(((CCadHoleRnd1Flat *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadHoleRnd1Flat *)pSel)->GetLineColor() );
			pUV->m_Edit_HoleRadius.SetValue(((CCadHoleRnd1Flat *)pSel)->GetRadius());
			pUV->m_Edit_FlatToCenterDist.SetValue(((CCadHoleRnd1Flat *)pSel)->GetFlatDist());
			break;
		case OBJECT_TYPE_HOLERND2FLAT:
			pUV->m_Edit_X1.SetValue(((CCadHoleRnd2Flat *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadHoleRnd2Flat *)pSel)->GetP1().y);
			pUV->m_Edit_LineThickness.SetValue(((CCadHoleRnd2Flat *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor( ((CCadHoleRnd2Flat *)pSel)->GetLineColor() );
			pUV->m_Edit_HoleRadius.SetValue(((CCadHoleRnd2Flat *)pSel)->GetRadius());
			pUV->m_Edit_FlatToCenterDist.SetValue(((CCadHoleRnd2Flat *)pSel)->GetFlatDist());
			break;
		case OBJECT_TYPE_TEXT:
			pUV->m_Edit_X1.SetValue(((CCadText *)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadText *)pSel)->GetP1().y);
			pUV->m_Edit_Text.SetWindowText(((CCadText *)pSel)->GetText());
			pUV->m_Button_Font.SetWindowText(((CCadText *)pSel)->GetFontName() );
			pUV->m_Static_BkGrndColor.SetColor(((CCadText *)pSel)->GetBkColor());
			pUV->m_Static_TextColor.SetColor(((CCadText *)pSel)->GetColor());
			pUV->m_Edit_FontHeight.SetValue(((CCadText *)pSel)->GetFontHeight());
			pUV->m_Edit_FontWidth.SetValue(((CCadText *)pSel)->GetFontWidth());
			pUV->m_Edit_TextAngle.SetValue(((CCadText *)pSel)->GetAngle());
			pUV->m_Check_TransparentFont.SetCheck(((CCadText *)pSel)->GetTransparent(),0);
			pUV->m_Combo_FontWeight.SetFontWeight(((CCadText *)pSel)->GetWeight());
			break;
		case OBJECT_TYPE_ARC:
			pUV->m_Edit_X1.SetValue(((CCadArc *)pSel)->GetP1().x);
			pUV->m_Edit_X2.SetValue(((CCadArc *)pSel)->GetP2().x);
			pUV->m_Edit_Y2.SetValue(((CCadArc *)pSel)->GetP2().y);
			pUV->m_Edit_Y1.SetValue(((CCadArc *)pSel)->GetP1().y);
			pUV->m_Edit_X3.SetValue(((CCadArc *)pSel)->GetStartAngle());
			pUV->m_Edit_Y3.SetValue(((CCadArc *)pSel)->GetEndAngle());
			pUV->m_Edit_LineThickness.SetValue(((CCadArc *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor(((CCadArc *)pSel)->GetLineColor());
			break;
		case OBJECT_TYPE_ARCCENTERED:
			pUV->m_Edit_X1.SetValue(((CCadArcCentered *)pSel)->GetP1().x);
			pUV->m_Edit_X2.SetValue(((CCadArcCentered *)pSel)->GetP2().x);
			pUV->m_Edit_Y2.SetValue(((CCadArcCentered *)pSel)->GetP2().y);
			pUV->m_Edit_Y1.SetValue(((CCadArcCentered *)pSel)->GetP1().y);
			pUV->m_Edit_X3.SetValue(((CCadArcCentered *)pSel)->GetStartAngle());
			pUV->m_Edit_Y3.SetValue(((CCadArcCentered *)pSel)->GetEndAngle());
			pUV->m_Edit_LineThickness.SetValue(((CCadArcCentered *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor(((CCadArcCentered *)pSel)->GetLineColor());
			break;
		case OBJECT_TYPE_ARROW:
			pUV->m_Edit_X1.SetValue(((CCadArrow *)pSel)->GetP1().x);
			pUV->m_Edit_X2.SetValue(((CCadArrow *)pSel)->GetP2().x);
			pUV->m_Edit_Y2.SetValue(((CCadArrow *)pSel)->GetP2().y);
			pUV->m_Edit_Y1.SetValue(((CCadArrow *)pSel)->GetP1().y);
			pUV->m_Edit_X3.SetValue(((CCadArrow *)pSel)->GetArrowLegnth());
			pUV->m_Edit_Y3.SetValue(((CCadArrow *)pSel)->GetArrowWidth());
			pUV->m_Static_FillColor.SetColor(((CCadArrow *)pSel)->GetFillColor() );
			pUV->m_Edit_LineThickness.SetValue(((CCadArrow*)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor(((CCadArrow*)pSel)->GetLineColor());
			break;
		case OBJECT_TYPE_ORIGIN:
			break;
		case OBJECT_TYPE_DIMENSION:
			pUV->m_Edit_LineThickness.SetValue(((CCadDimension *)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor(((CCadDimension *)pSel)->GetColor());

			pUV->m_Button_Font.SetWindowText( ( (CCadDimension *)pSel)->GetAttributes()->m_TextAtrib.m_pFontName );
			pUV->m_Static_BkGrndColor.SetColor(((CCadDimension *)pSel)->GetAttributes()->m_TextAtrib.m_BkColor);
			pUV->m_Static_TextColor.SetColor(((CCadDimension *)pSel)->GetAttributes()->m_TextAtrib.m_Color);
			pUV->m_Edit_FontHeight.SetValue(((CCadDimension *)pSel)->GetAttributes()->m_TextAtrib.m_FontHeight);
			pUV->m_Edit_FontWidth.SetValue(((CCadDimension *)pSel)->GetAttributes()->m_TextAtrib.m_FontWidth);
			pUV->m_Combo_FontWeight.SetFontWeight(((CCadDimension *)pSel)->GetAttributes()->m_TextAtrib.m_Weight);
			break;
		case OBJECT_TYPE_CIRCLE:
			pUV->m_Edit_X1.SetValue(((CCadCircle*)pSel)->GetP1().x);
			pUV->m_Edit_Y1.SetValue(((CCadCircle*)pSel)->GetP1().y);
			// Radius is entered into the X3 field in the utility view
			pUV->m_Edit_X3.SetValue(((CCadCircle*)pSel)->GetRadius());
			pUV->m_Edit_LineThickness.SetValue(((CCadCircle*)pSel)->GetLineWidth());
			pUV->m_Static_LineColor.SetColor(((CCadCircle*)pSel)->GetLineColor());
			pUV->m_Static_FillColor.SetColor(((CCadCircle*)pSel)->GetFillColor());
			pUV->m_Check_TransparentFill.SetCheck(((CCadCircle*)pSel)->GetTransparent());
			break;
	}
}


void CFrontCadView::ClearSelList()
{
	CCadObject *pO = GetTopSelection();
	CCadObject *next;
	while(pO)
	{
		next = pO->GetNextSelection();
		pO->SetSelected(0);
		RemoveObject(pO);
		pO = next;
	}
	m_SelectionCount = 0;

}

CCadObject *CFrontCadView::PopSelList(void)
{
	CCadObject *rObj;

	rObj = m_pSelObjList;
	if (rObj)
	{
		m_SelectionCount--;
		m_pSelObjList = rObj->GetNextSelection();
		rObj->SetNextSelection(0);
	}
	if (m_pSelObjList == NULL) m_pSelObjEnd = 0;
	return rObj;
}

void CFrontCadView::AddToSelList(CCadObject *pO)
{
	//----------------------------------------
	//	AddToSelList
	//		This function adds an object to the
	// selection list.
	//
	//	parameter:
	//		pO.....Object to add to list
	//---------------------------------------
	if(this->m_pSelObjList)
	{
		pO->SetNextSelection(m_pSelObjList);
		m_pSelObjList = pO;
	}
	else
	{
		m_pSelObjList = pO;
		m_pSelObjEnd = pO;
	}
	m_SelectionCount++;

}

CCadObject * CFrontCadView::GetTopSelection()
{
	//-------------------------------------------
	//	GetTopSelection
	//		Returns the object that is at the
	// top of the Selected Objects List
	//-------------------------------------------
	return m_pSelObjList;
}

void CFrontCadView::RemoveUnselected()
{
	//-------------------------------------
	// RemoveUnselected
	//remove all unselected objects
	//--------------------------------------
	CCadObject *pO,*pOr,*pPrev=0;

	pO = m_pSelObjList;
	while(pO)
	{
		if(!pO->GetSelected())
		{
			DecSelectionCount();

			pOr = pO;
			if(!pPrev)
			{
				m_pSelObjList = pO->GetNextSelection();
				pO = m_pSelObjList;
				pOr->SetNextSelection(0);
			}
			else
			{
				//pPrev will stay the same
				pO = pO->GetNextSelection();
				pPrev->SetNextSelection(pOr->GetNextSelection());
				pOr->SetNext(0);
			}
		}
		else
		{
			pPrev = pO;
			pO = pO->GetNextSelection();
		}

	}
	if(m_pSelObjList == 0) m_pSelObjEnd = 0;
}

void CFrontCadView::RemoveObject(CCadObject *pO)
{
	//----------------------------------------------
	//	RemoveObject
	// This fuction removes the specified object
	// from the selected list
	//		parameters:
	//			pO.....pointer to object to remove
	//----------------------------------------------
	CCadObject *pL,*pPrev=0;
	int loop=1;

	pL = m_pSelObjList;
	while(pL && loop)
	{
		if(pL == pO)
		{
			m_SelectionCount--;
			loop = 0;
			if(pPrev == 0)
			{
				m_pSelObjList = pL->GetNextSelection();
				pL->SetNextSelection(0);
			}
			else
			{
				pPrev->SetNextSelection(pL->GetNextSelection());
				pO->SetNextSelection(0);
			}
		}
		else
		{
			pPrev = pL;
			pL = pL->GetNextSelection();
		}

	}
	if(m_pSelObjList == 0) m_pSelObjEnd = 0;
}

void CFrontCadView::ChangeObject(CUtilView *pUV,CCadObject *pO)
{
	int Radius = 0;

	if(pO == NULL) return;
	CFrontCadDoc *pDoc = GetDocument();
	char *s = new char[256];
	if((m_Drawmode == DrawMode::SELECT) && pO)
	{
		pDoc->SetModifiedFlag(true);
		switch(pO->GetType())
		{
			case OBJECT_TYPE_NONE:
				break;
			case OBJECT_TYPE_LINE:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				pO->SetP2(CPoint(pUV->m_Edit_X2.GetValue(), pUV->m_Edit_Y2.GetValue()));
				((CCadLine *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadLine *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				Invalidate();
				break;
			case OBJECT_TYPE_RECT:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				pO->SetP2(CPoint(pUV->m_Edit_X2.GetValue(), pUV->m_Edit_Y2.GetValue()));
				((CCadRect *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadRect *)pO)->SetFillColor(pUV->m_Static_FillColor.GetColor());
				((CCadRect *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				Invalidate();
				break;
			case OBJECT_TYPE_ELLIPSE:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				pO->SetP2(CPoint(pUV->m_Edit_X2.GetValue(), pUV->m_Edit_Y2.GetValue()));
				((CCadElipse *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadElipse *)pO)->SetFillColor(pUV->m_Static_FillColor.GetColor());
				((CCadElipse *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				Invalidate();
				break;
			case OBJECT_TYPE_RNDRECT:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				pO->SetP2(CPoint(pUV->m_Edit_X2.GetValue(), pUV->m_Edit_Y2.GetValue()));
				((CCadRoundRect *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadRoundRect *)pO)->SetFillColor(pUV->m_Static_FillColor.GetColor());
				((CCadRoundRect *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadRoundRect *)pO)->SetArc(CPoint(pUV->m_Edit_X3.GetValue(),pUV->m_Edit_Y3.GetValue()));
				Invalidate();
				break;
			case OBJECT_TYPE_POLY:
				((CCadPolygon *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadPolygon *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadPolygon*)pO)->SetFillColor(pUV->m_Static_FillColor.GetColor());
				((CCadPolygon*)pO)->SetTransparent(pUV->m_Check_TransparentFill.GetCheck());
				Invalidate();
				break;
			case OBJECT_TYPE_LIBCOMP:
				break;
			case OBJECT_TYPE_HOLEROUND:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				((CCadHoleRound *)pO)->SetRadius(pUV->m_Edit_HoleRadius.GetValue());
				((CCadHoleRound *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadHoleRound *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				Invalidate();
				break;
			case OBJECT_TYPE_HOLERECT:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				((CCadRectHole *)pO)->SetHieghtWidth(pUV->m_Edit_X2.GetValue(),pUV->m_Edit_Y2.GetValue());
				((CCadRectHole *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadRectHole *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				Invalidate();
				break;
			case OBJECT_TYPE_HOLERND1FLAT:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				((CCadHoleRnd1Flat *)pO)->SetRadius(pUV->m_Edit_HoleRadius.GetValue());
				((CCadHoleRnd1Flat *)pO)->SetFlatDist(pUV->m_Edit_FlatToCenterDist.GetValue());
				((CCadHoleRnd1Flat *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadHoleRnd1Flat *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				Invalidate();
				break;
			case OBJECT_TYPE_HOLERND2FLAT:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				((CCadHoleRnd2Flat *)pO)->SetRadius(pUV->m_Edit_HoleRadius.GetValue());
				((CCadHoleRnd2Flat *)pO)->SetFlatDist(pUV->m_Edit_FlatToCenterDist.GetValue());
				((CCadHoleRnd2Flat *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadHoleRnd1Flat *)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				Invalidate();
				break;
			case OBJECT_TYPE_TEXT:
				pUV->m_Button_Font.GetWindowText(s,255);
				((CCadText *)pO)->SetFontName(s);
				((CCadText *)pO)->SetColor(pUV->m_Static_TextColor.GetColor());
				((CCadText *)pO)->SetBkColor(pUV->m_Static_BkGrndColor.GetColor());
				((CCadText *)pO)->SetWeight(pUV->m_Combo_FontWeight.GetFontWeight());
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				((CCadText *)pO)->SetFontHeight(pUV->m_Edit_FontHeight.GetValue());
				((CCadText *)pO)->SetFontWidth(pUV->m_Edit_FontWidth.GetValue());
				((CCadText *)pO)->SetTransparent(pUV->m_Check_TransparentFont.GetCheck());
				pUV->m_Edit_Text.GetWindowText(s,255);
				((CCadText *)pO)->SetText(s);
				((CCadText *)pO)->SetAngle(pUV->m_Edit_TextAngle.GetValue());
				Invalidate();
				break;
			case OBJECT_TYPE_ARC:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				pO->SetP2(CPoint(pUV->m_Edit_X2.GetValue(), pUV->m_Edit_Y2.GetValue()));
				((CCadArc*)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadArc*)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				break;
			case OBJECT_TYPE_ARCCENTERED:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				pO->SetP2(CPoint(pUV->m_Edit_X2.GetValue(), pUV->m_Edit_Y2.GetValue()));
				((CCadArcCentered*)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadArcCentered*)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				break;
			case OBJECT_TYPE_ARROW:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				pO->SetP2(CPoint(pUV->m_Edit_X2.GetValue(), pUV->m_Edit_Y2.GetValue()));
				((CCadArrow *)pO)->SetFillColor(pUV->m_Static_FillColor.GetColor());
				((CCadArrow*)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadArrow *)pO)->SetLegnth(pUV->m_Edit_X3.GetValue());
				((CCadArrow *)pO)->SetArrowWidth(pUV->m_Edit_Y3.GetValue());
				((CCadArrow*)pO)->SetTransparent(pUV->m_Check_TransparentFill.GetCheck());
				Invalidate();
				break;
			case OBJECT_TYPE_ORIGIN:
				((CCadOrigin *)pO)->SetColor(pUV->m_Static_LineColor.GetColor());
				((CCadOrigin *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				Invalidate();
				break;
			case OBJECT_TYPE_DIMENSION:
				((CCadDimension *)pO)->SetColor(pUV->m_Static_LineColor.GetColor());
				((CCadDimension *)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadDimension *)pO)->GetAttributes()->m_TextAtrib.m_FontHeight = pUV->m_Edit_FontHeight.GetValue();
				pUV->m_Button_Font.GetWindowTextA(s, 255);
				((CCadDimension*)pO)->GetAttributes()->m_TextAtrib.SetFontName(s); 
				((CCadDimension *)pO)->GetAttributes()->m_TextAtrib.m_Color = pUV->m_Static_TextColor.GetColor();
				((CCadDimension *)pO)->GetAttributes()->m_TextAtrib.m_BkColor = pUV->m_Static_BkGrndColor.GetColor();
				((CCadDimension*)pO)->GetAttributes()->m_TextAtrib.m_Transparent = pUV->m_Check_TransparentFont.GetCheck();
				((CCadDimension *)pO)->GetAttributes()->m_TextAtrib.m_FontWidth = pUV->m_Edit_FontWidth.GetValue();
				((CCadDimension *)pO)->GetAttributes()->m_TextAtrib.m_Weight = pUV->m_Combo_FontWeight.GetFontWeight();
				((CCadDimension *)pO)->UpdateText(GetOrigin());
				Invalidate();
				break;
			case OBJECT_TYPE_PRINTRECT:
				break;
			case OBJECT_TYPE_CIRCLE:
				pO->SetP1(CPoint(pUV->m_Edit_X1.GetValue(), pUV->m_Edit_Y1.GetValue()));
				((CCadCircle*)pO)->SetLineColor(pUV->m_Static_LineColor.GetColor());
				((CCadCircle*)pO)->SetFillColor(pUV->m_Static_FillColor.GetColor());
				((CCadCircle*)pO)->SetLineWidth(pUV->m_Edit_LineThickness.GetValue());
				((CCadCircle*)pO)->SetTransparent(pUV->m_Check_TransparentFill.GetCheck());
				// Radius is in the X3 field
				Radius = pUV->m_Edit_X3.GetValue();
				((CCadCircle*)pO)->SetRadius(Radius);
				Invalidate();
				break;
		}	//end of switch
	}//end of if
	delete[] s;
}	//change object

CLibFormView *CFrontCadView::GetLibFormView()
{
	return this->m_pParent->GetLibFormView();
}

void CFrontCadView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);

//	MessageBox("Lost Focus","DEBUG");
}

CPoint CFrontCadView::GetScrollPosition()
{
	return CPoint(0,0);
}


BOOL CFrontCadView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	dwStyle |=  WS_HSCROLL | WS_VSCROLL;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

LRESULT CFrontCadView::OnLibViewRequestReferencePoint(WPARAM wP, LPARAM lP)
{
	m_Drawmode = DrawMode::GETREF;
	theApp.GetMainFrame()->UpdateStatusBar("Define Reference Point");
	return 0;
}

void CFrontCadView::DrawGrid(CDC *pDC, ObjectMode mode,CRect rect)
{
	int i;
	if(this->m_GridOn)
	{
		double gd = m_Grid * ZF[m_ZoomLevel];
		CPen pen,*oldpen;
		pen.CreatePen(PS_SOLID,1,m_GridColor);
		oldpen = pDC->SelectObject(&pen);
		int H,W;
		W = rect.Width();
		H = rect.Height();
		int N = int(W/gd)+1;
		int offset = m_HScrollPos % int(gd);
		for(int i=0;i<N;++i)
		{
			pDC->MoveTo(CPoint(int((i+1)*gd)- offset,0));
			pDC->LineTo(CPoint(int((i+1)*gd)- offset,H-1));
		}
		N = int(H/gd)+1;
		offset = m_VScrollPos % int(gd);

		for(i=0;i<N;++i)
		{
			pDC->MoveTo(CPoint(0,int((i+1) * gd) - offset));
			pDC->LineTo(CPoint(W-1,int((i+1) * gd) - offset));
		}
		pDC->SelectObject(oldpen);
	}
}


void CFrontCadView::NextSnap(int mode, int SnapUnits)
{
	CSize rV;

	switch(mode)
	{
		case VK_LEFT:
			m_SnapPos.x -= SnapUnits;
			break;
		case VK_RIGHT:
			m_SnapPos.x += SnapUnits;
			break;
		case VK_UP:
			m_SnapPos.y -= SnapUnits;
			break;
		case VK_DOWN:
			m_SnapPos.y += SnapUnits;
			break;
	}
	m_MousePos = SnapToScreen(m_SnapPos);
}

CPoint CFrontCadView::Snap(CPoint nP, int SnapUnits)
{
	//-----------------------------------------------------
	// Snap
	// sets the position to nearest snap grid position
	//
	// Parameters:
	//	nP........Current corrected cursor position
	//	SnapUnits.Number of units for the snap grid
	//
	// Returns:
	//	Cursor position in real units for the display
	//-----------------------------------------------------
	int x, y;
	int HalfSnap;
	int off;

	x = int(nP.x * ZoomScaleDiv[m_ZoomLevel]);
	y = int(nP.y * ZoomScaleDiv[m_ZoomLevel]);
	if(!m_SnapOff)
	{
		HalfSnap = SnapUnits / 2;
		off = x % SnapUnits;
		if (off > HalfSnap)
			x += SnapUnits - off;
		else
			x -= off;

		off = y % SnapUnits;
		if (off > HalfSnap)
			y += SnapUnits - off;
		else
			y -= off;
	}
	return CPoint(x,y);
}

CPoint CFrontCadView::CorrectMousePosition(CPoint point)
{
	point += CPoint(this->m_HScrollPos,this->m_VScrollPos);
	return point;
}

void CFrontCadView::UpdateScrollbarInfo()
{
	CRect clientrect;
	GetClientRect(&clientrect);
	SCROLLINFO si;
	int cx = clientrect.Width();
	int cy = clientrect.Height();
	int HScrollMax = 0;

	memset(&si, 0, sizeof(SCROLLINFO));
	m_HScrollPos = 0;
	m_HPageSize = 0;
   if (cx < (m_DocSize.cx / ZoomScaleDiv[m_ZoomLevel])) {
        HScrollMax = (m_DocSize.cx / ZoomScaleDiv[m_ZoomLevel])- 1;
        m_HPageSize = cx;
        m_HScrollPos = min (m_HScrollPos, (m_DocSize.cx/ ZoomScaleDiv[m_ZoomLevel]) - m_HPageSize - 1);
    }

	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
    si.nMin = 0;
    si.nMax = HScrollMax;
    si.nPos = m_HScrollPos;
    si.nPage = m_HPageSize;
    SetScrollInfo (SB_HORZ, &si, TRUE);
	int VScrollMax=0;
	m_VScrollPos = 0;
	m_VPageSize = 0;

    if (cy < (m_DocSize.cy/ ZoomScaleDiv[m_ZoomLevel]) ) {
        VScrollMax = (m_DocSize.cy/ ZoomScaleDiv[m_ZoomLevel]) - 1;
        m_VPageSize = cy;
        m_VScrollPos = min (m_VScrollPos, (m_DocSize.cy/ ZoomScaleDiv[m_ZoomLevel]) - m_VPageSize - 1);
    }
    si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
    si.nMin = 0;
    si.nMax = VScrollMax;
    si.nPos = m_VScrollPos;
    si.nPage = m_VPageSize;

    SetScrollInfo (SB_VERT, &si, TRUE);
}

void CFrontCadView::OnEditCopy()
{
	m_Drawmode = DrawMode::COPY;
	m_DrawState = DRAWSTATE_GETREFEREMCE;
	theApp.GetMainFrame()->UpdateStatusBar("Define Reference Point");
}

void CFrontCadView::OnUpdateEditCopy(CCmdUI* pCmdUI)
{

}

void CFrontCadView::OnEditCut()
{
	m_Drawmode = DrawMode::CUT;
	m_DrawState = DRAWSTATE_GETREFEREMCE;
	theApp.GetMainFrame()->UpdateStatusBar("Define Reference Point");
}

void CFrontCadView::OnUpdateEditCut(CCmdUI* pCmdUI)
{

}

void CFrontCadView::OnEditPaste()
{
	m_Drawmode = DrawMode::PASTE;
	m_DrawState = DRAWSTATE_PLACE;
	theApp.GetMainFrame()->UpdateStatusBar("Select Paste Location");
}

void CFrontCadView::OnUpdateEditPaste(CCmdUI* pCmdUI)
{

}

void CFrontCadView::OnToolbarSelectregion()
{
	m_Drawmode = DrawMode::SELECTREGION;
	theApp.GetMainFrame()->UpdateStatusBar("Select Region:Select First Corner");
}

CPoint CFrontCadView::GetCursorPos()
{
	return m_MousePos;
}

BOOL CFrontCadView::SetCursorPos(CPoint pos)
{
	m_MousePos = pos;
	pos -= CPoint(this->m_HScrollPos,this->m_VScrollPos);
	ClientToScreen(&pos);
	return ::SetCursorPos(pos.x,pos.y);
}

BOOL CFrontCadView::DestroyWindow()
{
	return CView::DestroyWindow();
}


void CFrontCadView::OnFilePrinttoclipboard()
{
	CBitmap 	bitmap;
	CClientDC	dc(this);
	CDC 		memDC;
	CRect		rect;
	CPoint P1, P2;

	memDC.CreateCompatibleDC(&dc);

	if (m_nSelRegionLock == 0)
	{
		CCadPrintRect *pPRect;
		CFrontCadDoc *pDoc = GetDocument();
		pPRect = pDoc->GetPrintRect();
		if (pPRect)
		{
			rect = pPRect->GetRect();
		}
		else
		{
			rect.SetRect(CPoint(0, 0), CPoint(8500, 11000));
		}
		P1 = rect.TopLeft();
		P1 = CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]) * P1;
		P2 = rect.BottomRight();
		P2 = CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]) * P2;
	}
	else
	{
		P1 = CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]) * m_SelRegion_P1;
		P2 = CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]) * m_SelRegion_P2;
	}
	rect.SetRect((P1), (P2));
	rect.NormalizeRect();
	bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	PrintToDC(&memDC);
	this->OpenClipboard();
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, bitmap.GetSafeHandle());
	CloseClipboard();

	memDC.SelectObject(pOldBitmap);
	bitmap.Detach();
}

// //helper function for printing to clipboard
void CFrontCadView::PrintToDC(CDC * pDC)
{
	CFrontCadDoc* pDoc = GetDocument();
	CBrush br;
	CRect rect;
	CPoint P1, P2;
	CPoint Offset;

	if (m_nSelRegionLock == 0)
	{
		CCadPrintRect *pPRect;
		CFrontCadDoc *pDoc = GetDocument();
		pPRect = pDoc->GetPrintRect();
		if (pPRect)
		{
			rect = pPRect->GetRect();
		}
		else
		{
			rect.SetRect(CPoint(0, 0), CPoint(8500, 11000));
		}
		P1 = rect.TopLeft();
		P1 = CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]) * P1;
		P2 = rect.BottomRight();
		P2 = CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]) * P2;
	}
	else
	{
		P1 = CScale(ZF[m_ZoomLevel],ZF[m_ZoomLevel]) * m_SelRegion_P1;
		P2 = CScale(ZF[m_ZoomLevel],ZF[m_ZoomLevel]) * m_SelRegion_P2;
	}
	Offset = -P1;
	rect.SetRect(0, 0, P2.x - P1.x, P2.y - P1.y);
	br.CreateSolidBrush(pDoc->GetBkColor());
	pDC->FillRect(&rect, &br);
	//----------------------------------
	// Print to the clipboard
	//----------------------------------
	pDoc->Print(pDC, ObjectMode::Final, Offset, CScale(ZF[m_ZoomLevel], ZF[m_ZoomLevel]));

}

CPoint CFrontCadView::GetOrigin(void)
{
	CPoint rP = CPoint(0,0);
	CFrontCadDoc *pDoc = GetDocument();
	CCadObject *pOb;
	int loop = 1;

	pOb = pDoc->GetHead();
	while (pOb && loop)
	{
		if (pOb->GetType() == OBJECT_TYPE_ORIGIN)
		{
			loop = 0;
			rP = pOb->GetP1();
		}
		else
			pOb = pOb->GetNext();
	}
	return rP;
}

afx_msg LRESULT CFrontCadView::OnUpdatedimensions(WPARAM wParam, LPARAM lParam)
{
	CPoint p = GetOrigin();
	CFrontCadDoc *pDoc = GetDocument();
	CCadObject *pOb = pDoc->GetHead();
	CCadDimension *pDim;

	while (pOb)
	{
		if (pOb->GetType() == OBJECT_TYPE_DIMENSION)
		{
			pDim = (CCadDimension*)pOb;
			pDim->UpdateText(p);
		}
		pOb = pOb->GetNext();
	}
	return 0;
}


void CFrontCadView::OnViewRenderenable()
{
	CDialogRenderEnable dlg;

	dlg.DoModal();
}


CCadObject * CFrontCadView::FindHole(CCadObject * pHead,CPoint p)
{
	CCadObject *pRO = 0;

	while (pHead && !pRO)
	{
		if (pHead->CheckSelected(p) && IsHole(pHead))
		{
			pRO = pHead;
		}
		else
			pHead = pHead->GetNext();
	}
	return pRO;
}


int CFrontCadView::IsHole(CCadObject * pObj)
{
	int rV = 0;
	if ((pObj->GetType() == OBJECT_TYPE_HOLEROUND) ||
		(pObj->GetType() == OBJECT_TYPE_HOLERND1FLAT) ||
		(pObj->GetType() == OBJECT_TYPE_HOLERND2FLAT) ||
		(pObj->GetType() == OBJECT_TYPE_HOLERECT) )
		rV = 1;
	else if (pObj->GetType() == OBJECT_TYPE_LIBCOMP)
		rV = 2;
	return rV;
}


void CFrontCadView::OnAlignCentersvertical()
{
	CCadObject *pObj,*pObjRef;
	CPoint Ref,NewRef;
	pObjRef = PopSelList();	//this is the reference object
	pObj = PopSelList();
	Ref = pObjRef->GetCenter();
	Ref.x = 0;
	pObjRef->SetSelected(0);
	while (pObj)
	{
		NewRef = pObj->GetCenter();
		NewRef.x = 0;
		CSize v = NewRef - Ref;
		pObj->ChangeCenter(v);
		pObj->SetSelected(0);
		pObj = PopSelList();
	}
	Invalidate();
}


void CFrontCadView::OnAlignCentershorizontal()
{
	char *s = new char[256];
	CCadObject *pObj, *pObjRef;
	CPoint Ref, NewRef;
	pObjRef = PopSelList();	//this is the reference object
	pObj = PopSelList();
	Ref = pObjRef->GetCenter();
	Ref.y = 0;

	sprintf_s(s, 256,  "X=%d  Y=%d", Ref.x, Ref.y);
	((CFrontCadApp *)AfxGetApp())->WriteToLogFile(s);

	pObjRef->SetSelected(0);
	while (pObj)
	{
		NewRef = pObj->GetCenter();
		NewRef.y = 0;

		sprintf_s(s, 256, "X=%d  Y=%d", NewRef.x, NewRef.y);
		((CFrontCadApp *)AfxGetApp())->WriteToLogFile(s);

		CSize v = NewRef - Ref;

		sprintf_s(s, 256, "X=%d  Y=%d", v.cx, v.cy);
		((CFrontCadApp *)AfxGetApp())->WriteToLogFile(s);

		pObj->ChangeCenter(v);
		pObj->SetSelected(0);
		pObj = PopSelList();
	}
	Invalidate();
	delete[] s;
}


void CFrontCadView::OnAlignCenters()
{
	CCadObject *pObj, *pObjRef;
	CPoint Ref, NewRef;
	pObjRef = PopSelList();	//this is the reference object
	pObj = PopSelList();
	Ref = pObjRef->GetCenter();
	pObjRef->SetSelected(0);
	while (pObj)
	{
		NewRef = pObj->GetCenter();
		CSize v = NewRef - Ref;
		pObj->ChangeCenter(v);
		pObj->SetSelected(0);
		pObj = PopSelList();
	}
	Invalidate();
}


void CFrontCadView::OnUpdateAlignCentersUI(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount)?1:0);
}


void CFrontCadView::OnUpdateAlignCentershorizontal(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnUpdateAlignCentersvertical(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnAlignBottom()
{
	CCadObject *pObj, *pRefObj;
	CPoint Ref, NewRef;
	CPoint pointNewLR;

	//-------------------------------------
	// Get the object that all the other
	// objects are going to get alligned to
	//-------------------------------------
	pRefObj = PopSelList();
	Ref = pRefObj->GetLowerRightPoint();
	pRefObj->SetSelected(0);
	pObj = PopSelList();
	while (pObj)
	{
		int DeltaY;

		DeltaY = pObj->GetBottom() - pRefObj->GetBottom();
		pObj->AdjustRefernce(CPoint(0,DeltaY));
		pObj->SetSelected(0);
		pObj = PopSelList();

	}
	Invalidate();
}


void CFrontCadView::OnAlignLeft()
{
	CCadObject *pObj, *pRefObj;
	CPoint Ref, NewRef;

	pRefObj = PopSelList();
	Ref = pRefObj->GetUpperLeftPoint();
	pRefObj->SetSelected(0);
	pObj = PopSelList();
	while (pObj)
	{
		int DeltaX;

		DeltaX = pObj->GetLeft() - pRefObj->GetLeft();
		pObj->AdjustRefernce(CPoint(DeltaX,0));
		pObj->SetSelected(0);
		pObj = PopSelList();

	}
	Invalidate();
}


void CFrontCadView::OnAlignRight()
{
	CCadObject *pObj, *pRefObj;
	CPoint Ref, NewRef;

	pRefObj = PopSelList();
	Ref = pRefObj->GetLowerRightPoint();
	pRefObj->SetSelected(0);
	pObj = PopSelList();
	while (pObj)
	{
		int DeltaX;

		DeltaX = pObj->GetRight() - pRefObj->GetRight();
		pObj->AdjustRefernce(CPoint(DeltaX,0));
		pObj->SetSelected(0);
		pObj = PopSelList();

	}
	Invalidate();
}


void CFrontCadView::OnAlignSizeboth()
{
	CCadObject *pObj, *pRefObj;
	CSize RefSize, NewSize;

	pRefObj = PopSelList();
	RefSize = pRefObj->GetSize();
	pRefObj->SetSelected(0);
	pObj = PopSelList();
	while (pObj)
	{
		NewSize = RefSize - pObj->GetSize();
		pObj->ChangeSize(NewSize);
		pObj->SetSelected(0);
		pObj = PopSelList();

	}
	Invalidate();
}


void CFrontCadView::OnAlignSizex()
{
	CCadObject *pObj, *pRefObj;
	CSize RefSize, NewSize;

	pRefObj = PopSelList();
	RefSize = pRefObj->GetSize();
	pRefObj->SetSelected(0);
	pObj = PopSelList();
	while (pObj)
	{
		NewSize = RefSize - pObj->GetSize();
		NewSize.cy = 0;
		pObj->ChangeSize(NewSize);
		pObj->SetSelected(0);
		pObj = PopSelList();

	}
	Invalidate();
}


void CFrontCadView::OnAlignSizey()
{
	CCadObject *pObj, *pRefObj;
	CSize RefSize, NewSize;

	pRefObj = PopSelList();
	RefSize = pRefObj->GetSize();
	pRefObj->SetSelected(0);
	pObj = PopSelList();
	while (pObj)
	{
		NewSize = RefSize - pObj->GetSize();
		NewSize.cx = 0;
		pObj->ChangeSize(NewSize);
		pObj->SetSelected(0);
		pObj = PopSelList();

	}
	Invalidate();
}


void CFrontCadView::OnAlignTop()
{
	CCadObject* pObj, * pRefObj;
	CPoint Ref, NewRef;
	CPoint pointNewLR;

	//-------------------------------------
	// Get the object that all the other
	// objects are going to get alligned to
	//-------------------------------------
	pRefObj = PopSelList();
	Ref = pRefObj->GetLowerRightPoint();
	pRefObj->SetSelected(0);
	pObj = PopSelList();
	while (pObj)
	{
		int DeltaY;

		DeltaY = pObj->GetTop() - pRefObj->GetTop();
		pObj->AdjustRefernce(CPoint(0, DeltaY));
		pObj->SetSelected(0);
		pObj = PopSelList();

	}
	Invalidate();
}


void CFrontCadView::OnUpdateAlignBottom(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnUpdateAlignLeft(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnUpdateAlignRight(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnUpdateAlignSizeboth(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnUpdateAlignSizex(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnUpdateAlignSizey(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnUpdateAlignTop(CCmdUI *pCmdUI)
{
	pCmdUI->Enable((1 < m_SelectionCount) ? 1 : 0);
}


void CFrontCadView::OnButtonPrintRectangle()
{
	//-------------------------------------------
	// Place a Print Rectangle on the Drawing
	//-------------------------------------------
	m_Drawmode = DrawMode::PRINTRECT;
	m_DrawState = DRAWSTATE_WAITMOUSE_DOWN;
	theApp.GetMainFrame()->UpdateStatusBar("Print Rectangle:Place First Corner");
}


CPoint CFrontCadView::SnapToScreen(CPoint npSnap)
{
	//------------------------------------------------------
	// SnapToScreen
	//	This function is used to turn the actual coordinates
	// of a point into points on the screen.
	//
	// parameters:
	//	nSnap.......point that was calculated by the function Snap
	//
	//	Returns
	//		A scalled point
	//---------------------------------------------------------
	int x, y;

	x = int(npSnap.x * ZF[m_ZoomLevel]);
	y = int(npSnap.y * ZF[m_ZoomLevel]);
	return CPoint(x,y);
}


CPoint CFrontCadView::Scale(CPoint nP)
{
	int x, y;

	x = int(nP.x * ZoomScaleDiv[m_ZoomLevel]);
	y = int(nP.y * ZoomScaleDiv[m_ZoomLevel]);
	return CPoint(x,y);
}


void CFrontCadView::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CView::OnSysChar(nChar, nRepCnt, nFlags);
}

void CFrontCadView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//if (theApp.HasConsol()) 
	switch (nChar)
	{
	case VK_MENU:
		break;
	}

	CView::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CFrontCadView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//if (theApp.HasConsol()) 
	switch (nChar)
	{
	case VK_MENU:
		break;
	}
	CView::OnSysKeyUp(nChar, nRepCnt, nFlags);
}
