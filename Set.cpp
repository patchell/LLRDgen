#include "Global.h"

CSet::CSet()
{
	m_pHead = 0;
	m_pTail = 0;
	m_pNext = 0;
	m_pPrev = 0;
	m_nNumberOfMembers = 0;
	for (int i = 0; i < 128; ++i)
		m_aName[i] = 0;
}

CSet::~CSet()
{

}

BOOL CSet::Create(const char* pName, const char* pClassName)
{
	SetName(pName, pClassName);
	return TRUE;
}

void CSet::SetName(const char* pName, const char* pClassName)
{
	sprintf_s(m_aName, 128, "%s[\'%s\']", pClassName,pName);
}

BOOL CSet::Copy(CSet* pSourceSet)
{
	//--------------------------------------
	// returns TRUE is anything from pSetA
	// was added to this set.
	// Otherwise FALSE;
	//--------------------------------------
	BOOL bChanged = FALSE;

	CSetMember* pSM = pSourceSet->GetHead();
	while (pSM)
	{
		if (IsNotAlreadyInSet(pSM))
		{
			bChanged = TRUE;
			CSetMember* pNewSM = new CSetMember;
			pNewSM->Create(pSM->GetSetMemberLexeme()->GetLexemeSymbol());
			AddToSet(pNewSM);
		}
		pSM = pSM->GetNext();
	}
	return bChanged;
}

BOOL CSet::CopyExceptEmpty(CSet* pSourceSet)
{
	//--------------------------------------
	// returns TRUE is anything from pSetA
	// was added to this set.
	// Otherwise FALSE;
	//--------------------------------------
	BOOL bChanged = FALSE;

	CSetMember* pSM = pSourceSet->GetHead();
	while (pSM)
	{
		if (IsNotAlreadyInSet(pSM))
		{
			if (pSM->GetSetMemberSymbol()->IsNotEmpty())
			{
				bChanged = TRUE;
				CSetMember* pNewSM = new CSetMember;
				pNewSM->Create(pSM->GetSetMemberLexeme()->GetLexemeSymbol());
				AddToSet(pNewSM);
			}
		}
		pSM = pSM->GetNext();
	}
	return bChanged;
}

BOOL CSet::Union(CSet* pSetB, CSet& SetC)
{
	//----------------------------------------
	// Union
	// 
	// parameters:
	// pSetB....pointer to set to make union with this
	// SetC.....reference to destination set
	//----------------------------------------
	BOOL bChanged, rV1, rV2;
	
	rV1 = SetC.Copy(this);
	rV2 = SetC.Copy(pSetB);
	bChanged = rV1 || rV2;
	SetC.Print(LogFile(), FALSE, FALSE, 0);
	fprintf(LogFile(), " <= ");
	Print(LogFile(), FALSE, FALSE, 0);
	fprintf(LogFile(), " U ");
	pSetB->Print(LogFile(), FALSE, TRUE);
	return bChanged;
}

BOOL CSet::Union(CSet* pSetA)
{
	//--------------------------------------
	// returns TRUE is anything from pSetA
	// was added to this set.
	// Otherwise FALSE;
	//--------------------------------------
	BOOL bChanged;

	Print(LogFile(), FALSE,FALSE,0);
	fprintf(LogFile(), " U ");
	pSetA->Print(LogFile(),FALSE,FALSE,0);
	bChanged = Copy(pSetA);
	fprintf(LogFile(), " => ");
	Print(LogFile(), FALSE, TRUE, 0);

	return bChanged;
}

BOOL CSet::UnionExceptEmpty(CSet* pSetA)
{
	//--------------------------------------
	// returns TRUE is anything from pSetA
	// was added to this set.
	// Otherwise FALSE;
	//--------------------------------------
	BOOL bChanged;

	bChanged = CopyExceptEmpty(pSetA);
	return bChanged;
}

BOOL CSet::Intersection(CSet* pSetB, CSet& SetC)
{
	return 0;
}

BOOL CSet::IsMemberOf(CSet* pSetB)
{
	return 0;
}

