#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  js_State ;
struct TYPE_4__ {struct TYPE_4__* code; struct TYPE_4__* vartab; struct TYPE_4__* strtab; struct TYPE_4__* numtab; struct TYPE_4__* funtab; } ;
typedef  TYPE_1__ js_Function ;

/* Variables and functions */
 int /*<<< orphan*/  js_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void jsG_freefunction(js_State *J, js_Function *fun)
{
	js_free(J, fun->funtab);
	js_free(J, fun->numtab);
	js_free(J, fun->strtab);
	js_free(J, fun->vartab);
	js_free(J, fun->code);
	js_free(J, fun);
}