#include "Global.h"

BOOL CSymbol::Create(const char* pName, TokenType TokType)
{
	m_FirstSet.Create(pName, "FIRST");
	m_FollowSet.Create(pName,"FOLLOW");
	m_TokenType = TokType;
	CBin::SetName(pName);
	return TRUE;
}

BOOL CSymbol::Compare(const char* name)
{
	BOOL rV = FALSE;

	if (strcmp(GetName(), name) == 0)
		rV = TRUE;
	return rV;
}

BOOL CSymbol::Compare(CSymbol* pSym)
{
	BOOL bSymsAgreel = FALSE;

	if (this == pSym)
		bSymsAgreel = TRUE;
	return bSymsAgreel;
}

char* CSymbol::GetTokenString()
{
	return nullptr;
}

BOOL CSymbol::DoesThisProductionHaveEpsilon()
{
	BOOL bThisProductionHasEpsilon = FALSE;
	CRule* pRule = GetHead();

	while (pRule && !bThisProductionHasEpsilon)
	{
		if (pRule->DoesThisRuleHaveEpsilon())
			bThisProductionHasEpsilon = TRUE;
		else
			pRule = pRule->GetNext();
	}
    return bThisProductionHasEpsilon;
}

void CSymbol::PrintProduction(FILE* pOut, BOOL bLHS, BOOL bEOL, int nIndentSpaces)
{
	CRule* pRH = GetHead();

	//	INDENT(IndentString, Indent);
	if (pOut)
	{
		fprintf(pOut, "%s\n", GetName());
		while (pRH)
		{
			pRH->Print(pOut);
			pRH = pRH->GetNext();
		}
	}
}

void CSymbol::Print(FILE* pOut, BOOL bLHS, BOOL bEOL, int nIndentSpaces)
{
	if (pOut)
	{
		fprintf(pOut, "%s: Token:%s TargetValue:%d NULLABLE(%d) START(%d)\n",
			GetName(),
			CToken::LookupTokenName(CToken::LLRD_Token(GetTokenValue())),
			GetTargetTokenValue(),
			IsNullable(),
			IsStartSymbol()
		);
		GetFirstSet()->Print(pOut, FALSE, TRUE, nIndentSpaces + 5);
		GetFollowSet()->Print(pOut, FALSE, TRUE, nIndentSpaces + 5);
	}
}

void CSymbol::SetNullable(BOOL bF)
{
	if (CToken::LLRD_Token::TERMINAL == CToken::LLRD_Token(GetTokenValue()))
	{
		fprintf(LogFile(), "???????? %s Nullable Set(%d)\n", GetName(), bF);
	}
	m_IsNullable = bF;
}


BOOL CSymbol::IsTerminal()
{
	BOOL rV = FALSE;

	if (m_TokenValue == CToken::LLRD_Token::TERMINAL)
	{
		rV = TRUE;
	}
	return rV;
}

BOOL CSymbol::IsNonTerminal()
{
	return ! IsTerminal();
}

void CSymbol::AddRule(CRule* pRule)
{
	m_nTotalRules++;
	if (GetTail())
	{
		GetTail()->SetNext(pRule);
		pRule->SetPrev(GetTail());
		SetTail(pRule);
	}
	else
	{
		SetTail(pRule);
		SetHead(pRule);
	}
}

