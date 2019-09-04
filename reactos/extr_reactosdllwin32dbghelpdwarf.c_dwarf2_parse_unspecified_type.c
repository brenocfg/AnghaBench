#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct symt {int dummy; } ;
struct symt_basic {struct symt symt; } ;
struct TYPE_12__ {char* string; int uvalue; } ;
struct attribute {TYPE_1__ u; } ;
struct TYPE_13__ {struct symt** symt_cache; int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ dwarf2_parse_context_t ;
struct TYPE_14__ {struct symt* symt; } ;
typedef  TYPE_3__ dwarf2_debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_name ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btVoid ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_2__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_3__*) ; 
 int /*<<< orphan*/  dwarf2_find_attribute (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,struct attribute*) ; 
 scalar_t__ dwarf2_get_di_children (TYPE_2__*,TYPE_3__*) ; 
 size_t sc_void ; 
 struct symt_basic* symt_new_basic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct symt* dwarf2_parse_unspecified_type(dwarf2_parse_context_t* ctx,
                                           dwarf2_debug_info_t* di)
{
    struct attribute name;
    struct attribute size;
    struct symt_basic *basic;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));

    if (di->symt) return di->symt;

    if (!dwarf2_find_attribute(ctx, di, DW_AT_name, &name))
        name.u.string = "void";
    size.u.uvalue = sizeof(void *);

    basic = symt_new_basic(ctx->module, btVoid, name.u.string, size.u.uvalue);
    di->symt = &basic->symt;

    if (!ctx->symt_cache[sc_void])
        ctx->symt_cache[sc_void] = di->symt;

    if (dwarf2_get_di_children(ctx, di)) FIXME("Unsupported children\n");
    return di->symt;
}