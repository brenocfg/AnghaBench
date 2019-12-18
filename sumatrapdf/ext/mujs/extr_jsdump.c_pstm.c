#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int type; struct TYPE_10__* b; struct TYPE_10__* a; struct TYPE_10__* d; struct TYPE_10__* c; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
#define  AST_FUNDEC 146 
 int STM_BLOCK ; 
#define  STM_BREAK 145 
#define  STM_CONTINUE 144 
#define  STM_DEBUGGER 143 
#define  STM_DO 142 
#define  STM_EMPTY 141 
#define  STM_FOR 140 
#define  STM_FOR_IN 139 
#define  STM_FOR_IN_VAR 138 
#define  STM_FOR_VAR 137 
#define  STM_IF 136 
#define  STM_LABEL 135 
#define  STM_RETURN 134 
#define  STM_SWITCH 133 
#define  STM_THROW 132 
#define  STM_TRY 131 
#define  STM_VAR 130 
#define  STM_WHILE 129 
#define  STM_WITH 128 
 int /*<<< orphan*/  in (int) ; 
 int /*<<< orphan*/  minify ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  pargs (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pblock (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pc (char) ; 
 int /*<<< orphan*/  pcaselist (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pexp (int,TYPE_1__*) ; 
 int /*<<< orphan*/  ps (char*) ; 
 int /*<<< orphan*/  pstmh (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pstmlist (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pvarlist (int,TYPE_1__*) ; 
 int /*<<< orphan*/  sp () ; 

__attribute__((used)) static void pstm(int d, js_Ast *stm)
{
	if (stm->type == STM_BLOCK) {
		pblock(d, stm);
		return;
	}

	in(d);

	switch (stm->type) {
	case AST_FUNDEC:
		ps("function ");
		pexp(d, stm->a);
		pc('(');
		pargs(d, stm->b);
		pc(')'); sp(); pc('{'); nl();
		pstmlist(d, stm->c);
		in(d); pc('}');
		break;

	case STM_EMPTY:
		pc(';');
		break;

	case STM_VAR:
		ps("var ");
		pvarlist(d, stm->a);
		pc(';');
		break;

	case STM_IF:
		ps("if"); sp(); pc('('); pexp(d, stm->a); pc(')');
		pstmh(d, stm->b);
		if (stm->c) {
			nl(); in(d); ps("else");
			pstmh(d, stm->c);
		}
		break;

	case STM_DO:
		ps("do");
		pstmh(d, stm->a);
		nl();
		in(d); ps("while"); sp(); pc('('); pexp(d, stm->b); pc(')'); pc(';');
		break;

	case STM_WHILE:
		ps("while"); sp(); pc('('); pexp(d, stm->a); pc(')');
		pstmh(d, stm->b);
		break;

	case STM_FOR:
		ps("for"); sp(); pc('(');
		pexp(d, stm->a); pc(';'); sp();
		pexp(d, stm->b); pc(';'); sp();
		pexp(d, stm->c); pc(')');
		pstmh(d, stm->d);
		break;
	case STM_FOR_VAR:
		ps("for"); sp(); ps("(var ");
		pvarlist(d, stm->a); pc(';'); sp();
		pexp(d, stm->b); pc(';'); sp();
		pexp(d, stm->c); pc(')');
		pstmh(d, stm->d);
		break;
	case STM_FOR_IN:
		ps("for"); sp(); pc('(');
		pexp(d, stm->a); ps(" in ");
		pexp(d, stm->b); pc(')');
		pstmh(d, stm->c);
		break;
	case STM_FOR_IN_VAR:
		ps("for"); sp(); ps("(var ");
		pvarlist(d, stm->a); ps(" in ");
		pexp(d, stm->b); pc(')');
		pstmh(d, stm->c);
		break;

	case STM_CONTINUE:
		ps("continue");
		if (stm->a) {
			pc(' '); pexp(d, stm->a);
		}
		pc(';');
		break;

	case STM_BREAK:
		ps("break");
		if (stm->a) {
			pc(' '); pexp(d, stm->a);
		}
		pc(';');
		break;

	case STM_RETURN:
		ps("return");
		if (stm->a) {
			pc(' '); pexp(d, stm->a);
		}
		pc(';');
		break;

	case STM_WITH:
		ps("with"); sp(); pc('('); pexp(d, stm->a); pc(')');
		pstmh(d, stm->b);
		break;

	case STM_SWITCH:
		ps("switch"); sp(); pc('(');
		pexp(d, stm->a);
		pc(')'); sp(); pc('{'); nl();
		pcaselist(d, stm->b);
		in(d); pc('}');
		break;

	case STM_THROW:
		ps("throw "); pexp(d, stm->a); pc(';');
		break;

	case STM_TRY:
		ps("try");
		if (minify && stm->a->type != STM_BLOCK)
			pc(' ');
		pstmh(d, stm->a);
		if (stm->b && stm->c) {
			nl(); in(d); ps("catch"); sp(); pc('('); pexp(d, stm->b); pc(')');
			pstmh(d, stm->c);
		}
		if (stm->d) {
			nl(); in(d); ps("finally");
			pstmh(d, stm->d);
		}
		break;

	case STM_LABEL:
		pexp(d, stm->a); pc(':'); sp(); pstm(d, stm->b);
		break;

	case STM_DEBUGGER:
		ps("debugger");
		pc(';');
		break;

	default:
		pexp(d, stm);
		pc(';');
	}
}