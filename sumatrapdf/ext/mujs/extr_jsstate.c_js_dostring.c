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
 int /*<<< orphan*/  js_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_loadstring (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  js_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  js_pushundefined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_report (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_trystring (int /*<<< orphan*/ *,int,char*) ; 

int js_dostring(js_State *J, const char *source)
{
	if (js_try(J)) {
		js_report(J, js_trystring(J, -1, "Error"));
		js_pop(J, 1);
		return 1;
	}
	js_loadstring(J, "[string]", source);
	js_pushundefined(J);
	js_call(J, 0);
	js_pop(J, 1);
	js_endtry(J);
	return 0;
}