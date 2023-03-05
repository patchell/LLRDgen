#include "Global.h"

CParseTable::CParseTable()
{
	m_ppNonTerminalSymbols = 0;
	m_ppTerminalSymbols = 0;
	m_Rows = 0;
	m_Cols = 0;
	m_pTerminalSet = 0;
	m_pNonTerminalSet = 0;
}

CParseTable::~CParseTable()
{
}

BOOL CParseTable::Create(CSet* pTerm, CSet* pNon)
{
	BOOL rV = TRUE;
	int TableSize;
	int i, j;
	CSetMember* pSM;
	CParseTableEntry* pPTE;

	SetNonTerminalSet(pNon);
	SetTerminalSet(pTerm);
	//------------- Parse Table ------------------
	m_Rows = GetNonTerminalSet()->GetNumberOfMembers();
	m_Cols = GetTerminalSet()->GetNumberOfMembers();
	TableSize = m_Rows * m_Cols;
	m_matParseTable.Create(m_Rows, m_Cols);
	//-------------- Terminal Table --------------------------
	m_ppTerminalSymbols = new CLexeme * [sizeof(CLexeme *) * GetTerminalSet()->GetNumberOfMembers()];
	pSM = GetTerminalSet()->GetHead();
	for (i = 0; i < GetTerminalSet()->GetNumberOfMembers(); ++i)
	{
		m_ppTerminalSymbols[i] = new CLexeme;
		m_ppTerminalSymbols[i]->Create();
		m_ppTerminalSymbols[i]->SetLexemeSymbol(pSM->GetSetMemberSymbol());
		pSM = pSM->GetNext();
	}
	//---------------- Non Terminal Table ----------------------
	m_ppNonTerminalSymbols = new CLexeme * [sizeof(CLexeme*) * GetNonTerminalSet()->GetNumberOfMembers()];
	pSM = GetNonTerminalSet()->GetHead();
	for (i = 0; i < GetNonTerminalSet()->GetNumberOfMembers(); ++i)
	{
		m_ppNonTerminalSymbols[i] = new CLexeme;
		m_ppNonTerminalSymbols[i]->Create();
		m_ppNonTerminalSymbols[i]->SetLexemeSymbol(pSM->GetSetMemberSymbol());
		pSM = pSM->GetNext();
	}
	//----------------------------------------------
	for (i = 0; i < m_Rows; ++i)
	{
		for (j = 0; j < m_Cols; ++j)
		{
			pPTE = new CParseTableEntry;
			pPTE->Create();
			pPTE->SetColName(
				m_ppTerminalSymbols[j]->GetLexemeSymbol()->GetName()
			);
			pPTE->SetRowName(
				m_ppNonTerminalSymbols[i]->GetLexemeSymbol()->GetName()
			);
			m_matParseTable(i, j) = pPTE;
		}
	}

	//----------------------------------------------
	fprintf(stderr, "Terminals    :%d\n", m_Cols);
	fprintf(stderr, "Non Terminals:%d\n", m_Rows);
	return rV;
}

BOOL CParseTable::FillTable()
{
	//-----------------------------------------------
	// FillTable
	// 
	//	For each production Y->y of the grammar :
	//	1.	For each terminal 'a' in FIRST(Y), Add 
	//		Y->y to M(Y, a).
	//	2.	If e is in FIRST(y), then for each 
	//		terminal b in FOLLOW(Y), add Y->y into 
	//		M(Y, b).  If e is in FIRST(y) amd $ is in
	//		FOLLOW(Y).Then add Y->y into M(Y, $) as 
	//		well.	
	//-----------------------------------------------
	BOOL bConflicts = FALSE;
	int i;
	CLexeme* pY;	//current Non Terminal

	for (i = 0; i < m_Rows; ++i)
	{
		//------------------------------------
		// Get Left Hand Side of production
		//------------------------------------
		pY = m_ppNonTerminalSymbols[i];
		fprintf(LogFile(), "------- %s --------\n", pY->GetName());
		Rule1(pY);
		Rule2(pY);
	}
	Print(LogFile());
	return bConflicts;
}

