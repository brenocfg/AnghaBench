#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  default_strict; } ;
typedef  TYPE_1__ js_State ;
typedef  int /*<<< orphan*/  js_Function ;
struct TYPE_7__ {int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  line; } ;
typedef  TYPE_2__ js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * newfun (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

js_Function *jsC_compilefunction(js_State *J, js_Ast *prog)
{
	return newfun(J, prog->line, prog->a, prog->b, prog->c, 0, J->default_strict);
}