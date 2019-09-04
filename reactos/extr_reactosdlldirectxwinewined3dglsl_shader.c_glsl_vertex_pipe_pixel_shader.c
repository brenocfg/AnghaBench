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
struct wined3d_context {unsigned int shader_update_mask; } ;
struct TYPE_4__ {int major; } ;
struct TYPE_5__ {TYPE_1__ shader_version; } ;
struct TYPE_6__ {TYPE_2__ reg_maps; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t WINED3D_SHADER_TYPE_DOMAIN ; 
 size_t WINED3D_SHADER_TYPE_GEOMETRY ; 
 size_t WINED3D_SHADER_TYPE_VERTEX ; 

__attribute__((used)) static void glsl_vertex_pipe_pixel_shader(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    if (state->shader[WINED3D_SHADER_TYPE_GEOMETRY])
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_GEOMETRY;
    else if (state->shader[WINED3D_SHADER_TYPE_DOMAIN])
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_DOMAIN;
    else if (state->shader[WINED3D_SHADER_TYPE_VERTEX]
            && state->shader[WINED3D_SHADER_TYPE_VERTEX]->reg_maps.shader_version.major >= 4)
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_VERTEX;
}