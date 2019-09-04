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
struct wined3d_shader_instruction {int handler_idx; int src_count; int /*<<< orphan*/ * src; TYPE_1__* ctx; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_2__ {struct wined3d_string_buffer* buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
#define  WINED3DSIH_ABS 151 
#define  WINED3DSIH_BFREV 150 
#define  WINED3DSIH_COUNTBITS 149 
#define  WINED3DSIH_DSX 148 
#define  WINED3DSIH_DSX_COARSE 147 
#define  WINED3DSIH_DSX_FINE 146 
#define  WINED3DSIH_DSY 145 
#define  WINED3DSIH_DSY_COARSE 144 
#define  WINED3DSIH_DSY_FINE 143 
#define  WINED3DSIH_FIRSTBIT_HI 142 
#define  WINED3DSIH_FIRSTBIT_LO 141 
#define  WINED3DSIH_FIRSTBIT_SHI 140 
#define  WINED3DSIH_FRC 139 
#define  WINED3DSIH_IMAX 138 
#define  WINED3DSIH_IMIN 137 
#define  WINED3DSIH_MAX 136 
#define  WINED3DSIH_MIN 135 
#define  WINED3DSIH_ROUND_NE 134 
#define  WINED3DSIH_ROUND_NI 133 
#define  WINED3DSIH_ROUND_PI 132 
#define  WINED3DSIH_ROUND_Z 131 
#define  WINED3DSIH_SQRT 130 
#define  WINED3DSIH_UMAX 129 
#define  WINED3DSIH_UMIN 128 
 int /*<<< orphan*/  debug_d3dshaderinstructionhandler (int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_map2gl(const struct wined3d_shader_instruction *ins)
{
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct glsl_src_param src_param;
    const char *instruction;
    DWORD write_mask;
    unsigned i;

    /* Determine the GLSL function to use based on the opcode */
    /* TODO: Possibly make this a table for faster lookups */
    switch (ins->handler_idx)
    {
        case WINED3DSIH_ABS: instruction = "abs"; break;
        case WINED3DSIH_BFREV: instruction = "bitfieldReverse"; break;
        case WINED3DSIH_COUNTBITS: instruction = "bitCount"; break;
        case WINED3DSIH_DSX: instruction = "dFdx"; break;
        case WINED3DSIH_DSX_COARSE: instruction = "dFdxCoarse"; break;
        case WINED3DSIH_DSX_FINE: instruction = "dFdxFine"; break;
        case WINED3DSIH_DSY: instruction = "ycorrection.y * dFdy"; break;
        case WINED3DSIH_DSY_COARSE: instruction = "ycorrection.y * dFdyCoarse"; break;
        case WINED3DSIH_DSY_FINE: instruction = "ycorrection.y * dFdyFine"; break;
        case WINED3DSIH_FIRSTBIT_HI: instruction = "findMSB"; break;
        case WINED3DSIH_FIRSTBIT_LO: instruction = "findLSB"; break;
        case WINED3DSIH_FIRSTBIT_SHI: instruction = "findMSB"; break;
        case WINED3DSIH_FRC: instruction = "fract"; break;
        case WINED3DSIH_IMAX: instruction = "max"; break;
        case WINED3DSIH_IMIN: instruction = "min"; break;
        case WINED3DSIH_MAX: instruction = "max"; break;
        case WINED3DSIH_MIN: instruction = "min"; break;
        case WINED3DSIH_ROUND_NE: instruction = "roundEven"; break;
        case WINED3DSIH_ROUND_NI: instruction = "floor"; break;
        case WINED3DSIH_ROUND_PI: instruction = "ceil"; break;
        case WINED3DSIH_ROUND_Z: instruction = "trunc"; break;
        case WINED3DSIH_SQRT: instruction = "sqrt"; break;
        case WINED3DSIH_UMAX: instruction = "max"; break;
        case WINED3DSIH_UMIN: instruction = "min"; break;
        default: instruction = "";
            ERR("Opcode %s not yet handled in GLSL.\n", debug_d3dshaderinstructionhandler(ins->handler_idx));
            break;
    }

    write_mask = shader_glsl_append_dst(buffer, ins);

    /* In D3D bits are numbered from the most significant bit. */
    if (ins->handler_idx == WINED3DSIH_FIRSTBIT_HI || ins->handler_idx == WINED3DSIH_FIRSTBIT_SHI)
        shader_addline(buffer, "31 - ");
    shader_addline(buffer, "%s(", instruction);

    if (ins->src_count)
    {
        shader_glsl_add_src_param(ins, &ins->src[0], write_mask, &src_param);
        shader_addline(buffer, "%s", src_param.param_str);
        for (i = 1; i < ins->src_count; ++i)
        {
            shader_glsl_add_src_param(ins, &ins->src[i], write_mask, &src_param);
            shader_addline(buffer, ", %s", src_param.param_str);
        }
    }

    shader_addline(buffer, "));\n");
}