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
struct wined3d_shader_instruction {int /*<<< orphan*/  flags; TYPE_1__* ctx; int /*<<< orphan*/ * src; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_0 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_get_rel_op (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_ifc(const struct wined3d_shader_instruction *ins)
{
    struct glsl_src_param src0_param;
    struct glsl_src_param src1_param;

    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_0, &src0_param);
    shader_glsl_add_src_param(ins, &ins->src[1], WINED3DSP_WRITEMASK_0, &src1_param);

    shader_addline(ins->ctx->buffer, "if (%s %s %s) {\n",
            src0_param.param_str, shader_glsl_get_rel_op(ins->flags), src1_param.param_str);
}