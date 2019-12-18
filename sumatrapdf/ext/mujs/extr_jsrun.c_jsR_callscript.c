#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_Value ;
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {int varlen; int /*<<< orphan*/ * vartab; } ;
typedef  TYPE_1__ js_Function ;
typedef  int /*<<< orphan*/  js_Environment ;

/* Variables and functions */
 scalar_t__ BOT ; 
 scalar_t__ TOP ; 
 int /*<<< orphan*/  jsR_restorescope (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsR_run (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  jsR_savescope (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_initvar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushvalue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stackidx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void jsR_callscript(js_State *J, int n, js_Function *F, js_Environment *scope)
{
	js_Value v;
	int i;

	if (scope)
		jsR_savescope(J, scope);

	/* scripts take no arguments */
	js_pop(J, n);

	for (i = 0; i < F->varlen; ++i) {
		js_pushundefined(J);
		js_initvar(J, F->vartab[i], -1);
		js_pop(J, 1);
	}

	jsR_run(J, F);
	v = *stackidx(J, -1);
	TOP = --BOT; /* clear stack */
	js_pushvalue(J, v);

	if (scope)
		jsR_restorescope(J);
}