BOOL CParseTable::Rule1(CLexeme* pY)
{
	//---------------------------------------------
	// Rule1
	// 
	//	1.	For each terminal 'a' in FIRST(Y), Add 
	//		Y->y to M(Y, a).
	// 
	// parameters:
	//	pY is the left hand side of the production
	//---------------------------------------------
	BOOL rV = TRUE;
	CRule* pProductionRule;
	CParseTableEntryMember* pEntryMember;
	CSet FIRSTy;
	CSetMember* pSetMember;
	int Row, Col;

	pProductionRule = pY->GetLexemeSymbol()->GetHead();
	FIRSTy.Create("TempFirstY", "FIRST");
	fprintf(LogFile(), "################> Rule 1 <#################\n");
	while (pProductionRule)
	{
		fprintf(LogFile(), "--------");
		pProductionRule->Print(LogFile(),TRUE,FALSE,0);
		fprintf(LogFile(), "--------\n");
		pProductionRule->FIRST(pProductionRule->GetHead(), FIRSTy);
		pSetMember = FIRSTy.GetHead();
		while (pSetMember)
		{
			fprintf(LogFile(), "******* %s ******\n", pSetMember->GetSetMemberLexeme()->GetName());
			Col = GetTerminalIndex(pSetMember->GetSetMemberLexeme());
			Row = GetNonTerminalIndex(pProductionRule->GetLHS());
			pEntryMember = new CParseTableEntryMember;
			pEntryMember->Create(pProductionRule);
			m_matParseTable(Row, Col)->AddMember(pEntryMember);
			fprintf(LogFile(), "^^^^^^^ %s ^^^^^^^\n", pSetMember->GetSetMemberLexeme()->GetName());
			pSetMember = pSetMember->GetNext();
		}
		FIRSTy.MakeEmpty();
		pProductionRule = pProductionRule->GetNext();
	}
    return rV;
}

BOOL CParseTable::Rule2(CLexeme* pY)
{
	//-----------------------------------------------
	// Rule2
	// 
	//	For each production Y->y of the grammar :
	//	2.	If e is in FIRST(y), then for each 
	//		terminal b in FOLLOW(Y), add Y->y into 
	//		M(Y, b).  If e is in FIRST(y) amd $ is in
	//		FOLLOW(Y).Then add Y->y into M(Y, $) as 
	//		well.
	// parameters:
	//	pY is the left hand side of the production
	//-----------------------------------------------
	BOOL rV = TRUE;
	CRule* pProductionRule;
	CParseTableEntryMember* pEntryMember;
	CSet FIRSTy;
	CSet* pFollowY;
	CSetMember* pSetMember;
	int Row, Col;

	pY->GetFollowSet()->Print(LogFile(), FALSE, TRUE, 0);
	m_pTerminalSet->Print(LogFile(), FALSE, TRUE, 0);
	pProductionRule = pY->GetLexemeSymbol()->GetHead();
	FIRSTy.Create("TempFirstY", "FIRST");
	fprintf(LogFile(), "############< Rule 2 >############\n");
	while (pProductionRule)
	{
		fprintf(LogFile(), "--------");
		pProductionRule->Print(LogFile(), TRUE, FALSE, 0);
		fprintf(LogFile(), "--------\n");
		pProductionRule->FIRST(pProductionRule->GetHead(), FIRSTy);
		if (FIRSTy.Contains(CLexer::GetEmpty()))
		{
			pFollowY = pProductionRule->GetLHS()->GetFollowSet();
			pSetMember = pFollowY->GetHead();
			while (pSetMember)
			{
				pSetMember->Print(LogFile(), ' ', FALSE, TRUE, 5);
				Col = GetTerminalIndex(pSetMember->GetSetMemberLexeme());
				Row = GetNonTerminalIndex(pProductionRule->GetLHS());
				pEntryMember = new CParseTableEntryMember;
				pEntryMember->Create(pProductionRule);
				m_matParseTable(Row, Col)->AddMember(pEntryMember);
				pSetMember = pSetMember->GetNext();
			}
			if (pFollowY->Contains(CLexer::GetEndOfTokenStream()))
			{
				Col = GetTerminalIndex(CLexer::GetEndOfTokenStream());
				Row = GetNonTerminalIndex(pProductionRule->GetLHS());
				pEntryMember = new CParseTableEntryMember;
				pEntryMember->Create(pProductionRule);
				m_matParseTable(Row, Col)->AddMember(pEntryMember);
			}
		}
		pSetMember = FIRSTy.GetHead();
		FIRSTy.Print(LogFile(), FALSE, TRUE, 2);
		while (pSetMember)
		{
			pSetMember->Print(LogFile(), ' ', FALSE, TRUE, 5);
			pSetMember = pSetMember->GetNext();
		}
		pProductionRule = pProductionRule->GetNext();
	}
	return rV;
}

