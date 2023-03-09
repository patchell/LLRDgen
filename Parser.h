#pragma once

typedef struct {
	const char* pTokenName;
	int Token;
} TOKENS;

class CGrammar;

class CParser
{
	CSymbol* m_pCurrentNonTerminal;
	CRule* m_pCurrentRule;
	CLexer m_Lex;
	FILE* m_pOut;
	BOOL m_FirstGrammarSymbol;
public:
	CParser();
	virtual ~CParser();
	BOOL Create(FILE* pIn, FILE* pOut);
	void CloseFiles();
	virtual CLexer* GetLexer() { return &m_Lex; }
	CSymbol* GetCurrentNonTerminal() { return m_pCurrentNonTerminal; }
	void SetCurrentNonTerminal(CSymbol* pSym) { m_pCurrentNonTerminal = pSym; }
	virtual CRule* GetCurrentRule() { return m_pCurrentRule; }
	virtual void Parse();
	//---------------------------------------
	// Debug
	//---------------------------------------
	FILE* GetOutput() { return m_pOut; }
	//-------------------------------------
	// Parsing Methodes
	//-------------------------------------
private:
	CLexer::Token LLgrammar(CLexer::Token LookaHeadToken);
	CLexer::Token Terminals(CLexer::Token LookaHeadToken);
	CLexer::Token TerminalList(CLexer::Token LookaHeadToken);
	CLexer::Token TerminalList_1(CLexer::Token LookaHeadToken);
	CLexer::Token Terminal(CLexer::Token LookaHeadToken);
	CLexer::Token OptInit(CLexer::Token LookaHeadToken);
	CLexer::Token Grammar(CLexer::Token LookaHeadToken);
	CLexer::Token ProductionList(CLexer::Token LookaHeadToken);
	CLexer::Token ProductionList_1(CLexer::Token LookaHeadToken);
	CLexer::Token Production(CLexer::Token LookaHeadToken);
	CLexer::Token RHSide(CLexer::Token LookaHeadToken);
	CLexer::Token LexemeList(CLexer::Token LookaHeadToken);
	CLexer::Token LexemeList_1(CLexer::Token LookaHeadToken);
	CLexer::Token TermNonTerm(CLexer::Token LookaHeadToken);
};

