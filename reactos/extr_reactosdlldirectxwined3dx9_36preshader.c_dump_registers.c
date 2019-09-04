#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct d3dx_const_tab {unsigned int input_count; unsigned int* regset2table; TYPE_2__* inputs; TYPE_1__** inputs_param; } ;
struct TYPE_4__ {size_t RegisterSet; int /*<<< orphan*/  RegisterCount; int /*<<< orphan*/  RegisterIndex; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table_symbol ; 

__attribute__((used)) static void dump_registers(struct d3dx_const_tab *ctab)
{
    unsigned int table, i;

    for (i = 0; i < ctab->input_count; ++i)
    {
        table = ctab->regset2table[ctab->inputs[i].RegisterSet];
        TRACE("//   %-12s %s%-4u %u\n", ctab->inputs_param[i] ? ctab->inputs_param[i]->name : "(nil)",
                table_symbol[table], ctab->inputs[i].RegisterIndex, ctab->inputs[i].RegisterCount);
    }
}