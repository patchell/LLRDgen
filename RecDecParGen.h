#pragma once

constexpr auto KINDOF_RULE_MIXED = 0;
constexpr auto KINDOF_RULE_ALL_TERMINALS = 1;
constexpr auto KINDOF_RULE_ALL_NONTERMINALS = 2;

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
	char m_aParserCppFile[256];
	char m_aParserHeaderFile[256];
	char m_aLexerCppFile[256];
	char m_aLexerHeaderFile[256];
	char m_aLexerClassName[256];
	char m_aParserClassName[256];
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
	//------------------------------------------
	// Code Generation Methods
	//------------------------------------------
	void CodeGeneration(FILE *pLogFile);
	void GenerateLexerFiles(FILE* pLogFile);
	void GenerateParserFiles(FILE* pLogFile);
	void GenerateParserMethodBody(
		FILE* pLogFile, 
		CRule* pRule, 
		int Kind
	);
	int KindOfProduction(FILE* pLogFile, CSymbol* pSym);
	void TargetExpect(FILE* pOut, CLexeme* pLex);
	void NonTerminalFunction(CLexeme* pLex);
	void ParserHeaderCommon(FILE* pLogFile, char* pClassName);
	//-----------------------------
	// Debug Methods
	//-----------------------------
	void PrintGrammar(FILE* pOut);
	FILE* GetLogFile() { return m_pLog; }
};

