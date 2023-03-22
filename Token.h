#pragma once

constexpr auto TOKEN_NUMBER_OF = 11;
class CToken
{
public:
	enum LLRD_Token{
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
	struct STokenStrings {
		LLRD_Token m_Token;
		const char* m_pName;
	};
	static inline STokenStrings TokenNameLUT[TOKEN_NUMBER_OF] = {
		{IDENT,"IDENT"},
		{NUMBER,"NUMBER"},
		{STRING,"STRING"},
		{TOKEN,"TOKEN"},
		{REPLACED_BY,"->"},
		{GRAMMAR,"GRAMMAR"},
		{TERMINAL,"TERMINAL"},
		{NONTERMINAL,"NONTERMINAL"},
		{EMPTY,"e"},
		{ENDOFTOKENSTREAM,"$"},
		{ENDOFTOKENS,(const char*)0}
	};
	static const char* LookupTokenName(CToken::LLRD_Token Token);
};

