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

void CParseTableEntry::AddMember(CParseTableEntryMember* pPTE)
{
	m_nMembers++;
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
