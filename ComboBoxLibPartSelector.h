#if !defined(AFX_COMBOBOXLIBPARTSELECTOR_H__2CC452D2_52E9_4F24_85F6_6ADAD1739AF1__INCLUDED_)
#define AFX_COMBOBOXLIBPARTSELECTOR_H__2CC452D2_52E9_4F24_85F6_6ADAD1739AF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxLibPartSelector.h : header file
//

////////////////////////////////////////////////////
// CComboBoxLibPartSelector window

class CComboBoxLibPartSelector : public CComboBox
{
// Construction
public:
	CComboBoxLibPartSelector();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxLibPartSelector)
	//}}AFX_VIRTUAL

// Implementation
public:
	int InsertString(char *pName);
	CCadLibrary * m_pLib;
	void SetLibraryFile(CCadLibrary *pLib);
	virtual ~CComboBoxLibPartSelector();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboBoxLibPartSelector)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXLIBPARTSELECTOR_H__2CC452D2_52E9_4F24_85F6_6ADAD1739AF1__INCLUDED_)
