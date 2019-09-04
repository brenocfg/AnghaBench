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
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  WINED3DSIH_ADD 138 
#define  WINED3DSIH_AND 137 
#define  WINED3DSIH_DIV 136 
#define  WINED3DSIH_IADD 135 
#define  WINED3DSIH_ISHL 134 
#define  WINED3DSIH_ISHR 133 
#define  WINED3DSIH_MUL 132 
#define  WINED3DSIH_OR 131 
#define  WINED3DSIH_SUB 130 
#define  WINED3DSIH_USHR 129 
#define  WINED3DSIH_XOR 128 
 int /*<<< orphan*/  debug_d3dshaderinstructionhandler (int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_binop(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct glsl_src_param src0_param;
    struct glsl_src_param src1_param;
    DWORD write_mask;
    const char *op;

    /* Determine the GLSL operator to use based on the opcode */
    switch (ins->handler_idx)
    {
        case WINED3DSIH_ADD:  op = "+";  break;
        case WINED3DSIH_AND:  op = "&";  break;
        case WINED3DSIH_DIV:  op = "/";  break;
        case WINED3DSIH_IADD: op = "+";  break;
        case WINED3DSIH_ISHL: op = "<<"; break;
        case WINED3DSIH_ISHR: op = ">>"; break;
        case WINED3DSIH_MUL:  op = "*";  break;
        case WINED3DSIH_OR:   op = "|";  break;
        case WINED3DSIH_SUB:  op = "-";  break;
        case WINED3DSIH_USHR: op = ">>"; break;
        case WINED3DSIH_XOR:  op = "^";  break;
        default:
            op = "<unhandled operator>";
            FIXME("Opcode %s not yet handled in GLSL.\n", debug_d3dshaderinstructionhandler(ins->handler_idx));
            break;
    }

    write_mask = shader_glsl_append_dst(buffer, ins);
    shader_glsl_add_src_param(ins, &ins->src[0], write_mask, &src0_param);
    shader_glsl_add_src_param(ins, &ins->src[1], write_mask, &src1_param);
    shader_addline(buffer, "%s %s %s);\n", src0_param.param_str, op, src1_param.param_str);
}