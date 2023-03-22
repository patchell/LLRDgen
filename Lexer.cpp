#include "Global.h"

CLexer::CLexer()
{
	int i;

	for (i = 0; i < LEX_BUFFER_SIZE; ++i)
		m_aLexBuff[i] = 0;
	for (i = 0; i < UNGET_STACK_DEPTH; ++i)
		m_aUngetStack[i] = 0;
	m_pInputFile = 0;
	m_LexBuffIndex = 0;
	m_Number = 0;
	m_pLexSymbol = 0;
	m_pEmbeddedCodeBuffer = 0;
	m_nEmbeddedCodeBufferSize = 0;
	m_nUngetStackPointer = 0;
}

CLexer::~CLexer()
{
	if (m_pEmbeddedCodeBuffer) delete[] m_pEmbeddedCodeBuffer;
}	

BOOL CLexer::Create(FILE* pIn)
{
//	char Epsilon[3] = { char(207),char(181 ), 0};
	char Epsilon[2] = { 'e', 0};
	char Dollar[2] = { '$',0 };
	CRule* pRule;
	CLexeme* pLexeme;
	CSetMember* pSM;

	m_pInputFile = pIn;
	m_SymbolTable.Create(SYMTAB_SIZE);

	//--------------------------------
	// Create the empty (epsilon)
	// symbol
	//--------------------------------
	m_EmptySymbol.Create(Epsilon);
	m_EmptySymbol.SetEmpty(TRUE);
	m_EmptySymbol.SetNullable(TRUE);
	m_EmptySymbol.SetTokenValue(UINT(Token::TERMINAL));
	pLexeme = new CLexeme;
	pLexeme->Create(&m_EmptySymbol);
	pSM = new CSetMember;
	pSM->Create(&m_EmptySymbol);
	pRule = new CRule;
	pRule->Create(&m_EmptySymbol);
	pRule->AddLexeme(pLexeme);
	m_EmptySymbol.AddRule(pRule);
	m_EmptySymbol.GetFirstSet()->AddToSet(pSM);
	//----------------------------------
	// Create the End of Token Stream
	// symbol - $
	//----------------------------------
	m_EndOfTokenStream.Create(Dollar);
	m_EndOfTokenStream.SetEmpty(FALSE);
	m_EndOfTokenStream.SetTokenValue(UINT(Token::TERMINAL));
	m_EndOfTokenStream.SetEndOfTokenStream();
	m_EndOfTokenStream.SetNullable(FALSE);
	pLexeme = new CLexeme;
	pLexeme->Create(&m_EndOfTokenStream);
	pRule = new CRule;
	pRule->Create(&m_EndOfTokenStream);
	pRule->AddLexeme(pLexeme);
	m_EndOfTokenStream.AddRule(pRule);
	return TRUE;
}

void CLexer::CloseFiles()
{
	fclose(m_pInputFile);
}

void CLexer::Error(FILE* pO, const char* pErrorString)
{
	fprintf(pO, "Line %d  Col %d Error:%s\n", m_Line, m_Col, pErrorString);
	CloseAllFiles();
}

int CLexer::LexGet()
{
	int c = 0;

	if (m_nUngetStackPointer)
	{
		c = m_aUngetStack[--m_nUngetStackPointer];
	}
	else
	{
		if (m_pInputFile)
			c = fgetc(m_pInputFile);
		else
			c = EOF;
	}
	m_Col++;
	return c;
}

void CLexer::LexUnGet(int Value)
{

	if (UNGET_STACK_DEPTH > m_nUngetStackPointer)
		m_aUngetStack[m_nUngetStackPointer++] = Value;
	else
	{
		Error(stderr, "Lexer Unget Stack Overflow");
		exit(-2);
	}
}

BOOL CLexer::IsValidNumber(int c)
{
	BOOL IsValid = FALSE;

	switch (c)
	{
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		IsValid = TRUE;
		break;
	}
	return IsValid;
}

