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
struct wined3d_shader_instruction {TYPE_1__* ctx; int /*<<< orphan*/ * src; } ;
struct glsl_src_param {int /*<<< orphan*/  param_str; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_glsl_add_src_param (struct wined3d_shader_instruction const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct glsl_src_param*) ; 
 int /*<<< orphan*/  shader_glsl_append_dst (int /*<<< orphan*/ ,struct wined3d_shader_instruction const*) ; 

__attribute__((used)) static void shader_glsl_sgn(const struct wined3d_shader_instruction *ins)
{
    struct glsl_src_param src0_param;
    DWORD write_mask;

    write_mask = shader_glsl_append_dst(ins->ctx->buffer, ins);
    shader_glsl_add_src_param(ins, &ins->src[0], write_mask, &src0_param);

    shader_addline(ins->ctx->buffer, "sign(%s));\n", src0_param.param_str);
}