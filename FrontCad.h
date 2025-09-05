// FrontCad.h : main header file for the FRONTCAD application
//

#if !defined(AFX_FRONTCAD_H__E7F90698_BBB2_4535_A812_3FB737CDB14E__INCLUDED_)
#define AFX_FRONTCAD_H__E7F90698_BBB2_4535_A812_3FB737CDB14E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif



////////////////////////////////////////////////////
// CFrontCadApp:
// See FrontCad.cpp for the implementation of this class
//

class CFrontCadApp : public CWinApp
{
	const char *fname;
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
	SCALEWIZattributes m_SCALEWIZattributes;
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
	void SaveSettings(void);
	void LoadSettings(void);
	void WriteToLogFile(char * pS);
	CMainFrame *GetMainFrame(void) { return (CMainFrame *)m_pMainWnd; }
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
};

extern CFrontCadApp theApp;
extern double ArcTan(double x, double y);
extern int CheckAngle(double Start, double End,double Angle);

#endif // !defined(AFX_FRONTCAD_H__E7F90698_BBB2_4535_A812_3FB737CDB14E__INCLUDED_)
