#pragma once

class Cgrammar_Parser
{
public:
	Cgrammar_Parser();
	virtual ~Cgrammar_Parser();
	BOOL Create();
	//------------------------------
	//      Parsing Methods
	//------------------------------
	CgrammarLexer::Token grammar(CgrammarLexer::Token LookaHeadToken);
	CgrammarLexer::Token expr(CgrammarLexer::Token LookaHeadToken);
	CgrammarLexer::Token expr_1(CgrammarLexer::Token LookaHeadToken);
	CgrammarLexer::Token term(CgrammarLexer::Token LookaHeadToken);
	CgrammarLexer::Token term_1(CgrammarLexer::Token LookaHeadToken);
	CgrammarLexer::Token factor(CgrammarLexer::Token LookaHeadToken);
};
