#pragma once

class CParser
{
	CStack m_ValueStack;
	CSymbol* m_pCurrentNonTerminal;
	CRule* m_pCurrentRule;
	CLexer m_Lex;
	BOOL m_FirstGrammarSymbol;
	int m_AutoIncTokenValue;;
public:
	CParser();
	virtual ~CParser();
	BOOL Create(FILE* pIn);
	void CloseFiles();
	virtual CLexer* GetLexer() { return &m_Lex; }
	CSymbol* GetCurrentNonTerminal() { return m_pCurrentNonTerminal; }
	void SetCurrentNonTerminal(CSymbol* pSym) { m_pCurrentNonTerminal = pSym; }
	virtual CRule* GetCurrentRule() { return m_pCurrentRule; }
	virtual void Parse();
	void SetAutoIncTokenValue(int v) { m_AutoIncTokenValue = v; }
	int GetAutoIncTokenValue() {
		return ++m_AutoIncTokenValue;
	}
	CStack* GetValueStack() { return &m_ValueStack; }
	//-------------------------------------
	// Parsing Methodes
	//-------------------------------------
private:
	CLexer::Token LLRDgramer(CLexer::Token LookaHeadToken);
	CLexer::Token TokenDef(CLexer::Token LookaHeadToken);
	CLexer::Token TokenDef_1(CLexer::Token LookaHeadToken);
	CLexer::Token GrammarSection(CLexer::Token LookaHeadToken);
	CLexer::Token GrammarStmts(CLexer::Token LookaHeadToken);
	CLexer::Token GrammarStmts_1(CLexer::Token LookaHeadToken);
	CLexer::Token GrammarStmt(CLexer::Token LookaHeadToken);
	CLexer::Token RHSide(CLexer::Token LookaHeadToken);
	CLexer::Token RHSide_1(CLexer::Token LookaHeadToken);
	CLexer::Token Rule(CLexer::Token LookaHeadToken);
	CLexer::Token Embedded(CLexer::Token LookaHeadToken);
	CLexer::Token ReturnValue(CLexer::Token LookaHeadToken);
	CLexer::Token TokenIdent(CLexer::Token LookaHeadToken);
	CLexer::Token TokenIdent_1(CLexer::Token LookaHeadToken);
	CLexer::Token OptInit(CLexer::Token LookaHeadToken);
	CLexer::Token TokenToken(CLexer::Token LookaHeadToken);
	void UnexpectedToken(CLexer::Token Tokenvalue);
};

