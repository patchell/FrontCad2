// FileParser.h: interface for the CFileParser class.
//
///////////////////////////////////////////////

#pragma once



class CFileParser  
{
public:
	struct KEYWORD {
		const char* pKeyWord;
		Tokens Token;
		KEYWORD() {
			pKeyWord = 0;
			Token = Tokens(0);
		}
		KEYWORD(const char* pName, Tokens T) {
			pKeyWord = pName;
			Token = T;
		}
		BOOL IsKeyWord(const char* s) const
		{
			BOOL rV = FALSE;

			if (strcmp(pKeyWord, s) == 0)
				rV = TRUE;
			return rV;
		}
	};
private:
	inline static KEYWORD KeyWords[] = {
		{"ARC",Tokens::ARC},
		{"ARCCENT",Tokens::ARC_CENTER},
		{"CIRCLE",Tokens::CIRCLE},
		{"ELLIPSE", Tokens::ELLIPSE},
		{"RECT",Tokens::RECT},
		{"RNDRECT",Tokens::RNDRECT},
		{"POLY",Tokens::POLY},
		{"POLYFILL",Tokens::POLYFILL},
		{"LINE",Tokens::LINE},
		{"HOLERND",Tokens::HOLERND},
		{"HOLERECT",Tokens::HOLERECT},
		{"HOLE1FLAT",Tokens::HOLE_1FLAT},
		{"HOLE2FLAT",Tokens::HOLE_2FLAT},
		{"LIBPART",Tokens::LIBPART},
		{"TEXT",Tokens::TEXT},
		{"POINT", Tokens::POINT},
		{"POINT_1",Tokens::POINT_1},
		{"POINT_2",Tokens::POINT_2},
		{"POINT_3",Tokens::POINT_3},
		{"VERTEX_POINT",Tokens::VERTEX_POINT},
		{"BACKGROUND_COLOR",Tokens::BACKGROUND_COLOR},
		{"LINE_COLOR",Tokens::LINE_COLOR},
		{"TEXT_COLOR",Tokens::TEXT_COLOR},
		{"FILL_COLOR",Tokens::FILL_COLOR},
		{"RED",Tokens::RED},
		{"GREEN",Tokens::GREEN},
		{"BLUE",Tokens::BLUE},
		{"COLOR",Tokens::COLOR},
		{"FONT",Tokens::FONT},
		{"WEIGHT",Tokens::WEIGHT},
		{"HEIGHT",Tokens::HEIGHT},
		{"FONTHIEGHT",Tokens::FONTHIEGHT},
		{"FONTWIDTH",Tokens::FONTWIDTH},
		{"RADIUS",Tokens::RADIUS},
		{"FLATDIST",Tokens::FLATDIST},
		{"DRAWFILE",Tokens::DRAWFILE},
		{"LIBRARY",Tokens::LIBFILE},
		{"VERTEX",Tokens::VERTEX},
		{"RECTWIDTH",Tokens::RECTWIDTH},
		{"RECTHIEGHT",Tokens::RECTHIEGHT},
		{"ANGLE",Tokens::ANGLE},
		{"TRANSPARENT",Tokens::TRANSPARENTbkg},
		{"REF",Tokens::REFERENCE},
		{"BITMAP",Tokens::BITMAP},
		{"FILE",Tokens::FILE},
		{"ARROW",Tokens::ARROW},
		{"LENGTH",Tokens::LENGTH},
		{"ORIGIN",Tokens::ORG},
		{"DIMENSION",Tokens::DIMENSION},
		{"PRINTRECT",Tokens::PRINTRECT },
		{"SIZE",Tokens::SIZE },
		{"SCALE", Tokens::SCALE},
		{"START",Tokens::START_POINT},
		{"END",Tokens::END_POINT},
		{"WIDTH",Tokens::WIDTH},
		{"LINE_WIDTH",Tokens::LINE_WIDTH},
		{"ARROW_LENGTH",Tokens::ARROW_LENGTH},
		{"ARROW_WIDTH",Tokens::ARROW_WIDTH},
		// Scale Wizard Tokens amd Keywords
		{"SCALEWIZARD",Tokens::SCALEWIZARD},
		{"ARC_START",Tokens::WIZ_ARC_START},
		{"ARC_END",Tokens::WIZ_ARC_END},
		{"ARC_LINE_WIDTH",Tokens::WIZ_ARC_LINE_WIDTH},
		{"ARC_RADIUS",Tokens::WIZ_ARC_RADIUS},
		{"ARC_COLOR",Tokens::WIZ_ARC_COLOR},
		{"DIVISIONS",Tokens::WIZ_DIVISIONS},
		{"DIV_LINE_WIDTH",Tokens::WIZ_DIV_LINE_WIDTH},
		{"DIV_LINE_LENGTH",Tokens::WIZ_DIV_LINE_LENGTH},
		{"DIV_LINE_COLOR",Tokens::WIZ_DIV_LINE_COLOR},
		{"SUBDIVISIONS",Tokens::WIZ_SUBDIVISIONS},
		{"SUBDIV_LINE_WIDTH",Tokens::WIZ_SUBDIV_LINE_WIDTH},
		{"SUBDIV_LINE_LENGTH",Tokens::WIZ_SUBDIV_LINE_LENGTH},
		{"SUBDIV_LINE_COLOR",Tokens::WIZ_SUBDIV_LINE_COLOR},
		{"HOLE_SIZE",Tokens::WIZ_HOLE_SIZE},
		{"HOLE_TYPE",Tokens::WIZ_HOLE_TYPE},
		{"FLAT_DIST",Tokens::WIZ_FLAT_DIST},
		{"REF_POINT",Tokens::WIZ_REF_POINT},
		{"FONT_SIZE",Tokens::WIZ_FONT_SIZE},
		{"FONT_WEIGHT",Tokens::WIZ_FONT_WEIGHT},
		{"DIST_TO_TICK",Tokens::WIZ_DIST_TO_TICK},
		{"TEXT_COLOR",Tokens::WIZ_TEXT_COLOR},
		{"BK_COLOR",Tokens::WIZ_BK_COLOR},
		{"FONT",Tokens::WIZ_FONT},
		{"LABELS",Tokens::WIZ_LABELS},
		{"LABEL_COUNT",Tokens::WIZ_LABEL_COUNT},
		{"LABEL",Tokens::WIZ_LABEL},
		{NULL,Tokens(0)}
	};
	//--------------------------------------------
	// Member Data
	//--------------------------------------------
	CFrontCadDoc *m_pDoc;
	CCadLibrary *m_pLib;
	CCadLibObject *m_pLob;
	CCadLibObject *m_pDLob;
	int m_LexIndex;
	char m_LexBuff[256];
	int m_LexValue;
	int UnGetBuff;
	int m_Col;
	int m_Line;
public:
	CFileParser(CFrontCadDoc *pD);
	CFileParser();
	virtual ~CFileParser();
	//-------------------------------------
	// Parsing Utillity Methods
	//-------------------------------------
	Tokens LibPart(FILE *pIN, Tokens Token,CCadLibObject *pLibobj);
	Tokens Color(Tokens TargetToken, FILE* pIN, COLORREF& C, Tokens Token);
	Tokens Red(FILE* pIN, int& Color, Tokens token);
	Tokens Green(FILE* pIN, int& Color, Tokens token);
	Tokens Blue(FILE* pIN, int& Color, Tokens token);
	Tokens DecimalValue(Tokens TargetToken, FILE* pIN, int& v, Tokens Token);
	Tokens Font(FILE *pIN, char **F,Tokens token);
	Tokens Point(Tokens TargeToken, FILE* pIN, CPoint& Point, Tokens Token);
	Tokens Size(Tokens TargetToken, FILE* pIN, CSize& Sz, Tokens Token);
	//----------------------------------------------------
	// Parsing Methods
	//----------------------------------------------------
	Tokens LibFile(FILE *pIN, Tokens Token,CCadLibrary *pLib);
	Tokens DrawFile(FILE *pIN, Tokens Token, CFrontCadDoc*pDrawing);
	Tokens DrawFileAttributes(FILE* pIN, Tokens Token, CCadObject* pO);
	Tokens DrawFileAttributes2(FILE* pIN, Tokens Token, CCadObject* pO);
	Tokens DrawFileAttributes3(FILE* pIN, Tokens Token, CCadObject* pO);
	Tokens PrintRect(FILE* pIN, Tokens Token, CCadObject* pO);
	Tokens DrawObjects(FILE* pIN, Tokens Token, CCadObject* pO);
	//--------------------------------------------
	// Lexical Methods
	//--------------------------------------------
	Tokens Expect(Tokens token, Tokens lookahead, FILE *pIN);
	BOOL Accept(Tokens token, Tokens lookahead, FILE *pIN);
	int UnGetChar(int c);
	int GetChar(FILE* in);
	BOOL CheckKeywordChar(int c);
	Tokens Lex(FILE* pIN);
	char* GetLexBuff() { return m_LexBuff; }
	int GetLexValue() const { return m_LexValue; }
	int GetLine() const { return m_Line; }
	int GetCol() const { return m_Col; }
	//-------------------------------------------
	int Open(char *pFileName,CFrontCadDoc *pDoc);
	Tokens Parse(FILE *pIN);
	CCadLibrary *GetLib(void){return m_pLib;}
	//----------------------------------------
	// File Save Utils
	//----------------------------------------
	static char* SaveString(char* s, int n, Tokens Token, char* string);
	static char* SaveSize(char* s, int n, Tokens Token, CSize& size);
	static char* SavePoint(char* s, int n, Tokens Token, CPoint point);
	static char* SaveColor(char* s, int n, COLORREF color, Tokens Token);
	static char* SaveDecimalValue(char* s, int n, Tokens Token, int& value);
	static char* SaveTransparent(char* s, int n, Tokens Token, int& value);
	static Tokens LookupToken(const char* pName);
	static const char* LookupKeyword(Tokens Token);
};

