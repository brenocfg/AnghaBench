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
struct TYPE_3__ {char* name; int numparams; char** vartab; } ;
typedef  TYPE_1__ js_Function ;
typedef  int /*<<< orphan*/  js_Buffer ;

/* Variables and functions */
 int /*<<< orphan*/  js_putc (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char) ; 
 int /*<<< orphan*/  js_puts (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static void reprfun(js_State *J, js_Buffer **sb, js_Function *fun)
{
	int i;
	js_puts(J, sb, "function ");
	js_puts(J, sb, fun->name);
	js_putc(J, sb, '(');
	for (i = 0; i < fun->numparams; ++i) {
		if (i > 0)
			js_puts(J, sb, ", ");
		js_puts(J, sb, fun->vartab[i]);
	}
	js_puts(J, sb, ") { [byte code] }");
}