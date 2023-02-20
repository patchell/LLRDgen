#pragma once

class CRule
{
	CRule* m_pNext;
	CRule* m_pPrev;
	CLexeme* m_pHead;
	CLexeme* m_pTail;
	int m_nLexemes;
	BOOL m_NULL;
	CSymbol* m_pLHS;
public:
	CRule();
	virtual ~CRule();
	BOOL Create(CSymbol* pLeftHandSide);
	CSymbol* GetLHS() { return m_pLHS; }
	BOOL FIRST(CLexeme* pY1, CSet& FirstSet);
    BOOL FIRST_Y1Y2__Yk(
		CLexeme* pY11, 
		CSet& FirstSet
	);
	BOOL FOLLOW();
	BOOL FOLLOW_RULE2(CSymbol* pA, CSymbol* pB, CSymbol *pb);
	BOOL FOLLOW_RULE3(CSymbol* pA, CSymbol* pB);
	BOOL FOLLOW_RULE4(CSymbol* pA, CSymbol* pB, CSymbol *pb);
	BOOL DoAllLexemesContainEpsilong();
	BOOL DoesThisRuleHaveEpsilon();
	BOOL DoesThisRuleHave(CSymbol* pSym);
	BOOL IsNull() {
		return m_NULL;
	}
	int GetNumLexemes() { return m_nLexemes;}
	int IncNumLexemes() { return m_nLexemes++; }
	BOOL RuleTotallyNullable();
	//-----------------------------
	// Debug
	//-----------------------------
	void Print(FILE* pOut, 
		BOOL bLHS=FALSE, 
		BOOL bEOL = TRUE, 
		int IndentSpaces = 0
	);
	//-----------------------------
	// Linked List Managment
	//-----------------------------
	void SetNext(CRule* pN) { m_pNext = pN; }
	CRule* GetNext() { return m_pNext; }
	void SetPrev(CRule* pP) { m_pPrev = pP; }
	CRule* GetPrev() { return m_pPrev; }
	//-----------------------------
	// Rule Object Managment
	//-----------------------------
	void SetHead(CLexeme* pH) { m_pHead = pH; }
	CLexeme* GetHead() { return m_pHead; }
	void SetTail(CLexeme* pT) { m_pTail = pT; }
	CLexeme* GetTail() { return m_pTail; }
	int AddLexeme(CLexeme* pRO);
};

