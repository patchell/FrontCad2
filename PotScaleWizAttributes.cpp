#include "stdafx.h"

void SPotScaleWizAttributes::CopyTo(SPotScaleWizAttributes* pAttrDest)
{
	if (pAttrDest) {
		pAttrDest->m_ArcStart = m_ArcStart;
		pAttrDest->m_ArcEnd = m_ArcEnd;
		pAttrDest->m_ArcLineWidth = m_ArcLineWidth;
		pAttrDest->m_ArcRadius = m_ArcRadius;
		pAttrDest->m_ArcColor = m_ArcColor;
		pAttrDest->m_Divisions = m_Divisions;
		pAttrDest->m_DivisionLineWidth = m_DivisionLineWidth;
		pAttrDest->m_DivisionLineLegnth = m_DivisionLineLegnth;
		pAttrDest->m_DivLineColor = m_DivLineColor;
		pAttrDest->m_SubDivisions = m_SubDivisions;
		pAttrDest->m_SubDivisionLineWidth = m_SubDivisionLineWidth;
		pAttrDest->m_SubdivisionLengnth = m_SubdivisionLengnth;
		pAttrDest->m_SubDivColor = m_SubDivColor;
		pAttrDest->m_HoleSize = m_HoleSize;
		pAttrDest->m_HoleType = m_HoleType;
		pAttrDest->m_FlatDist = m_FlatDist;
		pAttrDest->m_Ref = m_Ref;		//reference point for scale object
		//scale labels
		pAttrDest->m_FontSize = m_FontSize;
		pAttrDest->m_FontWeight = m_FontWeight;
		pAttrDest->m_DistToTick = m_DistToTick;
		pAttrDest->m_TextColor = m_TextColor;
		pAttrDest->m_BkColor = m_BkColor;
		if (pAttrDest->m_pFont)
			delete[] pAttrDest->m_pFont;
		pAttrDest->m_pFont = new char[SCALE_LABELS_STRING_SIZE];
		sprintf_s(pAttrDest->m_pFont, SCALE_LABELS_STRING_SIZE, "%s", m_pFont);
		for (int i = 0; i < SCALE_LABELS_SIZE; i++) {
			if (pAttrDest->m_pLabels[i])
				delete[] pAttrDest->m_pLabels[i];
			pAttrDest->m_pLabels[i] = new char[SCALE_LABELS_STRING_SIZE];
			sprintf_s(pAttrDest->m_pLabels[i], SCALE_LABELS_STRING_SIZE, "%s", m_pLabels[i]);
		}
	}
}

void SPotScaleWizAttributes::CopyFrom(SPotScaleWizAttributes *pAttrSource)
{
	if (pAttrSource) {
		m_ArcStart = pAttrSource->m_ArcStart;
		m_ArcEnd = pAttrSource->m_ArcEnd;
		m_ArcLineWidth = pAttrSource->m_ArcLineWidth;
		m_ArcRadius = pAttrSource->m_ArcRadius;
		m_ArcColor = pAttrSource->m_ArcColor;
		m_Divisions = pAttrSource->m_Divisions;
		m_DivisionLineWidth = pAttrSource->m_DivisionLineWidth;
		m_DivisionLineLegnth = pAttrSource->m_DivisionLineLegnth;
		m_DivLineColor = pAttrSource->m_DivLineColor;
		m_SubDivisions = pAttrSource->m_SubDivisions;
		m_SubDivisionLineWidth = pAttrSource->m_SubDivisionLineWidth;
		m_SubdivisionLengnth = pAttrSource->m_SubdivisionLengnth;
		m_SubDivColor = pAttrSource->m_SubDivColor;
		m_HoleSize = pAttrSource->m_HoleSize;
		m_HoleType = pAttrSource->m_HoleType;
		m_FlatDist = pAttrSource->m_FlatDist;
		m_Ref = pAttrSource->m_Ref;		//reference point for scale object
										//scale labels
		m_FontSize = pAttrSource->m_FontSize;
		m_FontWeight = pAttrSource->m_FontWeight;
		m_DistToTick = pAttrSource->m_DistToTick;
		m_TextColor = pAttrSource->m_TextColor;
		m_BkColor = pAttrSource->m_BkColor;
		if (m_pFont)
			delete[] m_pFont;
		m_pFont = new char[SCALE_LABELS_STRING_SIZE];
		sprintf_s(m_pFont, SCALE_LABELS_STRING_SIZE, "%s", pAttrSource->m_pFont);
		for (int i = 0; i < SCALE_LABELS_SIZE; i++) {
			if (m_pLabels[i])
				delete[] m_pLabels[i];
			m_pLabels[i] = new char[SCALE_LABELS_STRING_SIZE];
			sprintf_s(m_pLabels[i], SCALE_LABELS_STRING_SIZE, "%s", pAttrSource->m_pLabels[i]);
		}
	}
}
void SPotScaleWizAttributes::Save(FILE* pO, int Indent, SPotScaleWizAttributes* pAttrSource)
{
	char* psIndent = new char[256];
	char* psIndent1 = new char[256];

	theApp.IndentString(psIndent, 256, Indent);
	theApp.IndentString(psIndent1, 256, Indent + 2);
	fprintf(pO, "%s%s{\n", psIndent, CFileParser::LookupKeyword(Tokens::SCALEWIZARD));
	// save ScaleWizard attributes
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_ARC_START, m_ArcStart));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_ARC_END, m_ArcEnd));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_ARC_LINE_WIDTH, m_ArcLineWidth));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_ARC_RADIUS, m_ArcRadius));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveColor(psIndent, 256, m_ArcColor, Tokens::WIZ_ARC_COLOR));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_DIVISIONS, m_Divisions));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_DIV_LINE_WIDTH, m_DivisionLineWidth));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_DIV_LINE_LENGTH, m_DivisionLineLegnth));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveColor(psIndent, 256, m_DivLineColor, Tokens::WIZ_DIV_LINE_COLOR));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_SUBDIVISIONS, m_SubDivisions));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_SUBDIV_LINE_WIDTH, m_SubDivisionLineWidth));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_SUBDIV_LINE_LENGTH, m_SubdivisionLengnth));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveColor(psIndent, 256, m_SubDivColor, Tokens::WIZ_SUBDIV_LINE_COLOR));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_HOLE_SIZE, m_HoleSize));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_HOLE_TYPE, m_HoleType));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_FLAT_DIST, m_FlatDist));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SavePoint(psIndent, 256, Tokens::WIZ_REF_POINT, m_Ref));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_FONT_SIZE, m_FontSize));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_FONT_WEIGHT, m_FontWeight));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveDecimalValue(psIndent, 256, Tokens::WIZ_DIST_TO_TICK, m_DistToTick));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveColor(psIndent, 256, m_TextColor, Tokens::WIZ_TEXT_COLOR));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveColor(psIndent, 256, m_BkColor, Tokens::WIZ_BK_COLOR));
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveString(psIndent, 256, Tokens::WIZ_FONT, m_pFont));
	//save labels

	delete[] psIndent1;
	delete[] psIndent;
}

Tokens SPotScaleWizAttributes::Parse(FILE* pIN, Tokens LookAHeadToken, CFileParser* pParser, SPotScaleWizAttributes* pAttrSource)
{
	return Tokens();
}


