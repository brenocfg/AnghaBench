#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* idx; } ;
struct wined3d_shader_src_param {scalar_t__ modifiers; TYPE_6__ reg; } ;
struct wined3d_shader_instruction {int flags; TYPE_9__* ctx; struct wined3d_shader_src_param* src; struct wined3d_shader_dst_param* dst; } ;
struct TYPE_13__ {TYPE_3__* idx; } ;
struct wined3d_shader_dst_param {TYPE_4__ reg; } ;
struct shader_arb_ctx_priv {TYPE_8__* cur_ps_args; } ;
typedef  enum wined3d_shader_src_modifier { ____Placeholder_wined3d_shader_src_modifier } wined3d_shader_src_modifier ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_18__ {int /*<<< orphan*/  buffer; TYPE_2__* reg_maps; struct shader_arb_ctx_priv* backend_data; } ;
struct TYPE_16__ {int tex_transform; } ;
struct TYPE_17__ {TYPE_7__ super; } ;
struct TYPE_14__ {int offset; } ;
struct TYPE_12__ {int offset; } ;
struct TYPE_10__ {int major; int minor; } ;
struct TYPE_11__ {TYPE_1__ shader_version; } ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int MAX_TEXTURES ; 
 int /*<<< orphan*/  TEX_BIAS ; 
 int /*<<< orphan*/  TEX_PROJ ; 
 scalar_t__ TRUE ; 
 int WINED3DSI_TEXLD_BIAS ; 
 int WINED3DSI_TEXLD_PROJECT ; 
 scalar_t__ WINED3DSPSM_DW ; 
 scalar_t__ WINED3DSPSM_DZ ; 
 void* WINED3DSPSM_NONE ; 
 int WINED3D_PSARGS_PROJECTED ; 
 int WINED3D_PSARGS_TEXTRANSFORM_SHIFT ; 
 int WINED3D_SHADER_VERSION (int,int) ; 
 int WINED3D_TTFF_COUNT3 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,struct wined3d_shader_src_param*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_hw_sample (struct wined3d_shader_instruction const*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void pshader_hw_tex(const struct wined3d_shader_instruction *ins)
{
    struct shader_arb_ctx_priv *priv = ins->ctx->backend_data;
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    DWORD shader_version = WINED3D_SHADER_VERSION(ins->ctx->reg_maps->shader_version.major,
            ins->ctx->reg_maps->shader_version.minor);
    struct wined3d_shader_src_param src;

    char reg_dest[40];
    char reg_coord[40];
    DWORD reg_sampler_code;
    WORD myflags = 0;
    BOOL swizzle_coord = FALSE;

    /* All versions have a destination register */
    shader_arb_get_dst_param(ins, dst, reg_dest);

    /* 1.0-1.4: Use destination register number as texture code.
       2.0+: Use provided sampler number as texture code. */
    if (shader_version < WINED3D_SHADER_VERSION(2,0))
        reg_sampler_code = dst->reg.idx[0].offset;
    else
        reg_sampler_code = ins->src[1].reg.idx[0].offset;

    /* 1.0-1.3: Use the texcoord varying.
       1.4+: Use provided coordinate source register. */
    if (shader_version < WINED3D_SHADER_VERSION(1,4))
        sprintf(reg_coord, "fragment.texcoord[%u]", reg_sampler_code);
    else {
        /* TEX is the only instruction that can handle DW and DZ natively */
        src = ins->src[0];
        if(src.modifiers == WINED3DSPSM_DW) src.modifiers = WINED3DSPSM_NONE;
        if(src.modifiers == WINED3DSPSM_DZ) src.modifiers = WINED3DSPSM_NONE;
        shader_arb_get_src_param(ins, &src, 0, reg_coord);
    }

    /* projection flag:
     * 1.1, 1.2, 1.3: Use WINED3D_TSS_TEXTURETRANSFORMFLAGS
     * 1.4: Use WINED3DSPSM_DZ or WINED3DSPSM_DW on src[0]
     * 2.0+: Use WINED3DSI_TEXLD_PROJECT on the opcode
     */
    if (shader_version < WINED3D_SHADER_VERSION(1,4))
    {
        DWORD flags = 0;
        if (reg_sampler_code < MAX_TEXTURES)
            flags = priv->cur_ps_args->super.tex_transform >> reg_sampler_code * WINED3D_PSARGS_TEXTRANSFORM_SHIFT;
        if (flags & WINED3D_PSARGS_PROJECTED)
        {
            myflags |= TEX_PROJ;
            if ((flags & ~WINED3D_PSARGS_PROJECTED) == WINED3D_TTFF_COUNT3)
                swizzle_coord = TRUE;
        }
    }
    else if (shader_version < WINED3D_SHADER_VERSION(2,0))
    {
        enum wined3d_shader_src_modifier src_mod = ins->src[0].modifiers;
        if (src_mod == WINED3DSPSM_DZ)
        {
            swizzle_coord = TRUE;
            myflags |= TEX_PROJ;
        } else if(src_mod == WINED3DSPSM_DW) {
            myflags |= TEX_PROJ;
        }
    } else {
        if (ins->flags & WINED3DSI_TEXLD_PROJECT) myflags |= TEX_PROJ;
        if (ins->flags & WINED3DSI_TEXLD_BIAS) myflags |= TEX_BIAS;
    }

    if (swizzle_coord)
    {
        /* TXP cannot handle DZ natively, so move the z coordinate to .w.
         * reg_coord is a read-only varying register, so we need a temp reg */
        shader_addline(ins->ctx->buffer, "SWZ TA, %s, x, y, z, z;\n", reg_coord);
        strcpy(reg_coord, "TA");
    }

    shader_hw_sample(ins, reg_sampler_code, reg_dest, reg_coord, myflags, NULL, NULL);
}