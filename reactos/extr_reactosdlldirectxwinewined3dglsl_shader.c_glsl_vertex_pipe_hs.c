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
struct wined3d_state {scalar_t__* shader; } ;
struct wined3d_context {unsigned int shader_update_mask; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 unsigned int WINED3D_SHADER_TYPE_DOMAIN ; 
 size_t WINED3D_SHADER_TYPE_VERTEX ; 

__attribute__((used)) static void glsl_vertex_pipe_hs(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    /* In Direct3D tessellator options (e.g. output primitive type, primitive
     * winding) are defined in Hull Shaders, while in GLSL those are
     * specified in Tessellation Evaluation Shaders. */
    context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_DOMAIN;

    if (state->shader[WINED3D_SHADER_TYPE_VERTEX])
        context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_VERTEX;
}