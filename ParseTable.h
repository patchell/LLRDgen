#pragma once

class CParseTable
{
	CMatrix m_matParseTable;
	CSet* m_pTerminalSet;
	CSet* m_pNonTerminalSet;
	CLexeme** m_ppTerminalSymbols;	//lables for colums
	CLexeme** m_ppNonTerminalSymbols;	//lables for rows
	int m_Rows;	//same as number of non terminals
	int m_Cols;	//Same as number of terminals
public:
	CParseTable();
	virtual ~CParseTable();
	BOOL Create(CSet* pTerm, CSet* pNon);
	BOOL FillTable();
	BOOL Rule1(CLexeme *pY);
	BOOL Rule2(CLexeme* pY);
	int GetTerminalIndex(CLexeme* pLex);
	int GetTerminalIndex(CSymbol* pSym);
	int GetNonTerminalIndex(CSymbol* pSym);
	int CheckForConflicts();
	void SetTerminalSet(CSet* pTrml) { m_pTerminalSet = pTrml; }
	CSet* GetTerminalSet() { return m_pTerminalSet; }
	void SetNonTerminalSet(CSet* pNTRML) { m_pNonTerminalSet = pNTRML; }
	CSet* GetNonTerminalSet() { return m_pNonTerminalSet; }
	void Print(FILE* pO);
};

