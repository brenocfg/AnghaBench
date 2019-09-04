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
struct wined3d_shader_instruction {int /*<<< orphan*/  ctx; int /*<<< orphan*/ * src; TYPE_3__* dst; } ;
struct glsl_src_param {int /*<<< orphan*/  reg_name; } ;
struct glsl_sample_function {int dummy; } ;
struct TYPE_5__ {TYPE_1__* idx; } ;
struct TYPE_6__ {TYPE_2__ reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DSP_NOSWIZZLE ; 
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_ALL ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_gen_sample_code (struct wined3d_shader_instruction const*,int /*<<< orphan*/ ,struct glsl_sample_function*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_get_sample_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct glsl_sample_function*) ; 
 int /*<<< orphan*/  shader_glsl_release_sample_function (int /*<<< orphan*/ ,struct glsl_sample_function*) ; 

__attribute__((used)) static void shader_glsl_texreg2gb(const struct wined3d_shader_instruction *ins)
{
    DWORD sampler_idx = ins->dst[0].reg.idx[0].offset;
    struct glsl_sample_function sample_function;
    struct glsl_src_param src0_param;

    shader_glsl_add_src_param(ins, &ins->src[0], WINED3DSP_WRITEMASK_ALL, &src0_param);

    shader_glsl_get_sample_function(ins->ctx, sampler_idx, sampler_idx, 0, &sample_function);
    shader_glsl_gen_sample_code(ins, sampler_idx, &sample_function, WINED3DSP_NOSWIZZLE, NULL, NULL, NULL, NULL,
            "%s.yz", src0_param.reg_name);
    shader_glsl_release_sample_function(ins->ctx, &sample_function);
}