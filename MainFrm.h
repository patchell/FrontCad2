// MainFrm.h : interface of the CMainFrame class
//
////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1F82F443_D91F_4BC5_9D41_58CC1A523A51__INCLUDED_)
#define AFX_MAINFRM_H__1F82F443_D91F_4BC5_9D41_58CC1A523A51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ruler.h"
#include "SplitterUtility.h"
#include "LibSplitterWnd.h"

class CUtilView;
class CLibFormView;

class CMainFrame : public CFrameWnd
{
	CSplitterUtility m_Utility;
	CLibSplitterWnd m_Libpane;
	CRulerSplitterWnd m_Rulers;
	char X_Y_Pos[32];

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

public:
    void ShowRulers(BOOL bShow);
    void UpdateRulersInfo(stRULER_INFO stRulerInfo);

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	void UpdateStatusBar(const char *s) { m_wndStatusBar.SetWindowTextA(s); }
	void SetXYPos(int X, int Y);
	CLibFormView * GetLibFormView(void);
	void FocusOnMainView();
	CUtilView * GetUtilityView(void);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateXYDisplay(CCmdUI *pCmdUI);
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_MAINFRM_H__1F82F443_D91F_4BC5_9D41_58CC1A523A51__INCLUDED_)
