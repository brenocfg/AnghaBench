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
struct wined3d_gl_info {scalar_t__* supported; } ;
struct glsl_blitter_args {int dummy; } ;

/* Variables and functions */
 size_t WINED3D_GL_LEGACY_CONTEXT ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void glsl_blitter_generate_p8_shader(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, const struct glsl_blitter_args *args,
        const char *output, const char *tex_type, const char *swizzle)
{
    shader_addline(buffer, "uniform sampler1D sampler_palette;\n");
    shader_addline(buffer, "\nvoid main()\n{\n");
    /* The alpha-component contains the palette index. */
    shader_addline(buffer, "    float index = texture%s(sampler, out_texcoord.%s).%c;\n",
            needs_legacy_glsl_syntax(gl_info) ? tex_type : "", swizzle,
            gl_info->supported[WINED3D_GL_LEGACY_CONTEXT] ? 'w' : 'x');
    /* Scale the index by 255/256 and add a bias of 0.5 in order to sample in
     * the middle. */
    shader_addline(buffer, "    index = (index * 255.0 + 0.5) / 256.0;\n");
    shader_addline(buffer, "    %s = texture%s(sampler_palette, index);\n",
            output, needs_legacy_glsl_syntax(gl_info) ? "1D" : "");
    shader_addline(buffer, "}\n");
}