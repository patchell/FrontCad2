// FrontCad.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CFrontCadApp

BEGIN_MESSAGE_MAP(CFrontCadApp, CWinApp)
	//{{AFX_MSG_MAP(CFrontCadApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CFrontCadApp construction

CFrontCadApp::CFrontCadApp()
{
	pConsol = 0;
	m_pMainView = 0;
	m_pLibView = 0;
	m_UtilView = 0;
	m_pDoc = 0;
	m_pLibView = 0;
	m_pMainView = 0;
	fname = "FrontCad.ini";
	m_pLogFile = 0;
 
}

////////////////////////////////////////////////////
// The one and only CFrontCadApp object

CFrontCadApp theApp;

////////////////////////////////////////////////////
// CFrontCadApp initialization

BOOL CFrontCadApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

//	fopen_s(&m_pLogFile, "Log.txt", "w");
	SetRegistryKey(_T("FrontCad_1_0"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CFrontCadDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CFrontCadView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
//	AllocConsole();
//	freopen_s(&pConsol, "CONOUT$", "w", stdout);
//	if (HasConsol())	printf("Ready\n");

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	LoadSettings();
	return TRUE;
}


////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    CStatic m_Statoc_Versopm;
    void SetVersion();
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CAboutDlg)
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_STATIC_ABOUT_VERSION, m_Statoc_Versopm);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CFrontCadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;

	aboutDlg.DoModal();
	
}

////////////////////////////////////////////////////
// CFrontCadApp message handlers


int CFrontCadApp::ExitInstance() 
{
	SaveSettings();
	if (m_pLogFile) fclose(m_pLogFile);
	if(HasConsol()){
		fclose(pConsol);
		FreeConsole();
	}
	return CWinApp::ExitInstance();
}


