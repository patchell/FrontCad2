#pragma once

//--------------------------------------------
// Scale Wizard Attributes Class
//--------------------------------------------

constexpr auto SCALE_LABELS_SIZE = 40;
constexpr auto SCALE_LABELS_STRING_SIZE = 32;

struct SPotScaleWizAttributes
{
	int m_ArcStart;
	int m_ArcEnd;
	int m_ArcLineWidth;
	int m_ArcRadius;
	COLORREF m_ArcColor;
	int m_Divisions;
	int m_DivisionLineWidth;
	int m_DivisionLineLegnth;
	COLORREF m_DivLineColor;
	int m_SubDivisions;
	int m_SubDivisionLineWidth;
	int m_SubdivisionLengnth;
	COLORREF m_SubDivColor;
	int m_HoleSize;
	int m_HoleType;
	int m_FlatDist;
	CPoint m_Ref;		//reference point for scale object
	//scale labels
	int m_FontSize;
	int m_FontWeight;
	int m_DistToTick;
	COLORREF m_TextColor;
	COLORREF m_BkColor;
	char* m_pFont;		//name of font.
	char* m_pLabels[SCALE_LABELS_SIZE];
	SPotScaleWizAttributes() {
		m_ArcStart = 135;
		m_ArcEnd = 45;
		m_ArcLineWidth = 2;
		m_ArcRadius = 100;
		m_ArcColor = RGB(0, 0, 0);
		m_Divisions = 10;
		m_DivisionLineWidth = 2;
		m_DivisionLineLegnth = 10;
		m_DivLineColor = RGB(0, 0, 0);
		m_SubDivisions = 5;
		m_SubDivisionLineWidth = 1;
		m_SubdivisionLengnth = 5;
		m_SubDivColor = RGB(0, 0, 0);
		m_HoleSize = 5;
		m_HoleType = 0;
		m_FlatDist = 7;
		m_Ref = CPoint(0, 0);
		m_FontSize = 12;
		m_FontWeight = 400;
		m_DistToTick = 15;
		m_TextColor = RGB(0, 0, 0);
		m_BkColor = RGB(255, 255, 255);
		m_pFont = new char[SCALE_LABELS_STRING_SIZE];
		sprintf_s(m_pFont, SCALE_LABELS_STRING_SIZE, "%s", "Arial");
		for (int i = 0; i < SCALE_LABELS_SIZE; i++) {
			m_pLabels[i] = new char[SCALE_LABELS_STRING_SIZE];
			sprintf_s(m_pLabels[i], SCALE_LABELS_STRING_SIZE, "%4.2f", double(i * 1.0));
		}
	}
	~SPotScaleWizAttributes()
	{
		if (m_pFont)
			delete[] m_pFont;
		for (int i = 0; i < SCALE_LABELS_SIZE; i++) {
			if (m_pLabels[i])
				delete[] m_pLabels[i];
		}
	}
	void CopyTo(SPotScaleWizAttributes* pAttrDest);
	void CopyFrom(SPotScaleWizAttributes* pAttrSource);
	void Save(FILE* pO, int Indent, SPotScaleWizAttributes* pAttrSource);
	Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CFileParser* pParser, SPotScaleWizAttributes* pAttrSource);
};


