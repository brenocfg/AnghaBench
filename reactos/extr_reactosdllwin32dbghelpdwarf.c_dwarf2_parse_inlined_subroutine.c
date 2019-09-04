#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct vector {int dummy; } ;
struct symt_block {int dummy; } ;
struct TYPE_21__ {TYPE_4__* func; TYPE_6__* ctx; } ;
typedef  TYPE_2__ dwarf2_subprogram_t ;
struct TYPE_22__ {TYPE_1__* abbrev; } ;
typedef  TYPE_3__ dwarf2_debug_info_t ;
struct TYPE_24__ {int /*<<< orphan*/  module; scalar_t__ load_offset; } ;
struct TYPE_23__ {scalar_t__ address; } ;
struct TYPE_20__ {int tag; } ;

/* Variables and functions */
#define  DW_TAG_GNU_call_site 133 
#define  DW_TAG_formal_parameter 132 
#define  DW_TAG_inlined_subroutine 131 
#define  DW_TAG_label 130 
#define  DW_TAG_lexical_block 129 
#define  DW_TAG_variable 128 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_6__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_3__*) ; 
 struct vector* dwarf2_get_di_children (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_parse_subprogram_block (TYPE_2__*,struct symt_block*,TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_parse_subprogram_label (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_parse_variable (TYPE_2__*,struct symt_block*,TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_read_range (TYPE_6__*,TYPE_3__*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  symt_close_func_block (int /*<<< orphan*/ ,TYPE_4__*,struct symt_block*,int /*<<< orphan*/ ) ; 
 struct symt_block* symt_open_func_block (int /*<<< orphan*/ ,TYPE_4__*,struct symt_block*,scalar_t__,unsigned long) ; 
 scalar_t__ vector_at (struct vector*,unsigned int) ; 
 unsigned int vector_length (struct vector*) ; 

__attribute__((used)) static void dwarf2_parse_inlined_subroutine(dwarf2_subprogram_t* subpgm,
                                            struct symt_block* parent_block,
                                            dwarf2_debug_info_t* di)
{
    struct symt_block*  block;
    unsigned long       low_pc, high_pc;
    struct vector*      children;
    dwarf2_debug_info_t*child;
    unsigned int        i;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(subpgm->ctx), dwarf2_debug_di(di));

    if (!dwarf2_read_range(subpgm->ctx, di, &low_pc, &high_pc))
    {
        FIXME("cannot read range\n");
        return;
    }

    block = symt_open_func_block(subpgm->ctx->module, subpgm->func, parent_block,
                                 subpgm->ctx->load_offset + low_pc - subpgm->func->address,
                                 high_pc - low_pc);

    children = dwarf2_get_di_children(subpgm->ctx, di);
    if (children) for (i = 0; i < vector_length(children); i++)
    {
        child = *(dwarf2_debug_info_t**)vector_at(children, i);

        switch (child->abbrev->tag)
        {
        case DW_TAG_formal_parameter:
        case DW_TAG_variable:
            dwarf2_parse_variable(subpgm, block, child);
            break;
        case DW_TAG_lexical_block:
            dwarf2_parse_subprogram_block(subpgm, block, child);
            break;
        case DW_TAG_inlined_subroutine:
            dwarf2_parse_inlined_subroutine(subpgm, block, child);
            break;
        case DW_TAG_label:
            dwarf2_parse_subprogram_label(subpgm, child);
            break;
        case DW_TAG_GNU_call_site:
            /* this isn't properly supported by dbghelp interface. skip it for now */
            break;
        default:
            FIXME("Unhandled Tag type 0x%lx at %s, for %s\n",
                  child->abbrev->tag, dwarf2_debug_ctx(subpgm->ctx),
                  dwarf2_debug_di(di));
        }
    }
    symt_close_func_block(subpgm->ctx->module, subpgm->func, block, 0);
}