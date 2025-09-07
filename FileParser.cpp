// FileParser.cpp: implementation of the CFileParser class.
//
///////////////////////////////////////////////

#include "stdafx.h"



///////////////////////////////////////////////
// Construction/Destruction
///////////////////////////////////////////////

CFileParser::CFileParser(CFrontCadDoc *pDoc)
{
	m_pDoc = pDoc;
	m_pLib = 0;
	m_pLob = 0;
	m_pDLob = 0;
	UnGetBuff = 0;
	m_LexIndex = 0;
	m_LexValue = 0;
	memset(m_LexBuff, 0, 256);
	UnGetBuff = 0;
	m_Col = 0;
	m_Line = 1;
}

CFileParser::CFileParser()
{
	m_pDLob = 0;
	m_pDoc = 0;
	m_pLib = 0;
	m_pLob = 0;
	UnGetBuff = 0;
	m_LexValue = 0;
	m_LexIndex = 0;
	memset(m_LexBuff, 0, 256);
	UnGetBuff = 0;
	m_Col = 0;
	m_Line = 1;
}

CFileParser::~CFileParser()
{

}

int CFileParser::GetChar(FILE *in)
{
	int rV;

	if(UnGetBuff)
	{
		rV = UnGetBuff;
		switch (rV)
		{
		case '\n':
			m_Line++;
			m_Col = 0;
			break;
		default:
			m_Col++;
			break;
		}
		UnGetBuff = 0;
	}
	else
	{
		rV = fgetc(in);
		switch (rV)
		{
		case '\n':
			m_Line++;
			m_Col = 0;
			break;
		default:
			m_Col++;
			break;
		}
	}
	return rV;
}

int CFileParser::UnGetChar(int c)
{
	UnGetBuff = c;
	return 0;
}

int CFileParser::Open(char *pFileName, CFrontCadDoc *pDoc)
{
	return 0;
}

Tokens CFileParser::Expect(Tokens ExpectedToken, Tokens LookAHead, FILE *pIN)
{
	/********************************************
	** Expect
	**
	** this function is used to match
	** the expected token with the current
	** token.  If they match, get the
	** next token.
	**
	** parameter:
	**	pI.....input file stream
	**	token..expected token
	**
	** Returns:Next token, or -1 on error
	********************************************/
	Tokens rV = Tokens(0);

	if (Accept(ExpectedToken, LookAHead, pIN))
		rV = Lex(pIN);
	else
	{
		char* pToken1 = new char[64],*pToken2 = new char[64];
		for (int i = 0; i < 64; ++i)
		{
			pToken1[i] = 0;
			pToken2[i] = 0;		//Expected Token String
		}
		if (LookAHead > Tokens(32) && LookAHead < Tokens(128))
			pToken1[0] = int(LookAHead);
		else if (LookAHead > Tokens(255))
		{
			sprintf_s(pToken1, 64, "%s", LookupKeyword(LookAHead));
		}
		else
			sprintf_s(pToken1, 64, "%d", LookAHead);
		if (ExpectedToken > Tokens(32) && ExpectedToken < Tokens(128))
			pToken2[0] = (char)ExpectedToken;
		else if (ExpectedToken > Tokens(255))
		{
			sprintf_s(pToken2, 64, "%s", LookupKeyword(ExpectedToken));
		}
		else
			sprintf_s(pToken2, 64, "%d", ExpectedToken);
		sprintf_s(Exception.ErrorString, 256, "Syntax Error:Line %d Col %d  Expected %s Got %s\n",
			m_Line,
			m_Col,
			pToken2,
			pToken1
		);
		throw Exception;

	}
	return rV;
}

BOOL CFileParser::Accept(Tokens token, Tokens LookAHead, FILE *pIN)
{
	BOOL rV=FALSE;

	if(token == LookAHead)
		rV = TRUE;
	return rV;
}

