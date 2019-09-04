#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_instruction {scalar_t__ handler_idx; TYPE_4__* ctx; TYPE_6__* dst; int /*<<< orphan*/ * src; } ;
struct shader_glsl_ctx_priv {TYPE_3__* cur_ps_args; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct glsl_sample_function {int coord_mask; } ;
struct glsl_dst_param {int /*<<< orphan*/  mask_str; int /*<<< orphan*/  reg_name; } ;
struct TYPE_8__ {TYPE_1__* idx; } ;
struct TYPE_11__ {TYPE_2__ reg; } ;
struct TYPE_10__ {int /*<<< orphan*/  buffer; struct shader_glsl_ctx_priv* backend_data; } ;
struct TYPE_9__ {int tex_transform; } ;
struct TYPE_7__ {int offset; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ WINED3DSIH_TEXBEML ; 
 int /*<<< orphan*/  WINED3DSP_NOSWIZZLE ; 
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int WINED3DSP_WRITEMASK_2 ; 
 int WINED3DSP_WRITEMASK_3 ; 
 int WINED3D_PSARGS_PROJECTED ; 
 int WINED3D_PSARGS_TEXTRANSFORM_MASK ; 
 int WINED3D_PSARGS_TEXTRANSFORM_SHIFT ; 
#define  WINED3D_TTFF_COUNT1 132 
#define  WINED3D_TTFF_COUNT2 131 
#define  WINED3D_TTFF_COUNT3 130 
#define  WINED3D_TTFF_COUNT4 129 
#define  WINED3D_TTFF_DISABLE 128 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int,char*,int,...) ; 
 int /*<<< orphan*/  shader_glsl_add_dst_param (struct wined3d_shader_instruction const*,TYPE_6__*,struct glsl_dst_param*) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_gen_sample_code (struct wined3d_shader_instruction const*,int,struct glsl_sample_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_get_sample_function (TYPE_4__*,int,int,int /*<<< orphan*/ ,struct glsl_sample_function*) ; 
 int /*<<< orphan*/  shader_glsl_release_sample_function (TYPE_4__*,struct glsl_sample_function*) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (int,char*) ; 

__attribute__((used)) static void shader_glsl_texbem(const struct wined3d_shader_instruction *ins)
{
    const struct shader_glsl_ctx_priv *priv = ins->ctx->backend_data;
    struct glsl_sample_function sample_function;
    struct glsl_src_param coord_param;
    DWORD sampler_idx;
    DWORD mask;
    DWORD flags;
    char coord_mask[6];

    sampler_idx = ins->dst[0].reg.idx[0].offset;
    flags = (priv->cur_ps_args->tex_transform >> sampler_idx * WINED3D_PSARGS_TEXTRANSFORM_SHIFT)
            & WINED3D_PSARGS_TEXTRANSFORM_MASK;

    /* Dependent read, not valid with conditional NP2 */
    shader_glsl_get_sample_function(ins->ctx, sampler_idx, sampler_idx, 0, &sample_function);
    mask = sample_function.coord_mask;

    shader_glsl_write_mask_to_str(mask, coord_mask);

    /* With projected textures, texbem only divides the static texture coord,
     * not the displacement, so we can't let GL handle this. */
    if (flags & WINED3D_PSARGS_PROJECTED)
    {
        DWORD div_mask=0;
        char coord_div_mask[3];
        switch (flags & ~WINED3D_PSARGS_PROJECTED)
        {
            case WINED3D_TTFF_COUNT1:
                FIXME("WINED3D_TTFF_PROJECTED with WINED3D_TTFF_COUNT1?\n");
                break;
            case WINED3D_TTFF_COUNT2:
                div_mask = WINED3DSP_WRITEMASK_1;
                break;
            case WINED3D_TTFF_COUNT3:
                div_mask = WINED3DSP_WRITEMASK_2;
                break;
            case WINED3D_TTFF_COUNT4:
            case WINED3D_TTFF_DISABLE:
                div_mask = WINED3DSP_WRITEMASK_3;
                break;
        }
        shader_glsl_write_mask_to_str(div_mask, coord_div_mask);
        shader_addline(ins->ctx->buffer, "T%u%s /= T%u%s;\n", sampler_idx, coord_mask, sampler_idx, coord_div_mask);
    }

    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_0 | WINED3DSP_WRITEMASK_1, &coord_param);

    shader_glsl_gen_sample_code(ins, sampler_idx, &sample_function, WINED3DSP_NOSWIZZLE, NULL, NULL, NULL, NULL,
            "T%u%s + vec4(bumpenv_mat%u * %s, 0.0, 0.0)%s", sampler_idx, coord_mask, sampler_idx,
            coord_param.param_str, coord_mask);

    if (ins->handler_idx == WINED3DSIH_TEXBEML)
    {
        struct glsl_src_param luminance_param;
        struct glsl_dst_param dst_param;

        shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_2, &luminance_param);
        shader_glsl_add_dst_param(ins, &ins->dst[0], &dst_param);

        shader_addline(ins->ctx->buffer, "%s%s *= (%s * bumpenv_lum_scale%u + bumpenv_lum_offset%u);\n",
                dst_param.reg_name, dst_param.mask_str,
                luminance_param.param_str, sampler_idx, sampler_idx);
    }
    shader_glsl_release_sample_function(ins->ctx, &sample_function);
}