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
typedef  int /*<<< orphan*/  js_Object ;

/* Variables and functions */
 int /*<<< orphan*/  JS_CERROR ; 
 scalar_t__ jsB_stacktrace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jsV_newobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int js_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_pushobject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_setproperty (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  js_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int jsB_ErrorX(js_State *J, js_Object *prototype)
{
	int top = js_gettop(J);
	js_pushobject(J, jsV_newobject(J, JS_CERROR, prototype));
	if (top > 1) {
		js_pushstring(J, js_tostring(J, 1));
		js_setproperty(J, -2, "message");
	}
	if (jsB_stacktrace(J, 1))
		js_setproperty(J, -2, "stackTrace");
	return 1;
}