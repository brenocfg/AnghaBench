#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int offset; int /*<<< orphan*/  table; } ;
struct TYPE_6__ {scalar_t__ table; } ;
struct TYPE_8__ {unsigned int opcode; unsigned int input_count; TYPE_2__ reg; scalar_t__ func_all_comps; TYPE_1__ index_reg; int /*<<< orphan*/  mnem; } ;
struct d3dx_pres_ins {unsigned int component_count; int scalar_op; unsigned int op; TYPE_3__ output; TYPE_3__* inputs; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 unsigned int PRES_NCOMP_MASK ; 
 unsigned int PRES_OPCODE_MASK ; 
 unsigned int PRES_OPCODE_SHIFT ; 
 scalar_t__ PRES_REGTAB_COUNT ; 
 unsigned int PRES_SCALAR_FLAG ; 
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ get_reg_offset (int /*<<< orphan*/ ,int) ; 
 unsigned int* parse_pres_arg (unsigned int*,unsigned int,TYPE_3__*) ; 
 TYPE_3__* pres_op_info ; 

__attribute__((used)) static unsigned int *parse_pres_ins(unsigned int *ptr, unsigned int count, struct d3dx_pres_ins *ins)
{
    unsigned int ins_code, ins_raw;
    unsigned int input_count;
    unsigned int i;

    if (count < 2)
    {
        WARN("Byte code buffer ends unexpectedly.\n");
        return NULL;
    }

    ins_raw = *ptr++;
    ins_code = (ins_raw & PRES_OPCODE_MASK) >> PRES_OPCODE_SHIFT;
    ins->component_count = ins_raw & PRES_NCOMP_MASK;
    ins->scalar_op = !!(ins_raw & PRES_SCALAR_FLAG);

    if (ins->component_count < 1 || ins->component_count > 4)
    {
        FIXME("Unsupported number of components %u.\n", ins->component_count);
        return NULL;
    }
    input_count = *ptr++;
    count -= 2;
    for (i = 0; i < ARRAY_SIZE(pres_op_info); ++i)
        if (ins_code == pres_op_info[i].opcode && input_count == pres_op_info[i].input_count)
            break;
    if (i == ARRAY_SIZE(pres_op_info))
    {
        FIXME("Unknown opcode %#x, input_count %u, raw %#x.\n", ins_code, input_count, ins_raw);
        return NULL;
    }
    ins->op = i;
    if (input_count > ARRAY_SIZE(ins->inputs))
    {
        FIXME("Actual input args count %u exceeds inputs array size, instruction %s.\n", input_count,
                pres_op_info[i].mnem);
        return NULL;
    }
    for (i = 0; i < input_count; ++i)
    {
        unsigned int *p;

        p = parse_pres_arg(ptr, count, &ins->inputs[i]);
        if (!p)
            return NULL;
        count -= p - ptr;
        ptr = p;
    }
    ptr = parse_pres_arg(ptr, count, &ins->output);
    if (ins->output.index_reg.table != PRES_REGTAB_COUNT)
    {
        FIXME("Relative addressing in output register not supported.\n");
        return NULL;
    }
    if (get_reg_offset(ins->output.reg.table, ins->output.reg.offset
            + (pres_op_info[ins->op].func_all_comps ? 0 : ins->component_count - 1))
            != get_reg_offset(ins->output.reg.table, ins->output.reg.offset))
    {
        FIXME("Instructions outputting multiple registers are not supported.\n");
        return NULL;
    }
    return ptr;
}