void CFrontCadApp::LoadSettings()
{
	//---------- Origin Attributes ------------------------------
	m_OriginAttrib.m_Color = GetProfileInt("Origin", "Color", (int)RGB(0, 0, 0));
	m_OriginAttrib.m_LineWidth = GetProfileInt("Origin", "Width", 10);
	//---------- Dimension Attributes ------------------------------
	m_DimAttrib.m_Color = GetProfileInt("Dimension", "Color", (int)RGB(0, 0, 0));
	m_DimAttrib.m_LineWidth = GetProfileInt("Dimension", "Width", 10);
	m_DimAttrib.m_TextAtrib.m_Color = GetProfileInt("Dimension", "Color", (int)RGB(0, 0, 0));
	m_DimAttrib.m_TextAtrib.m_BkColor = GetProfileInt("Dimension", "BackColor", (int)RGB(255, 255, 255));
	m_DimAttrib.m_TextAtrib.m_Angle = GetProfileInt("Dimension", "Angle", 0);
	m_DimAttrib.m_TextAtrib.m_FontHeight = GetProfileInt("Dimension", "FontHeight", 200);
	m_DimAttrib.m_TextAtrib.m_FontWidth = GetProfileInt("Dimension", "Width", 0);
	m_DimAttrib.m_TextAtrib.m_Format = GetProfileInt("Dimension", "Format", DT_BOTTOM | DT_SINGLELINE);
	m_DimAttrib.m_TextAtrib.m_Transparent = GetProfileInt("Dimension", "Transparent", 1);
	m_DimAttrib.m_TextAtrib.m_Weight = GetProfileInt("Dimension", "Weight", FW_DEMIBOLD);
	m_DimAttrib.m_TextAtrib.m_pFontName = new char[LF_FACESIZE];
	strcpy_s(m_DimAttrib.m_TextAtrib.m_pFontName, LF_FACESIZE, LPCTSTR(GetProfileString("Dimension", "Font", "Arial")));
	m_DimAttrib.m_TextAtrib.m_pText = 0;
	//---------- Arrow Attributes ------------------------------
	m_ArrowAttrib.m_LineColor = GetProfileInt("Arrow", "LineColor", (int)RGB(0, 0, 0));
	m_ArrowAttrib.m_FillColor = GetProfileInt("Arrow", "FillColor", (int)RGB(0, 0, 0));
	m_ArrowAttrib.m_Len = GetProfileInt("Arrow", "Len", 300);
	m_ArrowAttrib.m_ArrowWidth = GetProfileInt("Arrow", "Width", 200);
	m_ArrowAttrib.m_LineWidth = GetProfileInt("Arrow", "LineWidth", 20);
	m_ArrowAttrib.m_bTransparent = GetProfileInt("Arrow", "Transparent", 0);
	//----------- Rounded Rectangle Attributes ------------------------
	m_RndRectAttributes.m_FillColor = GetProfileInt("RndRect","FillColor",(int)RGB(0,128,255));
	m_RndRectAttributes.m_LineColor = GetProfileInt("RndRect","LineColor",(int)RGB(0,255,0));
	m_RndRectAttributes.m_LineWidth = GetProfileInt("RndRect","LineWidth", 100);
	m_RndRectAttributes.m_P3.x = GetProfileInt("RndRect","X3",250);
	m_RndRectAttributes.m_P3.y =  GetProfileInt("RndRect","Y3",250);
	m_RndRectAttributes.m_bTransparent = GetProfileInt("RndRect", "Transparent", 0);
	//----------- Line Attributes ------------------------
	m_LineAttrib.m_LineWidth = GetProfileInt("Line","LineWidth",125);
	m_LineAttrib.m_LineColor = GetProfileInt("Line","LineColor",(int)RGB(0,0,0));
	//----------- Rectangle Attributes ------------------------
	m_RectAttributes.m_FillColor = GetProfileInt("Rect","FillColor",(int)RGB(0,0,255) );
	m_RectAttributes.m_LineColor = GetProfileInt("Rect","LineColor",(int)RGB(0,0,0) );
	m_RectAttributes.m_LineWidth = GetProfileInt("Rect","LineWidth",100);
	m_RectAttributes.m_bTransparentFill = GetProfileInt("Rect", "Transparent", 0);
	//--------------------------------------------------------------
	// Load Circle Attributes
	//--------------------------------------------------------------
	m_CircleAttributs.m_FillColor = GetProfileInt("Circle", "FillColor", (int)RGB(0, 0, 255));
	m_CircleAttributs.m_LineColor = GetProfileInt("Circle", "LineColor", (int)RGB(0, 0, 0));
	m_CircleAttributs.m_LineWidth = GetProfileInt("Circle", "LineWidth", 100);
	m_CircleAttributs.m_bTransparent = GetProfileInt("Circle", "TransParenetFill",0);
	//----------- Elipse Attributes ------------------------
	m_EllipseAttributes.m_FillColor = GetProfileInt("Ellipse","FillColor",(int)RGB(0,0,255) );
	m_EllipseAttributes.m_LineColor = GetProfileInt("Ellipse","LineColor",(int)RGB(0,0,0) );
	m_EllipseAttributes.m_LineWidth = GetProfileInt("Ellipse","LineWidth",100);
	m_EllipseAttributes.m_Transparent = GetProfileInt("Ellipse","Transparent",0);
	//----------- Polygon Attributes ------------------------
	m_PolyAttributes.m_LineColor = GetProfileInt("Poly","LineColor",(int)RGB(0,0,0) );
	m_PolyAttributes.m_LineWidth = GetProfileInt("Poly","LineWidth",50);
	m_PolyAttributes.m_FillColor = GetProfileInt("Poly", "FillColor", 50);
	m_PolyAttributes.m_Transparent = GetProfileInt("Poly", "Transparent", 50);
	//----------- Arc Attributes ------------------------
	m_ArcAttributes.m_LineColor = GetProfileInt("Arc","LineColor",(int)RGB(0,0,0) );
	m_ArcAttributes.m_LineWidth = GetProfileInt("Arc","LineWidth",50);
	//----------- Hole Round Attributes ------------------------
	m_HoleRoundAttributes.m_Radius = GetProfileInt("HoleRound","Radius",188);
	m_HoleRoundAttributes.m_LineColor = GetProfileInt("HoleRound","LineColor",(int)RGB(0,0,0) );
	m_HoleRoundAttributes.m_LineWidth = GetProfileInt("HoleRound","LineWidth",20);
	//----------- Hole Round 2 Flat Attributes ------------------------
	m_HoleRnd2FlatAttributes.m_LineWidth = GetProfileInt("HoleRound2Flat","LineWidth",20);
	m_HoleRnd2FlatAttributes.m_FlatDist = GetProfileInt("HoleRound2Flat","FlatDist",150);
	m_HoleRnd2FlatAttributes.m_LineColor = GetProfileInt("HoleRound2Flat","LineColor",(int)RGB(0,0,0) );
	m_HoleRnd2FlatAttributes.m_Radius = GetProfileInt("HoleRound2Flat","Radius",188);
	//----------- Hole Round 1 Flat Attributes ------------------------
	m_HoleRnd1FlatAttributes.m_FlatDist = GetProfileInt("HoleRound1Flat","FlatDist",150);
	m_HoleRnd1FlatAttributes.m_LineColor = GetProfileInt("HoleRound1Flat","LineColor",(int)RGB(0,0,0) );
	m_HoleRnd1FlatAttributes.m_Radius = GetProfileInt("HoleRound1Flat","Radius",188);
	m_HoleRnd1FlatAttributes.m_LineWidth = GetProfileInt("HoleRound1Flat","LineWidth",20);;
	//----------- Rectangular Hole Attributes ------------------------
	m_RectHoleAttributes.m_H = GetProfileInt("HoleRect","Height",250);
	m_RectHoleAttributes.m_W = GetProfileInt("HoleRect","Width",250);
	m_RectHoleAttributes.m_LineWidth = GetProfileInt("HoleRect","LineWidth",20);
	m_RectHoleAttributes.m_LineColor = GetProfileInt("HoleRect","LineColor",(int)RGB(0,0,0) );
	//----------- Text Attributes ------------------------
	m_TextAttributes.m_Color = GetProfileInt("Text","Color",(int)RGB(0,0,0) );
	m_TextAttributes.m_BkColor = GetProfileInt("Text","BackColor",(int)RGB(255,255,255) );
	m_TextAttributes.m_Angle = GetProfileInt("Text","Angle",0);
	m_TextAttributes.m_FontHeight = GetProfileInt("Text","FontHeight",200);
	m_TextAttributes.m_FontWidth = GetProfileInt("Text","Width",0);
	m_TextAttributes.m_Format = GetProfileInt("Text","Format",DT_BOTTOM | DT_SINGLELINE);
	m_TextAttributes.m_Transparent = GetProfileInt("Text","Transparent",1);
	m_TextAttributes.m_Weight = GetProfileInt("Text","Weight",FW_DEMIBOLD);
	m_TextAttributes.m_pFontName = new char[LF_FACESIZE];
	strcpy_s(m_TextAttributes.m_pFontName, LF_FACESIZE,LPCTSTR(GetProfileString("Text","Font","Arial")));
	m_TextAttributes.m_pText = 0;
	//----------- Scale Wizard Attributes ------------------------
	m_SCALEWIZattributes.m_ArcEnd = GetProfileInt("SWiz","ArcEnd",2250);
	m_SCALEWIZattributes.m_ArcLineWidth = GetProfileInt("SWiz","ArcLineWidth",40);
	m_SCALEWIZattributes.m_ArcRadius = GetProfileInt("SWiz","ArcRadius",375);
	m_SCALEWIZattributes.m_ArcStart = GetProfileInt("SWiz","ArcStart",3150);
	m_SCALEWIZattributes.m_ArcColor = GetProfileInt("SWiz","ArcColor",(int)RGB(0,0,0) );
	m_SCALEWIZattributes.m_DivisionLineLegnth = GetProfileInt("SWiz","DivLinLen",100);
	m_SCALEWIZattributes.m_DivisionLineWidth = GetProfileInt("SWiz","DivLinW",20);
	m_SCALEWIZattributes.m_Divisions = GetProfileInt("SWiz","Divisions",10);
	m_SCALEWIZattributes.m_DivLineColor = GetProfileInt("SWiz","DivColor",(int)RGB(0,0,0) );
	m_SCALEWIZattributes.m_SubdivisionLengnth = GetProfileInt("SWiz","SubLinLen",85);
	m_SCALEWIZattributes.m_SubDivisionLineWidth = GetProfileInt("SWiz","SubLinW",15);
	m_SCALEWIZattributes.m_SubDivisions = GetProfileInt("SWiz","SubDiv",3);
	m_SCALEWIZattributes.m_SubDivColor = GetProfileInt("SWiz","SubDivColor",(int)RGB(0,0,0) );
	m_SCALEWIZattributes.m_FlatDist = GetProfileInt("SWiz","FlatDist",0);
	m_SCALEWIZattributes.m_HoleSize = GetProfileInt("SWiz","HoleRad",188);
	m_SCALEWIZattributes.m_HoleType = GetProfileInt("SWiz","HoleType",OBJECT_TYPE_HOLEROUND);
	char *s = new char[32];
	for(int i=0;i< SCALE_LABELS_SIZE;++i)
	{
		m_SCALEWIZattributes.m_pLabels[i] = new char[SCALE_LABELS_STRING_SIZE];
		sprintf_s(s, SCALE_LABELS_STRING_SIZE,"%d",i);
		strcpy_s(m_SCALEWIZattributes.m_pLabels[i], SCALE_LABELS_STRING_SIZE,s);
	}
	delete[] s;
	m_SCALEWIZattributes.m_FontSize = GetProfileInt("SWiz","FontSize",150);
	m_SCALEWIZattributes.m_FontWeight = GetProfileInt("SWiz","Weight",FW_DEMIBOLD);
	m_SCALEWIZattributes.m_DistToTick = GetProfileInt("SWiz","DistToTick",150);
	m_SCALEWIZattributes.m_TextColor = GetProfileInt("SWiz","TextColor",(int)RGB(0,0,0) );
	m_SCALEWIZattributes.m_BkColor = GetProfileInt("SWiz","TextBkColor",(int)RGB(255,255,255) );
	m_SCALEWIZattributes.m_pFont = new char[LF_FACESIZE];
	strcpy_s(m_SCALEWIZattributes.m_pFont, LF_FACESIZE,LPCTSTR(GetProfileString("SWiz","Font","Arial")) );
}

