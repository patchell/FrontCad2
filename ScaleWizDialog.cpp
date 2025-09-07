// ScaleWizDialog.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////
// CScaleWizDialog dialog


CScaleWizDialog::CScaleWizDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleWizDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScaleWizDialog)
	//}}AFX_DATA_INIT
	m_Pi = 4.0 * atan(1);
	int i;
	for(i=0;i<SCALE_LABELS_SIZE ;++i)
	{
		m_atrb.m_pLabels[i] = new char[SCALE_LABELS_STRING_SIZE];
		(m_atrb.m_pLabels[i])[0] = 0;
	}
	m_PrevLabel = 0;
	m_RotateTextFlag = 0;
	m_atrb.m_pFont = new char[LF_FACESIZE];
	m_RotateTextFlag = 0;
}

CScaleWizDialog::~CScaleWizDialog()
{
}


void CScaleWizDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScaleWizDialog)
	DDX_Control(pDX, IDC_EDIT_SCALEWIZ_YREF, m_Edit_YRef);
	DDX_Control(pDX, IDC_EDIT_SCALEWIZ_XREF, m_Edit_XRef);
	DDX_Control(pDX, IDC_COMBO_SCALEWIZ_LIBSEL, m_Combo_SelLib);
	DDX_Control(pDX, IDC_EDIT_WIZ_PARTNAME, m_Edit_PartName);
	DDX_Control(pDX, IDC_TAB_SCALEWIZ, m_Tab_Settings);
	DDX_Control(pDX, IDC_STATIC_SCALEWIZ_PREVIEW, m_Static_Preview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CScaleWizDialog, CDialog)
	//{{AFX_MSG_MAP(CScaleWizDialog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SCALEWIZ, OnSelchangeTabScalewiz)
	ON_BN_CLICKED(IDC_BUTTON_WIZ_SAVETOLIB, OnButtonWizSavetolib)
	ON_BN_CLICKED(IDC_BUTTON_SCALEWIZ_NEWLIB, OnButtonScalewizNewlib)
	ON_CBN_SELCHANGE(IDC_COMBO_SCALEWIZ_LIBSEL, OnSelchangeComboScalewizLibsel)
	ON_BN_CLICKED(IDC_BUTTON_SCALEWIZ_SETREF, OnButtonScalewizSetref)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TAB1_MESSAGE,OnTab1Message)
	ON_MESSAGE(WM_TAB2_MESSAGE,OnTab2Message)
	ON_MESSAGE(WM_TAB3_MESSAGE,OnTab3Message)
	ON_MESSAGE(WM_TAB2_LABELSEL,OnLabelSelScrollBar)
END_MESSAGE_MAP()

////////////////////////////////////////////////////
// CScaleWizDialog message handlers

