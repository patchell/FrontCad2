#pragma once
//------------------------------------------------------------
// ComboBoxLibrary.h : header file
//------------------------------------------------------------

class CCadLibrary;

////////////////////////////////////////////////////
// CComboBoxLibrary window

class CComboBoxLibrary : public CComboBox
{
	CCadLibrary *m_pLibChain;
// Construction
public:
	CComboBoxLibrary();
	virtual ~CComboBoxLibrary();
	int SetSelectionByName(char *pName);
	int m_MyIndex;
	int InsertString(char *s);
	void SetLibChain(CCadLibrary *pC);
protected:
	DECLARE_MESSAGE_MAP()
};


