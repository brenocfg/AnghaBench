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
struct wined3d_shader_signature_element {scalar_t__ sysval_semantic; unsigned int mask; int /*<<< orphan*/  register_idx; scalar_t__ semantic_idx; } ;
typedef  int DWORD ;

/* Variables and functions */
 unsigned int WINED3DSP_WRITEMASK_0 ; 
 scalar_t__ WINED3D_SV_CLIP_DISTANCE ; 
 int /*<<< orphan*/  shader_addline (struct wined3d_string_buffer*,char*,char const*,unsigned int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shader_glsl_write_mask_to_str (unsigned int,char*) ; 
 unsigned int wined3d_popcount (int) ; 

__attribute__((used)) static void shader_glsl_generate_clip_or_cull_distances(struct wined3d_string_buffer *buffer,
        const struct wined3d_shader_signature_element *element, DWORD clip_or_cull_distance_mask)
{
    unsigned int i, clip_or_cull_index;
    const char *name;
    char reg_mask[6];

    name = element->sysval_semantic == WINED3D_SV_CLIP_DISTANCE ? "Clip" : "Cull";
    /* Assign consecutive indices starting from 0. */
    clip_or_cull_index = element->semantic_idx ? wined3d_popcount(clip_or_cull_distance_mask & 0xf) : 0;
    for (i = 0; i < 4; ++i)
    {
        if (!(element->mask & (WINED3DSP_WRITEMASK_0 << i)))
            continue;

        shader_glsl_write_mask_to_str(WINED3DSP_WRITEMASK_0 << i, reg_mask);
        shader_addline(buffer, "gl_%sDistance[%u] = outputs[%u]%s;\n",
                name, clip_or_cull_index, element->register_idx, reg_mask);
        ++clip_or_cull_index;
    }
}