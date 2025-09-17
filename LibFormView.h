#pragma once

////////////////////////////////////////////////////
// CLibFormView form view

class CLibFormView : public CFormView
{
public:
	CComboBoxLibPartSelector	m_Combo_SelPart;
	CComboBoxLibrary	m_Combo_SelLIb;
	CStaticPreview	m_Static_Preview;
	CCadLibrary *m_pHead;
	CCadLibrary *m_pTail;
protected:
	CLibFormView();           // protected constructor used by dynamic creation
	virtual ~CLibFormView();
	DECLARE_DYNCREATE(CLibFormView)

public:
	enum { IDD = IDD_DIALOG_LIBVIEW };
public:
	CCadLibObject * GetCurrentPart(void);
	CCadLibrary * GetCurrentLibrary(void);
	void AddPartToCurLib(CCadLibObject *pObj);
	void DeleteLibrary(CCadLibrary *pL);
	void AddLibrary(CCadLibrary *pL);
	CCadLibrary *GetLibraryList(void){return m_pHead;}
	virtual void OnInitialUpdate();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	LRESULT OnMainViewGotReference(WPARAM wP,LPARAM lP);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	afx_msg void OnButtonLibviewCreatecomp();
	afx_msg void OnButtonLibviewPlace();
	afx_msg void OnButtonLibviewNewlib();
	afx_msg void OnButtonLibviewRemove();
	afx_msg void OnButtonLibviewDeletepart();
	afx_msg void OnSelchangeComboLibviewComponent();
	afx_msg void OnSelchangeComboLibviewLibrary();
	afx_msg void OnDblclkComboLibviewComponent();
	afx_msg void OnButtonLibviewSavelibrary();
public:
	afx_msg void OnButtonAddlibrary();
	afx_msg void OnViewRenderenable();
	afx_msg void OnClickedButtonLibEdit();
protected:
	DECLARE_MESSAGE_MAP()
};
