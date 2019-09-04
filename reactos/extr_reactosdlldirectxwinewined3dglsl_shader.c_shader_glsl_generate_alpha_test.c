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
typedef  enum wined3d_cmp_func { ____Placeholder_wined3d_cmp_func } wined3d_cmp_func ;

/* Variables and functions */
 int WINED3D_CMP_ALWAYS ; 
 int WINED3D_CMP_NEVER ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,...) ; 

__attribute__((used)) static void shader_glsl_generate_alpha_test(struct wined3d_string_buffer *buffer,
        const struct wined3d_gl_info *gl_info, enum wined3d_cmp_func alpha_func)
{
    const char *output = needs_legacy_glsl_syntax(gl_info) ? "gl_FragData[0]" : "ps_out0";

    /* alpha_func is the PASS condition, not the DISCARD condition. Instead of
     * flipping all the operators here, just negate the comparison below. */
    static const char * const comparison_operator[] =
    {
        "",   /* WINED3D_CMP_NEVER */
        "<",  /* WINED3D_CMP_LESS */
        "==", /* WINED3D_CMP_EQUAL */
        "<=", /* WINED3D_CMP_LESSEQUAL */
        ">",  /* WINED3D_CMP_GREATER */
        "!=", /* WINED3D_CMP_NOTEQUAL */
        ">=", /* WINED3D_CMP_GREATEREQUAL */
        ""    /* WINED3D_CMP_ALWAYS */
    };

    if (alpha_func == WINED3D_CMP_ALWAYS)
        return;

    if (alpha_func != WINED3D_CMP_NEVER)
        shader_addline(buffer, "if (!(%s.a %s alpha_test_ref))\n",
                output, comparison_operator[alpha_func - WINED3D_CMP_NEVER]);
    shader_addline(buffer, "    discard;\n");
}