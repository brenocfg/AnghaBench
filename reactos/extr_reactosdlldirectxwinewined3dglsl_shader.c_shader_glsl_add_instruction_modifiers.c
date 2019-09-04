#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_instruction {TYPE_1__* ctx; TYPE_2__* dst; int /*<<< orphan*/  dst_count; } ;
struct glsl_dst_param {int /*<<< orphan*/  mask_str; int /*<<< orphan*/  reg_name; } ;
struct TYPE_4__ {int modifiers; } ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int WINED3DSPDM_MSAMPCENTROID ; 
 int WINED3DSPDM_PARTIALPRECISION ; 
 int WINED3DSPDM_SATURATE ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_dst_param (struct wined3d_shader_instruction const*,TYPE_2__*,struct glsl_dst_param*) ; 

__attribute__((used)) static void shader_glsl_add_instruction_modifiers(const struct wined3d_shader_instruction *ins)
{
    struct glsl_dst_param dst_param;
    DWORD modifiers;

    if (!ins->dst_count) return;

    modifiers = ins->dst[0].modifiers;
    if (!modifiers) return;

    shader_glsl_add_dst_param(ins, &ins->dst[0], &dst_param);

    if (modifiers & WINED3DSPDM_SATURATE)
    {
        /* _SAT means to clamp the value of the register to between 0 and 1 */
        shader_addline(ins->ctx->buffer, "%s%s = clamp(%s%s, 0.0, 1.0);\n", dst_param.reg_name,
                dst_param.mask_str, dst_param.reg_name, dst_param.mask_str);
    }

    if (modifiers & WINED3DSPDM_MSAMPCENTROID)
    {
        FIXME("_centroid modifier not handled\n");
    }

    if (modifiers & WINED3DSPDM_PARTIALPRECISION)
    {
        /* MSDN says this modifier can be safely ignored, so that's what we'll do. */
    }
}