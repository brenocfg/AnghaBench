#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ astdepth; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/  jsP_foldconst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsP_next (TYPE_1__*) ; 
 int /*<<< orphan*/  jsY_initlex (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/ * script (TYPE_1__*,int /*<<< orphan*/ ) ; 

js_Ast *jsP_parse(js_State *J, const char *filename, const char *source)
{
	js_Ast *p;

	jsY_initlex(J, filename, source);
	jsP_next(J);
	J->astdepth = 0;
	p = script(J, 0);
	if (p)
		jsP_foldconst(p);

	return p;
}