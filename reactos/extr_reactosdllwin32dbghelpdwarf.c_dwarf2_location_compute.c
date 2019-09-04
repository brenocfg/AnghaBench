#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int name; } ;
struct symt_function {TYPE_3__* container; TYPE_1__ hash_elt; } ;
struct symt_compiland {scalar_t__ address; } ;
struct TYPE_11__ {scalar_t__ InstructionOffset; } ;
struct process {int /*<<< orphan*/  handle; TYPE_2__ ctx_frame; } ;
struct TYPE_15__ {TYPE_5__* dwarf2_info; } ;
struct module_format {TYPE_6__ u; } ;
struct location {int kind; int reg; scalar_t__ offset; } ;
struct TYPE_16__ {int /*<<< orphan*/  word_size; int /*<<< orphan*/  const* data; int /*<<< orphan*/  end_data; } ;
typedef  TYPE_7__ dwarf2_traverse_context_t ;
struct TYPE_13__ {scalar_t__ address; } ;
struct TYPE_14__ {int /*<<< orphan*/  word_size; TYPE_4__ debug_loc; } ;
struct TYPE_12__ {scalar_t__ tag; } ;
typedef  scalar_t__ DWORD_PTR ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ SymTagCompiland ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int compute_location (TYPE_7__*,struct location*,int /*<<< orphan*/ ,struct location*) ; 
 int /*<<< orphan*/  dwarf2_lookup_loclist (struct module_format const*,scalar_t__,scalar_t__,TYPE_7__*) ; 
 int loc_compute_frame (struct process*,struct module_format const*,struct symt_function const*,scalar_t__,struct location*) ; 
#define  loc_dwarf2_block 131 
#define  loc_dwarf2_location_list 130 
 int loc_err_internal ; 
 int loc_err_out_of_scope ; 
#define  loc_register 129 
#define  loc_regrel 128 

__attribute__((used)) static void dwarf2_location_compute(struct process* pcs,
                                    const struct module_format* modfmt,
                                    const struct symt_function* func,
                                    struct location* loc)
{
    struct location             frame;
    DWORD_PTR                   ip;
    int                         err;
    dwarf2_traverse_context_t   lctx;

    if (!func->container || func->container->tag != SymTagCompiland)
    {
        WARN("We'd expect function %s's container to exist and be a compiland\n", func->hash_elt.name);
        err = loc_err_internal;
    }
    else
    {
        /* instruction pointer relative to compiland's start */
        ip = pcs->ctx_frame.InstructionOffset - ((struct symt_compiland*)func->container)->address;

        if ((err = loc_compute_frame(pcs, modfmt, func, ip, &frame)) == 0)
        {
            switch (loc->kind)
            {
            case loc_dwarf2_location_list:
                /* Then, if the variable has a location list, find it !! */
                if (dwarf2_lookup_loclist(modfmt,
                                          modfmt->u.dwarf2_info->debug_loc.address + loc->offset,
                                          ip, &lctx))
                    goto do_compute;
                err = loc_err_out_of_scope;
                break;
            case loc_dwarf2_block:
                /* or if we have a copy of an existing block, get ready for it */
                {
                    unsigned*   ptr = (unsigned*)loc->offset;

                    lctx.data = (const BYTE*)(ptr + 1);
                    lctx.end_data = lctx.data + *ptr;
                    lctx.word_size = modfmt->u.dwarf2_info->word_size;
                }
            do_compute:
                /* now get the variable */
                err = compute_location(&lctx, loc, pcs->handle, &frame);
                break;
            case loc_register:
            case loc_regrel:
                /* nothing to do */
                break;
            default:
                WARN("Unsupported local kind %d\n", loc->kind);
                err = loc_err_internal;
            }
        }
    }
    if (err < 0)
    {
        loc->kind = loc_register;
        loc->reg = err;
    }
}