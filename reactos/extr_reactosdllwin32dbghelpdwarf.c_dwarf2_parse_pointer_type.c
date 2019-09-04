#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct symt {int dummy; } ;
struct TYPE_15__ {int uvalue; } ;
struct attribute {TYPE_1__ u; } ;
struct TYPE_16__ {int /*<<< orphan*/  module; struct symt** symt_cache; } ;
typedef  TYPE_2__ dwarf2_parse_context_t ;
struct TYPE_17__ {struct symt* symt; } ;
typedef  TYPE_3__ dwarf2_debug_info_t ;
struct TYPE_18__ {struct symt symt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_byte_size ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct symt*) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,struct attribute*) ; 
 scalar_t__ dwarf2_get_di_children (TYPE_2__*,TYPE_3__*) ; 
 struct symt* dwarf2_lookup_type (TYPE_2__*,TYPE_3__*) ; 
 size_t sc_void ; 
 TYPE_4__* symt_new_pointer (int /*<<< orphan*/ ,struct symt*,int) ; 

__attribute__((used)) static struct symt* dwarf2_parse_pointer_type(dwarf2_parse_context_t* ctx,
                                              dwarf2_debug_info_t* di)
{
    struct symt*        ref_type;
    struct attribute    size;

    if (di->symt) return di->symt;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di)); 

    if (!dwarf2_find_attribute(ctx, di, DW_AT_byte_size, &size)) size.u.uvalue = sizeof(void *);
    if (!(ref_type = dwarf2_lookup_type(ctx, di)))
    {
        ref_type = ctx->symt_cache[sc_void];
        assert(ref_type);
    }
    di->symt = &symt_new_pointer(ctx->module, ref_type, size.u.uvalue)->symt;
    if (dwarf2_get_di_children(ctx, di)) FIXME("Unsupported children\n");
    return di->symt;
}