void CFrontCadApp::SaveSettings()
{
	//----------- Dimension Attributes ------------------------------
	WriteProfileInt("Dimension", "Color", (int)m_DimAttrib.m_Color);
	WriteProfileInt("Dimension", "Width", m_DimAttrib.m_LineWidth);
	WriteProfileInt("Dimension", "Color", (int)m_DimAttrib.m_TextAtrib.m_Color);
	WriteProfileInt("Dimension", "BackColor",(int)m_DimAttrib.m_TextAtrib.m_BkColor);
	WriteProfileInt("Dimension", "Angle", m_DimAttrib.m_TextAtrib.m_Angle);
	WriteProfileInt("Dimension", "FontHeight", m_DimAttrib.m_TextAtrib.m_FontHeight);
	WriteProfileInt("Dimension", "Width", m_DimAttrib.m_TextAtrib.m_FontWidth);
	WriteProfileInt("Dimension", "Format", m_DimAttrib.m_TextAtrib.m_Format);
	WriteProfileInt("Dimension", "Transparent", m_DimAttrib.m_TextAtrib.m_Transparent);
	WriteProfileInt("Dimension", "Weight", m_DimAttrib.m_TextAtrib.m_Weight);
	WriteProfileStringA("Dimension", "Font", m_DimAttrib.m_TextAtrib.m_pFontName);
	//----------- Origin Attributes ------------------------------
	WriteProfileInt("Origin", "Color", (int)m_OriginAttrib.m_Color);
	WriteProfileInt("Origin", "Width", m_OriginAttrib.m_LineWidth);
	//----------- Arrow Attributes ------------------------------
	WriteProfileInt("Arrow", "LineColor", (int)m_ArrowAttrib.m_LineColor);
	WriteProfileInt("Arrow", "FillColor", (int)m_ArrowAttrib.m_FillColor);
	WriteProfileInt("Arrow", "Len", m_ArrowAttrib.m_Len);
	WriteProfileInt("Arrow", "Width", m_ArrowAttrib.m_ArrowWidth);
	WriteProfileInt("Arrow", "LineWidth", m_ArrowAttrib.m_LineWidth);
	WriteProfileInt("Arrow", "Transparent", m_ArrowAttrib.m_bTransparent);
	//----------- Rounded Rectangle Attributes ------------------------
	WriteProfileInt("RndRect","FillColor",(int)m_RndRectAttributes.m_FillColor);
	WriteProfileInt("RndRect","LineColor",(int)m_RndRectAttributes.m_LineColor);
	WriteProfileInt("RndRect","LineWidth", m_RndRectAttributes.m_LineWidth);
	WriteProfileInt("RndRect","X3",m_RndRectAttributes.m_P3.x);
	WriteProfileInt("RndRect","Y3",m_RndRectAttributes.m_P3.y);
	WriteProfileInt("RndRect", "Transparent", m_RndRectAttributes.m_bTransparent);
	//----------- Line Attributes ------------------------
	WriteProfileInt("Line","LineWidth",m_LineAttrib.m_LineWidth);
	WriteProfileInt("Line","LineColor",(int)m_LineAttrib.m_LineColor);
	//----------- Rectangle Attributes ------------------------
	WriteProfileInt("Rect","FillColor",(int)m_RectAttributes.m_FillColor );
	WriteProfileInt("Rect","LineColor",(int)m_RectAttributes.m_LineColor);
	WriteProfileInt("Rect","LineWidth",m_RectAttributes.m_LineWidth);
	WriteProfileInt("Rect", "TransParenetFill", m_RectAttributes.m_bTransparentFill);
	//---------------------------------------------------
	// Save Circle Attributes
	//---------------------------------------------------
	WriteProfileInt("Circle", "FillColor", (int)m_CircleAttributs.m_FillColor);
	WriteProfileInt("Circle", "LineColor", (int)m_CircleAttributs.m_LineColor);
	WriteProfileInt("Circle", "LineWidth", m_CircleAttributs.m_LineWidth);
	WriteProfileInt("Circle", "TransParenetFill", m_CircleAttributs.m_bTransparent);
	//----------- Elipse Attributes ------------------------
	WriteProfileInt("Ellipse","FillColor",(int)m_EllipseAttributes.m_FillColor );
	WriteProfileInt("Ellipse","LineColor",(int)m_EllipseAttributes.m_LineColor );
	WriteProfileInt("Ellipse","LineWidth",m_EllipseAttributes.m_LineWidth );
	WriteProfileInt("Ellipse", "Transparent", m_EllipseAttributes.m_Transparent);
	//----------- Polygon Attributes ------------------------
	WriteProfileInt("Poly","LineColor",(int)m_PolyAttributes.m_LineColor );
	WriteProfileInt("Poly","LineWidth",m_PolyAttributes.m_LineWidth);
	WriteProfileInt("Poly", "FillColor", m_PolyAttributes.m_FillColor);
	WriteProfileInt("Poly", "Transparent", m_PolyAttributes.m_Transparent);
	//----------- Arc Attributes ------------------------
	WriteProfileInt("Arc","LineColor",(int)m_ArcAttributes.m_LineColor );
	WriteProfileInt("Arc","LineWidth",m_ArcAttributes.m_LineWidth);
	//----------- Hole Round Attributes ------------------------
	WriteProfileInt("HoleRound","Radius",m_HoleRoundAttributes.m_Radius);
	WriteProfileInt("HoleRound","LineColor",(int)m_HoleRoundAttributes.m_LineColor );
	WriteProfileInt("HoleRound","LineWidth",m_HoleRoundAttributes.m_LineWidth);
	//----------- Hole Round 2 Flat Attributes ------------------------
	WriteProfileInt("HoleRound2Flat","LineWidth",m_HoleRnd2FlatAttributes.m_LineWidth);
	WriteProfileInt("HoleRound2Flat","FlatDist",m_HoleRnd2FlatAttributes.m_FlatDist);
	WriteProfileInt("HoleRound2Flat","LineColor",(int)m_HoleRnd2FlatAttributes.m_LineColor );
	WriteProfileInt("HoleRound2Flat","Radius",m_HoleRnd2FlatAttributes.m_Radius);
	//----------- Hole Round 1 Flat Attributes ------------------------
	WriteProfileInt("HoleRound1Flat","FlatDist",m_HoleRnd1FlatAttributes.m_FlatDist);
	WriteProfileInt("HoleRound1Flat","LineColor",(int)m_HoleRnd1FlatAttributes.m_LineColor );
	WriteProfileInt("HoleRound1Flat","Radius",m_HoleRnd1FlatAttributes.m_Radius);
	WriteProfileInt("HoleRound1Flat","LineWidth",m_HoleRnd1FlatAttributes.m_LineWidth);;
	//----------- Rectangular Hole Attributes ------------------------
	WriteProfileInt("HoleRect","Height",m_RectHoleAttributes.m_H);
	WriteProfileInt("HoleRect","Width",m_RectHoleAttributes.m_W);
	WriteProfileInt("HoleRect","LineWidth",m_RectHoleAttributes.m_LineWidth);
	WriteProfileInt("HoleRect","LineColor",(int)m_RectHoleAttributes.m_LineColor );
	//----------- Text Attributes ------------------------
	WriteProfileInt("Text","Color",(int)m_TextAttributes.m_Color );
	WriteProfileInt("Text","BackColor",(int)m_TextAttributes.m_BkColor );
	WriteProfileInt("Text","Angle",m_TextAttributes.m_Angle);
	WriteProfileInt("Text","FontHeight",m_TextAttributes.m_FontHeight);
	WriteProfileInt("Text","Width",m_TextAttributes.m_FontWidth);
	WriteProfileInt("Text","Format",m_TextAttributes.m_Format);
	WriteProfileInt("Text","Transparent",m_TextAttributes.m_Transparent);
	WriteProfileInt("Text","Weight",m_TextAttributes.m_Weight);
	WriteProfileString("Text","Font",m_TextAttributes.m_pFontName);
	//----------- Scale Wizard Attributes ------------------------
	WriteProfileInt("SWiz","ArcEnd",m_SCALEWIZattributes.m_ArcEnd);
	WriteProfileInt("SWiz","ArcLineWidth",m_SCALEWIZattributes.m_ArcLineWidth);
	WriteProfileInt("SWiz","ArcRadius",m_SCALEWIZattributes.m_ArcRadius);
	WriteProfileInt("SWiz","ArcStart",m_SCALEWIZattributes.m_ArcStart);
	WriteProfileInt("SWiz","ArcColor",(int)m_SCALEWIZattributes.m_ArcColor );
	WriteProfileInt("SWiz","DivLinLen",m_SCALEWIZattributes.m_DivisionLineLegnth);
	WriteProfileInt("SWiz","DivLinW",m_SCALEWIZattributes.m_DivisionLineWidth);
	WriteProfileInt("SWiz","Divisions",m_SCALEWIZattributes.m_Divisions);
	WriteProfileInt("SWiz","DivColor",(int)m_SCALEWIZattributes.m_DivLineColor );
	WriteProfileInt("SWiz","SubLinLen",m_SCALEWIZattributes.m_SubdivisionLengnth);
	WriteProfileInt("SWiz","SubLinW",m_SCALEWIZattributes.m_SubDivisionLineWidth);
	WriteProfileInt("SWiz","SubDiv",m_SCALEWIZattributes.m_SubDivisions);
	WriteProfileInt("SWiz","SubDivColor",(int)m_SCALEWIZattributes.m_SubDivColor );
	WriteProfileInt("SWiz","FlatDist",m_SCALEWIZattributes.m_FlatDist);
	WriteProfileInt("SWiz","HoleRad",m_SCALEWIZattributes.m_HoleSize);
	WriteProfileInt("SWiz","HoleType",m_SCALEWIZattributes.m_HoleType);
	WriteProfileInt("SWiz","FontSize",m_SCALEWIZattributes.m_FontSize);
	WriteProfileInt("SWiz","Weight",m_SCALEWIZattributes.m_FontWeight);
	WriteProfileInt("SWiz","DistToTick",m_SCALEWIZattributes.m_DistToTick);
	WriteProfileInt("SWiz","TextColor",(int)m_SCALEWIZattributes.m_TextColor );
	WriteProfileInt("SWiz","TextBkColor",(int)m_SCALEWIZattributes.m_BkColor );
	WriteProfileString("SWiz","Font",m_SCALEWIZattributes.m_pFont);
}