BOOL CScaleWizDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CLibFormView *pLVF = ((CFrontCadApp *)AfxGetApp())->GetLibView();
	CCadLibrary *pLib = pLVF->GetLibraryList();
	if(pLib)
	{
		while(pLib)
		{
			this->m_Combo_SelLib.AddString(pLib->GetName());
			pLib = pLib->GetNext();
		}
		pLib = pLVF->GetCurrentLibrary();
		m_Combo_SelLib.SetSelectionByName(pLib->GetName());
	}
	m_Edit_XRef.SetWindowText("0");
	m_Edit_YRef.SetWindowText("0");
	char *s = new char[256];
	m_Tab_Settings.InsertItem(0, _T("Scale Settup"));
	m_Tab_Settings.InsertItem(1, _T("Scale Labels"));
	m_Tab_Settings.InsertItem(2, _T("Tab Three"));

	m_Tab_Settings.Init();

	CScaleWizTabOne *pWTO = (CScaleWizTabOne *)m_Tab_Settings.m_tabPages[0];

	pWTO->m_Edit_ArcLineWidth.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_ARCLINEWIDTH);
	pWTO->m_Edit_ArcLineWidth.SetDecimalPlaces(3);
	pWTO->m_Edit_ArcLineWidth.SetValue(m_atrb.m_ArcLineWidth);

	pWTO->m_Edit_ArcRadius.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_ARCRADIUS);
	pWTO->m_Edit_ArcRadius.SetDecimalPlaces(3);
	pWTO->m_Edit_ArcRadius.SetValue(m_atrb.m_ArcRadius);

	pWTO->m_Edit_DivisionLineWidth.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_DIVLINEWIDTH);
	pWTO->m_Edit_DivisionLineWidth.SetDecimalPlaces(3);
	pWTO->m_Edit_DivisionLineWidth.SetValue(m_atrb.m_DivisionLineWidth);

	pWTO->m_Edit_Divisions.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_DIVISIONS);
	pWTO->m_Edit_Divisions.SetDecimalPlaces(0);
	pWTO->m_Edit_Divisions.SetValue(m_atrb.m_Divisions);

	pWTO->m_Edit_EndAngle.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_ARCEND);
	pWTO->m_Edit_EndAngle.SetDecimalPlaces(1);
	pWTO->m_Edit_EndAngle.SetValue(m_atrb.m_ArcEnd);

	pWTO->m_Edit_StartAngle.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_ARCSTART);
	pWTO->m_Edit_StartAngle.SetDecimalPlaces(1);
	pWTO->m_Edit_StartAngle.SetValue(m_atrb.m_ArcStart);

	pWTO->m_Edit_DivLineLen.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_DIVLINELEN);
	pWTO->m_Edit_DivLineLen.SetDecimalPlaces(3);
	pWTO->m_Edit_DivLineLen.SetValue(m_atrb.m_DivisionLineLegnth);

	pWTO->m_Edit_HoleRadius.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_HOLERADIUS);
	pWTO->m_Edit_HoleRadius.SetDecimalPlaces(3);
	pWTO->m_Edit_HoleRadius.SetValue(m_atrb.m_HoleSize);

	pWTO->m_Edit_FlatDist.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_FLATDIST);
	pWTO->m_Edit_FlatDist.SetDecimalPlaces(3);
	pWTO->m_Edit_FlatDist.SetValue(m_atrb.m_FlatDist);

	pWTO->m_Combo_HoleType.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_HOLETYPE);
	pWTO->m_Combo_HoleType.Init();

	pWTO->m_Edit_Subdivisions.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_SUBDIVISIONS);
	pWTO->m_Edit_Subdivisions.SetDecimalPlaces(0);
	pWTO->m_Edit_Subdivisions.SetValue(m_atrb.m_SubDivisions);

	pWTO->m_Edit_SubLineLen.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_SUBDIVLINELEN);
	pWTO->m_Edit_SubLineLen.SetDecimalPlaces(3);
	pWTO->m_Edit_SubLineLen.SetValue(m_atrb.m_SubdivisionLengnth);

	pWTO->m_Edit_SubLineWidth.SetupMessaging(this,WM_TAB1_MESSAGE,TAB1_SUBDIVLINWIDTH);
	pWTO->m_Edit_SubLineWidth.SetDecimalPlaces(3);
	pWTO->m_Edit_SubLineWidth.SetValue(m_atrb.m_SubDivisionLineWidth);

	pWTO->m_Static_ArcColor.SetColor(m_atrb.m_ArcColor);
	pWTO->m_Static_DivColor.SetColor(m_atrb.m_DivLineColor);
	pWTO->m_Static_SubColor.SetColor(m_atrb.m_SubDivColor);

	CCadLibObject *pLO;

	pLO = CreateLibObject("POTSCALE");
	m_Static_Preview.m_pLibObj = pLO;
	m_Static_Preview.Invalidate();

	CWizTab2Dialog *pWT2 = (CWizTab2Dialog *)m_Tab_Settings.m_tabPages[1];
	
	pWT2->m_CheckBox_RotateText.SetupMessaging(this,WM_TAB2_MESSAGE,TAB2_ROTATE_TEXT);

	pWT2->m_SB_LableSelect.SetActionMessage(this,WM_TAB2_LABELSEL);
	pWT2->m_SB_LableSelect.SetScrollRange(0,m_atrb.m_Divisions);
	pWT2->m_Edit_Label.SetWindowText(m_atrb.m_pLabels[0]);
	pWT2->m_SB_LableSelect.SetScrollPos(0);
	pWT2->m_Edit_Label.SetupMessaging(this,WM_TAB2_MESSAGE,TAB2_LABELTEXT);

	pWT2->m_Edit_FontSize.SetupMessaging(this,WM_TAB2_MESSAGE,TAB2_FONTSIZE);
	pWT2->m_Edit_FontSize.SetDecimalPlaces(3);
	pWT2->m_Edit_FontSize.SetValue(m_atrb.m_FontSize);

	pWT2->m_Edit_DistToTick.SetupMessaging(this,WM_TAB2_MESSAGE,TAB2_DISTTOTICK);
	pWT2->m_Edit_DistToTick.SetDecimalPlaces(3);
	pWT2->m_Edit_DistToTick.SetValue(m_atrb.m_DistToTick);

	pWT2->m_ComboBox_FontWeight.Init();
	pWT2->m_ComboBox_FontWeight.SetupMessaging(this,WM_TAB2_MESSAGE,TAB2_FONTWEIGHT);

	pWT2->m_Static_BkColor.SetColor(m_atrb.m_BkColor);
	pWT2->m_Static_FgColor.SetColor(m_atrb.m_TextColor);

	delete[] s;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CScaleWizDialog::OnOK() 
{
	CWnd *wC;
//	char *s = new char[256];

	//locate control that has gocus
	wC = GetFocus();
	// Get the ID of that control
	int id = wC->GetDlgCtrlID();
	switch(id)							//parse the id
	{
		case IDOK:
			CDialog::OnOK();
			break;
		default:
			wC = GetNextDlgTabItem(wC);	//reset the focus
			wC->SetFocus();
			break;
	}
//	delete[] s;
}