BOOL CFileParser::CheckKeywordChar(int c)
{
	BOOL rV = FALSE;

	if (isalnum(c) || c == '_')
		rV = TRUE;
	return rV;
}

Tokens CFileParser::Lex(FILE *pIN)
{
	int loop;
	Tokens rV;
	int c;
	Tokens token;
	loop = 1;
	while(loop)
	{
		c = GetChar(pIN);
		switch(c)
		{
			case EOF:
				loop = 0;
				rV = Tokens::EndOfFile;
				break;
			case ' ': case '\t':	//whitespace
				break;
			case '\n':	//end of line
				break;
			case '\"':	//string
				m_LexIndex = 0;
				while((c = GetChar(pIN)) != '\"')
				{
					m_LexBuff[m_LexIndex++] = c;
				}
				m_LexBuff[m_LexIndex] = 0;
				rV = Tokens::STRING;
				loop = 0;
				break;
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9':	case '-': //deccimal number
				m_LexIndex = 0;
				do
				{
					m_LexBuff[m_LexIndex++] = c;
				}while(isdigit(c = GetChar(pIN)));
				UnGetChar(c);
				m_LexBuff[m_LexIndex] = 0;
				loop = 0;
				m_LexValue = atoi(m_LexBuff);
				rV = Tokens::NUM;
				break;
			case ',': case '(': case ')': case '{': case '}':
			case '[':case ']':
				rV = Tokens(c);
				loop = 0;
				break;
			default:	//keywords
				m_LexIndex = 0;
				m_LexBuff[m_LexIndex++] = c;
				while(CheckKeywordChar(c = GetChar(pIN)))
				{
					m_LexBuff[m_LexIndex++] = c;
				}
				UnGetChar(c);
				m_LexBuff[m_LexIndex] = 0;
				token = LookupToken(m_LexBuff);
				if(token >= Tokens(0))
					rV = token;
				else
					rV = Tokens(-1);
				loop = 0;
				break;
		}
	}
	return rV;
}

Tokens CFileParser::Parse(FILE *pIN)
{
	// TODO:fix Drawing File Keyword parsing
	int loop = 1;
	Tokens Token;
	CCadLibrary *pLib=0;

	try
	{
		Token = Lex(pIN);
		while (loop)
		{
			switch (Token)
			{
			case Tokens::DRAWFILE:
				Token = DrawFile(pIN, Token, m_pDoc);
				break;
			case Tokens::LIBFILE:
				pLib = new CCadLibrary;
				Token = Expect(Tokens::LIBFILE, Token, pIN);
				Token = Expect(Tokens('('), Token, pIN);
				pLib->SetName(m_LexBuff);
				Token = Expect(Tokens::STRING, Token, pIN);
				Token = Expect(Tokens(')'), Token, pIN);
				Token = Expect(Tokens('{'), Token, pIN);
				Token = LibFile(pIN, Token, pLib);
				Token = Expect(Tokens('}'), Token, pIN);
				break;
			case Tokens::EndOfFile:
				loop = 0;
				if (pLib)
					this->m_pLib = pLib;
				break;
			}
		}
	}
	catch(SException& XCept)
	{
		MessageBox(NULL, XCept.ErrorString, "Error", MB_OK);
	}
	return Tokens(0);
}

Tokens CFileParser::LibFile(FILE *pIN, Tokens Token,CCadLibrary *pLib)
{
	CCadLibObject *pLibObj;
	int loop=1;
	while(loop)
	{
		switch(Token)
		{
			case Tokens::LIBPART:
				pLibObj = new CCadLibObject;
//				Token = pLibObj->Parse(pIN, Token, , this);
				Token = LibPart(pIN,Token,pLibObj);
				pLib->AddPart(pLibObj);
				break;
			case Tokens('}'):
				loop = 0;
				break;
		}
	}
	return Token;
}

