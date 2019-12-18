#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ astdepth; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * EXP3 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUN ; 
 int /*<<< orphan*/  jsP_next (TYPE_1__*) ; 
 int /*<<< orphan*/  jsP_parse (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  jsY_initlex (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/ * parameters (TYPE_1__*) ; 

js_Ast *jsP_parsefunction(js_State *J, const char *filename, const char *params, const char *body)
{
	js_Ast *p = NULL;
	int line = 0;
	if (params) {
		jsY_initlex(J, filename, params);
		jsP_next(J);
		J->astdepth = 0;
		p = parameters(J);
	}
	return EXP3(FUN, NULL, p, jsP_parse(J, filename, body));
}