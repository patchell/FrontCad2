// FrontCadDoc.cpp : implementation of the CFrontCadDoc class
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CFrontCadDoc

IMPLEMENT_DYNCREATE(CFrontCadDoc, CDocument)

BEGIN_MESSAGE_MAP(CFrontCadDoc, CDocument)
	//{{AFX_MSG_MAP(CFrontCadDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CFrontCadDoc construction/destruction

CFrontCadDoc::CFrontCadDoc()
{
	m_pDrawing = 0;
	m_pDocView = 0;
	m_pParser = 0;
	((CFrontCadApp*)AfxGetApp())->SetDoc(this);
}

CFrontCadDoc::~CFrontCadDoc()
{
	if (m_pDrawing) delete m_pDrawing;
}

BOOL CFrontCadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// (SDI documents will reuse this document)
	if(m_pDocView)
		m_pDocView->ClearSelList();
	if(m_pDrawing) delete m_pDrawing;
	m_pDrawing = new CCadDrawing;
	return TRUE;
}



////////////////////////////////////////////////////
// CFrontCadDoc serialization

void CFrontCadDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

////////////////////////////////////////////////////
// CFrontCadDoc diagnostics

#ifdef _DEBUG
void CFrontCadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFrontCadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

////////////////////////////////////////////////////
// CFrontCadDoc commands


BOOL CFrontCadDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	FILE *pO = 0;
	fopen_s(&pO, lpszPathName,"w");
	if(pO) m_pDrawing->Save(pO,0);
	if(pO) fclose(pO);
	SetModifiedFlag(false);
	return TRUE;
}

BOOL CFrontCadDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	FILE *pIn;
	CFileParser parser(this);

	m_pParser = &parser;
	fopen_s(&pIn, lpszPathName, "r");
	if(pIn == 0)
		return FALSE;
	parser.Parse(pIn);
	fclose(pIn);
	m_pParser = 0;
	return TRUE;
}

BOOL CFrontCadDoc::CanCloseFrame(CFrameWnd* pFrame) 
{
	return CDocument::CanCloseFrame(pFrame);
}


void CFrontCadDoc::InsertObject(CCadObject * pObj)
{
	m_pDrawing->InsertObject(pObj);
	SetModifiedFlag(true);
}


void CFrontCadDoc::AddObject(CCadObject * pObj)
{
	m_pDrawing->AddObjectToEnd(pObj);
	SetModifiedFlag(true);
}


void CFrontCadDoc::RemoveObject(CCadObject * pObj)
{
	m_pDrawing->RemoveObject(pObj);
	SetModifiedFlag(true);
}


CCadPrintRect * CFrontCadDoc::GetPrintRect()
{
	return m_pDrawing->GetPrintRect();
}


COLORREF CFrontCadDoc::GetBkColor()
{
	return m_pDrawing->GetBkColor();
}


void CFrontCadDoc::SetBkColor(COLORREF color)
{
	m_pDrawing->SetBkColor(color);
}