Tokens CFileParser::DrawFile(FILE *pIN, Tokens Token, CFrontCadDoc*pDrawing)
{
	//------------------------------------------------------------------------
	//	DrawFile	-> DRAWFILE DrawFileAttributes '{' DrawObjects '}'
	//				-> .
	//------------------------------------------------------------------------
	int Loop = TRUE;
	CCadDrawing* pDraw = pDrawing->GetDrawing();
	Token = Expect(Tokens::DRAWFILE, Token, pIN);
	pDraw->SetBkColor(RGB(255, 255, 255));	//default background
	Token = DrawFileAttributes(pIN, Token, pDraw);
	Token = Expect(Tokens('{'), Token, pIN);
	Token = DrawObjects(pIN, Token, pDraw);
	Token = Expect(Tokens('}'), Token, pIN);
	return Token;
}

Tokens CFileParser::DrawFileAttributes(FILE* pIN, Tokens Token, CCadObject* pO)
{
	//--------------------------------------------------------
	// DrawFileAttributes	-> '(' DrawFileAttributes1 ')'
	//						-> .
	//--------------------------------------------------------
	Token = Expect(Tokens('('), Token, pIN);
	Token = DrawFileAttributes2(pIN, Token, pO);
	Token = Expect(Tokens(')'), Token, pIN);
	return Token;
}


Tokens CFileParser::DrawFileAttributes2(FILE* pIN, Tokens Token, CCadObject* pO)
{
	//--------------------------------------------------------------------
	//	DrawFileAttributes1	-> DrawingAttributes3 DrawingAttributes2;
	// 
	//	DrawingAttributes2	-> ',' DrawingAttributes3 DrawingAttributes2
	//						-> .
	//--------------------------------------------------------------------
	BOOL Loop = TRUE;

	Token = DrawFileAttributes3(pIN, Token, pO);
	while (Loop)
	{
		switch (Token)
		{
		case Tokens(','):
			Token = Expect(Tokens(','), Token, pIN);
			Token = DrawFileAttributes3(pIN, Token, pO);
			break;
		default:
			Loop = FALSE;
			break;
		}
	}
	return Token;
}

Tokens CFileParser::DrawFileAttributes3(FILE* pIN, Tokens Token, CCadObject* pO)
{
	//-------------------------------------------------------------
	//	DrawFileAttributes3	-> COLOR '(' NUM ',' NUM ',' NUM ')'
	//						-> SCALE '(' NUM ')'
	//						-> .
	//-------------------------------------------------------------
	switch (Token)
	{
	case Tokens::BACKGROUND_COLOR:
		Token = Color(Token, pIN, ((CCadDrawing*)pO)->m_BkColor, Token);
		break;
	case Tokens::COLOR:	// compatability with older files
		Token = Color(Token, pIN, ((CCadDrawing*)pO)->m_BkColor, Token);
		break;
	case Tokens::SCALE:
		Token = Expect(Tokens::SCALE, Token, pIN);
		Token = Expect(Tokens('('), Token, pIN);
		Token = Expect(Tokens::NUM, Token, pIN);
		Token = Expect(Tokens(')'), Token, pIN);
		break;
	}
	return Token;
}

Tokens CFileParser::PrintRect(FILE* pIN, Tokens Token, CCadObject* pO)
{
	BOOL Loop = TRUE;
	CCadPrintRect* pPR;

	pPR = new CCadPrintRect;
	Token = Expect(Tokens::PRINTRECT, Token, pIN);
	Token = Expect(Tokens('('), Token, pIN);
	while (Loop)
	{
		switch (Token)
		{
		case Tokens::POINT_1:
			Token = Point(Tokens::POINT_1, pIN, pPR->GetP1(), Token);
			break;
		case Tokens::COLOR:
			Token = Color(Tokens::COLOR, pIN, pPR->m_Attrib.m_LineColor, Token);
			break;
		case Tokens::LINE_WIDTH:
			Token = DecimalValue(Tokens::LINE_WIDTH, pIN, pPR->m_Attrib.m_LineWidth, Token);
			break;
		case Tokens::SIZE:
			Token = Size(Tokens::SIZE, pIN, pPR->GetAttributes()->m_Size, Token);
			break;
		case Tokens(','):
			Token = Expect(Tokens(','), Token, pIN);
			break;
		case Tokens(')'):
			Loop = FALSE;
			break;
		}//end of switch token
	}
	Token = Expect(Tokens(')'), Token, pIN);
	pO->AddObjectToEnd(pPR);
	return Token;
}

