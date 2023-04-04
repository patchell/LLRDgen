CAction65Lexer::Token CAction65_Parser::Action65(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Action65
	//		Action65 -> Modules
	//---------------------------------
	LookaHeadToken = Modules(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::Modules(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Modules
	//		Modules -> PROCroutine Modules_1
	//---------------------------------
	LookaHeadToken = PROCroutine(LookaHeadToken);
	LookaHeadToken = Modules_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::Modules_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Modules_1
	//		Modules_1 -> MODULE PROCroutine Modules_1
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::MODULE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::MODULE);
		LookaHeadToken = PROCroutine(LookaHeadToken);
		LookaHeadToken = Modules_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::PROCroutine(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		PROCroutine
	//		PROCroutine -> SysDecl PROCroutine_1
	//---------------------------------
	LookaHeadToken = SysDecl(LookaHeadToken);
	LookaHeadToken = PROCroutine_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::PROCroutine_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		PROCroutine_1
	//		PROCroutine_1 -> PROC ProcDef PROCroutine_1
	//		              -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::PROC:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::PROC);
		LookaHeadToken = ProcDef(LookaHeadToken);
		LookaHeadToken = PROCroutine_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ProcDef(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcDef
	//		ProcDef -> ProcDecl ProcBody
	//---------------------------------
	LookaHeadToken = ProcDecl(LookaHeadToken);
	LookaHeadToken = ProcBody(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::FuncDef(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FuncDef
	//		FuncDef -> FuncDecl ProcBody
	//---------------------------------
	LookaHeadToken = FuncDecl(LookaHeadToken);
	LookaHeadToken = ProcBody(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ProcDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcDecl
	//		ProcDecl -> IDENT OptInit ( ParamList )
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToken = OptInit(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = ParamList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::FuncDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FuncDecl
	//		FuncDecl -> IDENT OptInit ( ParamList )
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToken = OptInit(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = ParamList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ProcBody(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcBody
	//		ProcBody -> BEGIN ProcBody_1 END
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::BEGIN:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BEGIN);
		LookaHeadToken = ProcBody_1(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::END);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ProcBody_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcBody_1
	//		ProcBody_1 -> LocalDecls Statements
	//---------------------------------
	LookaHeadToken = LocalDecls(LookaHeadToken);
	LookaHeadToken = Statements(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::Statements(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Statements
	//		Statements -> ProcCall Begin
	//---------------------------------
	LookaHeadToken = ProcCall(LookaHeadToken);
	LookaHeadToken = Begin(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::Begin(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Begin
	//		Begin -> BEGIN Statements END ProcCall Begin
	//		      -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::BEGIN:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BEGIN);
		LookaHeadToken = Statements(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::END);
		LookaHeadToken = ProcCall(LookaHeadToken);
		LookaHeadToken = Begin(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ProcCall(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcCall
	//		ProcCall -> ForStmt ProcCall_1
	//---------------------------------
	LookaHeadToken = ForStmt(LookaHeadToken);
	LookaHeadToken = ProcCall_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ProcCall_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcCall_1
	//		ProcCall_1 -> PROC_IDENT PROCstmt ; ForStmt ProcCall_1
	//		           -> FUNC_IDENT PROCstmt ; ForStmt ProcCall_1
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::PROC_IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::PROC_IDENT);
		LookaHeadToken = PROCstmt(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = ForStmt(LookaHeadToken);
		LookaHeadToken = ProcCall_1(LookaHeadToken);
		break;
	case CAction65Lexer::FUNC_IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::FUNC_IDENT);
		LookaHeadToken = PROCstmt(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = ForStmt(LookaHeadToken);
		LookaHeadToken = ProcCall_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::PROCstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		PROCstmt
	//		PROCstmt -> ( MemCntentsList )
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('('):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = MemCntentsList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ForStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ForStmt
	//		ForStmt -> IfStmt ForStmt_1
	//---------------------------------
	LookaHeadToken = IfStmt(LookaHeadToken);
	LookaHeadToken = ForStmt_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ForStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ForStmt_1
	//		ForStmt_1 -> FOR FORstmt OD IfStmt ForStmt_1
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::FOR:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::FOR);
		LookaHeadToken = FORstmt(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::OD);
		LookaHeadToken = IfStmt(LookaHeadToken);
		LookaHeadToken = ForStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::FORstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FORstmt
	//		FORstmt -> IDENT = Start TO Finish STEPoption DO Statements
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('=');
		LookaHeadToken = Start(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::TO);
		LookaHeadToken = Finish(LookaHeadToken);
		LookaHeadToken = STEPoption(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::DO);
		LookaHeadToken = Statements(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Start(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Start
	//		Start -> ArithExpr
	//---------------------------------
	LookaHeadToken = ArithExpr(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::Finish(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Finish
	//		Finish -> ArithExpr
	//---------------------------------
	LookaHeadToken = ArithExpr(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::STEPoption(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		STEPoption
	//		STEPoption -> STEP ArithExpr
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::STEP:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::STEP);
		LookaHeadToken = ArithExpr(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::IfStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IfStmt
	//		IfStmt -> WhileStmt IfStmt_1
	//---------------------------------
	LookaHeadToken = WhileStmt(LookaHeadToken);
	LookaHeadToken = IfStmt_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::IfStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IfStmt_1
	//		IfStmt_1 -> IF If FI WhileStmt IfStmt_1
	//		         -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IF:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IF);
		LookaHeadToken = If(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::FI);
		LookaHeadToken = WhileStmt(LookaHeadToken);
		LookaHeadToken = IfStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::If(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		If
	//		If -> ArithExpr ThenPart
	//---------------------------------
	LookaHeadToken = ArithExpr(LookaHeadToken);
	LookaHeadToken = ThenPart(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ThenPart(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ThenPart
	//		ThenPart -> THEN ThenPart_1
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::THEN:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::THEN);
		LookaHeadToken = ThenPart_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ThenPart_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ThenPart_1
	//		ThenPart_1 -> Statements ElseIfPart
	//---------------------------------
	LookaHeadToken = Statements(LookaHeadToken);
	LookaHeadToken = ElseIfPart(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ElseIfPart(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ElseIfPart
	//		ElseIfPart -> ELSEIF ArithExpr ThenPart
	//		           -> ELSE Statements
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::ELSEIF:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::ELSEIF);
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = ThenPart(LookaHeadToken);
		break;
	case CAction65Lexer::ELSE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::ELSE);
		LookaHeadToken = Statements(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::WhileStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		WhileStmt
	//		WhileStmt -> DoStmt WhileStmt_1
	//---------------------------------
	LookaHeadToken = DoStmt(LookaHeadToken);
	LookaHeadToken = WhileStmt_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::WhileStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		WhileStmt_1
	//		WhileStmt_1 -> WHILE ArithExpr DO Statements OD DoStmt WhileStmt_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::WHILE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::WHILE);
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::DO);
		LookaHeadToken = Statements(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::OD);
		LookaHeadToken = DoStmt(LookaHeadToken);
		LookaHeadToken = WhileStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::DoStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DoStmt
	//		DoStmt -> EXITstmt DoStmt_1
	//---------------------------------
	LookaHeadToken = EXITstmt(LookaHeadToken);
	LookaHeadToken = DoStmt_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::DoStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DoStmt_1
	//		DoStmt_1 -> DO Statements OD EXITstmt DoStmt_1
	//		         -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::DO:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::DO);
		LookaHeadToken = Statements(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::OD);
		LookaHeadToken = EXITstmt(LookaHeadToken);
		LookaHeadToken = DoStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::EXITstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		EXITstmt
	//		EXITstmt -> RetStmt EXITstmt_1
	//---------------------------------
	LookaHeadToken = RetStmt(LookaHeadToken);
	LookaHeadToken = EXITstmt_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::EXITstmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		EXITstmt_1
	//		EXITstmt_1 -> EXIT ; RetStmt EXITstmt_1
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::EXIT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::EXIT);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = RetStmt(LookaHeadToken);
		LookaHeadToken = EXITstmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RetStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RetStmt
	//		RetStmt -> CodeBlock RetStmt_1
	//---------------------------------
	LookaHeadToken = CodeBlock(LookaHeadToken);
	LookaHeadToken = RetStmt_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::RetStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RetStmt_1
	//		RetStmt_1 -> RETURN RetStmt_2 ; CodeBlock RetStmt_1
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::RETURN:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::RETURN);
		LookaHeadToken = RetStmt_2(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = CodeBlock(LookaHeadToken);
		LookaHeadToken = RetStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RetStmt_2(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RetStmt_2
	//		RetStmt_2 -> ( ArithExpr )
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('('):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::CodeBlock(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CodeBlock
	//		CodeBlock -> UntillStmt CodeBlock_1
	//---------------------------------
	LookaHeadToken = UntillStmt(LookaHeadToken);
	LookaHeadToken = CodeBlock_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::CodeBlock_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CodeBlock_1
	//		CodeBlock_1 -> [ ConstList ] UntillStmt CodeBlock_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('['):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('[');
		LookaHeadToken = ConstList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(']');
		LookaHeadToken = UntillStmt(LookaHeadToken);
		LookaHeadToken = CodeBlock_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ConstList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ConstList
	//		ConstList -> CompConst ConstList_1
	//---------------------------------
	LookaHeadToken = CompConst(LookaHeadToken);
	LookaHeadToken = ConstList_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ConstList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ConstList_1
	//		ConstList_1 -> , CompConst ConstList_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer(','):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(',');
		LookaHeadToken = CompConst(LookaHeadToken);
		LookaHeadToken = ConstList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::UntillStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		UntillStmt
	//		UntillStmt -> Assignment UntillStmt_1
	//---------------------------------
	LookaHeadToken = Assignment(LookaHeadToken);
	LookaHeadToken = UntillStmt_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::UntillStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		UntillStmt_1
	//		UntillStmt_1 -> UNTILL ArithExpr ; Assignment UntillStmt_1
	//		             -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::UNTILL:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::UNTILL);
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = Assignment(LookaHeadToken);
		LookaHeadToken = UntillStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Assignment(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Assignment
	//		Assignment -> MemContents ASSIGNstmt
	//---------------------------------
	LookaHeadToken = MemContents(LookaHeadToken);
	LookaHeadToken = ASSIGNstmt(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ASSIGNstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ASSIGNstmt
	//		ASSIGNstmt -> = ArithExpr ; MemContents
	//		           -> ==+ ArithExpr ; MemContents
	//		           -> ==- ArithExpr ; MemContents
	//		           -> ==* ArithExpr ; MemContents
	//		           -> ==/ ArithExpr ; MemContents
	//		           -> ==MOD ArithExpr ; MemContents
	//		           -> ==& ArithExpr ; MemContents
	//		           -> ==! ArithExpr ; MemContents
	//		           -> ==% ArithExpr ; MemContents
	//		           -> ==LSH ArithExpr ; MemContents
	//		           -> ==RSH ArithExpr ; MemContents
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('='):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('=');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==+'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==+');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==-'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==-');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==*'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==*');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==/'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==/');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==MOD'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==MOD');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==&'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==&');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==!'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==!');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==%'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==%');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==LSH'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==LSH');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer('==RSH'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('==RSH');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ArithExpr(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ArithExpr
	//		ArithExpr -> LogicalAND LogicalOR_1
	//---------------------------------
	LookaHeadToken = LogicalAND(LookaHeadToken);
	LookaHeadToken = LogicalOR_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::LogicalOR_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		LogicalOR_1
	//		LogicalOR_1 -> OR LogicalAND LogicalOR_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::OR:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::OR);
		LookaHeadToken = LogicalAND(LookaHeadToken);
		LookaHeadToken = LogicalOR_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::LogicalAND(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		LogicalAND
	//		LogicalAND -> RelOperation LogicalAND_1
	//---------------------------------
	LookaHeadToken = RelOperation(LookaHeadToken);
	LookaHeadToken = LogicalAND_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::LogicalAND_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		LogicalAND_1
	//		LogicalAND_1 -> AND RelOperation LogicalAND_1
	//		             -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::AND:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::AND);
		LookaHeadToken = RelOperation(LookaHeadToken);
		LookaHeadToken = LogicalAND_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RelOperation(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RelOperation
	//		RelOperation -> RelEquals RelOperation_1
	//---------------------------------
	LookaHeadToken = RelEquals(LookaHeadToken);
	LookaHeadToken = RelOperation_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::RelOperation_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RelOperation_1
	//		RelOperation_1 -> > RelEquals RelOperation_1
	//		               -> < RelEquals RelOperation_1
	//		               -> GTEQ RelEquals RelOperation_1
	//		               -> LTEQ RelEquals RelOperation_1
	//		               -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('>'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('>');
		LookaHeadToken = RelEquals(LookaHeadToken);
		LookaHeadToken = RelOperation_1(LookaHeadToken);
		break;
	case CAction65Lexer('<'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('<');
		LookaHeadToken = RelEquals(LookaHeadToken);
		LookaHeadToken = RelOperation_1(LookaHeadToken);
		break;
	case CAction65Lexer::GTEQ:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::GTEQ);
		LookaHeadToken = RelEquals(LookaHeadToken);
		LookaHeadToken = RelOperation_1(LookaHeadToken);
		break;
	case CAction65Lexer::LTEQ:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::LTEQ);
		LookaHeadToken = RelEquals(LookaHeadToken);
		LookaHeadToken = RelOperation_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RelEquals(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RelEquals
	//		RelEquals -> BitwiseOR RelEquals_1
	//---------------------------------
	LookaHeadToken = BitwiseOR(LookaHeadToken);
	LookaHeadToken = RelEquals_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::RelEquals_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RelEquals_1
	//		RelEquals_1 -> = BitwiseOR RelEquals_1
	//		            -> # BitwiseOR RelEquals_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('='):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('=');
		LookaHeadToken = BitwiseOR(LookaHeadToken);
		LookaHeadToken = RelEquals_1(LookaHeadToken);
		break;
	case CAction65Lexer('#'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('#');
		LookaHeadToken = BitwiseOR(LookaHeadToken);
		LookaHeadToken = RelEquals_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::BitwiseOR(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseOR
	//		BitwiseOR -> BitwiseAND BitwiseOR_1
	//---------------------------------
	LookaHeadToken = BitwiseAND(LookaHeadToken);
	LookaHeadToken = BitwiseOR_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::BitwiseOR_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseOR_1
	//		BitwiseOR_1 -> % BitwiseAND BitwiseOR_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('%'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('%');
		LookaHeadToken = BitwiseAND(LookaHeadToken);
		LookaHeadToken = BitwiseOR_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::BitwiseAND(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseAND
	//		BitwiseAND -> BitwiseXOR BitwiseAND_1
	//---------------------------------
	LookaHeadToken = BitwiseXOR(LookaHeadToken);
	LookaHeadToken = BitwiseAND_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::BitwiseAND_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseAND_1
	//		BitwiseAND_1 -> & BitwiseXOR BitwiseAND_1
	//		             -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('&'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('&');
		LookaHeadToken = BitwiseXOR(LookaHeadToken);
		LookaHeadToken = BitwiseAND_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::BitwiseXOR(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseXOR
	//		BitwiseXOR -> AddExpr BitwiseXOR_1
	//---------------------------------
	LookaHeadToken = AddExpr(LookaHeadToken);
	LookaHeadToken = BitwiseXOR_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::BitwiseXOR_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseXOR_1
	//		BitwiseXOR_1 -> ! AddExpr BitwiseXOR_1
	//		             -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('!'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('!');
		LookaHeadToken = AddExpr(LookaHeadToken);
		LookaHeadToken = BitwiseXOR_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::AddExpr(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		AddExpr
	//		AddExpr -> ShifExpr AddExpr_1
	//---------------------------------
	LookaHeadToken = ShifExpr(LookaHeadToken);
	LookaHeadToken = AddExpr_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::AddExpr_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		AddExpr_1
	//		AddExpr_1 -> + ShifExpr AddExpr_1
	//		          -> - ShifExpr AddExpr_1
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('+'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('+');
		LookaHeadToken = ShifExpr(LookaHeadToken);
		LookaHeadToken = AddExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer('-'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('-');
		LookaHeadToken = ShifExpr(LookaHeadToken);
		LookaHeadToken = AddExpr_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ShifExpr(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ShifExpr
	//		ShifExpr -> MultExpr ShiftExpr_1
	//---------------------------------
	LookaHeadToken = MultExpr(LookaHeadToken);
	LookaHeadToken = ShiftExpr_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ShiftExpr_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ShiftExpr_1
	//		ShiftExpr_1 -> LSH MultExpr ShiftExpr_1
	//		            -> RSH MultExpr ShiftExpr_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::LSH:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::LSH);
		LookaHeadToken = MultExpr(LookaHeadToken);
		LookaHeadToken = ShiftExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer::RSH:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::RSH);
		LookaHeadToken = MultExpr(LookaHeadToken);
		LookaHeadToken = ShiftExpr_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::MultExpr(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MultExpr
	//		MultExpr -> Unary MultExpr_1
	//---------------------------------
	LookaHeadToken = Unary(LookaHeadToken);
	LookaHeadToken = MultExpr_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::MultExpr_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MultExpr_1
	//		MultExpr_1 -> * Unary MultExpr_1
	//		           -> / Unary MultExpr_1
	//		           -> MOD Unary MultExpr_1
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('*'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('*');
		LookaHeadToken = Unary(LookaHeadToken);
		LookaHeadToken = MultExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer('/'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('/');
		LookaHeadToken = Unary(LookaHeadToken);
		LookaHeadToken = MultExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer::MOD:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::MOD);
		LookaHeadToken = Unary(LookaHeadToken);
		LookaHeadToken = MultExpr_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Unary(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Unary
	//		Unary -> - Unary
	//		      -> Factor
	//---------------------------------
MIXED
	case CAction65Lexer('-'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('-');
		LookaHeadToken = Unary(LookaHeadToken);
		break;
	default:
		LookaHeadToken = Factor(LookaHeadToken);
		break;
}
CAction65Lexer::Token CAction65_Parser::Factor(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Factor
	//		Factor -> FUNC_IDENT ( MemCntentsList )
	//		       -> ( ArithExpr )
	//		       -> NUMBER
	//		       -> *
	//		       -> @ MemContents
	//		       -> IDENT MemContentsType
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::FUNC_IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::FUNC_IDENT);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = MemCntentsList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		break;
	case CAction65Lexer('('):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		break;
	case CAction65Lexer::NUMBER:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::NUMBER);
		break;
	case CAction65Lexer('*'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('*');
		break;
	case CAction65Lexer('@'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('@');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToken = MemContentsType(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::MemCntentsList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MemCntentsList
	//		MemCntentsList -> MemContents MemCntentsList_1
	//---------------------------------
	LookaHeadToken = MemContents(LookaHeadToken);
	LookaHeadToken = MemCntentsList_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::MemCntentsList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MemCntentsList_1
	//		MemCntentsList_1 -> , MemContents MemCntentsList_1
	//		                 -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer(','):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(',');
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = MemCntentsList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::SysDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		SysDecl
	//		SysDecl -> TypeDecl Define
	//---------------------------------
	LookaHeadToken = TypeDecl(LookaHeadToken);
	LookaHeadToken = Define(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::Define(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Define
	//		Define -> DEFINE DefList TypeDecl Define
	//		       -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::DEFINE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::DEFINE);
		LookaHeadToken = DefList(LookaHeadToken);
		LookaHeadToken = TypeDecl(LookaHeadToken);
		LookaHeadToken = Define(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::DefList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DefList
	//		DefList -> Def DefList_1
	//---------------------------------
	LookaHeadToken = Def(LookaHeadToken);
	LookaHeadToken = DefList_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::DefList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DefList_1
	//		DefList_1 -> , Def DefList_1
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer(','):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(',');
		LookaHeadToken = Def(LookaHeadToken);
		LookaHeadToken = DefList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Def(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Def
	//		Def -> IDENT = CompConst
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('=');
		LookaHeadToken = CompConst(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::TypeDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		TypeDecl
	//		TypeDecl -> RecDecl TypeDecl_1
	//---------------------------------
	LookaHeadToken = RecDecl(LookaHeadToken);
	LookaHeadToken = TypeDecl_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::TypeDecl_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		TypeDecl_1
	//		TypeDecl_1 -> TYPE RecIdent RecDecl TypeDecl_1
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::TYPE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::TYPE);
		LookaHeadToken = RecIdent(LookaHeadToken);
		LookaHeadToken = RecDecl(LookaHeadToken);
		LookaHeadToken = TypeDecl_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RecIdent(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RecIdent
	//		RecIdent -> IDENT RecField
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToken = RecField(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RecField(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RecField
	//		RecField -> = [ VarDecls ]
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('='):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('=');
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('[');
		LookaHeadToken = VarDecls(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(']');
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::VarDecls(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		VarDecls
	//		VarDecls -> CHAR Modifier VarList ; VarDecls
	//		         -> BYTE Modifier VarList ; VarDecls
	//		         -> INT Modifier VarList ; VarDecls
	//		         -> CARD Modifier VarList ; VarDecls
	//		         -> BOOL Modifier VarList ; VarDecls
	//		         -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::CHAR:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CHAR);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = VarDecls(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BYTE);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = VarDecls(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::INT);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = VarDecls(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CARD);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = VarDecls(LookaHeadToken);
		break;
	case CAction65Lexer::BOOL:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BOOL);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = VarDecls(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::VarList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		VarList
	//		VarList -> Ident VarList_1
	//---------------------------------
	LookaHeadToken = Ident(LookaHeadToken);
	LookaHeadToken = VarList_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::VarList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		VarList_1
	//		VarList_1 -> , Ident VarList_1
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer(','):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(',');
		LookaHeadToken = Ident(LookaHeadToken);
		LookaHeadToken = VarList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Modifier(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Modifier
	//		Modifier -> POINTER
	//		         -> ARRAY ArrayStuff
	//		         -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::POINTER:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::POINTER);
		break;
	case CAction65Lexer::ARRAY:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::ARRAY);
		LookaHeadToken = ArrayStuff(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ArrayStuff(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ArrayStuff
	//		ArrayStuff -> ( ArithExpr ) OptArrayInit
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('('):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		LookaHeadToken = OptArrayInit(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::OptArrayInit(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		OptArrayInit
	//		OptArrayInit -> = [ ConstList ]
	//		             -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('='):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('=');
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('[');
		LookaHeadToken = ConstList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(']');
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RecDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RecDecl
	//		RecDecl -> FundDecl RecDecl_1
	//---------------------------------
	LookaHeadToken = FundDecl(LookaHeadToken);
	LookaHeadToken = RecDecl_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::RecDecl_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RecDecl_1
	//		RecDecl_1 -> RECORDTYPE Modifier DataDecl RecDecl_1
	//		          -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::RECORDTYPE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::RECORDTYPE);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = DataDecl(LookaHeadToken);
		LookaHeadToken = RecDecl_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::FundDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FundDecl
	//		FundDecl -> BOOL Modifier FUNCDecl FundDecl
	//		         -> CHAR Modifier FUNCDecl FundDecl
	//		         -> BYTE Modifier FUNCDecl FundDecl
	//		         -> INT Modifier FUNCDecl FundDecl
	//		         -> CARD Modifier FUNCDecl FundDecl
	//		         -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::BOOL:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BOOL);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = FUNCDecl(LookaHeadToken);
		LookaHeadToken = FundDecl(LookaHeadToken);
		break;
	case CAction65Lexer::CHAR:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CHAR);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = FUNCDecl(LookaHeadToken);
		LookaHeadToken = FundDecl(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BYTE);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = FUNCDecl(LookaHeadToken);
		LookaHeadToken = FundDecl(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::INT);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = FUNCDecl(LookaHeadToken);
		LookaHeadToken = FundDecl(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CARD);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = FUNCDecl(LookaHeadToken);
		LookaHeadToken = FundDecl(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::FUNCDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FUNCDecl
	//		FUNCDecl -> DataDecl FUNCDecl_1
	//---------------------------------
	LookaHeadToken = DataDecl(LookaHeadToken);
	LookaHeadToken = FUNCDecl_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::FUNCDecl_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FUNCDecl_1
	//		FUNCDecl_1 -> FUNC FuncDef DataDecl FUNCDecl_1
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::FUNC:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::FUNC);
		LookaHeadToken = FuncDef(LookaHeadToken);
		LookaHeadToken = DataDecl(LookaHeadToken);
		LookaHeadToken = FUNCDecl_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::DataDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DataDecl
	//		DataDecl -> IdentList DataCecl_1
	//---------------------------------
	LookaHeadToken = IdentList(LookaHeadToken);
	LookaHeadToken = DataCecl_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::DataCecl_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DataCecl_1
	//		DataCecl_1 -> ; IdentList DataCecl_1
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer(';'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = IdentList(LookaHeadToken);
		LookaHeadToken = DataCecl_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::IdentList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IdentList
	//		IdentList -> Ident IdentList_1
	//---------------------------------
	LookaHeadToken = Ident(LookaHeadToken);
	LookaHeadToken = IdentList_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::IdentList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IdentList_1
	//		IdentList_1 -> , Ident IdentList_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer(','):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(',');
		LookaHeadToken = Ident(LookaHeadToken);
		LookaHeadToken = IdentList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Ident(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Ident
	//		Ident -> IDENT OptInit
	//		      -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToken = OptInit(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::OptInit(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		OptInit
	//		OptInit -> = CompConst
	//		        -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('='):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('=');
		LookaHeadToken = CompConst(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ParamList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ParamList
	//		ParamList -> Param ParamList_1
	//---------------------------------
	LookaHeadToken = Param(LookaHeadToken);
	LookaHeadToken = ParamList_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::ParamList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ParamList_1
	//		ParamList_1 -> , Param ParamList_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer(','):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(',');
		LookaHeadToken = Param(LookaHeadToken);
		LookaHeadToken = ParamList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Param(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Param
	//		Param -> RECORDTYPE POINTER Ident
	//		      -> CHAR Modifier Ident
	//		      -> BYTE Modifier Ident
	//		      -> INT Modifier Ident
	//		      -> CARD Modifier Ident
	//		      -> BOOL Modifier Ident
	//		      -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::RECORDTYPE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::RECORDTYPE);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::POINTER);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::CHAR:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CHAR);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BYTE);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::INT);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CARD);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::BOOL:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BOOL);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::LocalDecls(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		LocalDecls
	//		LocalDecls -> CHAR Modifier VarList ; LocalDecls
	//		           -> BYTE Modifier VarList ; LocalDecls
	//		           -> INT Modifier VarList ; LocalDecls
	//		           -> CARD Modifier VarList ; LocalDecls
	//		           -> BOOL Modifier VarList ; LocalDecls
	//		           -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::CHAR:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CHAR);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = LocalDecls(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BYTE);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = LocalDecls(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::INT);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = LocalDecls(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::CARD);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = LocalDecls(LookaHeadToken);
		break;
	case CAction65Lexer::BOOL:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::BOOL);
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(';');
		LookaHeadToken = LocalDecls(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::CompConst(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CompConst
	//		CompConst -> BaseCompConst CompConst_1
	//---------------------------------
	LookaHeadToken = BaseCompConst(LookaHeadToken);
	LookaHeadToken = CompConst_1(LookaHeadToken);
}
CAction65Lexer::Token CAction65_Parser::CompConst_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CompConst_1
	//		CompConst_1 -> + BaseCompConst CompConst_1
	//		            -> - BaseCompConst CompConst_1
	//		            -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('+'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('+');
		LookaHeadToken = BaseCompConst(LookaHeadToken);
		LookaHeadToken = CompConst_1(LookaHeadToken);
		break;
	case CAction65Lexer('-'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('-');
		LookaHeadToken = BaseCompConst(LookaHeadToken);
		LookaHeadToken = CompConst_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::BaseCompConst(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BaseCompConst
	//		BaseCompConst -> NUMBER
	//		              -> *
	//		              -> @ MemContents
	//		              -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::NUMBER:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::NUMBER);
		break;
	case CAction65Lexer('*'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('*');
		break;
	case CAction65Lexer('@'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('@');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::MemContents(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MemContents
	//		MemContents -> IDENT MemContentsType
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::IDENT);
		LookaHeadToken = MemContentsType(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::MemContentsType(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MemContentsType
	//		MemContentsType -> ( ArithExpr )
	//		                -> ^
	//		                -> . MemContents
	//		                -> e
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer('('):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('(');
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::(')');
		break;
	case CAction65Lexer('^'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('^');
		break;
	case CAction65Lexer('.'):
		LookaHeadToke = GetLexer()->Expect(LookaHeadToken, CToken::LLRD_Token::('.');
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	}
}
