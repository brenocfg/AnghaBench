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
 int /*<<< orphan*/  JS_HNUMBER ; 
 int /*<<< orphan*/  isfinite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_getproperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  js_iscallable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ js_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushnull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_tonumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_toprimitive (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_typeerror (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void Dp_toJSON(js_State *J)
{
	js_copy(J, 0);
	js_toprimitive(J, -1, JS_HNUMBER);
	if (js_isnumber(J, -1) && !isfinite(js_tonumber(J, -1))) {
		js_pushnull(J);
		return;
	}
	js_pop(J, 1);

	js_getproperty(J, 0, "toISOString");
	if (!js_iscallable(J, -1))
		js_typeerror(J, "this.toISOString is not a function");
	js_copy(J, 0);
	js_call(J, 0);
}