Tokens CFileParser::DrawObjects(FILE* pIN, Tokens Token, CCadObject* pO)
{
	BOOL Loop = TRUE;
	ObjectTypes DrawingObjects;
	CCadDrawing* pDraw = (CCadDrawing*)pO;

	memset(&DrawingObjects, 0, sizeof(ObjectTypes));
	while (Loop)
	{
		switch (Token)
		{
		case Tokens::PRINTRECT:
			DrawingObjects.pPrintRect = new CCadPrintRect;
			Token = DrawingObjects.pPrintRect->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::DIMENSION:
			DrawingObjects.pDim = new CCadDimension;
			Token = DrawingObjects.pDim->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::ORG:
			DrawingObjects.pOrigin = new CCadOrigin;
			Token = DrawingObjects.pOrigin->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::TEXT:
			DrawingObjects.pText = new CCadText;
			Token = DrawingObjects.pText->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::ARC:
			DrawingObjects.pArcObj = new CCadArc;
			Token = DrawingObjects.pArcObj->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::ARC_CENTER:
			DrawingObjects.pArcCentObj = new CCadArcCentered;
			Token = DrawingObjects.pArcCentObj->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::ELLIPSE:
			DrawingObjects.pElipse = new CCadElipse;
			Token = DrawingObjects.pElipse->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::CIRCLE:
			DrawingObjects.pCircle = new CCadCircle;
			Token = DrawingObjects.pCircle->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::RECT:
			DrawingObjects.pRect = new CCadRect;
			Token = DrawingObjects.pRect->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::RNDRECT:
			DrawingObjects.pRndedRect = new CCadRoundRect;
			Token = DrawingObjects.pRndedRect->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::POLY:
		case Tokens::POLYFILL:
			DrawingObjects.pPoly = new CCadPolygon;
			Token = DrawingObjects.pPoly->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::LINE:
			DrawingObjects.pLine = new CCadLine;
			Token = DrawingObjects.pLine->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::HOLERND:
			DrawingObjects.pRndHole = new CCadHoleRound;
			Token = DrawingObjects.pRndHole->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::HOLERECT:
			DrawingObjects.pRectHole = new CCadRectHole;
			Token = DrawingObjects.pRectHole->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::HOLE_1FLAT:
			DrawingObjects.pRnd1Flat = new CCadHoleRnd1Flat;
			Token = DrawingObjects.pRnd1Flat->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::HOLE_2FLAT:
			DrawingObjects.pRnd2Flat = new CCadHoleRnd2Flat;
			Token = DrawingObjects.pRnd2Flat->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::LIBPART:
			DrawingObjects.pLibObj = new CCadLibObject;
			Token = DrawingObjects.pLibObj->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::BITMAP:
			DrawingObjects.pBitMap = new CCadBitmap;
			Token = DrawingObjects.pBitMap->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens::ARROW:
			DrawingObjects.pArrow = new CCadArrow;
			Token = DrawingObjects.pArrow->Parse(pIN, Token, &pDraw, this);
			break;
		case Tokens('}'):
			Loop = 0;
			break;
		default:
			sprintf_s(Exception.ErrorString, 256, "Syntax Error:Line %d Col %d  UnExpected Token %s\n",
				GetLine(),
				GetCol(),
				CFileParser::LookupKeyword(Token)
			);
			throw Exception;
			break;
		}//end of switch(Token)
	}	//end of while loop
	return Token;
}

