#pragma once


class CRecDecParGen :public CParser
{
	CParseTable m_PaarseTable;
	CSet m_NotNullables;
	CSet m_Nullables;
	FILE* m_pLog;
public:
	CRecDecParGen();
	virtual ~CRecDecParGen();
	BOOL Create(FILE* pIn, FILE* pOut, FILE* pLog);
	void CloseFiles();
	BOOL Run();
	void CreateFirstSets(FILE* pOut);
	void CreateFollowSets(FILE* pOut);
	BOOL ApplyFollowRulesTo(CSymbol* pSym);
	void CreateNullableSet(FILE* pOut);
	void CreateNonTerminals(FILE* pOut);
	void CreateNotNullablesSet(FILE* pOut);
	CSet* GetNotNullables() { return &m_NotNullables; }
	CSet* GetNullableSet(){return &m_Nullables; }
	CParseTable* GetParseTable() { return &m_PaarseTable; }
	//-----------------------------
	// Debug Methods
	//-----------------------------
	void PrintGrammar(FILE* pOut);
	FILE* GetLogFile() { return m_pLog; }
};

