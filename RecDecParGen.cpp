#include "Global.h"

CRecDecParGen::CRecDecParGen():CParser()
{
	m_pLog = 0;
}

CRecDecParGen::~CRecDecParGen()
{
}

BOOL CRecDecParGen::Create(FILE* pIn, FILE* pOut, FILE* pLog)
{
	m_pLog = pLog;
	CParser::Create(pIn, pOut);
	GetNullableSet()->Create("Nullables","NULLABLES");
	GetNotNullables()->Create("NOT_Nullables", "NOTNULLABLE");
	return TRUE;
}

void CRecDecParGen::CloseFiles()
{
	fclose(m_pLog);
	CParser::CloseFiles();
}

BOOL CRecDecParGen::Run()
{
	CSetMember* pDollarSign;
	int UndefinedNonTerminals;
	int Orphans;
	//-----------------------------------
	// Parse the Grammar
	//-----------------------------------
	Parse();
	fprintf(LogFile(), "*************  Print Out Grammar Structure************\n");
	PrintGrammar(LogFile());
	//------------------------------------
	// Check for Undefined Non Terminals
	//------------------------------------
	UndefinedNonTerminals = GetLexer()->GetSymTab()->CheckForUnUsedNonTerminala(LogFile());
	fprintf(stderr, "Undefined Non Terminals:%d\n", UndefinedNonTerminals);
	if (UndefinedNonTerminals)
	{
		CloseAllFiles();
		exit(10);
	}
	fprintf(LogFile(), "******************************\n");
	fprintf(LogFile(), "******* Check For Orphans ****\n");
	fprintf(LogFile(), "******************************\n");
	Orphans = GetLexer()->GetSymTab()->CheckForOrphans(stderr, GetNonTerminalSet());
	Orphans = GetLexer()->GetSymTab()->CheckForOrphans(LogFile(),GetNonTerminalSet());
	fprintf(stderr, "Total Orphans = %d\n", Orphans);
	if (Orphans)
	{
		CloseAllFiles();
		exit(11);
	}
	// Add $ to terminal list
	pDollarSign = new CSetMember;
	pDollarSign->Create(CLexer::GetEndOfTokenStream());
	GetTerminalSet()->AddToSet(pDollarSign);
	GetTerminalSet()->Print(LogFile(), FALSE, TRUE, 0);
	//-----------------------------------
	// Create a set of Non Terminals
	//-----------------------------------
	fprintf(LogFile(), "********** Non Terminals Set **********\n");
	GetNonTerminalSet()->Print(LogFile(),FALSE,TRUE,0);
	//------------------------------------
	// Create Nullable Set
	//------------------------------------
	fprintf(LogFile(), "*********** Build Nullable Set **********\n");
	CreateNullableSet(LogFile());
	GetNullableSet()->Print(LogFile(),FALSE,TRUE,0);
	fprintf(LogFile(), "\n");
	GetNonTerminalSet()->Print(LogFile(),FALSE,TRUE,0);
	fprintf(LogFile(), "\n");
	fprintf(LogFile(), "****************Create NOT nullable set ************************\n");
	CreateNotNullablesSet(LogFile());
	//----------------------------------------------
	// Create First Set
	//----------------------------------------------
	fprintf(LogFile(), "----- Calc First Sets------\n");
	CreateFirstSets(LogFile());;
	GetLexer()->GetSymTab()->PrintFirstSets(LogFile());
	fprintf(LogFile(), "\n");
	//---------------------------------------
	// Create Follow Sets
	//---------------------------------------
	fprintf(LogFile(), "----- Calc Follow Sets------\n");
	CreateFollowSets(LogFile());
	fprintf(LogFile(), "------------ Follow Sets ---------------\n");
	GetLexer()->GetSymTab()->PrintFollowSets(LogFile());
	fprintf(LogFile(), "\n");
	//--------------------------------------
	// Create Parse Table
	//--------------------------------------
	fprintf(LogFile(), "---------------- Create Parse Table --------------\n");
	GetParseTable()->Create(GetTerminalSet(), GetNonTerminalSet());
	GetParseTable()->FillTable();
	fprintf(LogFile(), "Table Entries = %d\n", 
		GetParseTable()->GetNumberOfEntries());
	//--------------------------------------------
	// Check For Conflicts
	//--------------------------------------------
	fprintf(LogFile(), "------------ Check For Conflicts-------------\n");
	fprintf(LogFile(), "Conflicts = %d\n",
		GetParseTable()->CheckForConflicts(LogFile())
	);
	fprintf(stderr , "Conflicts = %d\n",
		GetParseTable()->CheckForConflicts(stderr)
	);
	return 0;
}


