#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct d3dx_regstore {int dummy; } ;
struct d3dx_pres_ins {size_t op; int component_count; scalar_t__ scalar_op; int /*<<< orphan*/ * inputs; int /*<<< orphan*/  output; } ;
struct TYPE_2__ {unsigned int input_count; scalar_t__ func_all_comps; int /*<<< orphan*/  mnem; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  dump_arg (struct d3dx_regstore*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* pres_op_info ; 

__attribute__((used)) static void dump_ins(struct d3dx_regstore *rs, const struct d3dx_pres_ins *ins)
{
    unsigned int i;

    TRACE("%s ", pres_op_info[ins->op].mnem);
    dump_arg(rs, &ins->output, pres_op_info[ins->op].func_all_comps ? 1 : ins->component_count);
    for (i = 0; i < pres_op_info[ins->op].input_count; ++i)
    {
        TRACE(", ");
        dump_arg(rs, &ins->inputs[i], ins->scalar_op && !i ? 1 : ins->component_count);
    }
    TRACE("\n");
}