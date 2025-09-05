// ComboBoxLibrary.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CComboBoxLibrary

CComboBoxLibrary::CComboBoxLibrary()
{
	m_pLibChain = 0;
	m_MyIndex = 0;
}

CComboBoxLibrary::~CComboBoxLibrary()
{
}


BEGIN_MESSAGE_MAP(CComboBoxLibrary, CComboBox)
	//{{AFX_MSG_MAP(CComboBoxLibrary)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CComboBoxLibrary message handlers

void CComboBoxLibrary::SetLibChain(CCadLibrary *pC)
{
	int i;
	m_pLibChain = pC;
	//clear out combo box
	int n = GetCount();
	for(i=n-1;i>=0;--i)
	{
		this->DeleteString(i);
	}
	i=0;
	while(pC)
	{
		this->InsertString(pC->GetName());
		pC = pC->GetNext();
	}
	this->SetCurSel(0);
}

int CComboBoxLibrary::InsertString(char *s)
{
	int Index = this->GetCount();
	CComboBox::InsertString(Index,s);
	this->SetItemDataPtr(Index,s);
	return Index;
}

int CComboBoxLibrary::SetSelectionByName(char *pName)
{
	int n = GetCount();
	int i,loop;
	char *pN = new char[256];
	for(i=0,loop=0;i<n;++i)
	{
		this->GetLBText(i,pN);
	//	pN = (char *)GetItemDataPtr(i);
		if(strcmp(pName,pN)== 0)
		{
			loop = 0;
			SetCurSel(i);
		}
	}
	delete[] pN;
	return i;
}
