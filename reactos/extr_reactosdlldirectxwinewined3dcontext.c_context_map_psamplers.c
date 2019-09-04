#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {TYPE_3__** shader; } ;
struct wined3d_shader_resource_info {scalar_t__ type; } ;
struct TYPE_4__ {unsigned int ffp_blend_stages; } ;
struct wined3d_d3d_info {TYPE_1__ limits; } ;
struct wined3d_context {unsigned int* tex_unit_map; struct wined3d_d3d_info* d3d_info; } ;
struct TYPE_5__ {struct wined3d_shader_resource_info* resource_info; } ;
struct TYPE_6__ {TYPE_2__ reg_maps; } ;

/* Variables and functions */
 unsigned int MAX_FRAGMENT_SAMPLERS ; 
 int /*<<< orphan*/  STATE_SAMPLER (unsigned int) ; 
 size_t WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  context_invalidate_state (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_invalidate_texture_stage (struct wined3d_context*,unsigned int) ; 
 int /*<<< orphan*/  context_map_stage (struct wined3d_context*,unsigned int,unsigned int) ; 

__attribute__((used)) static void context_map_psamplers(struct wined3d_context *context, const struct wined3d_state *state)
{
    const struct wined3d_d3d_info *d3d_info = context->d3d_info;
    const struct wined3d_shader_resource_info *resource_info =
            state->shader[WINED3D_SHADER_TYPE_PIXEL]->reg_maps.resource_info;
    unsigned int i;

    for (i = 0; i < MAX_FRAGMENT_SAMPLERS; ++i)
    {
        if (resource_info[i].type && context->tex_unit_map[i] != i)
        {
            context_map_stage(context, i, i);
            context_invalidate_state(context, STATE_SAMPLER(i));
            if (i < d3d_info->limits.ffp_blend_stages)
                context_invalidate_texture_stage(context, i);
        }
    }
}