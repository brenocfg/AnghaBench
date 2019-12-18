#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_1__ ;

/* Type definitions */
struct TYPE_41__ {int lexline; char lookahead; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_42__ {scalar_t__ type; } ;
typedef  TYPE_2__ js_Ast ;

/* Variables and functions */
 scalar_t__ AST_IDENTIFIER ; 
 int /*<<< orphan*/  BREAK ; 
 int /*<<< orphan*/  CONTINUE ; 
 int /*<<< orphan*/  DEBUGGER ; 
 int /*<<< orphan*/  DECREC () ; 
 int /*<<< orphan*/  DO ; 
 int /*<<< orphan*/  EMPTY ; 
 scalar_t__ EXP_IDENTIFIER ; 
 int /*<<< orphan*/  IF ; 
 int /*<<< orphan*/  INCREC () ; 
 int /*<<< orphan*/  LABEL ; 
 int /*<<< orphan*/  RETURN ; 
 TYPE_2__* STM0 (int /*<<< orphan*/ ) ; 
 TYPE_2__* STM1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* STM2 (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* STM3 (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* STM4 (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SWITCH ; 
 int /*<<< orphan*/  THROW ; 
 char TK_BREAK ; 
 char TK_CATCH ; 
 char TK_CONTINUE ; 
 char TK_DEBUGGER ; 
 char TK_DO ; 
 char TK_ELSE ; 
 char TK_FINALLY ; 
 char TK_FOR ; 
 char TK_FUNCTION ; 
 char TK_IDENTIFIER ; 
 char TK_IF ; 
 char TK_RETURN ; 
 char TK_SWITCH ; 
 char TK_THROW ; 
 char TK_TRY ; 
 char TK_VAR ; 
 char TK_WHILE ; 
 char TK_WITH ; 
 int /*<<< orphan*/  TRY ; 
 int /*<<< orphan*/  VAR ; 
 int /*<<< orphan*/  WHILE ; 
 int /*<<< orphan*/  WITH ; 
 TYPE_2__* block (TYPE_1__*) ; 
 TYPE_2__* caselist (TYPE_1__*) ; 
 TYPE_2__* expression (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* forstatement (TYPE_1__*,int) ; 
 TYPE_2__* funstm (TYPE_1__*,int) ; 
 TYPE_2__* identifier (TYPE_1__*) ; 
 TYPE_2__* identifieropt (TYPE_1__*) ; 
 scalar_t__ jsP_accept (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsP_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsP_expect (TYPE_1__*,char) ; 
 int /*<<< orphan*/  jsP_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  jsY_tokenstring (char) ; 
 int /*<<< orphan*/  semicolon (TYPE_1__*) ; 
 TYPE_2__* vardeclist (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static js_Ast *statement(js_State *J)
{
	js_Ast *a, *b, *c, *d;
	js_Ast *stm;
	int line = J->lexline;

	INCREC();

	if (J->lookahead == '{') {
		stm = block(J);
	}

	else if (jsP_accept(J, TK_VAR)) {
		a = vardeclist(J, 0);
		semicolon(J);
		stm = STM1(VAR, a);
	}

	/* empty statement */
	else if (jsP_accept(J, ';')) {
		stm = STM0(EMPTY);
	}

	else if (jsP_accept(J, TK_IF)) {
		jsP_expect(J, '(');
		a = expression(J, 0);
		jsP_expect(J, ')');
		b = statement(J);
		if (jsP_accept(J, TK_ELSE))
			c = statement(J);
		else
			c = NULL;
		stm = STM3(IF, a, b, c);
	}

	else if (jsP_accept(J, TK_DO)) {
		a = statement(J);
		jsP_expect(J, TK_WHILE);
		jsP_expect(J, '(');
		b = expression(J, 0);
		jsP_expect(J, ')');
		semicolon(J);
		stm = STM2(DO, a, b);
	}

	else if (jsP_accept(J, TK_WHILE)) {
		jsP_expect(J, '(');
		a = expression(J, 0);
		jsP_expect(J, ')');
		b = statement(J);
		stm = STM2(WHILE, a, b);
	}

	else if (jsP_accept(J, TK_FOR)) {
		stm = forstatement(J, line);
	}

	else if (jsP_accept(J, TK_CONTINUE)) {
		a = identifieropt(J);
		semicolon(J);
		stm = STM1(CONTINUE, a);
	}

	else if (jsP_accept(J, TK_BREAK)) {
		a = identifieropt(J);
		semicolon(J);
		stm = STM1(BREAK, a);
	}

	else if (jsP_accept(J, TK_RETURN)) {
		if (J->lookahead != ';' && J->lookahead != '}' && J->lookahead != 0)
			a = expression(J, 0);
		else
			a = NULL;
		semicolon(J);
		stm = STM1(RETURN, a);
	}

	else if (jsP_accept(J, TK_WITH)) {
		jsP_expect(J, '(');
		a = expression(J, 0);
		jsP_expect(J, ')');
		b = statement(J);
		stm = STM2(WITH, a, b);
	}

	else if (jsP_accept(J, TK_SWITCH)) {
		jsP_expect(J, '(');
		a = expression(J, 0);
		jsP_expect(J, ')');
		jsP_expect(J, '{');
		b = caselist(J);
		jsP_expect(J, '}');
		stm = STM2(SWITCH, a, b);
	}

	else if (jsP_accept(J, TK_THROW)) {
		a = expression(J, 0);
		semicolon(J);
		stm = STM1(THROW, a);
	}

	else if (jsP_accept(J, TK_TRY)) {
		a = block(J);
		b = c = d = NULL;
		if (jsP_accept(J, TK_CATCH)) {
			jsP_expect(J, '(');
			b = identifier(J);
			jsP_expect(J, ')');
			c = block(J);
		}
		if (jsP_accept(J, TK_FINALLY)) {
			d = block(J);
		}
		if (!b && !d)
			jsP_error(J, "unexpected token in try: %s (expected 'catch' or 'finally')", jsY_tokenstring(J->lookahead));
		stm = STM4(TRY, a, b, c, d);
	}

	else if (jsP_accept(J, TK_DEBUGGER)) {
		semicolon(J);
		stm = STM0(DEBUGGER);
	}

	else if (jsP_accept(J, TK_FUNCTION)) {
		jsP_warning(J, "function statements are not standard");
		stm = funstm(J, line);
	}

	/* labelled statement or expression statement */
	else if (J->lookahead == TK_IDENTIFIER) {
		a = expression(J, 0);
		if (a->type == EXP_IDENTIFIER && jsP_accept(J, ':')) {
			a->type = AST_IDENTIFIER;
			b = statement(J);
			stm = STM2(LABEL, a, b);
		} else {
			semicolon(J);
			stm = a;
		}
	}

	/* expression statement */
	else {
		stm = expression(J, 0);
		semicolon(J);
	}

	DECREC();
	return stm;
}