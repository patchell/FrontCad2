// FrontCad.h : main header file for the FRONTCAD application
//

#pragma once

////////////////////////////////////////////////////
// CFrontCadApp:
// See FrontCad.cpp for the implementation of this class
//

class CFrontCadApp : public CWinApp
{
	const char* fname;
	CFrontCadView* m_pMainView;
	CLibFormView* m_pLibView;
	CUtilView* m_UtilView;
	CFrontCadDoc* m_pDoc;
	FILE* pConsol;
	FILE* m_pLogFile;
public:
	//------------------------------
	// Program settings
	//------------------------------
	RndRectAttb m_RndRectAttributes;
	TextAttributes m_TextAttributes;
	SPotScaleWizAttributes m_SCALEWIZattributes;
	PolyAttributes m_PolyAttributes;
	RectHoleAttributes m_RectHoleAttributes;
	HoleRnd1FlatAttributes m_HoleRnd1FlatAttributes;
	HoleRnd2FlatAttributes m_HoleRnd2FlatAttributes;
	HoleRoundAttributes m_HoleRoundAttributes;
	ArcAttributes m_ArcAttributes;
	RectAttributes m_RectAttributes;
	CircleAttributes m_CircleAttributs;
	ElipseAttributes m_EllipseAttributes;
	LineAttrib m_LineAttrib;
	ArrowAttributes m_ArrowAttrib;
	OriginAttrib m_OriginAttrib;
	DimAttrib m_DimAttrib;
public:
	CFrontCadApp();
	CScale GetScale() {
		return m_pMainView->GetScale();
	}
	void SaveSettings(void);
	void LoadSettings(void);
	void WriteToLogFile(char* pS);
	CMainFrame* GetMainFrame(void) { return (CMainFrame*)m_pMainWnd; }
	char* IndentString(char* s, int Size, int Indent);
	char* ConvertCStringToChar(char* cpDest, CString& csSource);
	void SetLibView(CLibFormView* pLFV) { m_pLibView = pLFV; }
	CLibFormView* GetLibView() {
		return m_pLibView;
	}
	void SetMainView(CFrontCadView* pFCV) { m_pMainView = pFCV; }
	CFrontCadView* GetMainView() {
		return m_pMainView;
	}
	void SetDoc(CFrontCadDoc* pD) { m_pDoc = pD; }
	CFrontCadDoc* GetDoc() { return m_pDoc; }
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
public:
	FILE* LogFile() { return m_pLogFile; }
	BOOL HasConsol() {
		BOOL rV = FALSE;
		if (pConsol)
			rV = TRUE;
		return rV;
	}
	BOOL IsPointInPoly(CPoint* pPolyPoint, int nPolyPoints, CPoint p);
	void RotatePoint(CPoint& p, CPoint pivot, double angle);
	//------------------------------------------------------
	// Update Default Attributes Methods
	//------------------------------------------------------
	void UpdateDimAttributes(CUtilView* pUV);
	void UpdateLineAttributes(CUtilView* pUV);
	void UpdateRectAttributes(CUtilView* pUV);
	void UpdateCircleAttributes(CUtilView* pUV);
	void UpdateEllipseAttributes(CUtilView* pUV);
	void UpdatePolyAttributes(CUtilView* pUV);
	void UpdateArcAttributes(CUtilView* pUV);
	void UpdateHoleRoundAttributes(CUtilView* pUV);
	void UpdateHoleRnd2FlatAttributes(CUtilView* pUV);
	void UpdateHoleRnd1FlatAttributes(CUtilView* pUV);
	void UpdateRectHoleAttributes(CUtilView* pUV);
	void UpdateTextAttributes(CUtilView* pUV);
	void UpdateScaleWizAttributes(CUtilView* pUV);
	void UpdateArrowAttributes(CUtilView* pUV);
	void UpdateRndRectAttributes(CUtilView* pUV);
	void UpdateLineAttrib(CUtilView* pUV);
	void UpdateOriginAttrib(CUtilView* pUV);
};

extern CFrontCadApp theApp;
extern double ArcTan(double x, double y);
extern int CheckAngle(double Start, double End,double Angle);
