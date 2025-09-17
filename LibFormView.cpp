// LibFormView.cpp : implementation file
//

#include "stdafx.h"

////////////////////////////////////////////////////
// CLibFormView

IMPLEMENT_DYNCREATE(CLibFormView, CFormView)

CLibFormView::CLibFormView()
	: CFormView(CLibFormView::IDD)
{
	m_pHead = 0;
	m_pTail = 0;
	((CFrontCadApp*)AfxGetApp())->SetLibView(this);
}

CLibFormView::~CLibFormView()
{
}

void CLibFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLibFormView)
	DDX_Control(pDX, IDC_COMBO_LIBVIEW_COMPONENT, m_Combo_SelPart);
	DDX_Control(pDX, IDC_COMBO_LIBVIEW_LIBRARY, m_Combo_SelLIb);
	DDX_Control(pDX, IDC_STATIC_LIBVIEW_PREVIEW, m_Static_Preview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLibFormView, CFormView)
	//{{AFX_MSG_MAP(CLibFormView)
	ON_BN_CLICKED(IDC_BUTTON_LIBVIEW_CREATECOMP, OnButtonLibviewCreatecomp)
	ON_BN_CLICKED(IDC_BUTTON_LIBVIEW_PLACE, OnButtonLibviewPlace)
	ON_BN_CLICKED(IDC_BUTTON_LIBVIEW_NEWLIB, OnButtonLibviewNewlib)
	ON_BN_CLICKED(IDC_BUTTON_ADDLIBRARY, OnButtonAddlibrary)
	ON_BN_CLICKED(IDC_BUTTON_LIBVIEW_REMOVE, OnButtonLibviewRemove)
	ON_BN_CLICKED(IDC_BUTTON_LIBVIEW_DELETEPART, OnButtonLibviewDeletepart)
	ON_CBN_SELCHANGE(IDC_COMBO_LIBVIEW_COMPONENT, OnSelchangeComboLibviewComponent)
	ON_CBN_SELCHANGE(IDC_COMBO_LIBVIEW_LIBRARY, OnSelchangeComboLibviewLibrary)
	ON_CBN_DBLCLK(IDC_COMBO_LIBVIEW_COMPONENT, OnDblclkComboLibviewComponent)
	ON_BN_CLICKED(IDC_BUTTON_LIBVIEW_SAVELIBRARY, OnButtonLibviewSavelibrary)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MAINVIEW_GOTREF,OnMainViewGotReference)
	ON_COMMAND(ID_VIEW_RENDERENABLE, &CLibFormView::OnViewRenderenable)
	ON_BN_CLICKED(IDC_BUTTON_LIB_EDIT, &CLibFormView::OnClickedButtonLibEdit)
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CLibFormView diagnostics

#ifdef _DEBUG
void CLibFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLibFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

////////////////////////////////////////////////////
// CLibFormView message handlers

void CLibFormView::OnButtonLibviewCreatecomp() 
{
	MessageBox("Select Reference Point","Hey Dude!");
	CFrontCadView *pFCV = ((CFrontCadApp *)AfxGetApp())->GetMainView();
	pFCV->PostMessageA(WM_LIBVIEW_GETREF);
}

void CLibFormView::OnButtonLibviewPlace() 
{
}

void CLibFormView::AddLibrary(CCadLibrary *pL)
{
	if(m_pHead == 0)
	{
		m_pHead = pL;
		m_pTail = pL;
	}
	else
	{
		m_pTail->SetNext(pL);
		pL->SetPrev(m_pTail);
		m_pTail = pL;
	}
	this->m_Combo_SelLIb.SetLibChain(this->m_pHead);
	this->m_Combo_SelLIb.SetSelectionByName(pL->GetName());
	this->m_Combo_SelPart.SetLibraryFile(pL);
	this->m_Combo_SelPart.SetCurSel(0);
	CCadLibObject *pPart = GetCurrentPart();
	if(pPart)
	{
		m_Static_Preview.SetLibObj(pPart);
		m_Static_Preview.Invalidate();
	}
}

void CLibFormView::DeleteLibrary(CCadLibrary *pL)
{
	if(pL == m_pHead)
	{
		m_pHead = pL->GetNext();
		m_pHead->SetPrev(0);
	}
	else if(pL == m_pTail)
	{
		m_pTail = m_pTail->GetPrev();
		m_pTail->SetNext(0);
	}
	else
	{
		pL->GetPrev()->SetNext(pL->GetNext());
		pL->GetNext()->SetPrev(pL->GetPrev());
	}
	delete pL;
}

void CLibFormView::OnButtonLibviewNewlib() 
{
	
}

void CLibFormView::OnButtonAddlibrary() 
{
	FILE* pIN;
	CFileDialog dlg(TRUE);
	CFileParser libfile;

	if(dlg.DoModal() == IDOK)
	{
		CString fname = dlg.GetPathName();
		fopen_s(&pIN, fname.GetString(), "r");
		if (pIN)
		{
			libfile.Parse(pIN);
			AddLibrary(libfile.GetLib());
			fclose(pIN);
		}
		else
		{
			MessageBoxA(fname.GetString(), "ERROR", MB_OK);
		}
	}
}

