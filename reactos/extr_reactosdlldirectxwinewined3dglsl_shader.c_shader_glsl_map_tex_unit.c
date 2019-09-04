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
struct wined3d_shader_version {int dummy; } ;
struct wined3d_context {int dummy; } ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 unsigned int WINED3D_UNMAPPED_STAGE ; 
 unsigned int* context_get_tex_unit_mapping (struct wined3d_context const*,struct wined3d_shader_version const*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static unsigned int shader_glsl_map_tex_unit(const struct wined3d_context *context,
        const struct wined3d_shader_version *shader_version, unsigned int sampler_idx)
{
    const DWORD *tex_unit_map;
    unsigned int base, count;

    tex_unit_map = context_get_tex_unit_mapping(context, shader_version, &base, &count);
    if (sampler_idx >= count)
        return WINED3D_UNMAPPED_STAGE;
    if (!tex_unit_map)
        return base + sampler_idx;
    return tex_unit_map[base + sampler_idx];
}