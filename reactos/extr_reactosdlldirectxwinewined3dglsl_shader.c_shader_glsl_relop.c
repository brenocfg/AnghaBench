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
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {int handler_idx; int /*<<< orphan*/ * src; TYPE_1__* ctx; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_2__ {struct wined3d_string_buffer* buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
#define  WINED3DSIH_EQ 137 
#define  WINED3DSIH_GE 136 
#define  WINED3DSIH_IEQ 135 
#define  WINED3DSIH_IGE 134 
#define  WINED3DSIH_ILT 133 
#define  WINED3DSIH_INE 132 
#define  WINED3DSIH_LT 131 
#define  WINED3DSIH_NE 130 
#define  WINED3DSIH_UGE 129 
#define  WINED3DSIH_ULT 128 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,unsigned int,char const*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*) ; 
 unsigned int shader_glsl_get_write_mask_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_relop(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct glsl_src_param src0_param;
    struct glsl_src_param src1_param;
    unsigned int mask_size;
    DWORD write_mask;
    const char *op;

    write_mask = shader_glsl_append_dst(buffer, ins);
    mask_size = shader_glsl_get_write_mask_size(write_mask);
    shader_glsl_add_src_param(ins, &ins->src[0], write_mask, &src0_param);
    shader_glsl_add_src_param(ins, &ins->src[1], write_mask, &src1_param);

    if (mask_size > 1)
    {
        switch (ins->handler_idx)
        {
            case WINED3DSIH_EQ:  op = "equal"; break;
            case WINED3DSIH_IEQ: op = "equal"; break;
            case WINED3DSIH_GE:  op = "greaterThanEqual"; break;
            case WINED3DSIH_IGE: op = "greaterThanEqual"; break;
            case WINED3DSIH_UGE: op = "greaterThanEqual"; break;
            case WINED3DSIH_LT:  op = "lessThan"; break;
            case WINED3DSIH_ILT: op = "lessThan"; break;
            case WINED3DSIH_ULT: op = "lessThan"; break;
            case WINED3DSIH_NE:  op = "notEqual"; break;
            case WINED3DSIH_INE: op = "notEqual"; break;
            default:
                op = "<unhandled operator>";
                ERR("Unhandled opcode %#x.\n", ins->handler_idx);
                break;
        }

        shader_addline(buffer, "uvec%u(%s(%s, %s)) * 0xffffffffu);\n",
                mask_size, op, src0_param.param_str, src1_param.param_str);
    }
    else
    {
        switch (ins->handler_idx)
        {
            case WINED3DSIH_EQ:  op = "=="; break;
            case WINED3DSIH_IEQ: op = "=="; break;
            case WINED3DSIH_GE:  op = ">="; break;
            case WINED3DSIH_IGE: op = ">="; break;
            case WINED3DSIH_UGE: op = ">="; break;
            case WINED3DSIH_LT:  op = "<"; break;
            case WINED3DSIH_ILT: op = "<"; break;
            case WINED3DSIH_ULT: op = "<"; break;
            case WINED3DSIH_NE:  op = "!="; break;
            case WINED3DSIH_INE: op = "!="; break;
            default:
                op = "<unhandled operator>";
                ERR("Unhandled opcode %#x.\n", ins->handler_idx);
                break;
        }

        shader_addline(buffer, "%s %s %s ? 0xffffffffu : 0u);\n",
                src0_param.param_str, op, src1_param.param_str);
    }
}