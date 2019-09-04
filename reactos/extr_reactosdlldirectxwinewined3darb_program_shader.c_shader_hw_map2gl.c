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
struct wined3d_shader_instruction {int handler_idx; unsigned int src_count; int /*<<< orphan*/ * src; struct wined3d_shader_dst_param* dst; TYPE_1__* ctx; } ;
struct wined3d_shader_dst_param {int dummy; } ;
struct TYPE_2__ {struct wined3d_string_buffer* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
#define  WINED3DSIH_ABS 146 
#define  WINED3DSIH_ADD 145 
#define  WINED3DSIH_CRS 144 
#define  WINED3DSIH_DP3 143 
#define  WINED3DSIH_DP4 142 
#define  WINED3DSIH_DST 141 
#define  WINED3DSIH_DSX 140 
#define  WINED3DSIH_FRC 139 
#define  WINED3DSIH_LIT 138 
#define  WINED3DSIH_LRP 137 
#define  WINED3DSIH_MAD 136 
#define  WINED3DSIH_MAX 135 
#define  WINED3DSIH_MIN 134 
#define  WINED3DSIH_MOV 133 
#define  WINED3DSIH_MOVA 132 
#define  WINED3DSIH_MUL 131 
#define  WINED3DSIH_SGE 130 
#define  WINED3DSIH_SLT 129 
#define  WINED3DSIH_SUB 128 
 int /*<<< orphan*/  debug_d3dshaderinstructionhandler (int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_modifier (struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,unsigned int,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 

__attribute__((used)) static void shader_hw_map2gl(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    const char *instruction;
    char arguments[256], dst_str[50];
    unsigned int i;
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];

    switch (ins->handler_idx)
    {
        case WINED3DSIH_ABS: instruction = "ABS"; break;
        case WINED3DSIH_ADD: instruction = "ADD"; break;
        case WINED3DSIH_CRS: instruction = "XPD"; break;
        case WINED3DSIH_DP3: instruction = "DP3"; break;
        case WINED3DSIH_DP4: instruction = "DP4"; break;
        case WINED3DSIH_DST: instruction = "DST"; break;
        case WINED3DSIH_FRC: instruction = "FRC"; break;
        case WINED3DSIH_LIT: instruction = "LIT"; break;
        case WINED3DSIH_LRP: instruction = "LRP"; break;
        case WINED3DSIH_MAD: instruction = "MAD"; break;
        case WINED3DSIH_MAX: instruction = "MAX"; break;
        case WINED3DSIH_MIN: instruction = "MIN"; break;
        case WINED3DSIH_MOV: instruction = "MOV"; break;
        case WINED3DSIH_MUL: instruction = "MUL"; break;
        case WINED3DSIH_SGE: instruction = "SGE"; break;
        case WINED3DSIH_SLT: instruction = "SLT"; break;
        case WINED3DSIH_SUB: instruction = "SUB"; break;
        case WINED3DSIH_MOVA:instruction = "ARR"; break;
        case WINED3DSIH_DSX: instruction = "DDX"; break;
        default: instruction = "";
            FIXME("Unhandled opcode %s.\n", debug_d3dshaderinstructionhandler(ins->handler_idx));
            break;
    }

    /* Note that shader_arb_add_dst_param() adds spaces. */
    arguments[0] = '\0';
    shader_arb_get_dst_param(ins, dst, dst_str);
    for (i = 0; i < ins->src_count; ++i)
    {
        char operand[100];
        strcat(arguments, ", ");
        shader_arb_get_src_param(ins, &ins->src[i], i, operand);
        strcat(arguments, operand);
    }
    shader_addline(buffer, "%s%s %s%s;\n", instruction, shader_arb_get_modifier(ins), dst_str, arguments);
}