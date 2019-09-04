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
struct wined3d_shader_instruction {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data_type; } ;
struct wined3d_shader_dst_param {TYPE_1__ reg; } ;
struct glsl_dst_param {char* mask_str; char* reg_name; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  shader_glsl_get_register_name (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct wined3d_shader_instruction const*) ; 
 int /*<<< orphan*/  shader_glsl_get_write_mask (struct wined3d_shader_dst_param const*,char*) ; 

__attribute__((used)) static DWORD shader_glsl_add_dst_param(const struct wined3d_shader_instruction *ins,
        const struct wined3d_shader_dst_param *wined3d_dst, struct glsl_dst_param *glsl_dst)
{
    BOOL is_color = FALSE;

    glsl_dst->mask_str[0] = '\0';
    glsl_dst->reg_name[0] = '\0';

    shader_glsl_get_register_name(&wined3d_dst->reg, wined3d_dst->reg.data_type,
            glsl_dst->reg_name, &is_color, ins);
    return shader_glsl_get_write_mask(wined3d_dst, glsl_dst->mask_str);
}