void CFrontCadApp::WriteToLogFile(char * pS)
{
	if (m_pLogFile)
		fprintf(m_pLogFile, "%s\n", pS);
}

char* CFrontCadApp::IndentString(char* s, int Size, int Indent)
{
	int i;

	for (i = 0; i < Size; ++i)
		s[i] = 0;
	for (i = 0; i < Indent; ++i)
		s[i] = ' ';
    return s;
}

char* CFrontCadApp::ConvertCStringToChar(char* cpDest, CString& csSource)
{

	const size_t newsizew = (csSource.GetLength() + 1) * 2;
	size_t convertedCharsw = 0;
//	wcstombs_s(&convertedCharsw, cpDest, newsizew, csSource.GetString(), _TRUNCATE);
	return cpDest;
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetVersion();
	return TRUE;  
}

BOOL CFrontCadApp::IsPointInPoly(CPoint* pPolyPoint, int nPointCount, CPoint p)
{
	//------------------------------------------------
	// PointEnclosed
	//	This function determines if a point
	// is enclosed within a polygon.
	//
	// parameters:
	//	nP....point to test
	// Returns: TRUE if point inside
	//          FALSE if point is outside
	//------------------------------------------------
	struct FPoint {
		double x;
		double y;
		FPoint() { x = 0; y = 0; }
		FPoint(double X, double Y) { x = X; y = Y; }
	};

	int   i, j = nPointCount - 1;
	BOOL  Enclosed = FALSE;
	int Xintercept;
	FPoint* vert = new FPoint[nPointCount];
	FPoint nP = FPoint((double)p.x, (double)p.y);

	printf("Is Point  (x=%5d y=%5d) Enclosed In\n", p.x, p.y);
	for (i = 0; i < nPointCount; ++i)
	{
		vert[i] = FPoint(double(pPolyPoint[i].x), double(pPolyPoint[i].y));
		printf("vert[%d] (x=%5d y=%5d)\n", i, pPolyPoint[i].x, pPolyPoint[i].y);
	}
	for (i = 0; i < nPointCount; i++)
	{
		if (((vert[i].y < nP.y && vert[j].y >= nP.y)
			|| (vert[j].y < nP.y && vert[i].y >= nP.y))
			&& (vert[i].x <= nP.x || vert[j].x <= nP.x))
		{
			Xintercept = vert[i].x + ((nP.y - vert[i].y) * (vert[j].x - vert[i].x)) / (vert[j].y - vert[i].y);
			Enclosed ^= Xintercept < nP.x;
		}
		j = i;
	}
	delete[] vert;
	if(Enclosed) printf("   Yes\n");
	else
		printf("   No\n");	
	return Enclosed;
}