void CScaleWizDialog::OnSelchangeTabScalewiz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

LRESULT CScaleWizDialog::OnTab1Message(WPARAM wP, LPARAM lP)
{
	switch(wP)
	{
		case TAB1_ARCSTART:
			m_atrb.m_ArcStart = lP;
			break;
		case TAB1_ARCEND:
			m_atrb.m_ArcEnd = lP;
			break;
		case TAB1_DIVISIONS:
			{
				int i;
				char *s = new char[256];
				for(i= m_atrb.m_Divisions;i<=lP;++i)
				{
					sprintf_s(s,256,"%d",i);
					strcpy_s(m_atrb.m_pLabels[i], SCALE_LABELS_STRING_SIZE,s);
				}
				delete[] s;
				m_atrb.m_Divisions = lP;
				CWizTab2Dialog *pWT2 = (CWizTab2Dialog *)m_Tab_Settings.m_tabPages[1];
				pWT2->m_SB_LableSelect.SetScrollRange(0,m_atrb.m_Divisions);
			}
			break;
		case TAB1_ARCLINEWIDTH:
			m_atrb.m_ArcLineWidth = lP;
			break;
		case TAB1_ARCRADIUS:
			m_atrb.m_ArcRadius = lP;
			break;
		case TAB1_DIVLINEWIDTH:
			m_atrb.m_DivisionLineWidth = lP;
			break;
		case TAB1_DIVLINELEN:
			m_atrb.m_DivisionLineLegnth = lP;
			break;
		case TAB1_HOLERADIUS:
			m_atrb.m_HoleSize = lP;
			break;
		case TAB1_FLATDIST:
			m_atrb.m_FlatDist = lP;
			break;
		case TAB1_HOLETYPE:
			m_atrb.m_HoleType = lP;
			break;
		case TAB1_SUBDIVISIONS:
			m_atrb.m_SubDivisions = lP;
			break;
		case TAB1_SUBDIVLINELEN:
			m_atrb.m_SubdivisionLengnth = lP;
			break;
		case TAB1_SUBDIVLINWIDTH:
			m_atrb.m_SubDivisionLineWidth = lP;
			break;
		case TAB1_DIVCOLOR:
			m_atrb.m_DivLineColor = lP;
			break;
		case TAB1_SUBCOLOR:
			m_atrb.m_SubDivColor = lP;
			break;
		case TAB1_ARCCOLOR:
			m_atrb.m_ArcColor = lP;
			break;
	}
	delete m_Static_Preview.m_pLibObj;
	m_Static_Preview.m_pLibObj = 0;
	char *s = new char[256];
	this->m_Edit_PartName.GetWindowText(s,255);
	m_Static_Preview.m_pLibObj = CreateLibObject(s);
	delete[] s;
	m_Static_Preview.Invalidate();
	return 0;
}