BOOL CLexer::IsValidNameChar(int c)
{
	BOOL IsValid = FALSE;

	if (isalnum(c) || c == '_')
		IsValid = TRUE;
	return IsValid;;
}

BOOL CLexer::IsWhiteSpace(int c)
{
	BOOL IsValid = FALSE;

	switch (c)
	{
	case '\n':
		m_Line++;
		m_Col = 0;
	case '\r':
	case '\t':
	case ' ':
		IsValid = TRUE;
		break;;
	}
	return IsValid;
}

CLexer::Token CLexer::Lex()
{
	BOOL Loop = TRUE;
	BOOL auxLoop = TRUE;
	int c;
	Token TokenValue = Token(0);

//	if (m_Line >= 285)
//		printf("Boo-Boo Line:%d\n", m_Line);
	m_LexBuffIndex = 0;
	m_aLexBuff[1] = 0;
	m_pLexSymbol = 0;
	while (Loop)
	{
		c = LexGet();
		m_aLexBuff[0] = c;

		switch (c)
		{
		case EOF:
			TokenValue = Token(EOF);
			Loop = FALSE;
			break;
		case '\n':	//white space
			m_Col = 0;
			m_Line++;
			break;
		case '\t':	//more white space
			m_Col += 4;
		case '\r':	
		case ' ':
			break;
		case '/':
			c = LexGet();
			if (c == '/')
			{
				//eat characters until the EOL
				do
				{
					c = LexGet();
				} while (c != '\n');
				LexUnGet(c);
			}
			else
			{
				LexUnGet('/');
				LexUnGet(c);
			}
			break;
		case '0':case '1':case '2':case '3':case '4':
		case '5':case '6':case '7':case '8':case '9':
			while (IsValidNumber(c))
			{
				m_aLexBuff[m_LexBuffIndex++] = c;
				c = LexGet();
			}
			m_aLexBuff[m_LexBuffIndex] = 0;
			m_Number = atoi(m_aLexBuff);
			Loop = FALSE;
			TokenValue = Token::NUMBER;
			LexUnGet(c);
			break;
		case '-':
			c = LexGet();
			if (c == '>')
			{
				m_aLexBuff[1] = c;
				m_aLexBuff[2] = 0;
				TokenValue = Token::REPLACED_BY;
				Loop = 0;
			}
			else
			{
				LexUnGet(c);
				TokenValue = Token('-');
				Loop = FALSE;
			}
			break;
		case '"':	//String
			auxLoop = TRUE;
			while (auxLoop)
			{
				c = LexGet();
				if (c == '\\')	//is it the escape char?
				{
					c = LexGet();
				}
				else if (c == '"')
				{
					auxLoop = FALSE;
					m_aLexBuff[m_LexBuffIndex] = 0;
					TokenValue = Token::STRING;
				}
				else
					m_aLexBuff[m_LexBuffIndex++] = c;
			}
			Loop = FALSE;
			break;
		case '.':	//empty rule
			TokenValue = Token::EMPTY;
			m_pLexSymbol = GetEmpty();
			Loop = FALSE;
			break;
		case '$':
			m_pLexSymbol = GetEndOfTokenStream();
			TokenValue = Token::ENDOFTOKENSTREAM;
			Loop = FALSE;
			break;
		case '=':	//misc tokens
		case ';':
		case ',':
			TokenValue = Token(c);
			Loop = FALSE;
			break;
		case '\'':	// Target Terminal Token
			m_LexBuffIndex = 0;
			auxLoop = TRUE;
			while (auxLoop)
			{
				c = LexGet();
				if (c == '\'')
				{
					m_aLexBuff[m_LexBuffIndex] = 0;
					auxLoop = FALSE;
				}
				else
				{
					m_aLexBuff[m_LexBuffIndex++] = c;
				}
			}
			m_pLexSymbol = (CSymbol*)LookupSymbol(m_aLexBuff);
			if (m_pLexSymbol)
			{
				TokenValue = Token(m_pLexSymbol->GetTokenValue());
				if (TokenValue == Token::NONTERMINAL)
				{
					//------------------------------
					// Sometbing wrong if this is
					// actually a Non Terminal
					//------------------------------
					fprintf(stderr, "ERROR Line:%d Col:%d  Using %s as a Terminal\n",
						m_Line,
						m_Col,
						m_pLexSymbol->GetName()
					);
					exit(4);
				}
				Loop = FALSE;
			}
			else
			{
				CSetMember* pSM;
				//-----------------------------------------
				// We have a new terminal for the target
				// grammar, add it to the
				// symbol table and terminal set
				//-----------------------------------------
				m_pLexSymbol = new CSymbol;
				m_pLexSymbol->Create(m_aLexBuff);
				m_pLexSymbol->SetTokenValue(UINT(CLexer::Token::TERMINAL));
				m_pLexSymbol->SetTargetTokenValue(m_aLexBuff[0]);
				GetSymTab()->AddSymbol(m_pLexSymbol);
				pSM = new CSetMember;
				pSM->Create(m_pLexSymbol);
				m_pLexSymbol->GetFirstSet()->AddToSet(pSM);
				pSM = new CSetMember;
				pSM->Create(m_pLexSymbol);
				GetSymTab()->GetTerminalSet()->AddToSet(pSM);
				TokenValue = CLexer::Token::TERMINAL;
				Loop = FALSE;
			}
			break;
		default:	//Keywords and Identifiers and non terminals
			m_aLexBuff[m_LexBuffIndex++] = c;
			auxLoop = TRUE;
			while (auxLoop)
			{
				c = LexGet();
				if (IsValidNameChar(c))
				{
					m_aLexBuff[m_LexBuffIndex++] = c;
				}
				else
				{
					auxLoop = FALSE;
					m_aLexBuff[m_LexBuffIndex] = 0;
					LexUnGet(c);
				}
			}	//END OF collecting characters for word
			//---------------------------------
			// First check to see if it is a
			// Keyword
			//---------------------------------
			TokenValue = LookupKeyword(m_aLexBuff);
			if (int(TokenValue))
			{
				//--------------------------
				// Keyword has matched
				//--------------------------
				Loop = 0;
			}
			else
			{
				//-------------------------------------
				// Is it an Identifier?
				//-------------------------------------
				m_pLexSymbol = (CSymbol*)LookupSymbol(m_aLexBuff);
				if (m_pLexSymbol)
				{
					TokenValue = Token(m_pLexSymbol->GetTokenValue());
					Loop = FALSE;
					if (TokenValue == Token::TERMINAL)
					{
						fprintf(stderr, "Line %d  Col %d\n", m_Line, m_Col);
						fprintf(stderr, "Terminal %s Not used properly\n", m_aLexBuff);
						fprintf(stderr, "Terminals Must be surrounded by \' marks'\n");
						fprintf(stderr, "For Example:\'%s\' rather than just %s\n",
							m_aLexBuff,m_aLexBuff
						);
						exit(6);
					}
				}
				else
				{
					//-------------------------------------
					// Identifier is New/Undefined
					//-------------------------------------
					m_pLexSymbol = new CSymbol;
					m_pLexSymbol->Create(m_aLexBuff);
					TokenValue = Token::IDENT;
					m_pLexSymbol->SetTokenValue(UINT(Token::IDENT));
					Loop = FALSE;
				}
			}
			break;	// end of default:
		}	// End of switch(c)
	}
	return TokenValue;
}

