CgrammarLexer::Token Cgrammar_Parser::grammar(CgrammarLexer::Token LookaHeadToken);
{
	//---------------------------------
	//		grammar
	//		grammar -> expr
	//---------------------------------
}
CgrammarLexer::Token Cgrammar_Parser::expr(CgrammarLexer::Token LookaHeadToken);
{
	//---------------------------------
	//		expr
	//		expr -> term expr_1
	//---------------------------------
}
CgrammarLexer::Token Cgrammar_Parser::expr_1(CgrammarLexer::Token LookaHeadToken);
{
	//---------------------------------
	//		expr_1
	//		expr_1 -> + term expr_1
	//		       -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CgrammarLexer('+'):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CgrammarLexer('+'));
		LookaHeadToken = term(LookaHeadToken);
		LookaHeadToken = expr_1(LookaHeadToken);
		break;
	}
}
CgrammarLexer::Token Cgrammar_Parser::term(CgrammarLexer::Token LookaHeadToken);
{
	//---------------------------------
	//		term
	//		term -> factor term_1
	//---------------------------------
}
CgrammarLexer::Token Cgrammar_Parser::term_1(CgrammarLexer::Token LookaHeadToken);
{
	//---------------------------------
	//		term_1
	//		term_1 -> * factor term_1
	//		       -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CgrammarLexer('*'):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CgrammarLexer('*'));
		LookaHeadToken = factor(LookaHeadToken);
		LookaHeadToken = term_1(LookaHeadToken);
		break;
	}
}
CgrammarLexer::Token Cgrammar_Parser::factor(CgrammarLexer::Token LookaHeadToken);
{
	//---------------------------------
	//		factor
	//		factor -> IDENT
	//		       -> ( expr )
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CgrammarLexer::IDENT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CgrammarLexer::IDENT);
		break;
	case CgrammarLexer('('):
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CgrammarLexer('('));
		LookaHeadToken = expr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CgrammarLexer(')'));
		break;
	}
}