void CFrontCadApp::RotatePoint(CPoint& p, CPoint pivot, double angle)
{
	CPoint p1;
	double s = sin(-angle);
	double c = cos(-angle);
	double newX, newY;
	double X, Y;

	p1 = p - pivot;
	X = p1.x;
	Y = p1.y;
	newX = X * c - Y * s;
	newY = X * s + Y * c;
	p.x = int(newX) + pivot.x;
	p.y = int(newY) + pivot.y;
}

void CFrontCadApp::UpdateDimAttributes(CUtilView* pUV)
{
	char* s = new char[256];
	//------------------------------
	// Line Attributes
	//------------------------------
	m_DimAttrib.m_Color = pUV->m_Static_LineColor.GetColor();
	m_DimAttrib.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
	//----------------------------------
	// Text Attributes
	//-----------------------------------
	m_DimAttrib.m_TextAtrib.m_Angle = pUV->m_Edit_TextAngle.GetValue();
	m_DimAttrib.m_TextAtrib.m_FontHeight = pUV->m_Edit_FontHeight.GetValue();
	m_DimAttrib.m_TextAtrib.m_FontWidth = pUV->m_Edit_FontWidth.GetValue();
	m_DimAttrib.m_TextAtrib.m_Transparent = pUV->m_Check_TransparentFont.GetCheck();
	m_DimAttrib.m_TextAtrib.m_Color = pUV->m_Static_TextColor.GetColor();
	m_DimAttrib.m_TextAtrib.m_BkColor = pUV->m_Static_BkGrndColor.GetColor();
	m_DimAttrib.m_TextAtrib.m_Weight = pUV->m_Combo_FontWeight.GetFontWeight();
	pUV->m_Button_Font.GetWindowText(s, 255);
	m_DimAttrib.m_TextAtrib.SetFontName(s);
}

