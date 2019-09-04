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
struct wined3d_shader_instruction {int handler_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  WINED3DSIH_BREAKP 130 
#define  WINED3DSIH_CONTINUEP 129 
#define  WINED3DSIH_RETP 128 
 int /*<<< orphan*/  shader_glsl_generate_conditional_op (struct wined3d_shader_instruction const*,char const*) ; 

__attribute__((used)) static void shader_glsl_conditional_op(const struct wined3d_shader_instruction *ins)
{
    const char *op;

    switch (ins->handler_idx)
    {
        case WINED3DSIH_BREAKP: op = "break;"; break;
        case WINED3DSIH_CONTINUEP: op = "continue;"; break;
        case WINED3DSIH_RETP: op = "return;"; break;
        default:
            ERR("Unhandled opcode %#x.\n", ins->handler_idx);
            return;
    }

    shader_glsl_generate_conditional_op(ins, op);
}