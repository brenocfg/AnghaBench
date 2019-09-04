#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct vector {int dummy; } ;
struct TYPE_11__ {scalar_t__* symt_cache; } ;
typedef  TYPE_1__ dwarf2_parse_context_t ;
struct TYPE_12__ {scalar_t__ symt; } ;
typedef  TYPE_2__ dwarf2_debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_debug_ctx (TYPE_1__*) ; 
 int /*<<< orphan*/  dwarf2_debug_di (TYPE_2__*) ; 
 struct vector* dwarf2_get_di_children (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  dwarf2_load_one_entry (TYPE_1__*,TYPE_2__*) ; 
 size_t sc_void ; 
 scalar_t__ vector_at (struct vector*,unsigned int) ; 
 unsigned int vector_length (struct vector*) ; 

__attribute__((used)) static void dwarf2_parse_namespace(dwarf2_parse_context_t* ctx,
                                   dwarf2_debug_info_t* di)
{
    struct vector*          children;
    dwarf2_debug_info_t*    child;
    unsigned int            i;

    if (di->symt) return;

    TRACE("%s, for %s\n", dwarf2_debug_ctx(ctx), dwarf2_debug_di(di));

    di->symt = ctx->symt_cache[sc_void];

    children = dwarf2_get_di_children(ctx, di);
    if (children) for (i = 0; i < vector_length(children); i++)
    {
        child = *(dwarf2_debug_info_t**)vector_at(children, i);
        dwarf2_load_one_entry(ctx, child);
    }
}