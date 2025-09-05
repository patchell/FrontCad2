#pragma once

#define BLUE(x)		((x & 0x00ff0000) >> 16)
#define GREEN(x)	((x & 0x0000ff00) >> 8)
#define RED(x)		(x & 0x000000ff)
//---------------------------------------
// CFrontCadView
//---------------------------------------

enum DrawMode {
	NONE,
	LINE,
	RECTANGLE,
	ELIPSE,
	SELECT,
	RNDRECT,
	ARC,
	POLYGON,
	POLYFILL,
	ARC_CENTER,
	HOLE_ROUND,
	HOLE_RECT,
	HOLE_RND1F,
	HOLE_RND2F,
	TEXT,
	LIBPART,
	GETREF,
	MOVE,
	COPY,
	CUT,
	PASTE,
	SELECTREGION,
	BITMAPIMAGE,
	ARROW,
	ORIGIN,
	DIMENSION,
	ALIGN_DIM_TO_HOLE,
	PRINTRECT,
	CIRCLE
};

/*
//------------------------------
// States for moving selections
//------------------------------

#define MOVESTATE_GETREFERENCE		0
#define MOVESTATE_DRAGSELECTION		1
*/
//---------------------------
// Draw States
//--------------------------

#define DRAWSTATE_WAITMOUSE_DOWN	0
#define DRAWSTATE_MOVE				1
#define DRAWSTATE_PLACE				2
#define DRAWSTATE_ARCSTART			3
#define DRAWSTATE_ARCEND			4
#define DRAWSTATE_GETREFEREMCE		5
#define DRAWSTATE_DRAG				6

#define MOUSESTATE_DOWN	1
#define MOUSESTATE_UP	0

//-----------------------------------
// CCadObject
//------------------------------------

enum {
	OBJECT_TYPE_NONE,			//0
	OBJECT_TYPE_LINE,			//1
	OBJECT_TYPE_RECT,			//2
	OBJECT_TYPE_ELLIPSE	,		//3
	OBJECT_TYPE_RNDRECT	,		//4
	OBJECT_TYPE_POLY,			//5
	OBJECT_TYPE_POLYFILL,		//6
	OBJECT_TYPE_LIBCOMP,		//7
	OBJECT_TYPE_HOLEROUND,		//8
	OBJECT_TYPE_HOLERECT,		//9
	OBJECT_TYPE_HOLERND1FLAT,	//10
	OBJECT_TYPE_HOLERND2FLAT,	//11
	OBJECT_TYPE_TEXT	,		//12
	OBJECT_TYPE_ARC	,			//13
	OBJECT_TYPE_ARCCENTERED,	//14
	OBJECT_TYPE_DRAWING,		//15
	OBJECT_TYPE_BITMAP,			//16
	OBJECT_TYPE_ARROW,			//17
	OBJECT_TYPE_ORIGIN,			//18
	OBJECT_TYPE_DIMENSION,		//19
	OBJECT_TYPE_PRINTRECT,		//20
	OBJECT_TYPE_CIRCLE			//21
};

enum class ObjectMode {
	None,
	Final,
	Selected,
	Sketch,
	Erase,
	ArcStart,
	ArcEnd
};


//------------------------------------
// Windows Messages
//------------------------------------

	//message from Utility Pane to Main Pane
#define WM_UTILMESSAGE		WM_USER+1

	//submessages for WM_UTILMESSAGE

enum UtilMsg {
	DEFAULT,
	X1,
	Y1,
	X2,
	Y2,
	X3,
	Y3,
	LINECOLOR,
	LINEWIDTH,
	FILLCOLOR,
	_TEXT,
	FLATDIST,
	HOLERADIUS,
	FONTHEIGHT,
	FONTWIDTH,
	TEXTANGLE,
	TEXTTRANSPARENT,
	TEXTCOLOR,
	FONT,
	TEXTBKCOLOR,
	FONTWEIGHT,
	BACKGROUND,
	_PRINTRECT,
	TRANSPARENT_FILL
};

#define WM_LIBVIEW_GETREF	WM_USER+6
#define WM_MAINVIEW_GOTREF	WM_USER+7

	//message from Tab1 to 
	//Pot Scale Wizard Dlg
#define WM_TAB1_MESSAGE		WM_USER+2

#define TAB1_ARCSTART		0
#define TAB1_ARCEND			1
#define TAB1_DIVISIONS		2
#define TAB1_ARCLINEWIDTH	3
#define TAB1_ARCRADIUS		4
#define TAB1_DIVLINEWIDTH	5
#define TAB1_DIVLINELEN		6
#define TAB1_HOLERADIUS		7
#define TAB1_FLATDIST		8
#define TAB1_HOLETYPE		9
#define TAB1_SUBDIVISIONS	10
#define TAB1_SUBDIVLINELEN	11
#define TAB1_SUBDIVLINWIDTH	12
#define TAB1_DIVCOLOR		13
#define TAB1_SUBCOLOR		14
#define TAB1_ARCCOLOR		15

#define WM_TAB2_MESSAGE		WM_USER+3

#define TAB2_FONTSIZE		0
#define TAB2_FONTWEIGHT		1
#define TAB2_LABELTEXT		2
#define TAB2_DISTTOTICK		3
#define TAB2_FONT			4
#define TAB2_TEXTCOLOR		5
#define TAB2_TEXTBKCOLOR	6
#define TAB2_ROTATE_TEXT	7

#define WM_TAB2_LABELSEL	WM_USER+4

#define WM_TAB3_MESSAGE		WM_USER+5

#define WM_UPDATEDIMENSIONS		WM_USER+8

//------------------------------
// Zoom
//-----------------------------

#define MAX_ZOOM		6

