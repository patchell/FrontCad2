// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__E9CF1AC9_DCF9_4F75_A090_0C41D7516327__INCLUDED_)
#define AFX_STDAFX_H__E9CF1AC9_DCF9_4F75_A090_0C41D7516327__INCLUDED_

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "afxdialogex.h"

//--------------------------------------------
// Tokens used for parsing
//--------------------------------------------

enum class Tokens {
	EndOfFile = -1,
	NUM = 256,
	STRING,			//1
	ARC,				//2
	ARC_CENTER,		//3
	CIRCLE,			//4
	ELLIPSE,
	RECT,				//5
	RNDRECT,			//6
	POLY,				//7
	POLYFILL,			//8
	LINE,				//9
	HOLERND,			//10
	HOLERECT,			//11
	HOLE_1FLAT,		//12
	HOLE_2FLAT,		//13
	LIBPART,			//14
	TEXT,				//15
	POINT,
	POINT_1,
	POINT_2,
	POINT_3,
	VERTEX_POINT,
	START_POINT,
	END_POINT,
	//colors
	BACKGROUND_COLOR,	//17
	LINE_COLOR,
	TEXT_COLOR,
	FILL_COLOR,
	RED,
	GREEN,
	BLUE,
	COLOR,
	//------- Text ----------
	FONT,
	WEIGHT,
	HEIGHT,
	FONTHIEGHT,
	FONTWIDTH,
	RADIUS,
	FLATDIST,
	DRAWFILE,
	LIBFILE,
	VERTEX,
	RECTWIDTH,
	RECTHIEGHT,
	ANGLE,
	TRANSPARENTbkg,
	REFERENCE,
	BITMAP,
	FILE,
	ARROW,
	LENGTH,
	ORG,	//token for origin object
	DIMENSION,
	PRINTRECT,
	SIZE,
	SCALE,
	WIDTH,
	LINE_WIDTH,
	ARROW_LENGTH,
	ARROW_WIDTH,
	// Scale Wizard Tokens
	SCALEWIZARD,
	WIZ_ARC_START,
	WIZ_ARC_END,
	WIZ_ARC_LINE_WIDTH,
	WIZ_ARC_RADIUS,
	WIZ_ARC_COLOR,
	WIZ_DIVISIONS,
	WIZ_DIV_LINE_WIDTH,
	WIZ_DIV_LINE_LENGTH,
	WIZ_DIV_LINE_COLOR,
	WIZ_SUBDIVISIONS,
	WIZ_SUBDIV_LINE_WIDTH,
	WIZ_SUBDIV_LINE_LENGTH,
	WIZ_SUBDIV_LINE_COLOR,
	WIZ_HOLE_SIZE,
	WIZ_HOLE_TYPE,
	WIZ_FLAT_DIST,
	WIZ_REF_POINT,
	WIZ_FONT_SIZE,
	WIZ_FONT_WEIGHT,
	WIZ_DIST_TO_TICK,
	WIZ_TEXT_COLOR,
	WIZ_BK_COLOR,
	WIZ_FONT,
	WIZ_LABEL_COUNT,
	WIZ_LABEL,
	WIZ_LABELS
};

//--------------------------------------------
// Scale Wizard Attributes Class
//--------------------------------------------

constexpr auto SCALE_LABELS_SIZE = 40;
constexpr auto SCALE_LABELS_STRING_SIZE = 32;

class CFileParser;
struct SCALEWIZattributes {
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
	SCALEWIZattributes() {
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
	~SCALEWIZattributes() {
		if (m_pFont)
			delete[] m_pFont;
		for (int i = 0; i < SCALE_LABELS_SIZE; i++) {
			if (m_pLabels[i])
				delete[] m_pLabels[i];
		}
	}
	void CopyTo(SCALEWIZattributes* pAttrDest) {
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
	void CopyFrom(SCALEWIZattributes* pAttrSource) {
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
	void Save(FILE* pO, int Indent, SCALEWIZattributes* pAttrSource);
	Tokens Parse(FILE* pIN, Tokens LookAHeadToken, CFileParser* pParser, SCALEWIZattributes* pAttrSource);
};



#include "resource.h"       // main symbols

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "Scale.h"
#include "Exception.h"
#include "FrontCadDefines.h"
//draw objects
#include "CadObject.h"
#include "CadArc.h"
#include "CadArcCentered.h"
#include "CadArrow.h"
#include "CadBitmap.h"
#include "CadCircle.h"
#include "CadElipse.h"
#include "CadHoleRnd1Flat.h"
#include "CadHoleRnd2Flat.h"
#include "CadHoleRound.h"
#include "CadLibObject.h"
#include "CadOrigin.h"
#include "CadPolygon.h"
#include "CadLine.h"
#include "CadPrintRect.h"
#include "CadRect.h"
#include "CadRectHole.h"
#include "CadRoundRect.h"
#include "CadText.h"
#include "CadDimension.h"
#include "CadDrawing.h"
#include "CadLibrary.h"

//controls
#include "ButtonMsg.h"
#include "StaticBitmap.h"
#include "StaticPreview.h"
#include "MyEdit.h"
#include "EditDecimal.h"
#include "ComboBoxPrintRect.h"
#include "ComboBoxHoleType.h"
#include "ComboBoxLibPartSelector.h"
#include "ComboBoxFontWeight.h"
#include "MyComboBox.h"
#include "HorzScrollBar.h"
#include "ComboBoxLibrary.h"
#include "MyBitmap.h"

#include "MoveObjects.h"

//mfc stuff
#include "DialogChoose.h"
#include "DialogGridSettings.h"
#include "DialogRenderEnable.h"
#include "NewLibDialog.h"

#include "MyTabCtrl.h"
#include "ScaleWizTabOne.h"
#include "WizTab2Dialog.h"
#include "WizTab3Dialog.h"
#include "ScaleWizDialog.h"
#include "SaveToLibDlg.h"

#include "RepeatDlg.h"

#include "SplitterUtility.h"
#include "LibSplitterWnd.h"
#include "LibFormView.h"
#include "UtilView.h"
#include "ruler.h"
#include "MainFrm.h"
#include "FrontCadDoc.h"
#include "FrontCadView.h"
#include "FileParser.h"
#include "FrontCad.h"


union ObjectTypes {
	CCadObject* pCadObj;
	CCadArc* pArcObj;
	CCadArcCentered* pArcCentObj;
	CCadArrow* pArrow;
	CCadBitmap* pBitMap;
	CCadDimension* pDim;
	CCadDrawing* pDrawing;
	CCadElipse* pElipse;
	CCadCircle* pCircle;
	CCadHoleRnd1Flat* pRnd1Flat;
	CCadHoleRnd2Flat* pRnd2Flat;
	CCadHoleRound* pRndHole;
	CCadLibObject* pLibObj;
	CCadLibrary* pLibrary;
	CCadLine* pLine;
	CCadOrigin* pOrigin;
	CCadPolygon* pPoly;
	CCadPrintRect* pPrintRect;
	CCadRect* pRect;
	CCadRectHole* pRectHole;
	CCadRoundRect* pRndedRect;
	CCadText* pText;
};
#endif // !defined(AFX_STDAFX_H__E9CF1AC9_DCF9_4F75_A090_0C41D7516327__INCLUDED_)
