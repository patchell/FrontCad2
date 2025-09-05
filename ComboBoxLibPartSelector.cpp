// ComboBoxLibPartSelector.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CComboBoxLibPartSelector

CComboBoxLibPartSelector::CComboBoxLibPartSelector()
{
}

CComboBoxLibPartSelector::~CComboBoxLibPartSelector()
{
}


BEGIN_MESSAGE_MAP(CComboBoxLibPartSelector, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxLibPartSelector)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CComboBoxLibPartSelector message handlers

void CComboBoxLibPartSelector::SetLibraryFile(CCadLibrary *pLib)
{
	m_pLib = pLib;
	int n = GetCount();
	int i;
	//clear out combo box
	for(i=n-1;i>=0;--i)
	{
		this->DeleteString(i);
	}
	CCadLibObject *pLO = pLib->GetHeadObj();
	while(pLO)
	{
		this->InsertString(pLO->GetPartName());
		pLO = (CCadLibObject *)pLO->GetNext();
	}
}

int CComboBoxLibPartSelector::InsertString(char *pName)
{
	int Index = this->GetCount();
	CComboBox::InsertString(Index,pName);
	this->SetItemDataPtr(Index,pName);
	return Index;
}
