#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_2__* gcast; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_12__ {int type; int line; struct TYPE_12__* gcnext; struct TYPE_12__* parent; scalar_t__ casejump; int /*<<< orphan*/ * jumps; int /*<<< orphan*/ * string; scalar_t__ number; struct TYPE_12__* d; struct TYPE_12__* c; struct TYPE_12__* b; struct TYPE_12__* a; } ;
typedef  TYPE_2__ js_Ast ;
typedef  enum js_AstType { ____Placeholder_js_AstType } js_AstType ;

/* Variables and functions */
 TYPE_2__* js_malloc (TYPE_1__*,int) ; 

__attribute__((used)) static js_Ast *jsP_newnode(js_State *J, enum js_AstType type, int line, js_Ast *a, js_Ast *b, js_Ast *c, js_Ast *d)
{
	js_Ast *node = js_malloc(J, sizeof *node);

	node->type = type;
	node->line = line;
	node->a = a;
	node->b = b;
	node->c = c;
	node->d = d;
	node->number = 0;
	node->string = NULL;
	node->jumps = NULL;
	node->casejump = 0;

	node->parent = NULL;
	if (a) a->parent = node;
	if (b) b->parent = node;
	if (c) c->parent = node;
	if (d) d->parent = node;

	node->gcnext = J->gcast;
	J->gcast = node;

	return node;
}