#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  GE; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Function ;
struct TYPE_21__ {int /*<<< orphan*/ * s; } ;
typedef  TYPE_2__ js_Buffer ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * jsC_compilefunction (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsP_freeparse (TYPE_1__*) ; 
 int /*<<< orphan*/ * jsP_parsefunction (TYPE_1__*,char*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  js_endtry (TYPE_1__*) ; 
 int /*<<< orphan*/  js_free (TYPE_1__*,TYPE_2__*) ; 
 int js_gettop (TYPE_1__*) ; 
 scalar_t__ js_isdefined (TYPE_1__*,int) ; 
 int /*<<< orphan*/  js_newfunction (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  js_putc (TYPE_1__*,TYPE_2__**,char) ; 
 int /*<<< orphan*/  js_puts (TYPE_1__*,TYPE_2__**,char*) ; 
 int /*<<< orphan*/  js_throw (TYPE_1__*) ; 
 char* js_tostring (TYPE_1__*,int) ; 
 scalar_t__ js_try (TYPE_1__*) ; 

__attribute__((used)) static void jsB_Function(js_State *J)
{
	int i, top = js_gettop(J);
	js_Buffer *sb = NULL;
	const char *body;
	js_Ast *parse;
	js_Function *fun;

	if (js_try(J)) {
		js_free(J, sb);
		jsP_freeparse(J);
		js_throw(J);
	}

	/* p1, p2, ..., pn */
	if (top > 2) {
		for (i = 1; i < top - 1; ++i) {
			if (i > 1)
				js_putc(J, &sb, ',');
			js_puts(J, &sb, js_tostring(J, i));
		}
		js_putc(J, &sb, ')');
		js_putc(J, &sb, 0);
	}

	/* body */
	body = js_isdefined(J, top - 1) ? js_tostring(J, top - 1) : "";

	parse = jsP_parsefunction(J, "[string]", sb ? sb->s : NULL, body);
	fun = jsC_compilefunction(J, parse);

	js_endtry(J);
	js_free(J, sb);
	jsP_freeparse(J);

	js_newfunction(J, fun, J->GE);
}