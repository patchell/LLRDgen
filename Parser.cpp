#include "Global.h"

CParser::CParser()
{
	m_pOut = 0;
	m_pCurrentNonTerminal = 0;
	m_pCurrentRule = 0;
	m_FirstGrammarSymbol = TRUE;
}

CParser::~CParser()
{

}

BOOL CParser::Create(FILE* pIn, FILE* pOut)
{
	m_pOut = pOut;
	m_Lex.Create(pIn);
	GetTerminalSet()->Create("Terminals", "TERMINALS");
	GetNonTerminalSet()->Create("Non Terminals","NONTERMINALS");
	return TRUE;
}

void CParser::CloseFiles()
{
	fclose(m_pOut);
	m_Lex.CloseFiles();
}

void CParser::Parse()
{
	CLexer::Token LookaHeadToken;

	LookaHeadToken = GetLexer()->Lex();
	LookaHeadToken = LLgrammar(LookaHeadToken);
}

CLexer::Token CParser::LLgrammar(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	LLgrammar -> Terminals Grammar $
	//	        -> eof
	//-----------------------------------
	LookaHeadToken = Terminals(LookaHeadToken);
	LookaHeadToken = Grammar(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::Terminals(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	Terminals	-> TERMINALS TerminalList END_TERMINALS
	//-----------------------------------
	LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::TERMINALS);
	LookaHeadToken = TerminalList(LookaHeadToken);
	LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::END_TERMINALS);
	GetLexer()->GetSymTab()->PrintTable(LogFile());
	return LookaHeadToken;
}

