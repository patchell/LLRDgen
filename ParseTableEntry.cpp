#include "Global.h"

CParseTableEntry::CParseTableEntry()
{
	m_pHead = 0;
	m_pTail = 0;
	m_nMembers = 0;
}

CParseTableEntry::~CParseTableEntry()
{
}

BOOL CParseTableEntry::Create()
{
	BOOL rV = TRUE;
	return rV;
}

BOOL CParseTableEntry::DoesNotContains(CRule* pRule)
{
	BOOL bNotThere = TRUE;
	CParseTableEntryMember* pETM;

	pETM = GetHead();
	while (pETM && bNotThere)
	{
		if (pETM->GetProduction() == pRule)
			bNotThere = FALSE;
		pETM = pETM->GetNext();
	}
	return bNotThere;
}

void CParseTableEntry::AddMember(CParseTableEntryMember* pPTE)
{
	if (DoesNotContains(pPTE->GetProduction()))
	{
		m_nMembers++;
		m_nEntries++;
		if (GetTail())
		{
			GetTail()->SetNext(pPTE);
			pPTE->SetPrev(GetTail());
			SetTail(pPTE);
		}
		else
		{
			SetTail(pPTE);
			SetHead(pPTE);
		}
	}
}

void CParseTableEntry::Print(FILE* pO, BOOL bLHS, BOOL bEOL, int nIndentSpaces)
{
	CParseTableEntryMember* pPTEM;

	pPTEM = GetHead();
	while (pPTEM)
	{
		pPTEM->Print(pO, bLHS, bEOL, nIndentSpaces);
		pPTEM = pPTEM->GetNext();
	}
}
