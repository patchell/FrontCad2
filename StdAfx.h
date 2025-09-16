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
#include "CadLine.h"
#include "CadOrigin.h"
#include "CadPolygon.h"
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

#include "PotScaleWizAttributes.h"
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


union UObjectTypes {
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