//**********************************************
// Expect
//
// This function is used to check that we get
// the token that we Expect.
//
// parameters:
//	Lookahead..Current lookahead token
//	token....this is the token we Expect
// return value:
//	reutns the next Lookahead token (>0)
//	reutnrs 0 or negative if we did not get what we Expected
//*********************************************

CLexer::Token CLexer::Expect(CLexer::Token LookaHeadToken, CLexer::Token Expected)
{
	if (Accept(LookaHeadToken, Expected))
		LookaHeadToken = Lex();
	else
	{
		char* pExp = new char[256], * pGot = new char[256];
		CLexer::KeyWord* pKY = 0;
		
		if (LookaHeadToken >= Token(256))
		{
			pKY = FindKeyword(LookaHeadToken);
			if (pKY)
				strcpy_s(pGot, 256, pKY->m_Name);
			else
			{
//				char* s = new char[256];
//				sprintf_s(s, 256, "Unknown Token %d:%s\n", 
//					LookaHeadToken,
//					LookupTokenName(LookaHeadToken)
//				);
//				CLexer::Error(stderr, s);
//				delete[] s;
//				CloseAllFiles();
				exit(-2);
			}
		}
		else
		{
			pGot[0] = int(LookaHeadToken);
			pGot[1] = 0;
		}
		if (Expected >= Token(256))
		{
			pKY = FindKeyword(Expected);
			if (pKY)
				strcpy_s(pExp, 256, pKY->m_Name);
			else
				fprintf(stderr, "Unknown Token %d\n", Expected);
		}
		else
		{
			pExp[0] = int(Expected);
			pGot[1] = 0;
		}
		fprintf(stderr, "Line %d: Column:%d Unexpected Token:Got %d:%s Expected %d:%s\n", 
			m_Line, 
			m_Col,
			LookaHeadToken, 
			pGot,
			Expected,
			pExp
		);
		exit(1);
	}
	return LookaHeadToken;
}

