#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;

/* Variables and functions */
 int JS_DONTCONF ; 
 int JS_DONTENUM ; 
 int JS_READONLY ; 
 int /*<<< orphan*/  callbound ; 
 int /*<<< orphan*/  constructbound ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_defproperty (int /*<<< orphan*/ *,int,char*,int) ; 
 int js_getlength (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newarray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_newcconstructor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  js_setindex (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Fp_bind(js_State *J)
{
	int i, top = js_gettop(J);
	int n;

	if (!js_iscallable(J, 0))
		js_typeerror(J, "not a function");

	n = js_getlength(J, 0);
	if (n > top - 2)
		n -= top - 2;
	else
		n = 0;

	/* Reuse target function's prototype for HasInstance check. */
	js_getproperty(J, 0, "prototype");
	js_newcconstructor(J, callbound, constructbound, "[bind]", n);

	/* target function */
	js_copy(J, 0);
	js_defproperty(J, -2, "__TargetFunction__", JS_READONLY | JS_DONTENUM | JS_DONTCONF);

	/* bound this */
	js_copy(J, 1);
	js_defproperty(J, -2, "__BoundThis__", JS_READONLY | JS_DONTENUM | JS_DONTCONF);

	/* bound arguments */
	js_newarray(J);
	for (i = 2; i < top; ++i) {
		js_copy(J, i);
		js_setindex(J, -2, i - 2);
	}
	js_defproperty(J, -2, "__BoundArguments__", JS_READONLY | JS_DONTENUM | JS_DONTCONF);
}