void CLibFormView::OnButtonLibviewRemove() 
{
	CCadLibrary *pL = this->GetCurrentLibrary();
	DeleteLibrary(pL);
	this->m_Combo_SelLIb.SetLibChain(m_pHead);
}

void CLibFormView::OnButtonLibviewDeletepart() 
{
	CCadLibObject *pLO = this->GetCurrentPart();
	CCadLibrary *pLib = this->GetCurrentLibrary();
	if(pLO && pLib) pLib->DeletePart(pLO);
	this->m_Combo_SelPart.SetLibraryFile(pLib);
}

void CLibFormView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_Static_Preview.SetScale(CScale(0.2, 0.2));

}

void CLibFormView::OnSelchangeComboLibviewComponent() 
{
	CCadLibObject *pPart = GetCurrentPart();
	m_Static_Preview.SetLibObj(pPart);
	m_Static_Preview.Invalidate();
}

void CLibFormView::OnDblclkComboLibviewComponent() 
{
	
}

void CLibFormView::OnSelchangeComboLibviewLibrary() 
{
	CCadLibrary *pL = GetCurrentLibrary();
	this->m_Combo_SelPart.SetLibraryFile(pL);
	this->m_Combo_SelPart.SetCurSel(0);
	CCadLibObject *pPart = GetCurrentPart();
	if(pPart)
	{
		m_Static_Preview.SetLibObj(pPart);
		m_Static_Preview.Invalidate();
	}
}

void CLibFormView::AddPartToCurLib(CCadLibObject *pObj)
{
	CCadLibrary *pLib = GetCurrentLibrary();
	pLib->AddPart(pObj);
	m_Combo_SelPart.SetLibraryFile(pLib);
	this->m_Combo_SelPart.SetCurSel(0);
	CCadLibObject *pPart = GetCurrentPart();
	if(pPart)
	{
		m_Static_Preview.SetLibObj(pPart);
		m_Static_Preview.Invalidate();
	}
}

CCadLibrary * CLibFormView::GetCurrentLibrary()
{
	int Sel = this->m_Combo_SelLIb.GetCurSel();
	char *LibName = (char *)m_Combo_SelLIb.GetItemDataPtr(Sel);
	CCadLibrary *pL = this->m_pHead;
	int loop = 1;
	while(pL && loop)
	{
		if(strcmp(LibName,pL->GetName()) == 0)
			loop = 0;
		else
			pL = pL->GetNext();
	}
	return pL;
}

CCadLibObject * CLibFormView::GetCurrentPart()
{
	int loop = 1;
	CCadLibObject *pPart = NULL;

	int Sel = this->m_Combo_SelPart.GetCurSel();
	if(Sel >= 0)
	{
		char *pPartName = (char *)m_Combo_SelPart.GetItemDataPtr(Sel);
		CCadLibrary *pLib = GetCurrentLibrary();
		pPart = pLib->GetHeadObj();
		while(pPart && loop)
		{
			if(strcmp(pPartName,pPart->GetPartName()) == 0)
				loop = 0;
			else 
				pPart = (CCadLibObject *)pPart->GetNext();
		}
	}
	return pPart;
}

void CLibFormView::OnButtonLibviewSavelibrary() 
{
	CCadLibrary *pLib = GetCurrentLibrary();
	CFileDialog dlg(FALSE);
	FILE* pO = 0;

	dlg.DoModal();

	CString FileName = dlg.GetPathName();
	fopen_s(&pO,FileName.GetString(), "w");
	if (pO)
	{
		pLib->Save(pO, 0);
		fclose(pO);
	}
	else
	{
		MessageBox(FileName.GetString(), "ERROR", MB_OK);
	}
}



LRESULT CLibFormView::OnMainViewGotReference(WPARAM wP, LPARAM lP)
{
	//----------------------------------
	// Ref.x is in wP, Ref.y is in lP
	//----------------------------------
	CPoint Ref;
	Ref.x = wP;
	Ref.y = lP;
	CNewLibDialog dlg;
	dlg.m_pCaption = "New Part Name";
	dlg.DoModal();

	CFrontCadDoc *pDoc = ((CFrontCadApp *)AfxGetApp())->GetDoc();
	CCadLibObject *pPart = pDoc->GetDrawing()->CreatePartFromSelected(dlg.m_LibName);
	CCadObject *pObj = pPart->GetHead();
	while(pObj)
	{
		pObj->AdjustRefernce(Ref);
		pObj= pObj->GetNext();
	}
	this->AddPartToCurLib(pPart);
	return 0;
}


void CLibFormView::OnViewRenderenable()
{

}

void CLibFormView::OnClickedButtonLibEdit()
{
	CScaleWizDialog dlg;

	dlg.DoModal();

}