LRESULT CScaleWizDialog::OnTab2Message(WPARAM wP, LPARAM lP)
{
	switch(wP)
	{
		case TAB2_FONTSIZE:
			m_atrb.m_FontSize = lP;
			break;
		case TAB2_FONTWEIGHT:
			m_atrb.m_FontWeight = lP;
			break;
		case TAB2_LABELTEXT:
			{
				CWizTab2Dialog *pDlg = (CWizTab2Dialog *) this->m_Tab_Settings.m_tabPages[1];
				char *s = new char[256];
				pDlg->m_Edit_Label.GetWindowText(s,255);
				strcpy_s(m_atrb.m_pLabels[m_PrevLabel], SCALE_LABELS_STRING_SIZE,s);
				int index = pDlg->m_SB_LableSelect.GetScrollPos();
				pDlg->m_SB_LableSelect.SetScrollPos(index+1);
				pDlg->m_Edit_Label.SetFocus();
				pDlg->m_Edit_Label.SetSel(0xffff0000);
				delete[] s;
			}
			break;
		case TAB2_FONT:
			{
				CWizTab2Dialog *pDlg = (CWizTab2Dialog *) this->m_Tab_Settings.m_tabPages[1];
				char *s = new char[LF_FACESIZE];
				pDlg->m_Static_Font.GetWindowText(s, LF_FACESIZE);
				strcpy_s(m_atrb.m_pFont, LF_FACESIZE,s);
				delete[] s;
			}
			break;
		case TAB2_TEXTCOLOR:
			m_atrb.m_TextColor = lP;
			break;
		case TAB2_TEXTBKCOLOR:
			m_atrb.m_BkColor = lP;
			break;
		case TAB2_DISTTOTICK:
			m_atrb.m_DistToTick = lP;
			break;
		case TAB2_ROTATE_TEXT:
			m_RotateTextFlag = lP;
			break;
	}
	delete m_Static_Preview.m_pLibObj;
	m_Static_Preview.m_pLibObj = 0;
	char *s = new char[256];
	this->m_Edit_PartName.GetWindowText(s,255);
	m_Static_Preview.m_pLibObj = CreateLibObject(s);
	delete[] s;
	m_Static_Preview.Invalidate();
	return 0;
}

LRESULT CScaleWizDialog::OnTab3Message(WPARAM wP, LPARAM lP)
{
	return 0;
}

CPoint CScaleWizDialog::CalcXYonArc(int Radius, int Angle)
{
	CPoint rP;

	rP.x = int((double)Radius * cos((m_Pi/180.0)  * double(Angle)) );
	rP.y = -int((double)Radius * sin((m_Pi/180.0) * double(Angle)) );
	return rP;
}

CPoint CScaleWizDialog::CalcXYonArc(int Radius, double Angle)
{
	CPoint rP;

	rP.x = int((double)Radius * cos((m_Pi/180.0)  * (Angle)) );
	rP.y = -int((double)Radius * sin((m_Pi/180.0) * (Angle)) );
	return rP;
}

