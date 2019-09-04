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
struct TYPE_2__ {int /*<<< orphan*/  data_type; } ;
struct wined3d_shader_src_param {TYPE_1__ reg; } ;
struct wined3d_shader_instruction {int dummy; } ;
struct glsl_src_param {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  shader_glsl_add_src_param_ext (struct wined3d_shader_instruction const*,struct wined3d_shader_src_param const*,int /*<<< orphan*/ ,struct glsl_src_param*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_add_src_param(const struct wined3d_shader_instruction *ins,
        const struct wined3d_shader_src_param *wined3d_src, DWORD mask, struct glsl_src_param *glsl_src)
{
    shader_glsl_add_src_param_ext(ins, wined3d_src, mask, glsl_src, wined3d_src->reg.data_type);
}