BOOL CSet::IsNotAlreadyInSet(CSetMember* pSetMember)
{
	BOOL rV;

	rV = IsAlreadyInSet(pSetMember);
	return !rV;
}
BOOL CSet::IsAlreadyInSet(CSetMember* pSetMembr)
{
	BOOL rV = FALSE;
	CSetMember* pSM;

	pSM = GetHead();
	while (pSM && !rV)
	{
		if (pSM->GetSetMemberLexeme()->GetLexemeSymbol() ==
			pSetMembr->GetSetMemberLexeme()->GetLexemeSymbol()
		)
		{
			rV = TRUE;
		}
		else
			pSM = pSM->GetNext();
	}
	return rV;
}

BOOL CSet::Contains(CSymbol* pSym)
{
	CSetMember* pMemBr;
	BOOL rV = FALSE;

	fprintf(LogFile(), "Is %s in Set %s\n", pSym->GetName(), GetName());
	pMemBr = GetHead();
	while (pMemBr && !rV)
	{
		if (pSym == pMemBr->GetSetMemberLexeme()->GetLexemeSymbol())
			rV = TRUE;
		else
			pMemBr = pMemBr->GetNext();
	}
	fprintf(LogFile(), "%s\n", rV ? "TRUE" : "FALSE");
    return rV;
}

BOOL CSet::Contains(CLexeme* pLexeme)
{
	return Contains(pLexeme->GetLexemeSymbol());
}

BOOL CSet::DoesNotContain(CSymbol* pSym)
{
	CSetMember* pMemBr;
	BOOL rV = TRUE;

	pMemBr = GetHead();
	if (LogFile())
	{
		fprintf(LogFile(), "Is \'%s\' Not Contained in \'%s\'\n",
			pSym->GetName(),
			GetName()
		);
	}
	while (pMemBr && rV)
	{
		if (LogFile())
		{
			fprintf(LogFile(), "\t\t\tCompare \'%s\' To \'%s\'\n",
				pSym->GetName(),
				pMemBr->GetSetMemberLexeme()->GetName()
			);
		}
		if (pSym == pMemBr->GetSetMemberLexeme()->GetLexemeSymbol())
			rV = FALSE;
		else
			pMemBr = pMemBr->GetNext();
	}
	fprintf(LogFile(), "%s\n", rV ? "TRUE" : "FALSE");
	return rV;
}

BOOL CSet::AddToSet(CSetMember* pNewMember)
{
	BOOL rV = FALSE;
	if (IsNotAlreadyInSet(pNewMember))
	{
		rV = TRUE;
		if (GetTail())
		{
			GetTail()->SetNext(pNewMember);
			pNewMember->SetPrev(GetTail());
			SetTail(pNewMember);
		}
		else
		{
			SetTail(pNewMember);
			SetHead(pNewMember);
		}
		++m_nNumberOfMembers;
	}
	return rV;
}

void CSet::RemoveFromSet(CSetMember* pObj)
{
	if (pObj == GetHead())
	{
		SetHead(pObj->GetNext());
		if (GetHead())
			GetHead()->SetPrev(0);
		else
			SetTail(0);
	}
	else if (pObj == GetTail())
	{
		SetTail(pObj->GetPrev());
		if (GetTail())
			GetTail()->SetNext(0);
		else
			SetHead(0);
	}
	else
	{
		pObj->GetNext()->SetPrev(pObj->GetPrev());
		pObj->GetPrev()->SetNext(pObj->GetNext());
	}
	pObj->SetNext(0);
	pObj->SetPrev(0);
	--m_nNumberOfMembers;
}

void CSet::MakeEmpty()
{
	CSetMember* pSM, *pTemp;

	pSM = GetHead();
	while (pSM)
	{
		pTemp = pSM->GetNext();
		RemoveFromSet(pSM);
		delete pSM;
		pSM = pTemp;
	}
}

void CSet::Print(FILE* pOut, BOOL bLHS, BOOL bEOL, int nIndentSpaces)
{
	CSetMember* pMember = GetHead();
	int DelemiterChar;

	fprintf(pOut, "\'%s\' {", GetName());
	while (pMember)
	{
		if (pMember->GetPrev())
			DelemiterChar = ',';
		else
			DelemiterChar = ' ';
		pMember->Print(pOut, DelemiterChar, FALSE, FALSE,0);
		pMember = pMember->GetNext();
	}
	fprintf(pOut, " }");
	if (bEOL)
		fprintf(pOut, "\n");
}