void CRecDecParGen::CreateFirstSets(FILE* pOut)
{
	//------------------------------------
	// CreateFirstSets:
	//	1.	If X is a terminal then 
	//			First(X) is just X!
	//	2.	If there is a Production
	//			 X ? ? then add ? to 
	//			first(X)
	//	3.	If there is a Production 
	//			X ? Y1Y2..Yk then add 
	//			first(Y1Y2..Yk) to 
	//			first(X)
	//	4.	First(Y1Y2..Yk) is either
	//		1.	First(Y1) (if First(Y1) 
	//				doesn't contain ?)
	//		2.	OR(if First(Y1) does 
	//			contain ?) then 
	//			First(Y1Y2..Yk) is 
	//			everything in First(Y1) 
	//			< except for ? > as well 
	//			as everything in First(Y2..Yk)
	//		3.	If First(Y1) First(Y2)..
	//			First(Yk) all contain ? 
	//			then add e to 
	//			First(Y1Y2..Yk) as well.
	//------------------------------------
	BOOL bChanged;
	CSetMember* pNonTerminalSetMember;
	CSymbol* pSymLHS;	//left hand side of production
	CRule* pRule;
	CSet* pFIRST_X;
	int Iterration = 1;

	fprintf(LogFile(), "******* Create First Set Ver 2 ********\n");
	do
	{
		fprintf(LogFile(), "###### First Set Iteration #%d\n", Iterration++);
		bChanged = FALSE;
		pNonTerminalSetMember = GetNonTerminalSet()->GetHead();
		while (pNonTerminalSetMember)
		{
			fprintf(LogFile(), "----------------------\n");
			fprintf(LogFile(), "FIRST(%s)\n", pNonTerminalSetMember->GetSetMemberSymbol()->GetName());
			pSymLHS = pNonTerminalSetMember->GetSetMemberSymbol();
			pRule = pSymLHS->GetHead();
			pFIRST_X = pSymLHS->GetFirstSet();
			while (pRule)
			{
				fprintf(LogFile(), "%s\t", pSymLHS->GetName());
				pRule->Print(LogFile());
				bChanged |= pRule->FIRST(
					pRule->GetHead(),
					pSymLHS->GetFirstSetRef()
				);
				pSymLHS->GetFirstSetRef().Print(LogFile());
				fprintf(LogFile(), "\n");
				pRule = pRule->GetNext();
			}
			pNonTerminalSetMember = pNonTerminalSetMember->GetNext();
		}
		fprintf(LogFile(), "###### Iteration #%d  DONE!\n", Iterration);
	} while (bChanged);
}

void CRecDecParGen::CreateFollowSets(FILE* pOut)
{
	//-------------------------------------------
	// CreateFollowSets
	// 
	// 
	//	1.	First put $(the end of input 
	//		marker) in Follow(S) (S is the
	//		 start symbol)
	//	2.	If there is a production A->aBb,
	//		 (where a can be a whole string)
	//		 then everything in FIRST(b) 
	//		except for e is placed in FOLLOW(B).
	//	3.	If there is a production A->aB, then
	//		 everything in FOLLOW(A) is in FOLLOW(B)
	//	4.	If there is a production A->aBb,
	//		 where FIRST(b) contains e, then 
	//		everything in FOLLOW(A) is in 
	//		FOLLOW(B)	//
	//-------------------------------------------
	CSymbol* pSym;
	CSetMember* pNonTerminalSetMember;
	int Iteration = 0;
	BOOL bChanged = FALSE;
	int LoopCount;
	int Itteration = 0;
	//----------------------------------------------
	// Rule #1 is NOT needed (ha-ha)
	//----------------------------------------------
	//---------------------------------------------
	// Find the FOLLOW set for all of the other non
	// terminal symbols.
	//---------------------------------------------
	LoopCount = 100;
	do
	{
		fprintf(LogFile(), "######### Follow Set Itteration #%d\n", ++Iteration);
		bChanged = FALSE;
		pNonTerminalSetMember = GetNonTerminalSet()->GetHead();
		while (pNonTerminalSetMember)
		{
			pSym = pNonTerminalSetMember->GetSetMemberSymbol();
			bChanged |= ApplyFollowRulesTo(pSym);
			pNonTerminalSetMember = pNonTerminalSetMember->GetNext();
		}
	} while (bChanged && --LoopCount);	//end of do loop
}

