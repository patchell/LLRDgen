#include "Global.h"

CRule::CRule()
{
	m_pHead = 0;
	m_pTail = 0;
	m_pNext = 0;
	m_pPrev = 0;
	m_nLexemes = 0;
	m_NULL = 0;
	m_pLHS = 0;
}

CRule::~CRule()
{
}

BOOL CRule::Create(CSymbol* pLHS)
{
	m_pLHS = pLHS;
	return TRUE;
}


BOOL CRule::FIRST(CLexeme *pY1, CSet& FirstSet)
{
	//-----------------------------------
	//	1.	If X is a terminal then 
	//			First(X) is just X!
	//	2.	If there is a Production
	//			 X -> e then add e to 
	//			first(X)
	//	3.	If there is a Production 
	//			X -> Y1Y2..Yk then add 
	//			first(Y1Y2..Yk) to 
	//			first(X)
	//	4.	First(Y1Y2..Yk) is either
	//		1.	First(Y1) (if First(Y1) 
	//				doesn't contain epsilon)
	//		2.	OR(if First(Y1) does 
	//			contain epsilon) then 
	// 
	//			First(Y1Y2..Yk) is 
	//			everything in First(Y1) 
	//			< except for epsilon > 
	// 
	//			as well as everything in First(Y2..Yk)
	//		3.	If First(Y1) First(Y2)..
	//			First(Yk) all contain epsion 
	//			then add epsilon to 
	//			First(Y1Y2..Yk) as well.
	//-----------------------------------
	BOOL bChanged = FALSE;
	CLexeme* pLexeme = GetHead();
	int n = GetNumLexemes();


	if (pY1->IsEmpty())	//Rule 2.
	{
		bChanged = FirstSet.Union(CLexer::GetEmpty()->GetFirstSet());
		fprintf(LogFile(), "Add %s", pY1->GetName());
	}
	else if (pY1->GetFirstSet()->DoesNotContain(CLexer::GetEmpty()))
	{
		//Rule 4.1
		fprintf(LogFile(), "Add First(%s)", pY1->GetName());
		pY1->GetFirstSet()->Print(LogFile(),FALSE,FALSE,0);
		bChanged = FirstSet.Union(pY1->GetFirstSet());
	}
	else
	{
		//Rule 4.2
		if (pY1->GetFirstSet()->Contains(CLexer::GetEmpty()))
		{
			bChanged = this->FIRST_Y1Y2__Yk(pY1, FirstSet);
		}
	}
	//Rule 4.3
	if (DoAllLexemesContainEpsilong())
		FirstSet.Union(CLexer::GetEmpty()->GetFirstSet());
	return bChanged;
}


BOOL CRule::FIRST_Y1Y2__Yk(
	CLexeme* pY1, 
	CSet& FirstSet
)
{
	//-------------------------------------
	//	4.	First(Y1Y2..Yk) is either
	//		2.	OR(if First(Y1) does 
	//			contain epsilon) then 
	//			First(Y1Y2..Yk) is 
	//			everything in First(Y1) 
	//			< except for epsilon > as well 
	//			as everything in First(Y2..Yk)
	//-------------------------------------
	BOOL bChanged = FALSE;

	if (pY1->GetNext() == 0)
	{
		//---------------------------------
		// End of the chain, from here we
		// will be only returning.
		//---------------------------------
		fprintf(LogFile(), "End of Y1Y2...Yk Chain\n");
	}
	else
	{
		//-------------------------------------------
		// There are still more Lexemes
		//-------------------------------------------
		bChanged = FIRST_Y1Y2__Yk(
			pY1->GetNext(), 
			FirstSet
		);
		bChanged |= FirstSet.UnionExceptEmpty(pY1->GetFirstSet());
	}
	return bChanged;
}

