#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 scalar_t__ AST_LIST ; 
 int minify ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  pstm (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pstmlist (int,TYPE_1__*) ; 
 int /*<<< orphan*/  putchar (char) ; 

void jsP_dumpsyntax(js_State *J, js_Ast *prog, int dominify)
{
	minify = dominify;
	if (prog->type == AST_LIST)
		pstmlist(-1, prog);
	else {
		pstm(0, prog);
		nl();
	}
	if (minify > 1)
		putchar('\n');
}