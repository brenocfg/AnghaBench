#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {int /*<<< orphan*/ * src; struct wined3d_shader_dst_param* dst; TYPE_3__* ctx; } ;
struct wined3d_shader_dst_param {int modifiers; int write_mask; int /*<<< orphan*/  reg; } ;
struct shader_arb_ctx_priv {scalar_t__ target_version; } ;
struct TYPE_6__ {TYPE_2__* reg_maps; struct shader_arb_ctx_priv* backend_data; struct wined3d_string_buffer* buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ NV2 ; 
 int WINED3DSPDM_SATURATE ; 
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param*,char*) ; 
 char* shader_arb_get_modifier (struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_arb_get_register_name (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ shader_is_pshader_version (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_hw_sincos(const struct wined3d_shader_instruction *ins)
{
    /* This instruction exists in ARB, but the d3d instruction takes two extra parameters which
     * must contain fixed constants. So we need a separate function to filter those constants and
     * can't use map2gl
     */
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    struct shader_arb_ctx_priv *priv = ins->ctx->backend_data;
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    char dst_name[50];
    char src_name0[50], src_name1[50], src_name2[50];
    BOOL is_color;

    shader_arb_get_src_param(ins, &ins->src[0], 0, src_name0);
    if(shader_is_pshader_version(ins->ctx->reg_maps->shader_version.type)) {
        shader_arb_get_dst_param(ins, &ins->dst[0], dst_name);
        /* No modifiers are supported on SCS */
        shader_addline(buffer, "SCS %s, %s;\n", dst_name, src_name0);

        if(ins->dst[0].modifiers & WINED3DSPDM_SATURATE)
        {
            shader_arb_get_register_name(ins, &dst->reg, src_name0, &is_color);
            shader_addline(buffer, "MOV_SAT %s, %s;\n", dst_name, src_name0);
        }
    } else if(priv->target_version >= NV2) {
        shader_arb_get_register_name(ins, &dst->reg, dst_name, &is_color);

        /* Sincos writemask must be .x, .y or .xy */
        if(dst->write_mask & WINED3DSP_WRITEMASK_0)
            shader_addline(buffer, "COS%s %s.x, %s;\n", shader_arb_get_modifier(ins), dst_name, src_name0);
        if(dst->write_mask & WINED3DSP_WRITEMASK_1)
            shader_addline(buffer, "SIN%s %s.y, %s;\n", shader_arb_get_modifier(ins), dst_name, src_name0);
    } else {
        /* Approximate sine and cosine with a taylor series, as per math textbook. The application passes 8
         * helper constants(D3DSINCOSCONST1 and D3DSINCOSCONST2) in src1 and src2.
         *
         * sin(x) = x - x^3/3! + x^5/5! - x^7/7! + ...
         * cos(x) = 1 - x^2/2! + x^4/4! - x^6/6! + ...
         *
         * The constants we get are:
         *
         *  +1   +1,     -1     -1     +1      +1      -1       -1
         *      ---- ,  ---- , ---- , ----- , ----- , ----- , ------
         *      1!*2    2!*4   3!*8   4!*16   5!*32   6!*64   7!*128
         *
         * If used with x^2, x^3, x^4 etc they calculate sin(x/2) and cos(x/2):
         *
         * (x/2)^2 = x^2 / 4
         * (x/2)^3 = x^3 / 8
         * (x/2)^4 = x^4 / 16
         * (x/2)^5 = x^5 / 32
         * etc
         *
         * To get the final result:
         * sin(x) = 2 * sin(x/2) * cos(x/2)
         * cos(x) = cos(x/2)^2 - sin(x/2)^2
         * (from sin(x+y) and cos(x+y) rules)
         *
         * As per MSDN, dst.z is undefined after the operation, and so is
         * dst.x and dst.y if they're masked out by the writemask. Ie
         * sincos dst.y, src1, c0, c1
         * returns the sine in dst.y. dst.x and dst.z are undefined, dst.w is not touched. The assembler
         * vsa.exe also stops with an error if the dest register is the same register as the source
         * register. This means we can use dest.xyz as temporary storage. The assembler vsa.exe output also
         * indicates that sincos consumes 8 instruction slots in vs_2_0(and, strangely, in vs_3_0).
         */
        shader_arb_get_src_param(ins, &ins->src[1], 1, src_name1);
        shader_arb_get_src_param(ins, &ins->src[2], 2, src_name2);
        shader_arb_get_register_name(ins, &dst->reg, dst_name, &is_color);

        shader_addline(buffer, "MUL %s.x, %s, %s;\n", dst_name, src_name0, src_name0);  /* x ^ 2 */
        shader_addline(buffer, "MUL TA.y, %s.x, %s;\n", dst_name, src_name0);           /* x ^ 3 */
        shader_addline(buffer, "MUL %s.y, TA.y, %s;\n", dst_name, src_name0);           /* x ^ 4 */
        shader_addline(buffer, "MUL TA.z, %s.y, %s;\n", dst_name, src_name0);           /* x ^ 5 */
        shader_addline(buffer, "MUL %s.z, TA.z, %s;\n", dst_name, src_name0);           /* x ^ 6 */
        shader_addline(buffer, "MUL TA.w, %s.z, %s;\n", dst_name, src_name0);           /* x ^ 7 */

        /* sin(x/2)
         *
         * Unfortunately we don't get the constants in a DP4-capable form. Is there a way to
         * properly merge that with MULs in the code above?
         * The swizzles .yz and xw however fit into the .yzxw swizzle added to ps_2_0. Maybe
         * we can merge the sine and cosine MAD rows to calculate them together.
         */
        shader_addline(buffer, "MUL TA.x, %s, %s.w;\n", src_name0, src_name2); /* x^1, +1/(1!*2) */
        shader_addline(buffer, "MAD TA.x, TA.y, %s.x, TA.x;\n", src_name2); /* -1/(3!*8) */
        shader_addline(buffer, "MAD TA.x, TA.z, %s.w, TA.x;\n", src_name1); /* +1/(5!*32) */
        shader_addline(buffer, "MAD TA.x, TA.w, %s.x, TA.x;\n", src_name1); /* -1/(7!*128) */

        /* cos(x/2) */
        shader_addline(buffer, "MAD TA.y, %s.x, %s.y, %s.z;\n", dst_name, src_name2, src_name2); /* -1/(2!*4), +1.0 */
        shader_addline(buffer, "MAD TA.y, %s.y, %s.z, TA.y;\n", dst_name, src_name1); /* +1/(4!*16) */
        shader_addline(buffer, "MAD TA.y, %s.z, %s.y, TA.y;\n", dst_name, src_name1); /* -1/(6!*64) */

        if(dst->write_mask & WINED3DSP_WRITEMASK_0) {
            /* cos x */
            shader_addline(buffer, "MUL TA.z, TA.y, TA.y;\n");
            shader_addline(buffer, "MAD %s.x, -TA.x, TA.x, TA.z;\n", dst_name);
        }
        if(dst->write_mask & WINED3DSP_WRITEMASK_1) {
            /* sin x */
            shader_addline(buffer, "MUL %s.y, TA.x, TA.y;\n", dst_name);
            shader_addline(buffer, "ADD %s.y, %s.y, %s.y;\n", dst_name, dst_name, dst_name);
        }
    }
}