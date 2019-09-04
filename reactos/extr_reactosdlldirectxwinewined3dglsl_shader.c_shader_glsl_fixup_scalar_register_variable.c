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
struct wined3d_gl_info {scalar_t__* supported; } ;

/* Variables and functions */
 size_t ARB_SHADING_LANGUAGE_420PACK ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static void shader_glsl_fixup_scalar_register_variable(char *register_name,
        const char *glsl_variable, const struct wined3d_gl_info *gl_info)
{
    /* The ARB_shading_language_420pack extension allows swizzle operations on
     * scalars. */
    if (gl_info->supported[ARB_SHADING_LANGUAGE_420PACK])
        sprintf(register_name, "%s", glsl_variable);
    else
        sprintf(register_name, "ivec2(%s, 0)", glsl_variable);
}