//------------------------------------------
// Utility Parsing Methods
//------------------------------------------

Tokens CFileParser::Point(Tokens TargeToken, FILE* pIN, CPoint& Point, Tokens Token)
{
	int x, y;

	Token = Expect(TargeToken, Token, pIN);
	Token = Expect(Tokens('('), Token, pIN);
	x = atoi(m_LexBuff);
	Token = Expect(Tokens::NUM, Token, pIN);
	Token = Expect(Tokens(','), Token, pIN);
	y = atoi(m_LexBuff);
	Token = Expect(Tokens::NUM, Token, pIN);
	Token = Expect(Tokens(')'), Token, pIN);
	Point = CPoint(x, y);
	return Token;
}

Tokens CFileParser::LibPart(FILE *pIN, Tokens Token,CCadLibObject *pLO)
{
	Token = Expect(Tokens::LIBPART,Token,pIN);
	Token = Expect(Tokens('('),Token,pIN);
	pLO->SetName(m_LexBuff);
	Token = Expect(Tokens::STRING,Token,pIN);
	Token = Expect(Tokens(','),Token,pIN);
	Token = Point(Tokens::REFERENCE, pIN,pLO->GetRef(), Token);
	Token = Expect(Tokens(','),Token,pIN);
	Token = Point(Tokens::POINT_1, pIN,pLO->GetP1(), Token);
	Token = Expect(Tokens(')'),Token,pIN);
	Token = Expect(Tokens('{'),Token,pIN);
	Token = DrawObjects(pIN,Token,pLO);
	Token = Expect(Tokens('}'),Token,pIN);
	return Token;
}

Tokens CFileParser::Color(Tokens TargetToken, FILE *pIN, COLORREF& ColorParam, Tokens Token)
{
	int RED = 0,BLUE = 0,GREEN = 0;
	BOOL Loop = TRUE;
	int Order = 0;

	Token = Expect(TargetToken,Token,pIN);
	Token = Expect(Tokens('('),Token,pIN);
	while (Loop)
	{
		switch (Token)
		{
		case Tokens::RED:
			Token = Red(pIN, RED, Token);
			break;
		case Tokens::GREEN:
			Token = Green(pIN, GREEN, Token);
			break;
		case Tokens::BLUE:
			Token = Blue(pIN, BLUE, Token);
			break;
		case Tokens::NUM:
			switch (Order)
			{
			case 2:
				RED = atoi(m_LexBuff);
				Token = Expect(Tokens::NUM, Token, pIN);
				++Order;
				break;
			case 1:
				GREEN = atoi(m_LexBuff);
				Token = Expect(Tokens::NUM, Token, pIN);
				++Order;
				break;
			case 0:
				BLUE = atoi(m_LexBuff);
				Token = Expect(Tokens::NUM, Token, pIN);
				++Order;
				break;
			}
			break; 
		case Tokens(','):
			Token = Expect(Tokens(','), Token, pIN);
			break;
		case Tokens(')'):
			Token = Expect(Tokens(')'), Token, pIN);
			Loop = FALSE;
			break;
		default:
			sprintf_s(Exception.ErrorString, 256, "Syntax Error:Line %d Col %d  UnExpected Token %s\n",
				GetLine(),
				GetCol(),
				CFileParser::LookupKeyword(Token)
			);
			throw Exception;
			break;
		}
	}
	ColorParam = RGB(RED,GREEN,BLUE);
	return Token;
}

Tokens CFileParser::Red(FILE* pIN, int& red, Tokens Token)
{
	Token = DecimalValue(Tokens::RED, pIN, red, Token);
	return Token;
}

Tokens CFileParser::Green(FILE* pIN, int& green, Tokens Token)
{
	Token = DecimalValue(Tokens::GREEN, pIN, green, Token);
	return Token;
}

