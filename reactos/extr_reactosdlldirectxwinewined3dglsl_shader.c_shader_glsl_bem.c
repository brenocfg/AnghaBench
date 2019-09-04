#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wined3d_shader_instruction {TYPE_1__* ctx; int /*<<< orphan*/ * src; TYPE_3__* dst; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_8__ {TYPE_2__* idx; } ;
struct TYPE_7__ {TYPE_4__ reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int WINED3DSP_WRITEMASK_0 ; 
 int WINED3DSP_WRITEMASK_1 ; 
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_bem(const struct wined3d_shader_instruction *ins)
{
    DWORD sampler_idx = ins->dst[0].reg.idx[0].offset;
    struct glsl_src_param src0_param, src1_param;

    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_0 | WINED3DSP_WRITEMASK_1, &src0_param);
    shader_glsl_add_src_param(ins, &ins->src[1], WINED3DSP_WRITEMASK_0 | WINED3DSP_WRITEMASK_1, &src1_param);

    shader_glsl_append_dst(ins->ctx->buffer, ins);
    shader_addline(ins->ctx->buffer, "%s + bumpenv_mat%u * %s);\n",
            src0_param.param_str, sampler_idx, src1_param.param_str);
}