CCadLibObject *CScaleWizDialog::CreateLibObject(const char *pName)
{
	CCadLibObject *pLibObj;
	CCadArcCentered *pAC;
	CCadLine *pCL;
	CCadText *pCT;

	CPoint p1,p2;
	int i;
	double Angle;

	this->m_Edit_PartName.SetWindowText(pName);
	pLibObj = new CCadLibObject;
	char *s = new char[256];
	pLibObj->SetName(pName);
	m_Edit_XRef.GetWindowText(s,255);
	pLibObj->GetRef().x = atoi(s);
	m_Edit_YRef.GetWindowText(s,255);
	pLibObj->GetRef().y = atoi(s);
	switch(m_atrb.m_HoleType)
	{
		case OBJECT_TYPE_HOLEROUND:
			{
				CCadHoleRound *pHR;
				pHR = new CCadHoleRound;
				pHR->SetP1(CPoint(0,0)); 
				pHR->SetLineColor(RGB(0,0,0));
				pHR->SetRadius(m_atrb.m_HoleSize);
				pHR->SetLineWidth(10);
				pLibObj->AddObjectToEnd(pHR);
			}
			break;
		case OBJECT_TYPE_HOLERECT:
			{
				CCadRectHole *pHR;
				pHR = new CCadRectHole;
				pHR->SetP1(CPoint(0, 0));
				pHR->SetLineColor(RGB(0,0,0));
				pHR->SetLineWidth(1);
				pLibObj->AddObjectToEnd(pHR);
			}
			break;
		case OBJECT_TYPE_HOLERND1FLAT:
			{
				CCadHoleRnd1Flat *pHR;
				pHR = new CCadHoleRnd1Flat;
				pHR->SetP1(CPoint(0, 0));
				pHR->SetFlatDist(m_atrb.m_FlatDist);
				pHR->SetLineColor(RGB(0,0,0));
				pHR->SetRadius(m_atrb.m_HoleSize);
				pHR->SetLineWidth(1);
				pLibObj->AddObjectToEnd(pHR);
			}
			break;
		case OBJECT_TYPE_HOLERND2FLAT:
			{
				CCadHoleRnd2Flat *pHR;
				pHR = new CCadHoleRnd2Flat;
				pHR->SetP1(CPoint(0, 0));
				pHR->SetLineColor(RGB(0,0,0));
				pHR->SetFlatDist(m_atrb.m_FlatDist);
				pHR->SetRadius(m_atrb.m_HoleSize);
				pHR->SetLineWidth(1);
				pLibObj->AddObjectToEnd(pHR);
			}
			break;
	}

	//-----------------------------------
	// Place ticks around arc
	//-----------------------------------
	if(m_atrb.m_ArcStart < m_atrb.m_ArcEnd)
		Angle = double(m_atrb.m_ArcEnd - m_atrb.m_ArcStart);
	else
		Angle = double(m_atrb.m_ArcEnd + (3600 - m_atrb.m_ArcStart));
	Angle /= (double)m_atrb.m_Divisions;
	double StrtAng = double(m_atrb.m_ArcEnd);
	double SubAngle;
	if(m_atrb.m_ArcStart < m_atrb.m_ArcEnd)
		SubAngle = double(m_atrb.m_ArcEnd - m_atrb.m_ArcStart)/double(m_atrb.m_Divisions * m_atrb.m_SubDivisions);
	else
		SubAngle = double(m_atrb.m_ArcEnd + 3600 - m_atrb.m_ArcStart)/double(m_atrb.m_Divisions * m_atrb.m_SubDivisions);

	for(i=0;i<(m_atrb.m_Divisions+1);++i,StrtAng-=Angle)
	{
		p1 = CalcXYonArc(m_atrb.m_ArcRadius,StrtAng/10.0);
		p2 = CalcXYonArc(m_atrb.m_ArcRadius+m_atrb.m_DivisionLineLegnth,StrtAng/10.0);
		pCL = new CCadLine;
		pCL->SetP1(p1);
		pCL->SetP2(p2);
		pCL->SetLineWidth(m_atrb.m_DivisionLineWidth);
		pCL->SetLineColor(m_atrb.m_DivLineColor);
		pLibObj->AddObjectToEnd(pCL);
		//--------------------------------
		// Ok, now we will do the sub
		// divistions
		//--------------------------------
		double SStartAng = double(StrtAng) - SubAngle;
		if(i< m_atrb.m_Divisions)
		{
			for(int j=0;j< (m_atrb.m_SubDivisions-1);++j)
			{
				p1 = CalcXYonArc(m_atrb.m_ArcRadius,SStartAng/10.0);
				p2 = CalcXYonArc(m_atrb.m_ArcRadius+m_atrb.m_SubdivisionLengnth,SStartAng/10.0);
				pCL = new CCadLine;
				pCL->SetP1(p1);
				pCL->SetP2(p2);
				pCL->SetLineWidth(m_atrb.m_SubDivisionLineWidth);
				pCL->SetLineColor(m_atrb.m_SubDivColor);
				pLibObj->AddObjectToEnd(pCL);
				SStartAng -= SubAngle;
			}
		}
	}
	//-----------------------------------
	// we need to find the center of the
	// text as we place it around the
	// circle.
	//-----------------------------------
	StrtAng = m_atrb.m_ArcEnd;
	CWnd *pW = this->GetParent();
	CDC *pDC = pW->GetDC();
	CFont fnt,*pOldFont;
	fnt.CreateFont(m_atrb.m_FontSize/10,0,0,0,
			m_atrb.m_FontWeight,0,0,0,DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
			CLIP_CHARACTER_PRECIS,PROOF_QUALITY,DEFAULT_PITCH,
			m_atrb.m_pFont);
	CSize rSize;
	pOldFont = pDC->SelectObject(&fnt);
	for(i=0;i<m_atrb.m_Divisions+1;++i,StrtAng-=Angle)
	{
		rSize = pDC->GetTextExtent(m_atrb.m_pLabels[i],strlen(m_atrb.m_pLabels[i]));
		rSize.cx *= 5;
		rSize.cy *= 5;
		CRect rect;
		p2 = CalcXYonArc(m_atrb.m_DistToTick + m_atrb.m_ArcRadius + m_atrb.m_DivisionLineLegnth,StrtAng/10);
		rect.SetRect(p2.x,p2.y,p2.x+rSize.cx,p2.y+rSize.cy);
		CPoint p3 = CalcTextShiftonRotation(p2,rect.CenterPoint(),StrtAng/10);
		pCT = new CCadText;
		pCT->SetColor(m_atrb.m_TextColor);
		pCT->SetBkColor(m_atrb.m_BkColor);
		pCT->SetFontHeight(m_atrb.m_FontSize);
		pCT->SetFontWidth(0);
		pCT->SetFormat(0);
		pCT->SetWeight(m_atrb.m_FontWeight);
		pCT->SetFontName(m_atrb.m_pFont);
		pCT->SetText(m_atrb.m_pLabels[i]);
		if(m_RotateTextFlag > 0)
		{
			pCT->SetP1(p2 + p3);
			pCT->SetAngle(int(StrtAng)-900);
		}
		else
		{
			pCT->SetP1(p2 - CPoint(rSize.cx, rSize.cy));
			pCT->SetAngle(0);
		}
		pLibObj->AddObjectToEnd(pCT);
	}
	pDC->SelectObject(pOldFont);

	pAC = new CCadArcCentered;
	pAC->SetP1(CPoint(0, 0));
	i = m_atrb.m_ArcRadius;
	pAC->SetP2(CPoint(i, i));
	pAC->SetStartPoint(CalcXYonArc(m_atrb.m_ArcRadius*2,m_atrb.m_ArcStart/10));
	pAC->SetEndPoint(CalcXYonArc(m_atrb.m_ArcRadius*2,m_atrb.m_ArcEnd/10));
	pAC->SetLineWidth(m_atrb.m_ArcLineWidth);
	pAC->SetLineColor(m_atrb.m_ArcColor);
	pLibObj->AddObjectToEnd(pAC);
	return pLibObj;
}