int CParseTable::GetTerminalIndex(CLexeme* pLex)
{
	int Index = 0;
	int i;
	BOOL bLoop;

	for (i = 0, bLoop = TRUE; i < m_Cols && bLoop; ++i)
	{
		if (pLex->Compare(m_ppTerminalSymbols[i]))
		{
			bLoop = FALSE;
			Index = i;
		}
	}
	return Index;
}

int CParseTable::GetTerminalIndex(CSymbol* pSym)
{
	int Index = 0;
	int i;
	BOOL bLoop;

	for (i = 0, bLoop = TRUE; i < m_Cols && bLoop; ++i)
	{
		if (pSym == m_ppTerminalSymbols[i]->GetLexemeSymbol())
		{
			bLoop = FALSE;
			Index = i;
		}
	}
	return Index;
}


int CParseTable::GetNonTerminalIndex(CSymbol* pSym)
{
	int Index = 0;
	int i;
	BOOL bLoop;

	for (i = 0, bLoop = TRUE; i < m_Cols && bLoop; ++i)
	{
		if (pSym->Compare(m_ppNonTerminalSymbols[i]->GetLexemeSymbol()))
		{
			bLoop = FALSE;
			Index = i;
		}
	}
	return Index;
}

int CParseTable::GetNumberOfEntries()
{
	int TotalEntries = 0;
	int i, j;
	int ni, nj;
	CParseTableEntry* pEntry;

	ni = GetRows();
	nj = GetCols();
	for (i = 0; i < ni; ++i)
	{
		for (j = 0; j < nj; ++j)
		{
			pEntry = m_matParseTable(i, j);
			if (pEntry->GetNumMembers() > 0)
			{
				++TotalEntries;
			}
		}
	}
	return TotalEntries;
}

int CParseTable::CheckForConflicts(FILE* pOut)
{
	int TotalConflicts = 0;
	int i, j;
	int ni, nj;
	CParseTableEntry* pEntry;

	ni = GetRows();
	nj = GetCols();
	for (i = 0; i < ni; ++i)
	{
		for (j = 0; j < nj; ++j)
		{
			pEntry = m_matParseTable(i, j);
			if (pEntry->GetNumMembers() > 1)
			{
				fprintf(pOut, "%d(\'%s\',\'%s\')\n",
					pEntry->GetNumMembers(),
					m_ppNonTerminalSymbols[i]->GetName(),
					m_ppTerminalSymbols[j]->GetName()
				);
				m_matParseTable(i, j)->Print(pOut, TRUE, TRUE, 10,TRUE);
				TotalConflicts += pEntry->GetNumMembers();
			}
		}
	}
	return TotalConflicts;
}

void CParseTable::Print(FILE* pO)
{
	int i, j;
	BOOL bNumberLines = FALSE;

	if (pO)
		fprintf(pO, "xxxxxxxxxxxx Parse Table xxxxxxxxxxxxxxxxx\n");
	for (i = 0; i < m_Rows; i++)
	{
		for (j = 0; j < m_Cols; j++)
		{
			if (m_matParseTable(i, j)->GetNumMembers())
			{
				if(pO) fprintf(pO, "(\'%s\',\'%s\')\n",
					m_ppNonTerminalSymbols[i]->GetName(),
					m_ppTerminalSymbols[j]->GetName()
				);
				if (pO)
				{
					if (m_matParseTable(i, j)->GetNumMembers() > 1)
						bNumberLines = TRUE;
					m_matParseTable(i, j)->Print(pO, TRUE, TRUE, 5, bNumberLines);
				}
			}
		}
	}
}
