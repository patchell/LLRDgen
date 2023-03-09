#include "Global.h"

CParseTableEntry::CParseTableEntry()
{
	m_pHead = 0;
	m_pTail = 0;
	m_nMembers = 0;
	m_pColName = 0;
	m_pRowName = 0;
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

void CParseTableEntry::Print(
	FILE* pO, 
	BOOL bLHS, 
	BOOL bEOL, 
	int nIndentSpaces,
	BOOL bNumberLines
)
{
	int Item = 0;
	CParseTableEntryMember* pPTEM;
	char* s = 0;

	if (pO)
	{
		pPTEM = GetHead();
		while (pPTEM)
		{
			if (bNumberLines)
			{
				if (s == 0)
				{
					s = new char[256];
					IndentString(s, nIndentSpaces);
					nIndentSpaces = 0;
				}
				fprintf(pO, "%s%d. ", s, ++Item);
			}
			pPTEM->Print(pO, bLHS, bEOL, 1);
			pPTEM = pPTEM->GetNext();
		}
	}
	if(s) delete[] s;
}