void CFrontCadApp::UpdateLineAttributes(CUtilView* pUV)
{
	m_LineAttrib.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
	m_LineAttrib.m_LineColor = pUV->m_Static_LineColor.GetColor();
}

void CFrontCadApp::UpdateRectAttributes(CUtilView* pUV)
{
	m_RectAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
	m_RectAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
	m_RectAttributes.m_FillColor = pUV->m_Static_FillColor.GetColor();
	m_RectAttributes.m_bTransparentFill = pUV->m_Check_TransparentFill.GetCheck();
}

void CFrontCadApp::UpdateCircleAttributes(CUtilView* pUV)
{
	m_CircleAttributs.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
	m_CircleAttributs.m_LineColor = pUV->m_Static_LineColor.GetColor();
	m_CircleAttributs.m_FillColor = pUV->m_Static_FillColor.GetColor();
	m_CircleAttributs.m_bTransparent = pUV->m_Check_TransparentFill.GetCheck();
}

void CFrontCadApp::UpdateEllipseAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_EllipseAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_EllipseAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
		m_EllipseAttributes.m_FillColor = pUV->m_Static_FillColor.GetColor();
		m_EllipseAttributes.m_Transparent = pUV->m_Check_TransparentFill.GetCheck();
	}
}

void CFrontCadApp::UpdatePolyAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_PolyAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_PolyAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
		m_PolyAttributes.m_FillColor = pUV->m_Static_FillColor.GetColor();
		m_PolyAttributes.m_Transparent = pUV->m_Check_TransparentFill.GetCheck();
	}
}

