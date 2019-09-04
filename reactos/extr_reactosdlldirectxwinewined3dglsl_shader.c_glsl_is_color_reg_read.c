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
struct wined3d_shader_signature_element {unsigned int register_idx; unsigned int semantic_idx; int /*<<< orphan*/  semantic_name; } ;
struct wined3d_shader_signature {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct TYPE_6__ {int major; } ;
struct wined3d_shader_reg_maps {unsigned int input_registers; TYPE_3__ shader_version; } ;
struct TYPE_4__ {unsigned int input_reg_used; } ;
struct TYPE_5__ {TYPE_1__ ps; } ;
struct wined3d_shader {TYPE_2__ u; struct wined3d_shader_reg_maps reg_maps; struct wined3d_shader_signature input_signature; } ;
typedef  unsigned int DWORD ;
typedef  unsigned int BOOL ;

/* Variables and functions */
 unsigned int FALSE ; 
 int /*<<< orphan*/  WINED3D_DECL_USAGE_COLOR ; 
 scalar_t__ shader_match_semantic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL glsl_is_color_reg_read(const struct wined3d_shader *shader, unsigned int idx)
{
    const struct wined3d_shader_signature *input_signature = &shader->input_signature;
    const struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    DWORD input_reg_used = shader->u.ps.input_reg_used;
    unsigned int i;

    if (reg_maps->shader_version.major < 3)
        return input_reg_used & (1u << idx);

    for (i = 0; i < input_signature->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *input = &input_signature->elements[i];

        if (!(reg_maps->input_registers & (1u << input->register_idx)))
            continue;

        if (shader_match_semantic(input->semantic_name, WINED3D_DECL_USAGE_COLOR)
                && input->semantic_idx == idx)
            return input_reg_used & (1u << input->register_idx);
    }
    return FALSE;
}