BOOL CRule::FOLLOW()
{
	//	1.	First put $(the end of input 
	//		marker) in Follow(S) (S is the
	//		 start symbol)
	//	2.	If there is a production A->aBb,
	//		 (where a can be a whole string)
	//		 then everything in FIRST(b) 
	//		except for e is placed in FOLLOW(B).
	//		NOTE:We are looking for a NON Terminal
	//		followed by "something", which can be
	//		either a Terminal or NON Terminal
	//	3.	If there is a production A->aB, then
	//		 everything in FOLLOW(A) is in FOLLOW(B)
	//		NOTE:B is a Non Terminal
	//	4.	If there is a production A->aBb,
	//		 where FIRST(b) contains e, then 
	//		everything in FOLLOW(A) is in 
	//		FOLLOW(B)
	//		NOTE:We have a NON Terminal followed
	//		by another NON Terminal that has
	//		e in its first set
	//-------------------------------------------
	BOOL bChanged = FALSE;
	CLexeme* pLast, * pNextToLast;

	pLast = GetTail();
	pNextToLast = pLast->GetPrev();
	if (pNextToLast &&
		pNextToLast->IsNonTerminal() &&
		pLast->GetFirstSet()->Contains(CLexer::GetEmpty())
	)
	{
		//------------
		// Rule #4
		//------------
		fprintf(LogFile(), "Apply Rule 4\n");
//		bChanged = FOLLOW_RULE4();
		fprintf(LogFile(), "----------\n");
	}
	else if (pNextToLast && 
		pNextToLast->IsNonTerminal()
	)
	{
		//------------
		// Rule #2
		//------------
		fprintf(LogFile(), "Apply Rule 2\n");
//		bChanged = FOLLOW_RULE2();
		fprintf(LogFile(), "----------\n");
	}
	else if (pLast->IsNonTerminal())
	{
		//------------
		// Rule #3
		//------------
		fprintf(LogFile(), "Apply Rule 3\n");
//		bChanged = FOLLOW_RULE3();
		fprintf(LogFile(), "----------\n");
	}
	fprintf(LogFile(), "Changed?:%s\n", bChanged ? "TRUE" : "FALSE");
	return bChanged;
}

BOOL CRule::FOLLOW_RULE2(CSymbol* pA, CSymbol* pB, CSymbol *pb)
{
	//-------------------------------------------
	//	2.	If there is a production A->aBb,
	//		 (where a can be a whole string)
	//		 then everything in FIRST(b) 
	//		except for e is placed in FOLLOW(B).
	//-------------------------------------------
	BOOL bChanged;

	bChanged = pB->GetFollowSet()->UnionExceptEmpty(pb->GetFirstSet());
	return bChanged;
}

BOOL CRule::FOLLOW_RULE3(CSymbol *pA, CSymbol* pB)
{
	//-------------------------------------------
	//	3.	If there is a production A->aB, then
	//		 everything in FOLLOW(A) is in 
	//		FOLLOW(B)
	//-------------------------------------------
	BOOL bChanged;

	bChanged = pB->GetFollowSet()->Union(pA->GetFollowSet());
	return bChanged;
}

BOOL CRule::FOLLOW_RULE4(CSymbol* pA, CSymbol* pB, CSymbol *pb)
{
	//-------------------------------------------
	//	4.	If there is a production A->aBb,
	//		 where FIRST(b) contains e, then 
	//		everything in FOLLOW(A) is in 
	//		FOLLOW(B)	
	//-------------------------------------------
	BOOL bChanged;

	bChanged = pB->GetFollowSet()->Union(pA->GetFollowSet());
	return bChanged;
}

BOOL CRule::DoAllLexemesContainEpsilong()
{
	BOOL bAllLexemesContainEpsilong = TRUE;
	CLexeme* pLexeme = GetHead();

	while (pLexeme && bAllLexemesContainEpsilong)
	{
		bAllLexemesContainEpsilong = pLexeme->GetLexemeSymbol()->DoesThisProductionHaveEpsilon();
		pLexeme = pLexeme->GetNext();
	}
	return bAllLexemesContainEpsilong;
}

BOOL CRule::DoesThisRuleHaveEpsilon()
{
	//--------------------------------------
	// Epsilon had damn well be the first
	// Lexeme in the rule.
	//--------------------------------------
	BOOL bRuleHasEpsilon = TRUE;
	CLexeme* pLexeme;
	CSymbol* pEpsilon;

	pEpsilon = CLexer::GetEmpty();
	pLexeme = GetHead();
	if (pLexeme->GetLexemeSymbol() != pEpsilon)
		bRuleHasEpsilon = FALSE;
	return bRuleHasEpsilon;
}

