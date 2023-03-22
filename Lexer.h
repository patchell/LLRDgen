#pragma once

constexpr auto EPSILON = 238;
constexpr auto LEX_BUFFER_SIZE = 4096;
constexpr auto UNGET_STACK_DEPTH = 16;

class CLexer
{
public:
	enum  class Token {
		IDENT = 256,
		NUMBER,
		STRING,
		TOKEN,
		REPLACED_BY,
		GRAMMAR,
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
		{Token::TOKEN,"TOKEN"},
		{Token::REPLACED_BY,"REPLACED_BY"},
		{Token::GRAMMAR,"GRAMMAR"},
		{Token::TERMINAL,"TERMINAL"},
		{Token::NONTERMINAL,"NONTERMINAL"},
		{Token::ENDOFTOKENS,"ENDOFTOKENS"}
	};
	static inline KeyWord KeyWords[] = {
		{Token::REPLACED_BY, "REPLACED_BY"},
		{Token::TOKEN,"TOKEN"},
		{Token::GRAMMAR, "GRAMMAR"},
		{Token::ENDOFTOKENS,"$"}
	};
	CSymTab m_SymbolTable;
	FILE* m_pInputFile;
	char m_aLexBuff[LEX_BUFFER_SIZE];
	int m_LexBuffIndex;
	static inline int m_Line = 1;
	static inline int m_Col = 0;
	int m_Number;
	CSymbol* m_pLexSymbol;
	char* m_pEmbeddedCodeBuffer;
	int m_nEmbeddedCodeBufferSize;
	inline static CSymbol m_EmptySymbol;
	inline static CSymbol m_EndOfTokenStream;
	int m_aUngetStack[UNGET_STACK_DEPTH];
	int m_nUngetStackPointer;
public:
	CLexer();
	virtual ~CLexer();
	BOOL Create(FILE* pIn);
	void CloseFiles();
	static void Error(FILE* pO, const char* pErrorString);
	int LexGet();
	void LexUnGet(int Value);
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

