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

/* Variables and functions */
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_glsl_generate_srgb_write_correction(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info)
{
    const char *output = needs_legacy_glsl_syntax(gl_info) ? "gl_FragData[0]" : "ps_out0";

    shader_addline(buffer, "tmp0.xyz = pow(%s.xyz, vec3(srgb_const0.x));\n", output);
    shader_addline(buffer, "tmp0.xyz = tmp0.xyz * vec3(srgb_const0.y) - vec3(srgb_const0.z);\n");
    shader_addline(buffer, "tmp1.xyz = %s.xyz * vec3(srgb_const0.w);\n", output);
    shader_addline(buffer, "bvec3 srgb_compare = lessThan(%s.xyz, vec3(srgb_const1.x));\n", output);
    shader_addline(buffer, "%s.xyz = mix(tmp0.xyz, tmp1.xyz, vec3(srgb_compare));\n", output);
    shader_addline(buffer, "%s = clamp(%s, 0.0, 1.0);\n", output, output);
}