CLexer::Token CParser::TerminalList(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	TerminalList	-> Terminal TerminalList_1
	//-----------------------------------
	LookaHeadToken = Terminal(LookaHeadToken);
	LookaHeadToken = TerminalList_1(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::TerminalList_1(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	TerminalList_1	-> ',' Terminal TerminalList_1
	//					-> .
	//-----------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token(','):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token(','));
		LookaHeadToken = Terminal(LookaHeadToken);
		LookaHeadToken = TerminalList_1(LookaHeadToken);
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::Terminal(CLexer::Token LookaHeadToken)
{
	//--------------------------------------
	// Terminal	-> STRING OptInit
	//--------------------------------------
	CSymbol* pSym = new CSymbol;
	CSetMember* pMember = new CSetMember;
	CRule* pRule = new CRule;
	CLexeme* pLexeme = new CLexeme;

	pSym->Create(GetLexer()->GetLexbuff());
	pSym->SetTokenValue(UINT(CLexer::Token::TERMINAL));
	pMember->Create(pSym);
	pRule->Create(pSym);
	pLexeme->Create();
	pLexeme->SetLexemeSymbol(pSym);
	pRule->AddLexeme(pLexeme);
	pSym->AddRule(pRule);
	pSym->GetFirstSet()->AddToSet(pMember);
	GetLexer()->GetSymTab()->AddSymbol(pSym);

	pMember = new CSetMember;
	pMember->Create(pSym);
	GetTerminalSet()->AddToSet(pMember);

	LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::STRING);
	LookaHeadToken = OptInit(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::OptInit(CLexer::Token LookaHeadToken)
{
	//------------------------------------
	// OptInit	-> '=' NUMBER
	//			-> .
	//------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token('='):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token('='));
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::NUMBER);
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::Grammar(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	Grammar		-> GRAMMAR ProductionList END_GRAMMAR
	//-----------------------------------
	LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::GRAMMAR);
	LookaHeadToken = ProductionList(LookaHeadToken);
	LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::END_GRAMMAR);
	return LookaHeadToken;
}

CLexer::Token CParser::ProductionList(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	ProductionList	-> Production ProductionList_1
	//-----------------------------------
	LookaHeadToken = Production(LookaHeadToken);
	LookaHeadToken = ProductionList_1(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::ProductionList_1(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	ProductionList_1-> ';' Production ProductionList_1
	//					->  .
	//-----------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token(';'):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token(';'));
		LookaHeadToken = Production(LookaHeadToken);
		LookaHeadToken = ProductionList_1(LookaHeadToken);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::Production(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	Production		-> NONTERMINAL RHSide
	//-----------------------------------
	// If the symbol has not yet been
	// defined, the token will be IDENT
	// Need to add the symbol to the
	// Symbol Table and change it's
	// token to NONTERMINAL
	//-----------------------------------
	CSymbol* pSym = 0;
	CSetMember* pMember;

	if (LookaHeadToken == CLexer::Token::IDENT)
	{
		pSym = GetLexer()->GetSymbol();
		if (pSym->GetLineWhereDefined() == 0)
			pSym->SetLineWhereDefined(GetLexer()->GetLineNumber());
		pSym->SetTokenValue(UINT(CLexer::Token::NONTERMINAL));
		if (m_FirstGrammarSymbol)
		{
			pSym->SetStartSymbol();
			pMember = new CSetMember;
			pMember->Create(CLexer::GetEndOfTokenStream());
			pSym->GetFollowSet()->AddToSet(pMember);
			m_FirstGrammarSymbol = FALSE;
			pMember = new CSetMember;
			pMember->Create(pSym);
			GetNonTerminalSet()->AddToSet(pMember);
			pSym->Print(LogFile());
		}
		GetLexer()->GetSymTab()->AddSymbol(pSym);
		pMember = new CSetMember;
		pMember->Create(pSym);
		GetNonTerminalSet()->AddToSet(pMember);
		LookaHeadToken = CLexer::Token::NONTERMINAL;
	}
	else if (LookaHeadToken == CLexer::Token::NONTERMINAL)
	{
		pSym = GetLexer()->GetSymbol();
		pMember = new CSetMember;
		pMember->Create(pSym);
		GetNonTerminalSet()->AddToSet(pMember);
		pSym->SetLineWhereDefined(GetLexer()->GetLineNumber());
	}
	switch (LookaHeadToken)
	{
	case CLexer::Token::NONTERMINAL:
		//------------------------
		// Add Procution to Grammar
		//------------------------
		pSym = GetLexer()->GetSymbol();
		SetCurrentNonTerminal(pSym);
		//---------------------------------------
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::NONTERMINAL);
		LookaHeadToken = RHSide(LookaHeadToken);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::RHSide(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	RHSide	-> REPLACEDBY LexemeList RHSide
	//			-> .
	//-----------------------------------
	BOOL Loop = TRUE;
	CRule* pRule;

	while (Loop)
	{
		switch (LookaHeadToken)
		{
		case CLexer::Token::REPLACED_BY:
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::REPLACED_BY);
			//----------------------------
			// Create New Rule
			//----------------------------
			pRule = new CRule;
			pRule->Create(GetCurrentNonTerminal());
			GetCurrentNonTerminal()->AddRule(pRule);
			m_pCurrentRule = pRule;
			//----------------------------
			LookaHeadToken = LexemeList(LookaHeadToken);
			break;
		default:
			Loop = FALSE;
			break;
		}
	}
	return LookaHeadToken;
}

CLexer::Token CParser::LexemeList(CLexer::Token LookaHeadToken)
{
	//-----------------------------------
	//	LexemeList	-> TERMINAL LexemeList
	//				-> NONTERMINAL LexemeList
	//				-> IDENT LexemeList
	//				-> ENDOFTOKENSTREAM LexemeList
	//				-> .
	//-----------------------------------
	CSymbol* pSym = 0;
	BOOL Loop = TRUE;
	CLexeme* pLexeme;

	while (Loop)
	{
		switch (LookaHeadToken)
		{
		case CLexer::Token::ENDOFTOKENSTREAM:
			pLexeme = new CLexeme;
			pLexeme->Create();
			pSym = GetLexer()->GetEndOfTokenStream();
			fprintf(LogFile(), "Parser:EOT:%s\n", pSym->GetName());
			pLexeme->SetLexemeSymbol(pSym);
			GetCurrentRule()->AddLexeme(pLexeme);
			GetCurrentNonTerminal()->SetStartSymbol();
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::ENDOFTOKENSTREAM);
			break;
		case CLexer::Token::TERMINAL:
			//---------------------------------
			// Add Terminal Lexeme
			//---------------------------------
			pLexeme = new CLexeme;
			pLexeme->Create();
			pSym = GetLexer()->GetSymbol();
			fprintf(LogFile(), "Parser:NT:%s\n", pSym->GetName());
			pLexeme->SetLexemeSymbol(pSym);
			GetCurrentRule()->AddLexeme(pLexeme);
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::TERMINAL);
			break;
		case CLexer::Token::NONTERMINAL:
			//---------------------------------
			// Add Non Terminal Lexeme
			//---------------------------------
			pLexeme = new CLexeme;
			pLexeme->Create();
			pSym = GetLexer()->GetSymbol();
			pLexeme->SetLexemeSymbol(pSym);
			GetCurrentRule()->AddLexeme(pLexeme);
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::NONTERMINAL);
			break;
		case CLexer::Token::IDENT:	//Makes NO sense
			pSym = GetLexer()->GetSymbol();
			pSym->SetTokenValue(UINT(CLexer::Token::NONTERMINAL));
			GetLexer()->GetSymTab()->AddSymbol(pSym);
			//---------------------------------
			// Add Non Terminal Lexeme
			//---------------------------------
			pLexeme = new CLexeme;
			pLexeme->Create();
			pLexeme->SetLexemeSymbol(pSym);
			GetCurrentRule()->AddLexeme(pLexeme);
			//-----------------------------------
			LookaHeadToken = CLexer::Token::NONTERMINAL;
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::NONTERMINAL);
			break;
		case CLexer::Token::EMPTY:	//emptyh rule
			pLexeme = new CLexeme;
			pLexeme->Create();
			pSym = GetLexer()->GetSymbol();
			pLexeme->SetLexemeSymbol(pSym);
			GetCurrentRule()->AddLexeme(pLexeme);
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
			break;
		default:
			Loop = FALSE;
			break;
		}
	}
	return LookaHeadToken;
}
