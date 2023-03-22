#include "Global.h"

CParser::CParser()
{
	m_pCurrentNonTerminal = 0;
	m_pCurrentRule = 0;
	m_FirstGrammarSymbol = TRUE;
	m_AutoIncTokenValue = 256;
}

CParser::~CParser()
{

}

BOOL CParser::Create(FILE* pIn)
{
	m_Lex.Create(pIn);
	return TRUE;
}

void CParser::CloseFiles()
{
	m_Lex.CloseFiles();
}

void CParser::Parse()
{
	CLexer::Token LookaHeadToken;
//	CRule* pRule;
	CSetMember* pSM, *pSM_EOT;
//	CLexeme* pLexeme;

	LookaHeadToken = GetLexer()->Lex();
	LookaHeadToken = LLRDgramer(LookaHeadToken);
	//------------------------------------------
	// All done, just need to tack $ onto the
	// head grammar rule.
	//------------------------------------------
	pSM = GetLexer()->GetSymTab()->GetNonTerminalSet()->GetHead();
	pSM_EOT = new CSetMember;
	pSM_EOT->Create(CLexer::GetEndOfTokenStream());
	pSM->GetSetMemberSymbol()->GetFollowSet()->AddToSet(pSM_EOT);
}

//-------------------------------------
// Parsing Methodes
//-------------------------------------

