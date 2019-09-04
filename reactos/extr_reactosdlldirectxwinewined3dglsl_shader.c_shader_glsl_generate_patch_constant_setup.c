#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wined3d_string_buffer {int dummy; } ;
struct wined3d_shader_signature_element {scalar_t__ register_idx; int /*<<< orphan*/  mask; int /*<<< orphan*/  sysval_semantic; } ;
struct wined3d_shader_signature {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 unsigned int max (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_generate_patch_constant_name (struct wined3d_string_buffer*,struct wined3d_shader_signature_element const*,unsigned int*,char*) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void shader_glsl_generate_patch_constant_setup(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_signature *signature, BOOL input_setup)
{
    unsigned int i, register_count, user_constant_index, user_constant_count;

    register_count = user_constant_count = 0;
    for (i = 0; i < signature->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *constant = &signature->elements[i];
        register_count = max(constant->register_idx + 1, register_count);
        if (!constant->sysval_semantic)
            ++user_constant_count;
    }

    if (user_constant_count)
        shader_addline(buffer, "patch %s vec4 user_patch_constant[%u];\n",
                input_setup ? "in" : "out", user_constant_count);
    if (input_setup)
        shader_addline(buffer, "vec4 vpc[%u];\n", register_count);

    shader_addline(buffer, "void setup_patch_constant_%s()\n{\n", input_setup ? "input" : "output");
    for (i = 0, user_constant_index = 0; i < signature->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *constant = &signature->elements[i];
        char reg_mask[6];

        shader_glsl_write_mask_to_str(constant->mask, reg_mask);

        if (input_setup)
            shader_addline(buffer, "vpc[%u]%s", constant->register_idx, reg_mask);
        else
            shader_glsl_generate_patch_constant_name(buffer, constant, &user_constant_index, reg_mask);

        shader_addline(buffer, " = ");

        if (input_setup)
            shader_glsl_generate_patch_constant_name(buffer, constant, &user_constant_index, reg_mask);
        else
            shader_addline(buffer, "hs_out[%u]%s", constant->register_idx, reg_mask);

        shader_addline(buffer, ";\n");
    }
    shader_addline(buffer, "}\n");
}