#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; char* string; double number; struct TYPE_9__* c; struct TYPE_9__* b; struct TYPE_9__* a; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
#define  AST_IDENTIFIER 192 
#define  EXP_ADD 191 
#define  EXP_ARRAY 190 
#define  EXP_ASS 189 
#define  EXP_ASS_ADD 188 
#define  EXP_ASS_BITAND 187 
#define  EXP_ASS_BITOR 186 
#define  EXP_ASS_BITXOR 185 
#define  EXP_ASS_DIV 184 
#define  EXP_ASS_MOD 183 
#define  EXP_ASS_MUL 182 
#define  EXP_ASS_SHL 181 
#define  EXP_ASS_SHR 180 
#define  EXP_ASS_SUB 179 
#define  EXP_ASS_USHR 178 
#define  EXP_BITAND 177 
#define  EXP_BITNOT 176 
#define  EXP_BITOR 175 
#define  EXP_BITXOR 174 
#define  EXP_CALL 173 
#define  EXP_COMMA 172 
#define  EXP_COND 171 
#define  EXP_DELETE 170 
#define  EXP_DIV 169 
#define  EXP_EQ 168 
#define  EXP_FALSE 167 
#define  EXP_FUN 166 
#define  EXP_GE 165 
#define  EXP_GT 164 
#define  EXP_IDENTIFIER 163 
#define  EXP_IN 162 
#define  EXP_INDEX 161 
#define  EXP_INSTANCEOF 160 
#define  EXP_LE 159 
#define  EXP_LOGAND 158 
#define  EXP_LOGNOT 157 
#define  EXP_LOGOR 156 
#define  EXP_LT 155 
#define  EXP_MEMBER 154 
#define  EXP_MOD 153 
#define  EXP_MUL 152 
#define  EXP_NE 151 
#define  EXP_NEG 150 
#define  EXP_NEW 149 
#define  EXP_NULL 148 
#define  EXP_NUMBER 147 
#define  EXP_OBJECT 146 
#define  EXP_POS 145 
#define  EXP_POSTDEC 144 
#define  EXP_POSTINC 143 
#define  EXP_PREDEC 142 
#define  EXP_PREINC 141 
#define  EXP_REGEXP 140 
#define  EXP_SHL 139 
#define  EXP_SHR 138 
#define  EXP_STRICTEQ 137 
#define  EXP_STRICTNE 136 
#define  EXP_STRING 135 
#define  EXP_SUB 134 
#define  EXP_THIS 133 
#define  EXP_TRUE 132 
#define  EXP_TYPEOF 131 
#define  EXP_UNDEF 130 
#define  EXP_USHR 129 
#define  EXP_VOID 128 
 int /*<<< orphan*/  in (int) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  pargs (int,TYPE_1__*) ; 
 int /*<<< orphan*/  parray (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pbin (int,int,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pc (char) ; 
 int /*<<< orphan*/  pobject (int,TYPE_1__*) ; 
 int prec (int) ; 
 int /*<<< orphan*/  pregexp (char*,double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  ps (char*) ; 
 int /*<<< orphan*/  pstmlist (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pstr (char*) ; 
 int /*<<< orphan*/  puna (int,int,TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  sp () ; 

__attribute__((used)) static void pexpi(int d, int p, js_Ast *exp)
{
	int tp, paren;

	if (!exp) return;

	tp = prec(exp->type);
	paren = 0;
	if (tp < p) {
		pc('(');
		paren = 1;
	}
	p = tp;

	switch (exp->type) {
	case AST_IDENTIFIER: ps(exp->string); break;
	case EXP_IDENTIFIER: ps(exp->string); break;
	case EXP_NUMBER: printf("%.9g", exp->number); break;
	case EXP_STRING: pstr(exp->string); break;
	case EXP_REGEXP: pregexp(exp->string, exp->number); break;

	case EXP_UNDEF: break;
	case EXP_NULL: ps("null"); break;
	case EXP_TRUE: ps("true"); break;
	case EXP_FALSE: ps("false"); break;
	case EXP_THIS: ps("this"); break;

	case EXP_OBJECT: pobject(d, exp->a); break;
	case EXP_ARRAY: parray(d, exp->a); break;

	case EXP_DELETE: puna(d, p, exp, "delete ", ""); break;
	case EXP_VOID: puna(d, p, exp, "void ", ""); break;
	case EXP_TYPEOF: puna(d, p, exp, "typeof ", ""); break;
	case EXP_PREINC: puna(d, p, exp, "++", ""); break;
	case EXP_PREDEC: puna(d, p, exp, "--", ""); break;
	case EXP_POSTINC: puna(d, p, exp, "", "++"); break;
	case EXP_POSTDEC: puna(d, p, exp, "", "--"); break;
	case EXP_POS: puna(d, p, exp, "+", ""); break;
	case EXP_NEG: puna(d, p, exp, "-", ""); break;
	case EXP_BITNOT: puna(d, p, exp, "~", ""); break;
	case EXP_LOGNOT: puna(d, p, exp, "!", ""); break;

	case EXP_LOGOR: pbin(d, p, exp, "||"); break;
	case EXP_LOGAND: pbin(d, p, exp, "&&"); break;
	case EXP_BITOR: pbin(d, p, exp, "|"); break;
	case EXP_BITXOR: pbin(d, p, exp, "^"); break;
	case EXP_BITAND: pbin(d, p, exp, "&"); break;
	case EXP_EQ: pbin(d, p, exp, "=="); break;
	case EXP_NE: pbin(d, p, exp, "!="); break;
	case EXP_STRICTEQ: pbin(d, p, exp, "==="); break;
	case EXP_STRICTNE: pbin(d, p, exp, "!=="); break;
	case EXP_LT: pbin(d, p, exp, "<"); break;
	case EXP_GT: pbin(d, p, exp, ">"); break;
	case EXP_LE: pbin(d, p, exp, "<="); break;
	case EXP_GE: pbin(d, p, exp, ">="); break;
	case EXP_IN: pbin(d, p, exp, "in"); break;
	case EXP_SHL: pbin(d, p, exp, "<<"); break;
	case EXP_SHR: pbin(d, p, exp, ">>"); break;
	case EXP_USHR: pbin(d, p, exp, ">>>"); break;
	case EXP_ADD: pbin(d, p, exp, "+"); break;
	case EXP_SUB: pbin(d, p, exp, "-"); break;
	case EXP_MUL: pbin(d, p, exp, "*"); break;
	case EXP_DIV: pbin(d, p, exp, "/"); break;
	case EXP_MOD: pbin(d, p, exp, "%"); break;
	case EXP_ASS: pbin(d, p, exp, "="); break;
	case EXP_ASS_MUL: pbin(d, p, exp, "*="); break;
	case EXP_ASS_DIV: pbin(d, p, exp, "/="); break;
	case EXP_ASS_MOD: pbin(d, p, exp, "%="); break;
	case EXP_ASS_ADD: pbin(d, p, exp, "+="); break;
	case EXP_ASS_SUB: pbin(d, p, exp, "-="); break;
	case EXP_ASS_SHL: pbin(d, p, exp, "<<="); break;
	case EXP_ASS_SHR: pbin(d, p, exp, ">>="); break;
	case EXP_ASS_USHR: pbin(d, p, exp, ">>>="); break;
	case EXP_ASS_BITAND: pbin(d, p, exp, "&="); break;
	case EXP_ASS_BITXOR: pbin(d, p, exp, "^="); break;
	case EXP_ASS_BITOR: pbin(d, p, exp, "|="); break;

	case EXP_INSTANCEOF:
		pexpi(d, p, exp->a);
		ps(" instanceof ");
		pexpi(d, p, exp->b);
		break;

	case EXP_COMMA:
		pexpi(d, p, exp->a);
		pc(','); sp();
		pexpi(d, p, exp->b);
		break;

	case EXP_COND:
		pexpi(d, p, exp->a);
		sp(); pc('?'); sp();
		pexpi(d, p, exp->b);
		sp(); pc(':'); sp();
		pexpi(d, p, exp->c);
		break;

	case EXP_INDEX:
		pexpi(d, p, exp->a);
		pc('[');
		pexpi(d, 0, exp->b);
		pc(']');
		break;

	case EXP_MEMBER:
		pexpi(d, p, exp->a);
		pc('.');
		pexpi(d, 0, exp->b);
		break;

	case EXP_CALL:
		pexpi(d, p, exp->a);
		pc('(');
		pargs(d, exp->b);
		pc(')');
		break;

	case EXP_NEW:
		ps("new ");
		pexpi(d, p, exp->a);
		pc('(');
		pargs(d, exp->b);
		pc(')');
		break;

	case EXP_FUN:
		if (p == 0) pc('(');
		ps("function ");
		pexpi(d, 0, exp->a);
		pc('(');
		pargs(d, exp->b);
		pc(')'); sp(); pc('{'); nl();
		pstmlist(d, exp->c);
		in(d); pc('}');
		if (p == 0) pc(')');
		break;

	default:
		ps("<UNKNOWN>");
		break;
	}

	if (paren) pc(')');
}