Tokens CFileParser::Blue(FILE* pIN, int& blue, Tokens Token)
{
	Token = DecimalValue(Tokens::BLUE, pIN, blue, Token);
	return Token;
}

Tokens CFileParser::Font(FILE *pIN, char **F, Tokens Token)
{
	Token = Expect(Tokens::FONT,Token,pIN);
	Token = Expect(Tokens('('),Token,pIN);
	int len = strlen(m_LexBuff) + 1;
	*F = new char[len];
	strcpy_s(*F,len,m_LexBuff);
	Token = Expect(Tokens::STRING,Token,pIN);
	Token = Expect(Tokens(')'),Token,pIN);
	return Token;
}

Tokens CFileParser::DecimalValue(Tokens TargetToken, FILE* pIN, int &v, Tokens Token)
{
	Token = Expect(TargetToken,Token,pIN);
	Token = Expect(Tokens('('),Token,pIN);
	v = atoi(m_LexBuff);
	Token = Expect(Tokens::NUM,Token,pIN);
	Token = Expect(Tokens(')'),Token,pIN);
	return Token;
}

Tokens CFileParser::Size(Tokens TargetToken, FILE * pIN, CSize & Sz, Tokens Token)
{
	int x, y;

	Token = Expect(TargetToken, Token, pIN);
	Token = Expect(Tokens('('), Token, pIN);
	x = atoi(m_LexBuff);
	Token = Expect(Tokens::NUM, Token, pIN);
	Token = Expect(Tokens(','), Token, pIN);
	y = atoi(m_LexBuff);
	Token = Expect(Tokens::NUM, Token, pIN);
	Token = Expect(Tokens(')'), Token, pIN);
	Sz = CSize(x, y);
	return Token;
}

char* CFileParser::SaveString(char* s, int n, Tokens Token, char* string)
{
    return s;
}

char* CFileParser::SaveSize(char* s, int n, Tokens Token, CSize& size)
{
	sprintf_s(s, n, "%s(%d,%d)",
		LookupKeyword(Token),
		size.cx,
		size.cy
	);
	return s;
}

char* CFileParser::SavePoint(char* s, int n, Tokens Token, CPoint point)
{
	sprintf_s(s, n, "%s(%d,%d)",
		LookupKeyword(Token),
		point.x, 
		point.y
	);
	return s;
}

char* CFileParser::SaveColor(char* s, int n, COLORREF color, Tokens Token)
{
	sprintf_s(s, n, "%s(RED(%d),GREEN(%d),BLUE(%d))",
		LookupKeyword(Token),
		RED(color),
		GREEN(color),
		BLUE(color)
	);
	return s;
}

char* CFileParser::SaveDecimalValue(char* s, int n, Tokens Token, int& value)
{
	sprintf_s(s, n, "%s(%d)",
		LookupKeyword(Token),
		value
	);
	return s;
}

char* CFileParser::SaveTransparent(char* s, int n, Tokens Token, int& value)
{
	sprintf_s(s, n, "%s(%d)",
		LookupKeyword(Token),
		value
	);
	return s;
}

Tokens CFileParser::LookupToken(const char* pName)
{
	Tokens rV = Tokens(0);
	int i;
	BOOL Loop = TRUE;

	for (i = 0; KeyWords[i].pKeyWord && Loop; ++i)
	{
		if (strcmp(KeyWords[i].pKeyWord, pName) == 0)
		{
			rV = KeyWords[i].Token;
			Loop = FALSE;
		}
	}
	return rV;
}

const char* CFileParser::LookupKeyword(Tokens Token)
{
	static const char* pDef = "<Undefine Token>";
	const char* pS = pDef;
	int i;
	BOOL Loop = TRUE;

	for (i = 0; KeyWords[i].pKeyWord && Loop; ++i)
	{
		if (KeyWords[i].Token == Token)
		{
			pS = KeyWords[i].pKeyWord;
			Loop = FALSE;
		}
	}
	return pS;
}


