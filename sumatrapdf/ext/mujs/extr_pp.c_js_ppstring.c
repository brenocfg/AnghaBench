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
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  jsP_dumplist (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsP_dumpsyntax (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jsP_freeparse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsP_parse (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  js_endtry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  js_throw (int /*<<< orphan*/ *) ; 
 scalar_t__ js_try (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void js_ppstring(js_State *J, const char *filename, const char *source, int minify)
{
	js_Ast *P;
	if (js_try(J)) {
		jsP_freeparse(J);
		js_throw(J);
	}
	P = jsP_parse(J, filename, source);
	if (minify > 2)
		jsP_dumplist(J, P);
	else
		jsP_dumpsyntax(J, P, minify);
	jsP_freeparse(J);
	js_endtry(J);
}