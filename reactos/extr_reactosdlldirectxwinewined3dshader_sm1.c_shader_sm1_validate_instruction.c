#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_shader_instruction {scalar_t__ handler_idx; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ WINED3DSIH_BREAKP ; 
 scalar_t__ WINED3DSIH_IF ; 
 int /*<<< orphan*/  debug_d3dshaderinstructionhandler (scalar_t__) ; 

__attribute__((used)) static void shader_sm1_validate_instruction(struct wined3d_shader_instruction *ins)
{
    if (ins->handler_idx == WINED3DSIH_BREAKP || ins->handler_idx == WINED3DSIH_IF)
    {
        if (ins->flags)
        {
            FIXME("Ignoring unexpected instruction flags %#x for %s.\n",
                    ins->flags, debug_d3dshaderinstructionhandler(ins->handler_idx));
            ins->flags = 0;
        }
    }
}