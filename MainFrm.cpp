// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CMainFrame

int m_Splits = 0;

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI ( ID_INDICATOR_XY,OnUpdateXYDisplay)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_XY,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	memset(X_Y_Pos, 0, 32);
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(
		this, 
		TBSTYLE_FLAT, 
		WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) 
		|| 	!m_wndToolBar.LoadToolBar(IDR_MAINFRAME)
	)
	{
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_XY,SBPS_POPOUT,128);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	this->X_Y_Pos[0] = 0;
	return TRUE;
}

////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

////////////////////////////////////////////////////
// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	if(!m_Libpane.CreateLibraryPane(this,pContext))
	{
		TRACE("Error Creating Lib Pane\n");
		return FALSE;
	}
	if( !m_Utility.CreateUtility(&m_Libpane,pContext,WS_CHILD | WS_VISIBLE | WS_BORDER,m_Libpane.IdFromRowCol(0, 0)))
	{
		TRACE("Error creation of utility\n");
		return CFrameWnd::OnCreateClient(lpcs, pContext);
	}	
    if (!m_Rulers.CreateRulers(&m_Utility, pContext,WS_CHILD | WS_VISIBLE | WS_BORDER,m_Utility.IdFromRowCol(1, 0))) {
        TRACE("Error creation of rulers\n");
        return CFrameWnd::OnCreateClient(lpcs, pContext);
    }
	m_Splits = 1;
	return TRUE;	
}

void CMainFrame::ShowRulers(BOOL bShow)
{
    m_Rulers.ShowRulers(bShow);
}

void CMainFrame::UpdateRulersInfo(stRULER_INFO stRulerInfo)
{
    m_Rulers.UpdateRulersInfo(stRulerInfo);
}


void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	CRect rect;
	GetClientRect(&rect);
	if(m_Splits)
	{
		//------------------------------------------
		// here we set the width of the library
		// panel
		//------------------------------------------
		m_Libpane.SetColumnInfo(0,rect.Width()-285,50);
		m_Libpane.SetColumnInfo(1,285,50);
		m_Libpane.RecalcLayout();
	}
}

CUtilView * CMainFrame::GetUtilityView()
{
	return (CUtilView *)m_Utility.GetPane(0,0);
}

void CMainFrame::FocusOnMainView()
{
//	m_Utility.SetActivePane(1,0,0);
//	m_Libpane.SetActivePane(0,0,0);
//	m_Rulers.SetActivePane(1,1,0);
//	this->m_Rulers.GetPane(1,1)->SetFocus();
}

CLibFormView * CMainFrame::GetLibFormView()
{
	return (CLibFormView *)m_Libpane.GetPane(0,1);
}

void CMainFrame::OnUpdateXYDisplay(CCmdUI *pCmdUI)
{
	CString XY;

	XY.Format(ID_INDICATOR_XY,X_Y_Pos);
	m_wndStatusBar.SetPaneText(m_wndStatusBar.CommandToIndex(ID_INDICATOR_XY),XY);
}

void CMainFrame::SetXYPos(int X, int Y)
{
	sprintf_s(this->X_Y_Pos,32,"X=%d Y=%d",X,Y);
}
