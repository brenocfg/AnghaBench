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
typedef  int /*<<< orphan*/  js_Function ;
struct TYPE_4__ {int /*<<< orphan*/  line; } ;
typedef  TYPE_1__ js_Ast ;

/* Variables and functions */
 int /*<<< orphan*/ * newfun (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

js_Function *jsC_compilescript(js_State *J, js_Ast *prog, int default_strict)
{
	return newfun(J, prog ? prog->line : 0, NULL, NULL, prog, 1, default_strict);
}