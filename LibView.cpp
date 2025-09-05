// LibView.cpp : implementation file
//

#include "stdafx.h"
#include "FrontCad.h"
#include "LibView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLibView

IMPLEMENT_DYNCREATE(CLibView, CView)

CLibView::CLibView()
{
}

CLibView::~CLibView()
{
}


BEGIN_MESSAGE_MAP(CLibView, CView)
	//{{AFX_MSG_MAP(CLibView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLibView drawing

void CLibView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	CRect rect;
	GetClientRect(&rect);
	CBrush BlueBr;
	BlueBr.CreateSolidBrush(RGB(255,0,0));
	pDC->FillRect(&rect,&BlueBr);
}

/////////////////////////////////////////////////////////////////////////////
// CLibView diagnostics

#ifdef _DEBUG
void CLibView::AssertValid() const
{
	CView::AssertValid();
}

void CLibView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLibView message handlers