CLexer::Token CParser::LLRDgramer(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// LLRDgramer -> TokenDef;
	//------------------------------------------------
	LookaHeadToken = TokenDef(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::TokenDef(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// TokenDef	-> GrammarSection TokenDef_1;
	//------------------------------------------------
	LookaHeadToken = GrammarSection(LookaHeadToken);
	LookaHeadToken = TokenDef_1(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::TokenDef_1(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// TokenDef_1	-> TOKEN TokenIdent GrammarSection TokenDef_1
	//				-> .
	//				;
	//
	//------------------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token::TOKEN:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::TOKEN);
		LookaHeadToken = TokenIdent(LookaHeadToken);
		LookaHeadToken = GrammarSection(LookaHeadToken);
		LookaHeadToken = TokenDef_1(LookaHeadToken);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::GrammarSection(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// GrammarSection	-> GRAMMAR GrammarStmts
	//					-> .
	//					;
	//------------------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token::GRAMMAR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::GRAMMAR);
		LookaHeadToken = GrammarStmts(LookaHeadToken);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::GrammarStmts(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// GrammarStmts	-> GrammarStmt GrammarStmts_1;
	//------------------------------------------------
	LookaHeadToken = GrammarStmt(LookaHeadToken);
	LookaHeadToken = GrammarStmts_1(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::GrammarStmts_1(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// GrammarStmts_1	-> ';' GrammarStmt GrammarStmts_1
	//					-> .
	//					;
	//------------------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token(';'):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token(';'));
		LookaHeadToken = GrammarStmt(LookaHeadToken);
		LookaHeadToken = GrammarStmts_1(LookaHeadToken);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::GrammarStmt(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// GrammarStmt		-> IDENT RHSide
	//					-> NONTERMINAL RHSide
	//					-> .
	//					;
	//------------------------------------------------
	CSymbol* pSym;
	CStackItem* pSI;
	CSetMember* pSM;

	switch (LookaHeadToken)
	{
	case CLexer::Token::IDENT:
		pSym = GetLexer()->GetSymbol();
		GetLexer()->GetSymbol()->SetTokenValue(UINT(CLexer::Token::NONTERMINAL));
		if (m_FirstGrammarSymbol)
		{
			m_FirstGrammarSymbol = FALSE;
			pSym->SetStartSymbol();
		}
		GetLexer()->GetSymTab()->AddSymbol(pSym);
		//--------------------------------------------
		// Add To Non Terminal List (set)
		//--------------------------------------------
		pSM = new CSetMember;
		pSM->Create(pSym);
		GetLexer()->GetSymTab()->GetNonTerminalSet()->AddToSet(pSM);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::IDENT);
		pSI = new CStackItem();
		pSI->Create(CStackItem::ValueType::pSYMBOL, pSym);
		GetValueStack()->Push(pSI);
		LookaHeadToken = RHSide(LookaHeadToken);
		break;
	case CLexer::Token::NONTERMINAL:
		pSym = GetLexer()->GetSymbol();
		//--------------------------------------------
		// Add To Non Terminal List (set)
		//--------------------------------------------
		pSM = new CSetMember;
		pSM->Create(pSym);
		GetLexer()->GetSymTab()->GetNonTerminalSet()->AddToSet(pSM);
		//-------------------------------------------------------
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::NONTERMINAL);
		pSI = new CStackItem();
		pSI->Create(CStackItem::ValueType::pSYMBOL, pSym);
		GetValueStack()->Push(pSI);
		LookaHeadToken = RHSide(LookaHeadToken);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::RHSide(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// RHSide			-> Rule RHSide_1;
	//------------------------------------------------
	LookaHeadToken = Rule(LookaHeadToken);
	LookaHeadToken = RHSide_1(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::RHSide_1(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// RHSide_1		-> REPLACED_BY Rule RHSide_1
	//				-> .
	//				;
	//------------------------------------------------
	CRule* pRule;
	CSymbol* pSym;
	CStackItem* pSI;

	switch (LookaHeadToken)
	{
	case CLexer::Token::REPLACED_BY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::REPLACED_BY);
		pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
		CStackItem::CheckStackItem(pSI, CStackItem::ValueType::pSYMBOL);
		pSym = (CSymbol*)pSI->GetPointerData();
		pRule = new CRule();
		pRule->Create(pSym);
		pSI = new CStackItem;
		pSI->Create(CStackItem::ValueType::pRULE, pRule);
		pSym->AddRule(pRule);
		GetValueStack()->Push(pSI);
		LookaHeadToken = Rule(LookaHeadToken);
		GetValueStack()->Pop();
		LookaHeadToken = RHSide_1(LookaHeadToken);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::Rule(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// Rule			-> IDENT Rule
	//				-> NONTERMINAL Rule
	//				->TERMINAL Rule
	//				-> .
	//				;
	//------------------------------------------------
	CSymbol* pSym;
	CRule* pRule;
	CLexeme* pLexeme;
	CStackItem* pSI;
	BOOL Loop = TRUE;

	while (Loop)		//minimize recursion
	{
		switch (LookaHeadToken)
		{
		case CLexer::Token::IDENT:
			pSym = GetLexer()->GetSymbol();
			pSym->SetTokenValue(UINT(CLexer::Token::NONTERMINAL));
			pLexeme = new CLexeme;
			pLexeme->Create(pSym);
			pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
			CStackItem::CheckStackItem(pSI, CStackItem::ValueType::pRULE);
			pRule = (CRule*)pSI->GetPointerData();
			pRule->AddLexeme(pLexeme);
			GetLexer()->GetSymTab()->AddSymbol(pSym);
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::IDENT);
			break;
		case CLexer::Token::NONTERMINAL:
			pSym = GetLexer()->GetSymbol();
			pLexeme = new CLexeme;
			pLexeme->Create(pSym);
			pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
			CStackItem::CheckStackItem(pSI, CStackItem::ValueType::pRULE);
			pRule = (CRule*)pSI->GetPointerData();
			pRule->AddLexeme(pLexeme);
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::NONTERMINAL);
			break;
		case CLexer::Token::TERMINAL:
			pSym = GetLexer()->GetSymbol();
			pLexeme = new CLexeme;
			pLexeme->Create(pSym);
			pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
			CStackItem::CheckStackItem(pSI, CStackItem::ValueType::pRULE);
			pRule = (CRule*)pSI->GetPointerData();
			pRule->AddLexeme(pLexeme);
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::TERMINAL);
			break;
		case CLexer::Token::EMPTY:
			pSym = GetLexer()->GetEmpty();
			pLexeme = new CLexeme;
			pLexeme->Create(pSym);
			pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
			CStackItem::CheckStackItem(pSI, CStackItem::ValueType::pRULE);
			pRule = (CRule*)pSI->GetPointerData();
			pRule->AddLexeme(pLexeme);
			LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
			Loop = FALSE;
			break;
		default:
			Loop = FALSE;
			break;
		}
	}
	return LookaHeadToken;
}

CLexer::Token CParser::Embedded(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// Embedded	-> '{'  '}'
	//			-> .
	//			;
	//------------------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token('{'):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token('{'));
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token('}'));
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::ReturnValue(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// ReturnValue	-> ':' 'IDENT'
	//				-> .
	//				;
	//
	//------------------------------------------------
	switch (LookaHeadToken)
	{
	case CLexer::Token(':'):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token(':'));
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token('{'));
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token('}'));
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}


CLexer::Token CParser::TokenIdent(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// TokenIdent		-> TokenToken TokenIdent_1;
	//------------------------------------------------
	LookaHeadToken = TokenToken(LookaHeadToken);
	LookaHeadToken = TokenIdent_1(LookaHeadToken);
	return LookaHeadToken;
}

CLexer::Token CParser::TokenIdent_1(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// TokenIdent_1		-> IDENT OptInit TokenToken TokenIdent_1
	//					-> .
	//					;
	//------------------------------------------------
	CSymbol* pSym;
	CSetMember* pMember;
	CRule* pRule;
	CLexeme* pLexeme;
	CStackItem* pStackItem;

	switch (LookaHeadToken)
	{
	case CLexer::Token::IDENT:
		pSym = GetLexer()->GetSymbol();
		pSym->Create(GetLexer()->GetLexbuff());
		pSym->SetTokenValue(UINT(CLexer::Token::TERMINAL));
		pMember = new CSetMember;
		pMember->Create(pSym);
		pRule = new CRule;
		pRule->Create(pSym);
		pLexeme = new CLexeme;
		pLexeme->Create(pSym);
		pRule->AddLexeme(pLexeme);
		pSym->AddRule(pRule);
		pSym->GetFirstSet()->AddToSet(pMember);
		GetLexer()->GetSymTab()->AddSymbol(pSym);

		pStackItem = new CStackItem;
		pStackItem->Create(CStackItem::ValueType::pSYMBOL, pSym);;
		GetValueStack()->Push(pStackItem);

		pMember = new CSetMember;
		pMember->Create(pSym);
		GetLexer()->GetSymTab()->GetTerminalSet()->AddToSet(pMember);
		
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::IDENT);
		LookaHeadToken = OptInit(LookaHeadToken);
		LookaHeadToken = TokenToken(LookaHeadToken);
		LookaHeadToken = TokenIdent_1(LookaHeadToken);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::OptInit(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// OptInit	-> '=' NUMBER
	//			-> .
	//			;
	//------------------------------------------------
	CSymbol* pSym;
	CStackItem *pSI;
	int NumberValue;

	switch (LookaHeadToken)
	{
	case CLexer::Token('='):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token('='));
		pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
		CStackItem::CheckStackItem(pSI, CStackItem::ValueType::pSYMBOL);
		pSym = (CSymbol*)pSI->GetPointerData();
		NumberValue = GetLexer()->GetNumber();
		pSym->SetTargetTokenValue(NumberValue);
		SetAutoIncTokenValue(NumberValue);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::NUMBER);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
		CStackItem::CheckStackItem(pSI, CStackItem::ValueType::pSYMBOL);
		pSym = (CSymbol*)pSI->GetPointerData();
		NumberValue = GetAutoIncTokenValue();;
		pSym->SetTargetTokenValue(NumberValue);
		break;
	default:
			break;
	}
	return LookaHeadToken;
}

CLexer::Token CParser::TokenToken(CLexer::Token LookaHeadToken)
{
	//------------------------------------------------
	// TokenToken	-> STRING
	//				-> .
	//				;
	// 
	// This Method represents the production that 
	// gets the string that represents the TOKEN and
	// adds it to the SYMBOL
	//------------------------------------------------
	CSymbol* pSym;
	CStackItem* pSI;

	switch (LookaHeadToken)
	{
	case CLexer::Token::STRING:
		pSI = GetValueStack()->Look(CStack::StackPosition::STACK_TOP);
		if (pSI)
		{
			if (pSI->IsType(CStackItem::ValueType::pSYMBOL))
				pSym = (CSymbol*)pSI->GetPointerData();
			else
			{
				char* s = new char[256];
				sprintf_s(s, 256, "Value On Stack Mismatch:Expected %s Got %s",
					CStackItem::LookupValueType(CStackItem::ValueType::pSYMBOL),
					CStackItem::LookupValueType(pSI->GetType())
				);
				CLexer::Error(stderr, s);
				delete[] s;
				exit(-2);
			}
		}
		else
		{
			CLexer::Error(stderr, "Value Stack Was Empty");
			exit(-2);
		}
		pSym->SetName(GetLexer()->GetLexbuff());
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::STRING);
		break;
	case CLexer::Token::EMPTY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken, CLexer::Token::EMPTY);
		break;
	default:
		break;
	}
	return LookaHeadToken;
}

void CParser::UnexpectedToken(CLexer::Token Tokenvalue)
{
	char* s;

	s = new char[256];
	sprintf_s(s, 256, "Unexpected Token %s\n",
		CLexer::LookupTokenName(Tokenvalue)
	);
	GetLexer()->Error(stderr, s);
	delete[] s;
	exit(-1);
}
