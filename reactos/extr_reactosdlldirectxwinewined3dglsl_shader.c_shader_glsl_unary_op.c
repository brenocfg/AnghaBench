#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_instruction {int handler_idx; TYPE_1__* ctx; int /*<<< orphan*/ * src; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
#define  WINED3DSIH_INEG 129 
#define  WINED3DSIH_NOT 128 
 int /*<<< orphan*/  debug_d3dshaderinstructionhandler (int) ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_unary_op(const struct wined3d_shader_instruction *ins)
{
    struct glsl_src_param src_param;
    DWORD write_mask;
    const char *op;

    switch (ins->handler_idx)
    {
        case WINED3DSIH_INEG: op = "-"; break;
        case WINED3DSIH_NOT:  op = "~"; break;
        default:
            op = "<unhandled operator>";
            ERR("Unhandled opcode %s.\n",
                    debug_d3dshaderinstructionhandler(ins->handler_idx));
            break;
    }

    write_mask = shader_glsl_append_dst(ins->ctx->buffer, ins);
    shader_glsl_add_src_param(ins, &ins->src[0], write_mask, &src_param);
    shader_addline(ins->ctx->buffer, "%s%s);\n", op, src_param.param_str);
}