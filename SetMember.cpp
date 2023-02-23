#include "Global.h"

CSetMember::CSetMember()
{
	m_pLexeme = 0;
	m_pNext = 0;
	m_pPrev = 0;
	memset(SetName, 0, sizeof(SetName));
}

CSetMember::~CSetMember()
{
}

BOOL CSetMember::Create(CSymbol* pSym)
{
	CLexeme* pLxme;

	pLxme = new CLexeme;
	pLxme->Create();
	pLxme->SetLexemeSymbol(pSym);
	SetSetMemberLexem(pLxme);
	return TRUE;
}

void CSetMember::Copy(CSetMember* pSetMemberSource)
{
	CLexeme* pLexeme = new CLexeme;
	pLexeme->Create();
	pLexeme->Copy(pSetMemberSource->GetSetMemberLexeme());
	SetSetMemberLexem(pLexeme);
}

BOOL CSetMember::Compare(CLexeme* pLex)
{
	BOOL bLexemsAgree;
	bLexemsAgree = GetSetMemberLexeme()->Compare(pLex);
    return bLexemsAgree;
}

BOOL CSetMember::Compare(CSymbol* pSym)
{
	BOOL bSymsAgree;

	bSymsAgree = GetSetMemberSymbol()->Compare(pSym);
	return bSymsAgree;
}

void CSetMember::Print(FILE* pOut, int DelimiterChar, BOOL bLHS, BOOL bEOL, int nIndentSpaces)
{
	fprintf(pOut, "%c\'%s\'", DelimiterChar, GetSetMemberLexeme()->GetLexemeSymbol()->GetName());
	if (bEOL)
		fprintf(pOut, "\n");
}