void CFrontCadApp::UpdateArcAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_ArcAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_ArcAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
	}
}

void CFrontCadApp::UpdateHoleRoundAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_HoleRoundAttributes.m_Radius = pUV->m_Edit_HoleRadius.GetValue();
		m_HoleRoundAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_HoleRoundAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
	}
}

void CFrontCadApp::UpdateHoleRnd2FlatAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_HoleRnd2FlatAttributes.m_Radius = pUV->m_Edit_HoleRadius.GetValue();
		m_HoleRnd2FlatAttributes.m_FlatDist = pUV->m_Edit_FlatToCenterDist.GetValue();
		m_HoleRnd2FlatAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_HoleRnd2FlatAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
	}
}

void CFrontCadApp::UpdateHoleRnd1FlatAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_HoleRnd1FlatAttributes.m_Radius = pUV->m_Edit_HoleRadius.GetValue();
		m_HoleRnd1FlatAttributes.m_FlatDist = pUV->m_Edit_FlatToCenterDist.GetValue();
		m_HoleRnd1FlatAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_HoleRnd1FlatAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
	}
}

void CFrontCadApp::UpdateRectHoleAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_RectHoleAttributes.m_W = pUV->m_Edit_X2.GetValue();
		m_RectHoleAttributes.m_H = pUV->m_Edit_Y2.GetValue();
		m_RectHoleAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_RectHoleAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
	}
}

