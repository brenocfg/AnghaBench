#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_3__ {int gcmark; int funlen; struct TYPE_3__** funtab; } ;
typedef  TYPE_1__ js_Function ;

/* Variables and functions */

__attribute__((used)) static void jsG_markfunction(js_State *J, int mark, js_Function *fun)
{
	int i;
	fun->gcmark = mark;
	for (i = 0; i < fun->funlen; ++i)
		if (fun->funtab[i]->gcmark != mark)
			jsG_markfunction(J, mark, fun->funtab[i]);
}