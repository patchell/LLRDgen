#pragma once

constexpr auto EPSILON = 238;
class CLexer
{
public:
	enum  class Token {
		IDENT = 256,
		NUMBER,
		STRING,
		TERMINALS,
		END_TERMINALS,
		REPLACED_BY,
		GRAMMAR,
		END_GRAMMAR,
		TERMINAL,
		NONTERMINAL,
		EMPTY,
		ENDOFTOKENSTREAM,
		ENDOFTOKENS
	};
private:
	struct KeyWord {
		Token m_TokenID;	//token value
		const char* m_Name;	//token name
	};
	static inline KeyWord TokenNames[] = {
		{Token::IDENT,"IDENT"},
		{Token::NUMBER,"NUMBER"},
		{Token::STRING,"STRING"},
		{Token::TERMINALS,"TERMINALS"},
		{Token::END_TERMINALS,"END_TERMINALS"},
		{Token::REPLACED_BY,"REPLACED_BY"},
		{Token::GRAMMAR,"GRAMMAR"},
		{Token::END_GRAMMAR,"END_GRAMMAR"},
		{Token::TERMINAL,"TERMINAL"},
		{Token::NONTERMINAL,"NONTERMINAL"},
		{Token::ENDOFTOKENS,"ENDOFTOKENS"}
	};
	static inline KeyWord KeyWords[] = {
		{Token::TERMINALS, "TERMINALS"},
		{Token::END_TERMINALS, "END_TERMINALS"},
		{Token::REPLACED_BY, "REPLACED_BY"},
		{Token::GRAMMAR, "GRAMMAR"},
		{Token::END_GRAMMAR, "END_GRAMMAR"},
		{Token::ENDOFTOKENS,NULL}
	};
	CSymTab m_SymbolTable;
	FILE* m_pInputFile;
	int m_UngetBuffer;
	char m_aLexBuff[4096];
	int m_LexBuffIndex;
	static inline int m_Line;
	static inline int m_Col;
	int m_Number;
	CSymbol* m_pLexSymbol;
	char* m_pEmbeddedCodeBuffer;
	int m_nEmbeddedCodeBufferSize;
	inline static CSymbol m_EmptySymbol;
	inline static CSymbol m_EndOfTokenStream;
public:
	CLexer();
	virtual ~CLexer();
	BOOL Create(FILE *pIn);
	void CloseFiles();
	static void Error(FILE* pO, const char* pErrorString);
	int LexGet();
	void LexUnGet(int Value) {
		m_UngetBuffer = Value;
		m_Col--;
	}
	BOOL IsValidNumber(int c);
	BOOL IsValidNameChar(int c);
	BOOL IsWhiteSpace(int c);
	Token Lex();
	Token Expect(CLexer::Token Lookahead, CLexer::Token Expected);
	BOOL Accept(Token Lookahead, Token Expected);
	static CSymbol* GetEmpty() { return &m_EmptySymbol; }
	static CSymbol* GetEndOfTokenStream() {
		return &m_EndOfTokenStream;
	}
	void SetEmbeddedCodeBufferSize(int Size) {
		m_nEmbeddedCodeBufferSize = Size;
		m_pEmbeddedCodeBuffer = new char[Size];
	}
	//------------------------------------------
	// Symbol Table Methods
	//------------------------------------------
	CBin* LookupSymbol(const char* pName);
	CSymTab* GetSymTab() { return &m_SymbolTable; }
	//------------------------------------------
	// Keyword Lookup Methods
	//------------------------------------------
	Token LookupKeyword(const char* pKeyword);
	KeyWord* FindKeyword(Token KeywordToken);
	//--------------------------------------
	// Symbol Methods
	//--------------------------------------
	CSymbol* GetSymbol() { return m_pLexSymbol; }
	int GetNumber() { return m_Number; }
	char* GetLexbuff() { return m_aLexBuff; }
	int GetLineNumber() { return m_Line; }
	int GetColunm() { return m_Col; }
	static const char* LookupTokenName(Token TheToken);
};

