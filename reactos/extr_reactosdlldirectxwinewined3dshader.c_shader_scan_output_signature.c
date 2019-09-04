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
struct wined3d_shader_signature_element {unsigned int register_idx; scalar_t__ sysval_semantic; } ;
struct wined3d_shader_signature {unsigned int element_count; struct wined3d_shader_signature_element* elements; } ;
struct wined3d_shader_reg_maps {unsigned int output_registers; unsigned int clip_distance_mask; unsigned int cull_distance_mask; int viewport_array; } ;
struct wined3d_shader {struct wined3d_shader_reg_maps reg_maps; struct wined3d_shader_signature output_signature; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_OK ; 
 scalar_t__ WINED3D_SV_CLIP_DISTANCE ; 
 scalar_t__ WINED3D_SV_CULL_DISTANCE ; 
 scalar_t__ WINED3D_SV_VIEWPORT_ARRAY_INDEX ; 
 int /*<<< orphan*/  shader_calculate_clip_or_cull_distance_mask (struct wined3d_shader_signature_element const*,unsigned int*) ; 

__attribute__((used)) static HRESULT shader_scan_output_signature(struct wined3d_shader *shader)
{
    const struct wined3d_shader_signature *output_signature = &shader->output_signature;
    struct wined3d_shader_reg_maps *reg_maps = &shader->reg_maps;
    unsigned int i;
    HRESULT hr;

    for (i = 0; i < output_signature->element_count; ++i)
    {
        const struct wined3d_shader_signature_element *e = &output_signature->elements[i];
        unsigned int mask;

        reg_maps->output_registers |= 1u << e->register_idx;
        if (e->sysval_semantic == WINED3D_SV_CLIP_DISTANCE)
        {
            if (FAILED(hr = shader_calculate_clip_or_cull_distance_mask(e, &mask)))
                return hr;
            reg_maps->clip_distance_mask |= mask;
        }
        else if (e->sysval_semantic == WINED3D_SV_CULL_DISTANCE)
        {
            if (FAILED(hr = shader_calculate_clip_or_cull_distance_mask(e, &mask)))
                return hr;
            reg_maps->cull_distance_mask |= mask;
        }
        else if (e->sysval_semantic == WINED3D_SV_VIEWPORT_ARRAY_INDEX)
        {
            reg_maps->viewport_array = 1;
        }
    }

    return WINED3D_OK;
}