BOOL CRecDecParGen::ApplyFollowRulesTo(CSymbol* pSym)
{
	//-------------------------------------------------
	// ApplyFollowRulesTo
	// 
	// pSym is a Non Terminal symbol.  We use this
	// symbol to go through all of the productions
	// looking for a production that the FOLLOW SET
	// rules can be applied to.
	//-------------------------------------------------
	BOOL bChanged = FALSE;
	CSymbol* pProductionSymbol;
	CSetMember* pNonTerminalSetMember;
	CRule* pRule;

	pNonTerminalSetMember = GetNonTerminalSet()->GetHead();
	fprintf(LogFile(), "------------Looking For %s ---------------\n", pSym->GetName());
	while (pNonTerminalSetMember)
	{
		pProductionSymbol = pNonTerminalSetMember->GetSetMemberSymbol();
		pRule = pProductionSymbol->GetHead();
		while (pRule)
		{
			bChanged |= pRule->DoesThisRuleHave(pSym);
			pRule = pRule->GetNext();
		}
		pNonTerminalSetMember = pNonTerminalSetMember->GetNext();
	}
	return bChanged;
}

void CRecDecParGen::CreateNullableSet(FILE* pOut)
{
	//-----------------------------------------------
	// CreateNullableSet
	//-----------------------------------------------
	CSymbol* pSymLHS;
	CRule* pRule;
	CSetMember* pMember;
	CSetMember* pNTLHS;
	int Iteration = 0;
	BOOL bChanged = FALSE;
	BOOL bNull = FALSE;

	fprintf(LogFile(),"----- Generate Nullables-------\n");
	do
	{
		bChanged = FALSE;
		pNTLHS = GetNonTerminalSet()->GetHead();
		while (pNTLHS)
		{
			bNull = FALSE;
			pSymLHS = pNTLHS->GetSetMemberSymbol();
			pRule = pSymLHS->GetHead();
			while (pRule && !bNull)
			{
				pRule->Print(LogFile(), TRUE, TRUE, 0);
				bNull |= pRule->DoesThisRuleHaveEpsilon();
				if (bNull)
				{
					pSymLHS->SetNullable(TRUE);
					pMember = new CSetMember;
					pMember->Create(pSymLHS);
					bChanged |= GetNullableSet()->AddToSet(pMember);
				}
				bNull = FALSE;
				pRule = pRule->GetNext();
			}
			pNTLHS = pNTLHS->GetNext();
		}
		fprintf(LogFile(), "************ Nullable Iteration %d *********\n", ++Iteration);
		if (Iteration > 100)
			bChanged = FALSE;
	} while (bChanged);
	fprintf(LogFile(), "----- Done Generate Nullables-------\n");
}


void CRecDecParGen::CreateNonTerminals(FILE* pOut)
{
	CBucket* pBucket;
	CBin* pBin;
	CSymbol* pSym;
	CSetMember* pMember;
	int i;

	for (i = 0; i < GetLexer()->GetSymTab()->GetTableSize(); ++i)
	{
		pBucket = GetLexer()->GetSymTab()->GetBucket(i);
		if (pBucket)
		{
			pBin = pBucket->GetHead();
			while (pBin)
			{
				pSym = (CSymbol*)pBin;
				if (pSym->IsNonTerminal())
				{
					pMember = new CSetMember;
					pMember->Create(pSym);
					GetNonTerminalSet()->AddToSet(pMember);
				}
				pBin = pBin->GetNext();
			}
		}
	}
}

void CRecDecParGen::CreateNotNullablesSet(FILE* pOut)
{
	CBucket* pBucket;
	CBin* pBin;
	CSymbol* pSym;
	CSetMember* pMember;
	int i;


	for (i = 0; i < GetLexer()->GetSymTab()->GetTableSize(); ++i)
	{
		pBucket = GetLexer()->GetSymTab()->GetBucket(i);
		if (pBucket)
		{
			pBin = pBucket->GetHead();
			while (pBin)
			{
				pSym = (CSymbol*)pBin;
				if (pSym->IsNotNullable() && pSym->IsNonTerminal())
				{
					pMember = new CSetMember;
					pMember->Create(pSym);
					GetNotNullables()->AddToSet(pMember);
				}
				pBin = pBin->GetNext();
			}
		}
	}
}

void CRecDecParGen::PrintGrammar(FILE* pOut)
{
	CSymTab* pSymTab = 0;
	CBucket* pBucket = 0;
	CSymbol* pSym = 0;
	CBin* pBin;
	int i;

	pSymTab = GetLexer()->GetSymTab();
	for (i = 0; i < SYMTAB_SIZE; ++i)
	{
		if (pSymTab->GetBucket(i))
		{
			pBin = pSymTab->GetBucket(i)->GetHead();
			while (pBin)
			{
				pSym = (CSymbol*)pBin;
				if (CLexer::Token(pSym->GetTokenValue()) == CLexer::Token::NONTERMINAL)
				{
					pSym->PrintProduction(pOut);
				}
				pBin = pBin->GetNext();
			}
		}
	}
}

