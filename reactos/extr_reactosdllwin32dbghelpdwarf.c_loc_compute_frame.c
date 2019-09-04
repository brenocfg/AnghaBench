#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct location {int kind; scalar_t__ offset; } ;
struct symt_hierarchy_point {struct location loc; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct symt_function {TYPE_1__ hash_elt; int /*<<< orphan*/  vchildren; } ;
struct symt {scalar_t__ tag; } ;
struct process {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_3__* dwarf2_info; } ;
struct module_format {TYPE_4__ u; } ;
typedef  enum location_error { ____Placeholder_location_error } location_error ;
typedef  int /*<<< orphan*/  dwarf2_traverse_context_t ;
struct TYPE_6__ {scalar_t__ address; } ;
struct TYPE_7__ {TYPE_2__ debug_loc; } ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 scalar_t__ SymTagCustom ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int compute_location (int /*<<< orphan*/ *,struct location*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwarf2_lookup_loclist (struct module_format const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
#define  loc_dwarf2_location_list 130 
 int loc_err_internal ; 
 int loc_err_out_of_scope ; 
 int loc_err_too_complex ; 
#define  loc_register 129 
#define  loc_regrel 128 
 int loc_user ; 
 struct symt** vector_at (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int vector_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum location_error loc_compute_frame(struct process* pcs,
                                             const struct module_format* modfmt,
                                             const struct symt_function* func,
                                             DWORD_PTR ip, struct location* frame)
{
    struct symt**               psym = NULL;
    struct location*            pframe;
    dwarf2_traverse_context_t   lctx;
    enum location_error         err;
    unsigned int                i;

    for (i=0; i<vector_length(&func->vchildren); i++)
    {
        psym = vector_at(&func->vchildren, i);
        if ((*psym)->tag == SymTagCustom)
        {
            pframe = &((struct symt_hierarchy_point*)*psym)->loc;

            /* First, recompute the frame information, if needed */
            switch (pframe->kind)
            {
            case loc_regrel:
            case loc_register:
                *frame = *pframe;
                break;
            case loc_dwarf2_location_list:
                WARN("Searching loclist for %s\n", func->hash_elt.name);
                if (!dwarf2_lookup_loclist(modfmt,
                                           modfmt->u.dwarf2_info->debug_loc.address + pframe->offset,
                                           ip, &lctx))
                    return loc_err_out_of_scope;
                if ((err = compute_location(&lctx, frame, pcs->handle, NULL)) < 0) return err;
                if (frame->kind >= loc_user)
                {
                    WARN("Couldn't compute runtime frame location\n");
                    return loc_err_too_complex;
                }
                break;
            default:
                WARN("Unsupported frame kind %d\n", pframe->kind);
                return loc_err_internal;
            }
            return 0;
        }
    }
    WARN("Couldn't find Custom function point, whilst location list offset is searched\n");
    return loc_err_internal;
}