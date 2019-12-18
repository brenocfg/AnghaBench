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
typedef  int /*<<< orphan*/  js_CFunction ;

/* Variables and functions */
 int /*<<< orphan*/  JS_DONTENUM ; 
 int /*<<< orphan*/  js_defglobal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_newcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void jsB_globalf(js_State *J, const char *name, js_CFunction cfun, int n)
{
	js_newcfunction(J, cfun, name, n);
	js_defglobal(J, name, JS_DONTENUM);
}