LRESULT CScaleWizDialog::OnLabelSelScrollBar(WPARAM Item, LPARAM lp)
{
	CWizTab2Dialog *pDlg = (CWizTab2Dialog *) this->m_Tab_Settings.m_tabPages[1];
	char *s = new char[256];
	pDlg->m_Edit_Label.GetWindowText(s,255);
	strcpy_s(m_atrb.m_pLabels[m_PrevLabel], SCALE_LABELS_STRING_SIZE,s);
	pDlg->m_Edit_Label.SetWindowText(this->m_atrb.m_pLabels[Item]);
	m_PrevLabel = Item;
	delete[] s;
	return 0;
}

void CScaleWizDialog::OnButtonWizSavetolib() 
{
	CLibFormView *pLV = ((CFrontCadApp *)AfxGetApp())->GetLibView();

	CDialogChoose dlg;
	int id;

	int cursel = m_Combo_SelLib.GetCurSel();
	if(cursel < 0)
	{
		id = dlg.DoModal();
		switch(id)
		{
			case IDC_BUTTON_CHOOSE_CREATE:
				OnButtonScalewizNewlib();
				cursel = m_Combo_SelLib.GetCurSel();
				break;
			case IDC_BUTTON_CHOOSE_LOADLIB:
				pLV->OnButtonAddlibrary();
				{
					CCadLibrary *pLib = pLV->GetLibraryList();
					if(pLib)
					{
						while(pLib)
						{
							m_Combo_SelLib.AddString(pLib->GetName());
							pLib = pLib->GetNext();
						}
						pLib = pLV->GetCurrentLibrary();
						m_Combo_SelLib.SetSelectionByName(pLib->GetName());
					}
				}
				cursel = m_Combo_SelLib.GetCurSel();
				break;
		}
	}
	if(cursel >= 0)
	{
		CLibFormView *pLFV = ((CFrontCadApp *)AfxGetApp())->GetLibView();
		CCadLibObject *pLib = this->m_Static_Preview.m_pLibObj;
		CCadLibObject *pLP = new CCadLibObject(pLib->GetHead());
		char *libname = (char *)m_Combo_SelLib.GetItemDataPtr(cursel);
		char *s = new char[256];
		this->m_Edit_PartName.GetWindowText(s,255);
		pLP->SetName(s);
		pLFV->AddPartToCurLib(pLP);
	}
}