//********************************************
// Accept
//
// This function compares the token you want
// versus the token that is current.  If they
// match, then we get another token.
// If not, then just return.
//
// parameter:
//	Lookahead..The current lookahead token
//	token.....this is the token we want
//
// return value:
//	returns the new token value (>0)
//	returns 0 or negative if we don't get the token we want
//**********************************************

BOOL CLexer::Accept(Token Lookahead, Token Expected)
{
	BOOL rv = FALSE;

	if (Expected == Lookahead)
		rv = TRUE;
	return rv;
}

CBin* CLexer::LookupSymbol(const char* pName)
{
	CBin* pSym = 0;

	pSym = m_SymbolTable.FindSymbol(pName);
	return pSym;
}

CLexer::Token CLexer::LookupKeyword(const char* pKeyword)
{
	int i;
	Token KeywordToken = Token(0);
	BOOL Loop = TRUE;

	for (i = 0; Loop && KeyWords[i].m_TokenID != Token::ENDOFTOKENS; ++i)
	{
		if (strcmp(pKeyword, KeyWords[i].m_Name) == 0)
		{
			Loop = FALSE;
			KeywordToken = KeyWords[i].m_TokenID;
		}
	}
	return KeywordToken;
}

CLexer::KeyWord* CLexer::FindKeyword(Token KeywordToken)
{
	KeyWord* pKeyword = 0;
	BOOL Loop = TRUE;
	int i = 0;

	while (Loop)
	{
		if (KeyWords[i].m_TokenID != Token::ENDOFTOKENS)
		{
			if (KeyWords[i].m_TokenID == KeywordToken)
			{
				pKeyword = (KeyWord*)&KeyWords[i];
				Loop = 0;
			}
			else
				++i;
		}
		else
			Loop = 0;
	}
	return pKeyword;
}

const char* CLexer::LookupTokenName(Token TheToken)
{
	int i;
	BOOL Loop = TRUE;
	const char* rV = 0;
	static char AltString[16];

	for (i = 0; Loop && TokenNames[i].m_TokenID != Token::ENDOFTOKENS; ++i)
	{
		if (TokenNames[i].m_TokenID == TheToken)
		{
			Loop = FALSE;
			rV = TokenNames[i].m_Name;
		}
	}
	if (rV == 0)
	{
		if (isprint(int(TheToken)))
		{
			AltString[0] = int(TheToken);
			AltString[1] = 0;
			rV = (const char*)AltString;
		}
		else
			rV = "?";
	}
    return rV;
}

