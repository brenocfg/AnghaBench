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
struct wined3d_shader_signature_element {unsigned int register_idx; int /*<<< orphan*/  mask; scalar_t__ stream_idx; } ;
struct wined3d_shader_signature {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct wined3d_shader_reg_maps {unsigned int output_registers; } ;
struct shader_glsl_priv {struct wined3d_string_buffer shader_buffer; } ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,unsigned int,char*,unsigned int,char*) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void shader_glsl_setup_sm4_shader_output(struct shader_glsl_priv *priv,
        unsigned int input_count, const struct wined3d_shader_signature *output_signature,
        const struct wined3d_shader_reg_maps *reg_maps_out, const char *output_variable_name,
        BOOL rasterizer_setup)
{
    struct wined3d_string_buffer *buffer = &priv->shader_buffer;
    char reg_mask[6];
    unsigned int i;

    for (i = 0; i < output_signature->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *output = &output_signature->elements[i];

        if (!(reg_maps_out->output_registers & (1u << output->register_idx)))
            continue;

        if (output->stream_idx)
            continue;

        if (output->register_idx >= input_count)
            continue;

        shader_glsl_write_mask_to_str(output->mask, reg_mask);

        shader_addline(buffer,
                rasterizer_setup ? "%s.reg%u%s = outputs[%u]%s;\n" : "%s.reg[%u]%s = outputs[%u]%s;\n",
                output_variable_name, output->register_idx, reg_mask, output->register_idx, reg_mask);
    }
}