void CScaleWizDialog::OnButtonScalewizNewlib() 
{
	CNewLibDialog dlg;

	int id;
	if((id = dlg.DoModal()) == IDOK)
	{
		CLibFormView *pLV = ((CFrontCadApp *)AfxGetApp())->GetLibView();
		CCadLibrary *pLib = new CCadLibrary;
		pLib->SetName(dlg.m_LibName);
		pLV->AddLibrary(pLib);
		pLV->m_Combo_SelLIb.SetSelectionByName(pLib->GetName());
		int sel = m_Combo_SelLib.AddString(pLib->GetName());
		m_Combo_SelLib.SetCurSel(sel);

	}
}

void CScaleWizDialog::OnSelchangeComboScalewizLibsel() 
{
	CLibFormView *pLFV = ((CFrontCadApp *)AfxGetApp())->GetLibView();
	int sel = m_Combo_SelLib.GetCurSel();
	char *s = new char[256];
	this->m_Combo_SelLib.GetLBText(sel,s);
	pLFV->m_Combo_SelLIb.SetSelectionByName(s);
	CCadLibrary *pL = pLFV->GetCurrentLibrary();
	pLFV->m_Combo_SelPart.SetLibraryFile(pL);
	pLFV->m_Combo_SelPart.SetCurSel(0);
	delete[] s;
}

void CScaleWizDialog::OnButtonScalewizSetref() 
{
}



CPoint CScaleWizDialog::CalcTextShiftonRotation(CPoint p1, CPoint Center, double angle)
{
	CPoint rP;
	double r2;
	double dx = double(p1.x - Center.x);
	double dy = double(p1.y - Center.y);

	r2 = sqrt(dx*dx+dy*dy);
	rP.x = -int(r2 * cos((m_Pi/180.0) *(angle - 90.0)));
	rP.y = int(r2 * sin((m_Pi/180.0) *(angle - 90.0)));
//	if((angle - 90.0) < 0.0)
//		rP += CPoint(int(dx),int(dy));
//	else
//		rP += CPoint(int(dx),-int(dy));
	return rP;

}
