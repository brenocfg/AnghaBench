#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t type; double number; struct TYPE_6__* d; struct TYPE_6__* c; struct TYPE_6__* b; struct TYPE_6__* a; int /*<<< orphan*/  string; int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
#define  AST_FUNDEC 140 
#define  AST_IDENTIFIER 139 
 size_t AST_LIST ; 
#define  EXP_FUN 138 
#define  EXP_IDENTIFIER 137 
#define  EXP_NUMBER 136 
#define  EXP_PROP_GET 135 
#define  EXP_PROP_SET 134 
#define  EXP_REGEXP 133 
#define  EXP_STRING 132 
#define  STM_BLOCK 131 
#define  STM_CASE 130 
#define  STM_DEFAULT 129 
#define  STM_SWITCH 128 
 int /*<<< orphan*/ * astname ; 
 int /*<<< orphan*/  pc (char) ; 
 int /*<<< orphan*/  pn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pregexp (int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  ps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pstr (int /*<<< orphan*/ ) ; 
 void sblock (int,TYPE_1__*) ; 
 int /*<<< orphan*/  slist (int,TYPE_1__*) ; 

__attribute__((used)) static void snode(int d, js_Ast *node)
{
	void (*afun)(int,js_Ast*) = snode;
	void (*bfun)(int,js_Ast*) = snode;
	void (*cfun)(int,js_Ast*) = snode;
	void (*dfun)(int,js_Ast*) = snode;

	if (!node) {
		return;
	}

	if (node->type == AST_LIST) {
		slist(d, node);
		return;
	}

	pc('(');
	ps(astname[node->type]);
	pc(':');
	pn(node->line);
	switch (node->type) {
	default: break;
	case AST_IDENTIFIER: pc(' '); ps(node->string); break;
	case EXP_IDENTIFIER: pc(' '); ps(node->string); break;
	case EXP_STRING: pc(' '); pstr(node->string); break;
	case EXP_REGEXP: pc(' '); pregexp(node->string, node->number); break;
	case EXP_NUMBER: printf(" %.9g", node->number); break;
	case STM_BLOCK: afun = sblock; break;
	case AST_FUNDEC: case EXP_FUN: cfun = sblock; break;
	case EXP_PROP_GET: cfun = sblock; break;
	case EXP_PROP_SET: cfun = sblock; break;
	case STM_SWITCH: bfun = sblock; break;
	case STM_CASE: bfun = sblock; break;
	case STM_DEFAULT: afun = sblock; break;
	}
	if (node->a) { pc(' '); afun(d, node->a); }
	if (node->b) { pc(' '); bfun(d, node->b); }
	if (node->c) { pc(' '); cfun(d, node->c); }
	if (node->d) { pc(' '); dfun(d, node->d); }
	pc(')');
}