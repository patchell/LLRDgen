CAction65Lexer::Token CAction65_Parser::Action65(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Action65
	//		Action65 -> Modules
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::Modules(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Modules
	//		Modules -> PROCroutine Modules_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::Modules_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Modules_1
	//		Modules_1 -> MODULE PROCroutine Modules_1
	//		          -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::MODULE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::MODULE)
		LookaHeadToken = PROCroutine(LookaHeadToken);
		LookaHeadToken = Modules_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::PROCroutine(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		PROCroutine
	//		PROCroutine -> FUNCroutine PROCroutine_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::PROCroutine_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		PROCroutine_1
	//		PROCroutine_1 -> PROC ProcDef FUNCroutine PROCroutine_1
	//		              -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::PROC:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::PROC)
		LookaHeadToken = ProcDef(LookaHeadToken);
		LookaHeadToken = FUNCroutine(LookaHeadToken);
		LookaHeadToken = PROCroutine_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::FUNCroutine(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FUNCroutine
	//		FUNCroutine -> SysDecls FUNCroutine_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::FUNCroutine_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FUNCroutine_1
	//		FUNCroutine_1 -> FUNC FuncDef SysDecls FUNCroutine_1
	//		              -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::FUNC:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::FUNC)
		LookaHeadToken = FuncDef(LookaHeadToken);
		LookaHeadToken = SysDecls(LookaHeadToken);
		LookaHeadToken = FUNCroutine_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ProcDef(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcDef
	//		ProcDef -> ProcDecl ProcBody
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::FuncDef(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FuncDef
	//		FuncDef -> FuncDecl ProcBody
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::ProcBody(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcBody
	//		ProcBody -> BEGIN SysDecls ProcBody_1
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::BEGIN:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BEGIN)
		LookaHeadToken = SysDecls(LookaHeadToken);
		LookaHeadToken = ProcBody_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ProcBody_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcBody_1
	//		ProcBody_1 -> Statements END
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::ProcDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcDecl
	//		ProcDecl -> ProcIdent OptInit ( ParamList )
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::FuncDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FuncDecl
	//		FuncDecl -> FundType FuncIdent OptInit ( ParamList )
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::ProcIdent(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcIdent
	//		ProcIdent -> PROC_IDENT
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::PROC_IDENT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::PROC_IDENT)
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::FuncIdent(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FuncIdent
	//		FuncIdent -> FUNC_IDENT
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::FUNC_IDENT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::FUNC_IDENT)
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Statements(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Statements
	//		Statements -> ProcCall Begin
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::Begin(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Begin
	//		Begin -> BEGIN ProcCall END Begin
	//		      -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::BEGIN:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BEGIN)
		LookaHeadToken = ProcCall(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::END)
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
}
CAction65Lexer::Token CAction65_Parser::ProcCall_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ProcCall_1
	//		ProcCall_1 -> PROC_IDENT PROCstmt ; ForStmt ProcCall_1
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::PROC_IDENT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::PROC_IDENT)
		LookaHeadToken = PROCstmt(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = ForStmt(LookaHeadToken);
		LookaHeadToken = ProcCall_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ForStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ForStmt
	//		ForStmt -> IfStmt ForStmt_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::ForStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ForStmt_1
	//		ForStmt_1 -> FOR FORstmt OD IfStmt ForStmt_1
	//		          -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::FOR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::FOR)
		LookaHeadToken = FORstmt(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::OD)
		LookaHeadToken = IfStmt(LookaHeadToken);
		LookaHeadToken = ForStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::IfStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IfStmt
	//		IfStmt -> WhileStmt IfStmt_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::IfStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IfStmt_1
	//		IfStmt_1 -> IF If FI WhileStmt IfStmt_1
	//		         -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IF:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::IF)
		LookaHeadToken = If(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::FI)
		LookaHeadToken = WhileStmt(LookaHeadToken);
		LookaHeadToken = IfStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::WhileStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		WhileStmt
	//		WhileStmt -> DoStmt WhileStmt_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::WhileStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		WhileStmt_1
	//		WhileStmt_1 -> WHILE WhileLoop OD DoStmt WhileStmt_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::WHILE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::WHILE)
		LookaHeadToken = WhileLoop(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::OD)
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
}
CAction65Lexer::Token CAction65_Parser::DoStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DoStmt_1
	//		DoStmt_1 -> DO DOstmt OD EXITstmt DoStmt_1
	//		         -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::DO:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::DO)
		LookaHeadToken = DOstmt(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::OD)
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
}
CAction65Lexer::Token CAction65_Parser::EXITstmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		EXITstmt_1
	//		EXITstmt_1 -> EXIT ; RetStmt EXITstmt_1
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::EXIT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::EXIT)
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
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
}
CAction65Lexer::Token CAction65_Parser::RetStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RetStmt_1
	//		RetStmt_1 -> RETURN RETURNstmt ; CodeBlock RetStmt_1
	//		          -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::RETURN:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::RETURN)
		LookaHeadToken = RETURNstmt(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = CodeBlock(LookaHeadToken);
		LookaHeadToken = RetStmt_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::CodeBlock(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CodeBlock
	//		CodeBlock -> UntillStmt CodeBlock_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::CodeBlock_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CodeBlock_1
	//		CodeBlock_1 -> [ CODEblock ] UntillStmt CodeBlock_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::[:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::[)
		LookaHeadToken = CODEblock(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::])
		LookaHeadToken = UntillStmt(LookaHeadToken);
		LookaHeadToken = CodeBlock_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::UntillStmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		UntillStmt
	//		UntillStmt -> Assignment UntillStmt_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::UntillStmt_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		UntillStmt_1
	//		UntillStmt_1 -> UNTILL UNTILLstmt ; Assignment UntillStmt_1
	//		             -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::UNTILL:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::UNTILL)
		LookaHeadToken = UNTILLstmt(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
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
}
CAction65Lexer::Token CAction65_Parser::ASSIGNstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ASSIGNstmt
	//		ASSIGNstmt -> = ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==+ ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==- ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==* ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==/ ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==MOD ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==& ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==! ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==XOR ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==% ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==LSH ArithExpr ; MemContents ASSIGNstmt
	//		           -> ==RSH ArithExpr ; MemContents ASSIGNstmt
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::=:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::=)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==+:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==+)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==-:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==-)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==*:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==*)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==/:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==/)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==MOD:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==MOD)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==&:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==&)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==!:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==!)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==XOR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==XOR)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==%:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==%)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==LSH:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==LSH)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	case CAction65Lexer::==RSH:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::==RSH)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = ASSIGNstmt(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::PROCstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		PROCstmt
	//		PROCstmt -> ( IdentList )
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::(:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::()
		LookaHeadToken = IdentList(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::))
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::If(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		If
	//		If -> ArithExpr ThenPart
	//---------------------------------
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
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::THEN)
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
}
CAction65Lexer::Token CAction65_Parser::ElseIfPart(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ElseIfPart
	//		ElseIfPart -> ELSEIF ArithExpr ThenPart
	//		           -> ELSE Statements
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::ELSEIF:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::ELSEIF)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = ThenPart(LookaHeadToken);
		break;
	case CAction65Lexer::ELSE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::ELSE)
		LookaHeadToken = Statements(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::DOstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DOstmt
	//		DOstmt -> Statements
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::UNTILLstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		UNTILLstmt
	//		UNTILLstmt -> UNTILL ArithExpr
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::UNTILL:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::UNTILL)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::WhileLoop(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		WhileLoop
	//		WhileLoop -> ArithExpr DO Statements
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::FORstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FORstmt
	//		FORstmt -> Ident = Start TO Finish STEPoption DO Statements
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::Start(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Start
	//		Start -> ArithExpr
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::Finish(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Finish
	//		Finish -> ArithExpr
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::STEPoption(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		STEPoption
	//		STEPoption -> STEP ArithExpr
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::STEP:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::STEP)
		LookaHeadToken = ArithExpr(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::CODEblock(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CODEblock
	//		CODEblock -> CompConst CODEblock_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::CODEblock_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CODEblock_1
	//		CODEblock_1 -> , CompConst CODEblock_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::,:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::,)
		LookaHeadToken = CompConst(LookaHeadToken);
		LookaHeadToken = CODEblock_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RETURNstmt(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RETURNstmt
	//		RETURNstmt -> ( ArithExpr )
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::(:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::()
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::))
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ArithExpr(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ArithExpr
	//		ArithExpr -> LogicalAND LogicalOR_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::LogicalOR_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		LogicalOR_1
	//		LogicalOR_1 -> OR LogicalAND LogicalOR_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::OR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::OR)
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
}
CAction65Lexer::Token CAction65_Parser::LogicalAND_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		LogicalAND_1
	//		LogicalAND_1 -> AND RelOperation LogicalAND_1
	//		             -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::AND:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::AND)
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
}
CAction65Lexer::Token CAction65_Parser::RelOperation_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RelOperation_1
	//		RelOperation_1 -> > RelEquals RelOperation_1
	//		               -> < RelEquals RelOperation_1
	//		               -> GTEQ RelEquals RelOperation_1
	//		               -> LTEQ RelEquals RelOperation_1
	//		               -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::>:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::>)
		LookaHeadToken = RelEquals(LookaHeadToken);
		LookaHeadToken = RelOperation_1(LookaHeadToken);
		break;
	case CAction65Lexer::<:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::<)
		LookaHeadToken = RelEquals(LookaHeadToken);
		LookaHeadToken = RelOperation_1(LookaHeadToken);
		break;
	case CAction65Lexer::GTEQ:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::GTEQ)
		LookaHeadToken = RelEquals(LookaHeadToken);
		LookaHeadToken = RelOperation_1(LookaHeadToken);
		break;
	case CAction65Lexer::LTEQ:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::LTEQ)
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
}
CAction65Lexer::Token CAction65_Parser::RelEquals_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RelEquals_1
	//		RelEquals_1 -> = BitwiseOR RelEquals_1
	//		            -> # BitwiseOR RelEquals_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::=:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::=)
		LookaHeadToken = BitwiseOR(LookaHeadToken);
		LookaHeadToken = RelEquals_1(LookaHeadToken);
		break;
	case CAction65Lexer::#:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::#)
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
}
CAction65Lexer::Token CAction65_Parser::BitwiseOR_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseOR_1
	//		BitwiseOR_1 -> % BitwiseAND BitwiseOR_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::%:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::%)
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
}
CAction65Lexer::Token CAction65_Parser::BitwiseAND_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseAND_1
	//		BitwiseAND_1 -> & BitwiseXOR BitwiseAND_1
	//		             -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::&:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::&)
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
}
CAction65Lexer::Token CAction65_Parser::BitwiseXOR_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		BitwiseXOR_1
	//		BitwiseXOR_1 -> ! AddExpr BitwiseXOR_1
	//		             -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::!:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::!)
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
}
CAction65Lexer::Token CAction65_Parser::AddExpr_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		AddExpr_1
	//		AddExpr_1 -> + ShifExpr AddExpr_1
	//		          -> - ShifExpr AddExpr_1
	//		          -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::+:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::+)
		LookaHeadToken = ShifExpr(LookaHeadToken);
		LookaHeadToken = AddExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer::-:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::-)
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
}
CAction65Lexer::Token CAction65_Parser::ShiftExpr_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ShiftExpr_1
	//		ShiftExpr_1 -> LSH MultExpr ShiftExpr_1
	//		            -> RSH MultExpr ShiftExpr_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::LSH:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::LSH)
		LookaHeadToken = MultExpr(LookaHeadToken);
		LookaHeadToken = ShiftExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer::RSH:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::RSH)
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
}
CAction65Lexer::Token CAction65_Parser::MultExpr_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MultExpr_1
	//		MultExpr_1 -> * Unary MultExpr_1
	//		           -> / Unary MultExpr_1
	//		           -> MOD Unary MultExpr_1
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::*:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::*)
		LookaHeadToken = Unary(LookaHeadToken);
		LookaHeadToken = MultExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer::/:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::/)
		LookaHeadToken = Unary(LookaHeadToken);
		LookaHeadToken = MultExpr_1(LookaHeadToken);
		break;
	case CAction65Lexer::MOD:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::MOD)
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
}
CAction65Lexer::Token CAction65_Parser::Factor(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Factor
	//		Factor -> BaseCompConst
	//		       -> FUNCcall
	//		       -> ( ArithExpr )
	//		       -> MemContents
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::FUNCcall(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FUNCcall
	//		FUNCcall -> FuncIdent ( IdentList )
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::IdentList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IdentList
	//		IdentList -> MemContents IdentList_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::IdentList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		IdentList_1
	//		IdentList_1 -> , MemContents IdentList_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::,:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::,)
		LookaHeadToken = MemContents(LookaHeadToken);
		LookaHeadToken = IdentList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::FundType(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		FundType
	//		FundType -> BOOL OptModifier
	//		         -> CHAR OptModifier
	//		         -> BYTE OptModifier
	//		         -> INT OptModifier
	//		         -> CARD OptModifier
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::BOOL:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BOOL)
		LookaHeadToken = OptModifier(LookaHeadToken);
		break;
	case CAction65Lexer::CHAR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CHAR)
		LookaHeadToken = OptModifier(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BYTE)
		LookaHeadToken = OptModifier(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::INT)
		LookaHeadToken = OptModifier(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CARD)
		LookaHeadToken = OptModifier(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::OptModifier(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		OptModifier
	//		OptModifier -> POINTER
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::POINTER:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::POINTER)
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ParamList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ParamList
	//		ParamList -> Param ParamList_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::ParamList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ParamList_1
	//		ParamList_1 -> , Param ParamList_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::,:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::,)
		LookaHeadToken = Param(LookaHeadToken);
		LookaHeadToken = ParamList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Param(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Param
	//		Param -> RECORDTYPE OptModifier Ident
	//		      -> CHAR OptModifier Ident
	//		      -> BYTE OptModifier Ident
	//		      -> INT OptModifier Ident
	//		      -> CARD OptModifier Ident
	//		      -> BOOL OptModifier Ident
	//		      -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::RECORDTYPE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::RECORDTYPE)
		LookaHeadToken = OptModifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::CHAR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CHAR)
		LookaHeadToken = OptModifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BYTE)
		LookaHeadToken = OptModifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::INT)
		LookaHeadToken = OptModifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CARD)
		LookaHeadToken = OptModifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	case CAction65Lexer::BOOL:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BOOL)
		LookaHeadToken = OptModifier(LookaHeadToken);
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::VarDecls(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		VarDecls
	//		VarDecls -> RECORDTYPE Modifier VarList
	//		         -> CHAR Modifier VarList
	//		         -> BYTE Modifier VarList
	//		         -> INT Modifier VarList
	//		         -> CARD Modifier VarList
	//		         -> BOOL Modifier VarList
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::RECORDTYPE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::RECORDTYPE)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::CHAR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CHAR)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BYTE)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::INT)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CARD)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::BOOL:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BOOL)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::SysDecls(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		SysDecls
	//		SysDecls -> SysDecl SysDecls_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::SysDecls_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		SysDecls_1
	//		SysDecls_1 -> ; SysDecl SysDecls_1
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::;:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = SysDecl(LookaHeadToken);
		LookaHeadToken = SysDecls_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::SysDecl(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		SysDecl
	//		SysDecl -> DEFINE DefList
	//		        -> TYPE RecIdent
	//		        -> RECORDTYPE Modifier VarList
	//		        -> CHAR Modifier VarList
	//		        -> BYTE Modifier VarList
	//		        -> INT Modifier VarList
	//		        -> CARD Modifier VarList
	//		        -> BOOL VarList
	//		        -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::DEFINE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::DEFINE)
		LookaHeadToken = DefList(LookaHeadToken);
		break;
	case CAction65Lexer::TYPE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::TYPE)
		LookaHeadToken = RecIdent(LookaHeadToken);
		break;
	case CAction65Lexer::RECORDTYPE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::RECORDTYPE)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::CHAR:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CHAR)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::BYTE:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BYTE)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::INT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::INT)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::CARD:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::CARD)
		LookaHeadToken = Modifier(LookaHeadToken);
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	case CAction65Lexer::BOOL:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::BOOL)
		LookaHeadToken = VarList(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::VarList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		VarList
	//		VarList -> VarName VarList_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::VarList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		VarList_1
	//		VarList_1 -> , VarName VarList_1
	//		          -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::,:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::,)
		LookaHeadToken = VarName(LookaHeadToken);
		LookaHeadToken = VarList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::VarName(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		VarName
	//		VarName -> Ident OptInit
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::OptInit(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		OptInit
	//		OptInit -> = CompConst
	//		        -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::=:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::=)
		LookaHeadToken = CompConst(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::DefList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DefList
	//		DefList -> Def DefList_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::DefList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		DefList_1
	//		DefList_1 -> , Def DefList_1
	//		          -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::,:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::,)
		LookaHeadToken = Def(LookaHeadToken);
		LookaHeadToken = DefList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Def(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Def
	//		Def -> Ident = CompConst
	//---------------------------------
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
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::IDENT)
		LookaHeadToken = RecField(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RecField(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RecField
	//		RecField -> = [ RecFieldList ]
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::=:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::=)
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::[)
		LookaHeadToken = RecFieldList(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::])
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::RecFieldList(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RecFieldList
	//		RecFieldList -> VarDecls RecFieldList_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::RecFieldList_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		RecFieldList_1
	//		RecFieldList_1 -> ; VarDecls RecFieldList_1
	//		               -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::;:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::;)
		LookaHeadToken = VarDecls(LookaHeadToken);
		LookaHeadToken = RecFieldList_1(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Modifier(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Modifier
	//		Modifier -> POINTER
	//		         -> ARRAY ArrayStuff
	//		         -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::POINTER:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::POINTER)
		break;
	case CAction65Lexer::ARRAY:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::ARRAY)
		LookaHeadToken = ArrayStuff(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::ArrayStuff(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		ArrayStuff
	//		ArrayStuff -> ( ArithExpr ) OptArrayInit
	//		           -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::(:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::()
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::))
		LookaHeadToken = OptArrayInit(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::OptArrayInit(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		OptArrayInit
	//		OptArrayInit -> = [ CodeBlock ]
	//		             -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::=:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::=)
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::[)
		LookaHeadToken = CodeBlock(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::])
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::CompConst(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CompConst
	//		CompConst -> BaseCompConst CompConst_1
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::CompConst_1(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		CompConst_1
	//		CompConst_1 -> + BaseCompConst CompConst_1
	//		            -> - BaseCompConst CompConst_1
	//		            -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::+:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::+)
		LookaHeadToken = BaseCompConst(LookaHeadToken);
		LookaHeadToken = CompConst_1(LookaHeadToken);
		break;
	case CAction65Lexer::-:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::-)
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
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::NUMBER:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::NUMBER)
		break;
	case CAction65Lexer::*:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::*)
		break;
	case CAction65Lexer::@:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::@)
		LookaHeadToken = MemContents(LookaHeadToken);
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::Ident(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		Ident
	//		Ident -> IDENT
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::IDENT:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::IDENT)
		break;
	}
}
CAction65Lexer::Token CAction65_Parser::MemContents(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MemContents
	//		MemContents -> Ident MemContentsType
	//---------------------------------
}
CAction65Lexer::Token CAction65_Parser::MemContentsType(CAction65Lexer::Token LookaHeadToken);
{
	//---------------------------------
	//		MemContentsType
	//		MemContentsType -> ( ArithExpr )
	//		                -> ^
	//		                -> . Ident
	//		                -> ϵ
	//---------------------------------
	switch(LookaHeadToken)
	{
	case CAction65Lexer::(:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::()
		LookaHeadToken = ArithExpr(LookaHeadToken);
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::))
		break;
	case CAction65Lexer::^:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::^)
		break;
	case CAction65Lexer::.:
		LookaHeadToken = GetLexer()->Expect(LookaHeadToken,CAction65Lexer::.)
		LookaHeadToken = Ident(LookaHeadToken);
		break;
	}
}
