#pragma once


class CSymbol: public CBin
{
	class CLexer friend;
	UINT m_TokenValue;
	UINT m_TargetTokenValue;
	BOOL m_IsEmpty;
	BOOL m_IsNullable;
	BOOL m_StartSymbol;
	BOOL m_EndOfTokenStream;
	CRule* m_pHead;
	CRule* m_pTail;
	CSet m_FirstSet;
	CSet m_FollowSet;
	int m_nTotalRules;
	int m_LineNumber;		//line where defined
public:
	CSymbol() {
		m_IsEmpty = FALSE;
		m_IsNullable = FALSE;
		m_StartSymbol = FALSE;
		m_EndOfTokenStream = FALSE;
		m_TokenValue = 0;
		m_TargetTokenValue = 0;
		m_pHead = 0;
		m_pTail = 0;
		m_nTotalRules = 0;
		m_LineNumber = 0;
	}
	virtual ~CSymbol() {}
	BOOL Create(const char* pName);
	virtual BOOL Compare(const char* name);
	virtual BOOL Compare(CSymbol* pSym);
	char* GetTokenString();
	int GetNumberOfRules() { return m_nTotalRules; }
	CSymbol* GetNext() { return (CSymbol*)CBin::GetNext(); }
	BOOL DoesThisProductionHaveEpsilon();
	//----------------------------
	// Debug Stuff
	//----------------------------
	virtual void PrintProduction(
		FILE* pOut, 
		BOOL bLHS = FALSE, 
		BOOL bEOL = TRUE, 
		int nIndentSpaces = 0
	);
	virtual void Print(FILE* pOut, 
		BOOL bLHS = FALSE, 
		BOOL bEO = TRUE, 
		int nIndentSpaces = 0
	);
	//-----------------------------
	// Accessor Methods
	//-----------------------------
	UINT GetTargetTokenValue() {
		return m_TargetTokenValue;
	}
	void SetTargetTokenValue(UINT v) { m_TargetTokenValue = v; }
	int GetLineWhereDefined() { return m_LineNumber; }
	void SetLineWhereDefined(int ln) { m_LineNumber = ln; }
	UINT GetTokenValue() { return m_TokenValue; }
	void SetTokenValue(UINT TV) { m_TokenValue = TV; }
	BOOL IsEmpty() { return m_IsEmpty; }
	BOOL IsNotEmpty() { return !m_IsEmpty; }
	void SetNullable(BOOL bF);
	BOOL IsNullable() { return m_IsNullable; }
	BOOL IsNotNullable() { return !m_IsNullable; }
	void SetStartSymbol() { m_StartSymbol = TRUE; }
	virtual BOOL IsStartSymbol() { return m_StartSymbol; }
	virtual BOOL IsNotStartSymbol() { return !m_StartSymbol; }
	void SetEndOfTokenStream() { m_EndOfTokenStream = TRUE; }
	BOOL IsEndOfTokenSteam() {
		return m_EndOfTokenStream;
	}
private:
	void SetEmpty(BOOL IE) { m_IsEmpty = IE; }
public:
	BOOL IsTerminal();
	BOOL IsNonTerminal();
	//-----------------------------
	// Rule Management
	//-----------------------------
	CRule* GetHead() { return m_pHead; }
	void SetHead(CRule* pH) { m_pHead = pH; }
	CRule* GetTail() { return m_pTail; }
	void SetTail(CRule* pT) { m_pTail = pT; }
	void AddRule(CRule* pRule);
	//----------------------------
	// Set Managment
	//----------------------------
	CSet* GetFirstSet() { return &m_FirstSet; }
	CSet& GetFirstSetRef() { return m_FirstSet; }
	CSet* GetFollowSet() { return &m_FollowSet; }
};

