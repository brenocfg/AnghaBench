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
struct wined3d_shader_reg_maps {int dummy; } ;
struct wined3d_shader_phase {unsigned int temporary_count; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ instance_count; } ;
struct wined3d_shader {int dummy; } ;
struct shader_glsl_ctx_priv {int dummy; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_generate_code (struct wined3d_shader const*,struct wined3d_string_buffer*,struct wined3d_shader_reg_maps const*,struct shader_glsl_ctx_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT shader_glsl_generate_shader_phase(const struct wined3d_shader *shader,
        struct wined3d_string_buffer *buffer, const struct wined3d_shader_reg_maps *reg_maps,
        struct shader_glsl_ctx_priv *priv_ctx, const struct wined3d_shader_phase *phase,
        const char *phase_name, unsigned phase_idx)
{
    unsigned int i;
    HRESULT hr;

    shader_addline(buffer, "void hs_%s_phase%u(%s)\n{\n",
            phase_name, phase_idx, phase->instance_count ? "int phase_instance_id" : "");
    for (i = 0; i < phase->temporary_count; ++i)
        shader_addline(buffer, "vec4 R%u;\n", i);
    hr = shader_generate_code(shader, buffer, reg_maps, priv_ctx, phase->start, phase->end);
    shader_addline(buffer, "}\n");
    return hr;
}