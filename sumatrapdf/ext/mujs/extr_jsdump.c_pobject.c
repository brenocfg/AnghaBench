#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* b; int /*<<< orphan*/  c; struct TYPE_5__* a; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 scalar_t__ AST_LIST ; 
 int /*<<< orphan*/  COMMA ; 
#define  EXP_PROP_GET 130 
#define  EXP_PROP_SET 129 
#define  EXP_PROP_VAL 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  in (int) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  pargs (int,TYPE_1__*) ; 
 int /*<<< orphan*/  pc (char) ; 
 int /*<<< orphan*/  pexpi (int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ps (char*) ; 
 int /*<<< orphan*/  pstmlist (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sp () ; 

__attribute__((used)) static void pobject(int d, js_Ast *list)
{
	pc('{');
	if (list) {
		nl();
		in(d+1);
	}
	while (list) {
		js_Ast *kv = list->a;
		assert(list->type == AST_LIST);
		switch (kv->type) {
		default: break;
		case EXP_PROP_VAL:
			pexpi(d+1, COMMA, kv->a);
			pc(':'); sp();
			pexpi(d+1, COMMA, kv->b);
			break;
		case EXP_PROP_GET:
			ps("get ");
			pexpi(d+1, COMMA, kv->a);
			ps("()"); sp(); pc('{'); nl();
			pstmlist(d+1, kv->c);
			in(d+1); pc('}');
			break;
		case EXP_PROP_SET:
			ps("set ");
			pexpi(d+1, COMMA, kv->a);
			pc('(');
			pargs(d+1, kv->b);
			pc(')'); sp(); pc('{'); nl();
			pstmlist(d+1, kv->c);
			in(d+1); pc('}');
			break;
		}
		list = list->b;
		if (list) {
			pc(',');
			nl();
			in(d+1);
		} else {
			nl();
			in(d);
		}
	}
	pc('}');
}