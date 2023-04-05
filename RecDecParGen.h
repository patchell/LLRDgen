#pragma once

constexpr auto KINDOF_RULE_MIXED = 0;
constexpr auto KINDOF_RULE_ALL_TERMINALS = 1;
constexpr auto KINDOF_RULE_ALL_NONTERMINALS = 2;
constexpr auto TOKEN_TYPE_POSTDEFINED = 1;
constexpr auto TOKEN_TYPE_PREDEFINED = 2;

class CRecDecParGen :public CParser
{
	CParseTable m_PaarseTable;
	CSet m_NotNullables;
	CSet m_Nullables;
	FILE* m_pLog;
	FILE* m_pParserCppFile;
	FILE* m_pParserHeaderFile;
	FILE* m_pLexerCppFile;
	FILE* m_pLexerHeaderFile;
	FILE* m_pTokenCppFile;
	FILE* m_pTokenHeaderFile;

	char m_aParserCppFile[256];
	char m_aParserHeaderFile[256];
	char m_aLexerCppFile[256];
	char m_aLexerHeaderFile[256];
	char m_aTokenCppName[256];
	char m_aTokenHeaderName[256];

	char m_aLexerClassName[256];
	char m_aParserClassName[256];
	char m_aTokenClassName[256];
	char m_aTokenEnumClassName[256];
public:
	CRecDecParGen();
	virtual ~CRecDecParGen();
	BOOL Create(FILE* pIn, FILE* pLog);
	void CloseFiles();
	BOOL Run();
	int CheckForDirectRecursion(FILE* pO, CSet* pNonTerminals);
	void CreateFirstSets(FILE* pOut);
	void CreateFollowSets(FILE* pOut);
	BOOL ApplyFollowRulesTo(FILE* pOut, CSymbol* pSym);
	void CreateNullableSet(FILE* pOut);
	void CreateNotNullablesSet(FILE* pOut);
	CSet* GetNotNullables() { return &m_NotNullables; }
	CSet* GetNullableSet(){return &m_Nullables; }
	CParseTable* GetParseTable() { return &m_PaarseTable; }
	char* GetParserClassName() { return m_aParserClassName; }
	char* GetLexerClassName() { return m_aLexerClassName; }
	CSymTab* GetSymTab() {
		return GetLexer()->GetSymTab();
	}
	//------------------------------------------
	// Code Generation Methods
	//------------------------------------------
	void CodeGeneration(FILE *pLogFile);
	void GenerateLexerFiles(FILE* pLogFile);
	void GenerateTokenFiles(FILE*pLog);
	void GenerateParserFiles(FILE* pLogFile);
	void GenerateParserMethodBody(
		FILE* pLogFile, 
		CRule* pRule, 
		int Kind
	);
	void GenBreak(FILE* pO, int Tabs);
	void GenExpect(FILE* pO, int Tabs, CLexeme* pTokenLexeme, int Type);
	void GenDefault(FILE* pO, int Tabs = 1);
	void GenCase(FILE *, int Tabs, CLexeme* pLexeme, int Type);
	void GenSwitch(FILE* pOut, int Tabs);
	int KindOfProduction(FILE* pLogFile, CSymbol* pSym);
	void NonTerminalFunction(FILE* pOut, int Tabs, CLexeme* pLex);
	//---------------------------------
	// Parser Header File Methodes
	//---------------------------------
	void ParserHeaderCommon(FILE* pLogFile, char* pClassName);
	void GenMethodeDecl(FILE* pOut, int Tabs, CLexeme* pLexeme);
	//----------------------------------------------------
	// Token Files Methods
	//----------------------------------------------------
	void GenToken(CSymbol* pSym, int Tabs, int InitValue);
	int CountPredefinedTokens();
	void GenTokenNameItem(CSymbol* pSym, int Tabs, BOOL bComma);
	void GenTokenEnums();
	void GenTokenNames();
	//-----------------------------
	// Debug Methods
	//-----------------------------
	void PrintGrammar(FILE* pOut);
	FILE* GetLogFile() { return m_pLog; }
};

