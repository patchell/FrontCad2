// stdafx.cpp : source file that includes just the standard includes
//	FrontCad.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

SException Exception;

//--------------------------------------------
// SCALEWIZattributes Load/Save/Parse
//--------------------------------------------

void SCALEWIZattributes::Save(FILE* pO, int Indent, SCALEWIZattributes* pAttrSource)
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
	fprintf(pO, "%s%s,\n", psIndent1, CFileParser::SaveColor(psIndent, 256,  m_ArcColor, Tokens::WIZ_ARC_COLOR ));
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

Tokens SCALEWIZattributes::Parse(FILE* pIN, Tokens LookAHeadToken, CFileParser* pParser, SCALEWIZattributes* pAttrSource)
{
	return Tokens();
}
