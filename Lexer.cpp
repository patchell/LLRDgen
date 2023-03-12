#include "Global.h"

CLexer::CLexer()
{
	int i;

	for (i = 0; i < 256; ++i)
		m_aLexBuff[i] = 0;
	m_pInputFile = 0;
	m_UngetBuffer = 0;
	m_LexBuffIndex = 0;
	m_Line = 1;
	m_Col = 0;
	m_Number = 0;
	m_pLexSymbol = 0;
	m_pEmbeddedCodeBuffer = 0;
	m_nEmbeddedCodeBufferSize = 0;
}

CLexer::~CLexer()
{
	if (m_pEmbeddedCodeBuffer) delete[] m_pEmbeddedCodeBuffer;
}	

BOOL CLexer::Create(FILE* pIn)
{
	char Epsilon[3] = { char(207),char(181 ), 0};
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
	pLexeme->Create();
	pLexeme->SetLexemeSymbol(&m_EmptySymbol);
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
	pLexeme->Create();
	pLexeme->SetLexemeSymbol(&m_EndOfTokenStream);
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
	exit(9);
}

int CLexer::LexGet()
{
	int c = 0;

	if (m_UngetBuffer)
	{
		c = m_UngetBuffer;
		m_UngetBuffer = 0;
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
	while (Loop)
	{
		c = LexGet();
		switch (c)
		{
		case EOF:
			TokenValue = Token(EOF);
			Loop = FALSE;
			break;
		case '\n':	//white space
			m_Col = 0;
			m_Line++;
		case '\r':	//more white space
		case '\t':
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
				LexUnGet(c);
				printf("Fix Big Problem\n");
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
		case '"':	//Terminal Name
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
		case '=':
		case ';':
		case ',':
			TokenValue = Token(c);
			Loop = FALSE;
			break;
		case '\'':	// Terminal Token
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
				fprintf(stderr, "Line %d Col %d Undefined Token %s\n", 
					m_Line,
					m_Col,
					m_aLexBuff
				);
				exit(7);
			}
			break;
		default:	//Keywords and Identifiers
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
		}	// ejd 0f switch(c)
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
				fprintf(stderr, "Unknown Token %d\n", LookaHeadToken);
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

	for (i = 0; Loop && TokenNames[i].m_TokenID != Token::ENDOFTOKENS; ++i)
	{
		if (TokenNames[i].m_TokenID == TheToken)
		{
			Loop = FALSE;
			rV = TokenNames[i].m_Name;
		}
	}
    return rV;
}

