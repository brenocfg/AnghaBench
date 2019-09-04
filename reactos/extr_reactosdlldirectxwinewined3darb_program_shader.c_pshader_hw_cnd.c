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
struct wined3d_shader_src_param {int /*<<< orphan*/  modifiers; } ;
struct wined3d_shader_instruction {struct wined3d_shader_src_param* src; struct wined3d_shader_dst_param* dst; scalar_t__ coissue; TYPE_3__* ctx; } ;
struct wined3d_shader_dst_param {scalar_t__ write_mask; } ;
struct TYPE_6__ {TYPE_2__* reg_maps; struct wined3d_string_buffer* buffer; } ;
struct TYPE_4__ {int major; int minor; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ WINED3DSP_WRITEMASK_3 ; 
 int /*<<< orphan*/  WINED3D_SHADER_VERSION (int,int) ; 
 int /*<<< orphan*/  negate_modifiers (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char,char*,...) ; 
 int /*<<< orphan*/  shader_arb_get_dst_param (struct wined3d_shader_instruction const*,struct wined3d_shader_dst_param const*,char*) ; 
 int /*<<< orphan*/  shader_arb_get_modifier (struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_arb_get_src_param (struct wined3d_shader_instruction const*,struct wined3d_shader_src_param*,int,char*) ; 

__attribute__((used)) static void pshader_hw_cnd(const struct wined3d_shader_instruction *ins)
{
    const struct wined3d_shader_dst_param *dst = &ins->dst[0];
    struct wined3d_string_buffer *buffer = ins->ctx->buffer;
    char dst_name[50];
    char src_name[3][50];
    DWORD shader_version = WINED3D_SHADER_VERSION(ins->ctx->reg_maps->shader_version.major,
            ins->ctx->reg_maps->shader_version.minor);

    shader_arb_get_dst_param(ins, dst, dst_name);
    shader_arb_get_src_param(ins, &ins->src[1], 1, src_name[1]);

    if (shader_version <= WINED3D_SHADER_VERSION(1, 3) && ins->coissue
            && ins->dst->write_mask != WINED3DSP_WRITEMASK_3)
    {
        shader_addline(buffer, "MOV%s %s, %s;\n", shader_arb_get_modifier(ins), dst_name, src_name[1]);
    }
    else
    {
        struct wined3d_shader_src_param src0_copy = ins->src[0];
        char extra_neg;

        /* src0 may have a negate srcmod set, so we can't blindly add "-" to the name */
        src0_copy.modifiers = negate_modifiers(src0_copy.modifiers, &extra_neg);

        shader_arb_get_src_param(ins, &src0_copy, 0, src_name[0]);
        shader_arb_get_src_param(ins, &ins->src[2], 2, src_name[2]);
        shader_addline(buffer, "ADD TA, %c%s, coefdiv.x;\n", extra_neg, src_name[0]);
        shader_addline(buffer, "CMP%s %s, TA, %s, %s;\n", shader_arb_get_modifier(ins),
                dst_name, src_name[1], src_name[2]);
    }
}