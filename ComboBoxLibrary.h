#if !defined(AFX_COMBOBOXLIBRARY_H__EB73272F_0EC3_4FE2_888A_E3D427DB8332__INCLUDED_)
#define AFX_COMBOBOXLIBRARY_H__EB73272F_0EC3_4FE2_888A_E3D427DB8332__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxLibrary.h : header file
//

#include "CadLibrary.h"

////////////////////////////////////////////////////
// CComboBoxLibrary window

class CComboBoxLibrary : public CComboBox
{
	CCadLibrary *m_pLibChain;
// Construction
public:
	CComboBoxLibrary();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxLibrary)
	//}}AFX_VIRTUAL

// Implementation
public:
	int SetSelectionByName(char *pName);
	int m_MyIndex;
	int InsertString(char *s);
	virtual ~CComboBoxLibrary();
	void SetLibChain(CCadLibrary *pC);
	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxLibrary)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXLIBRARY_H__EB73272F_0EC3_4FE2_888A_E3D427DB8332__INCLUDED_)
