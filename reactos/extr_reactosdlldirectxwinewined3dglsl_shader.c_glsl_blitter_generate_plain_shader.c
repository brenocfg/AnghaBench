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
struct wined3d_gl_info {int dummy; } ;
struct glsl_blitter_args {int /*<<< orphan*/  fixup; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINED3DSP_WRITEMASK_ALL ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 
 int /*<<< orphan*/  shader_glsl_color_correction_ext (struct wined3d_string_buffer*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void glsl_blitter_generate_plain_shader(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, const struct glsl_blitter_args *args,
        const char *output, const char *tex_type, const char *swizzle)
{
    shader_addline(buffer, "\nvoid main()\n{\n");
    shader_addline(buffer, "    %s = texture%s(sampler, out_texcoord.%s);\n",
            output, needs_legacy_glsl_syntax(gl_info) ? tex_type : "", swizzle);
    shader_glsl_color_correction_ext(buffer, output, WINED3DSP_WRITEMASK_ALL, args->fixup);
    shader_addline(buffer, "}\n");
}