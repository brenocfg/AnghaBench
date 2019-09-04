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
struct wined3d_state {int dummy; } ;
struct wined3d_context {unsigned int shader_update_mask; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  STATE_VDECL ; 
 unsigned int WINED3D_SHADER_TYPE_VERTEX ; 
 int /*<<< orphan*/  context_apply_state (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isStateDirty (struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void glsl_vertex_pipe_vs(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    context->shader_update_mask |= 1u << WINED3D_SHADER_TYPE_VERTEX;
    /* Different vertex shaders potentially require a different vertex attributes setup. */
    if (!isStateDirty(context, STATE_VDECL))
        context_apply_state(context, state, STATE_VDECL);
}