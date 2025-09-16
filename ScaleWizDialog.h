#pragma once
// ScaleWizDialog.h : header file


////////////////////////////////////////////////////
// CScaleWizDialog dialog

class CScaleWizDialog : public CDialog
{
	double m_Pi;
	CEdit	m_Edit_YRef;
	CEdit	m_Edit_XRef;
	CComboBoxLibrary	m_Combo_SelLib;
	CEdit	m_Edit_PartName;
	CMyTabCtrl	m_Tab_Settings;
	CStaticPreview	m_Static_Preview;
	int m_RotateTextFlag;
	int m_PrevLabel;
public:
	SPotScaleWizAttributes m_atrb;
	enum { IDD = IDD_DIALOG_SCALEWIZ };
public:
	CScaleWizDialog(CWnd* pParent = NULL);   // standard constructor
	virtual  ~CScaleWizDialog();
	CPoint CalcTextShiftonRotation(CPoint p1, CPoint Center, double angle);
	CPoint CalcXYonArc(int Radius, double Angle);
	CPoint CalcXYonArc(int Radius, int Angle);
	CCadLibObject *CreateLibObject(const char *name);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	LRESULT OnLabelSelScrollBar(WPARAM Item,LPARAM lp);
	LRESULT OnTab1Message(WPARAM wP, LPARAM lP);
	LRESULT OnTab2Message(WPARAM wP, LPARAM lP);
	LRESULT OnTab3Message(WPARAM wP, LPARAM lP);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeTabScalewiz(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonWizSavetolib();
	afx_msg void OnButtonScalewizNewlib();
	afx_msg void OnSelchangeComboScalewizLibsel();
	afx_msg void OnButtonScalewizSetref();
	DECLARE_MESSAGE_MAP()
};

