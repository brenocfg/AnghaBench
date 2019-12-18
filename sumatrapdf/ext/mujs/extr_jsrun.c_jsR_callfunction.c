#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_Value ;
struct TYPE_22__ {int /*<<< orphan*/  strict; } ;
typedef  TYPE_1__ js_State ;
struct TYPE_23__ {int numparams; char** vartab; int varlen; scalar_t__ arguments; } ;
typedef  TYPE_2__ js_Function ;
typedef  int /*<<< orphan*/  js_Environment ;

/* Variables and functions */
 scalar_t__ BOT ; 
 int /*<<< orphan*/  JS_COBJECT ; 
 int /*<<< orphan*/  JS_DONTENUM ; 
 scalar_t__ TOP ; 
 int /*<<< orphan*/ * jsR_newenvironment (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsR_restorescope (TYPE_1__*) ; 
 int /*<<< orphan*/  jsR_run (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  jsR_savescope (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsV_newobject (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_copy (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_currentfunction (TYPE_1__*) ; 
 int /*<<< orphan*/  js_defproperty (TYPE_1__*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_initvar (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  js_newarguments (TYPE_1__*) ; 
 int /*<<< orphan*/  js_pop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_pushnumber (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_pushundefined (TYPE_1__*) ; 
 int /*<<< orphan*/  js_pushvalue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setindex (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * stackidx (TYPE_1__*,int) ; 

__attribute__((used)) static void jsR_callfunction(js_State *J, int n, js_Function *F, js_Environment *scope)
{
	js_Value v;
	int i;

	scope = jsR_newenvironment(J, jsV_newobject(J, JS_COBJECT, NULL), scope);

	jsR_savescope(J, scope);

	if (F->arguments) {
		js_newarguments(J);
		if (!J->strict) {
			js_currentfunction(J);
			js_defproperty(J, -2, "callee", JS_DONTENUM);
		}
		js_pushnumber(J, n);
		js_defproperty(J, -2, "length", JS_DONTENUM);
		for (i = 0; i < n; ++i) {
			js_copy(J, i + 1);
			js_setindex(J, -2, i);
		}
		js_initvar(J, "arguments", -1);
		js_pop(J, 1);
	}

	for (i = 0; i < n && i < F->numparams; ++i)
		js_initvar(J, F->vartab[i], i + 1);
	js_pop(J, n);

	for (; i < F->varlen; ++i) {
		js_pushundefined(J);
		js_initvar(J, F->vartab[i], -1);
		js_pop(J, 1);
	}

	jsR_run(J, F);
	v = *stackidx(J, -1);
	TOP = --BOT; /* clear stack */
	js_pushvalue(J, v);

	jsR_restorescope(J);
}