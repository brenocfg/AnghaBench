#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_instruction {TYPE_9__* src; TYPE_8__* dst; TYPE_3__* ctx; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
typedef  enum wined3d_shader_src_modifier { ____Placeholder_wined3d_shader_src_modifier } wined3d_shader_src_modifier ;
struct TYPE_17__ {TYPE_6__* idx; } ;
struct TYPE_19__ {int modifiers; TYPE_7__ reg; } ;
struct TYPE_15__ {TYPE_4__* idx; } ;
struct TYPE_18__ {TYPE_5__ reg; } ;
struct TYPE_16__ {int /*<<< orphan*/  offset; } ;
struct TYPE_14__ {int /*<<< orphan*/  offset; } ;
struct TYPE_13__ {TYPE_2__* reg_maps; struct wined3d_string_buffer* buffer; } ;
struct TYPE_11__ {int major; int minor; } ;
struct TYPE_12__ {TYPE_1__ shader_version; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int WINED3DSPSM_DW ; 
 int WINED3DSPSM_DZ ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_2 ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_3 ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,TYPE_9__*,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (struct wined3d_string_buffer*,struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_glsl_get_swizzle (TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_get_write_mask (TYPE_8__*,char*) ; 
 unsigned int shader_glsl_get_write_mask_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_texcoord(const struct wined3d_shader_instruction *ins)
{
    /* FIXME: Make this work for more than just 2D textures */
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    DWORD write_mask = shader_glsl_append_dst(ins->ctx->buffer, ins);

    if (!(ins->ctx->reg_maps->shader_version.major == 1 && ins->ctx->reg_maps->shader_version.minor == 4))
    {
        char dst_mask[6];

        shader_glsl_get_write_mask(&ins->dst[0], dst_mask);
        shader_addline(buffer, "clamp(ffp_texcoord[%u], 0.0, 1.0)%s);\n",
                ins->dst[0].reg.idx[0].offset, dst_mask);
    }
    else
    {
        enum wined3d_shader_src_modifier src_mod = ins->src[0].modifiers;
        DWORD reg = ins->src[0].reg.idx[0].offset;
        char dst_swizzle[6];

        shader_glsl_get_swizzle(&ins->src[0], FALSE, write_mask, dst_swizzle);

        if (src_mod == WINED3DSPSM_DZ || src_mod == WINED3DSPSM_DW)
        {
            unsigned int mask_size = shader_glsl_get_write_mask_size(write_mask);
            struct glsl_src_param div_param;
            DWORD src_writemask = src_mod == WINED3DSPSM_DZ ? WINED3DSP_WRITEMASK_2 : WINED3DSP_WRITEMASK_3;

            shader_glsl_add_src_param(ins, &ins->src[0], src_writemask, &div_param);

            if (mask_size > 1)
                shader_addline(buffer, "ffp_texcoord[%u]%s / vec%d(%s));\n", reg, dst_swizzle, mask_size, div_param.param_str);
            else
                shader_addline(buffer, "ffp_texcoord[%u]%s / %s);\n", reg, dst_swizzle, div_param.param_str);
        }
        else
        {
            shader_addline(buffer, "ffp_texcoord[%u]%s);\n", reg, dst_swizzle);
        }
    }
}