void CFrontCadApp::UpdateTextAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		char* s = new char[256];
		//------------------------------
		// Line Attributes
		//------------------------------
		m_TextAttributes.m_Color = pUV->m_Static_TextColor.GetColor();
		m_TextAttributes.m_BkColor = pUV->m_Static_BkGrndColor.GetColor();
		m_TextAttributes.m_Angle = pUV->m_Edit_TextAngle.GetValue();
		m_TextAttributes.m_FontHeight = pUV->m_Edit_FontHeight.GetValue();
		m_TextAttributes.m_FontWidth = pUV->m_Edit_FontWidth.GetValue();
		m_TextAttributes.m_Transparent = pUV->m_Check_TransparentFont.GetCheck();
		m_TextAttributes.m_Weight = pUV->m_Combo_FontWeight.GetFontWeight();
		pUV->m_Button_Font.GetWindowText(s, 255);
		m_TextAttributes.SetFontName(s);
		delete[] s;
	}
}

void CFrontCadApp::UpdateScaleWizAttributes(CUtilView* pUV)
{
}

void CFrontCadApp::UpdateArrowAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_ArrowAttrib.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_ArrowAttrib.m_LineColor = pUV->m_Static_LineColor.GetColor();
		m_ArrowAttrib.m_FillColor = pUV->m_Static_FillColor.GetColor();
		m_ArrowAttrib.m_bTransparent = pUV->m_Check_TransparentFill.GetCheck();
		m_ArrowAttrib.m_Len = pUV->m_Edit_X3.GetValue();
		m_ArrowAttrib.m_ArrowWidth = pUV->m_Edit_Y3.GetValue();
	}
}

void CFrontCadApp::UpdateRndRectAttributes(CUtilView* pUV)
{
	if(pUV)
	{
		m_RndRectAttributes.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_RndRectAttributes.m_LineColor = pUV->m_Static_LineColor.GetColor();
		m_RndRectAttributes.m_FillColor = pUV->m_Static_FillColor.GetColor();
		m_RndRectAttributes.m_bTransparent = pUV->m_Check_TransparentFill.GetCheck();
		m_RndRectAttributes.m_P3.x = pUV->m_Edit_X3.GetValue();
		m_RndRectAttributes.m_P3.y = pUV->m_Edit_Y3.GetValue();
	}
}

void CFrontCadApp::UpdateLineAttrib(CUtilView* pUV)
{
	if(pUV)
	{
		m_LineAttrib.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_LineAttrib.m_LineColor = pUV->m_Static_LineColor.GetColor();
	}
}

void CFrontCadApp::UpdateOriginAttrib(CUtilView* pUV)
{
	if(pUV)
	{
		m_OriginAttrib.m_LineWidth = pUV->m_Edit_LineThickness.GetValue();
		m_OriginAttrib.m_Color = pUV->m_Static_LineColor.GetColor();
	}
}


void CAboutDlg::SetVersion()
{
	char* s = new char[256];
	static const char* pVersion = "Simple and Down Right Crude Cad\nFor Designing Front Panel\nArtwork\nVersion 1.6.0.1";
	static const char* pBuildDate = "Build Date Sept 15, 2025";
	static const char* pCopyright = "Copyright (c) 2015, 2025";

	sprintf_s(s, 256, "%s\n%s\n%s",
		pVersion,
		pBuildDate,
		pCopyright
	);
	m_Statoc_Versopm.SetWindowTextA((const char*)s);
	delete[] s;
}
