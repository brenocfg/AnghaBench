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
struct TYPE_8__ {TYPE_2__* module; } ;
typedef  TYPE_3__ dwarf2_parse_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  ModuleName; } ;
struct TYPE_7__ {TYPE_1__ module; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 char const* wine_dbg_sprintf (char*,TYPE_3__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char* dwarf2_debug_ctx(const dwarf2_parse_context_t* ctx)
{
    return wine_dbg_sprintf("ctx(%p,%s)",
                            ctx, debugstr_w(ctx->module->module.ModuleName));
}