BOOL CRule::DoesThisRuleHave(CSymbol* pSym)
{
	BOOL bYes = FALSE;
	CLexeme* pLexemeLast;
	CLexeme* pLexemeNextToLast;
	int Count = 0;

	pLexemeLast = GetTail();
	pLexemeNextToLast = pLexemeLast->GetPrev();
	if (pLexemeNextToLast)
	{
		if (pLexemeNextToLast->GetLexemeSymbol() == pSym)
		{
			fprintf(LogFile(), "\t%s", GetLHS()->GetName());
			Print(LogFile());
			if (pLexemeNextToLast->IsNonTerminal())
			{
				if (pLexemeLast->GetFirstSet()->Contains(CLexer::GetEmpty()))
				{
					fprintf(LogFile(), "Rule 2 3 4:%s", GetLHS()->GetName());
					Print(LogFile());
					bYes |= FOLLOW_RULE2(
						GetLHS(),
						pLexemeNextToLast->GetLexemeSymbol(),
						pLexemeLast->GetLexemeSymbol()
					);
					bYes |= FOLLOW_RULE3(
						GetLHS(),
						pLexemeLast->GetLexemeSymbol()
					);
					bYes |= FOLLOW_RULE4(
						GetLHS(), 
						pLexemeNextToLast->GetLexemeSymbol(),
						pLexemeLast->GetLexemeSymbol()
					);
				}
				else 
				{
					fprintf(LogFile(), "Rule 2 3:%s", GetLHS()->GetName());
					Print(LogFile());
					bYes = FOLLOW_RULE2(
						GetLHS(),
						pLexemeNextToLast->GetLexemeSymbol(),
						pLexemeLast->GetLexemeSymbol()
					);
					bYes |= FOLLOW_RULE3(
						GetLHS(),
						pLexemeLast->GetLexemeSymbol()
					);
				}
			}
			else if (pLexemeLast->GetLexemeSymbol() == pSym)
			{
				fprintf(LogFile(), "Rule 3:%s", GetLHS()->GetName());
				Print(LogFile());
				bYes = FOLLOW_RULE3(GetLHS(), pLexemeLast->GetLexemeSymbol());
			}
		}
	}
	else if (pLexemeLast->GetLexemeSymbol() == pSym)
	{
		fprintf(LogFile(), "Rule 3:%s", GetLHS()->GetName());
		Print(LogFile());
		FOLLOW_RULE3(GetLHS(), pLexemeLast->GetLexemeSymbol());
	}
	return bYes;
}

BOOL CRule::RuleTotallyNullable()
{
	BOOL rV = FALSE;
	CLexeme* pLexeme = GetHead();
	int n = this->GetNumLexemes();
	int count = 0;

	while (pLexeme)
	{
		if (pLexeme->IsNullable())
			count++;
		pLexeme = pLexeme->GetNext();
	}
	if (count == n)
		rV = TRUE;
	return 0;
}

void CRule::Print(FILE* pOut, BOOL bLHS, BOOL bEOL, int nIndentSpaces)
{
	CLexeme* pL = GetHead();
	char* s = new char[256];

	if (bLHS)
		fprintf(pOut, "%s%s", 
			IndentString(s, nIndentSpaces + 2),
			GetLHS()->GetName());
	fprintf(pOut, "->");
	if (pL)
	{
		while (pL)
		{
			pL->Print(pOut,FALSE,TRUE, nIndentSpaces);
			pL = pL->GetNext();
		}
	}
	else
	{
		fprintf(pOut, " .");
	}
	if(bEOL)
		fprintf(pOut, "\n");
	delete[] s;
}

int CRule::AddLexeme(CLexeme* pRO)
{
	if (GetTail())
	{
		GetTail()->SetNext(pRO);
		pRO->SetPrev(GetTail());
		SetTail(pRO);
	}
	else
	{
		SetTail(pRO);
		SetHead(pRO);
	}
	return IncNumLexemes();
}
