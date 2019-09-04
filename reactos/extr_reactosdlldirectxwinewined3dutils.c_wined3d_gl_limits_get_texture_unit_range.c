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
struct wined3d_gl_limits {unsigned int combined_samplers; unsigned int graphics_samplers; unsigned int* samplers; } ;
typedef  enum wined3d_shader_type { ____Placeholder_wined3d_shader_type } wined3d_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int WINED3D_SHADER_TYPE_COMPUTE ; 
 unsigned int WINED3D_SHADER_TYPE_GRAPHICS_COUNT ; 

void wined3d_gl_limits_get_texture_unit_range(const struct wined3d_gl_limits *gl_limits,
        enum wined3d_shader_type shader_type, unsigned int *base, unsigned int *count)
{
    unsigned int i;

    if (shader_type == WINED3D_SHADER_TYPE_COMPUTE)
    {
        if (gl_limits->combined_samplers == gl_limits->graphics_samplers)
            *base = 0;
        else
            *base = gl_limits->graphics_samplers;
        *count = gl_limits->samplers[WINED3D_SHADER_TYPE_COMPUTE];
        return;
    }

    *base = 0;
    for (i = 0; i < WINED3D_SHADER_TYPE_GRAPHICS_COUNT; ++i)
    {
        *count = gl_limits->samplers[i];
        if (i == shader_type)
            return;
        *base += *count;
    }

    ERR("Unrecognized shader type %#x.\n", shader_type);
    *count = 0;
}