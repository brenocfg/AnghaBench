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
struct wined3d_context {int /*<<< orphan*/  constant_update_mask; } ;
typedef  int DWORD ;

/* Variables and functions */
 int STATE_TRANSFORM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINED3D_SHADER_CONST_FFP_VERTEXBLEND_INDEX (int) ; 
 int /*<<< orphan*/  WINED3D_TS_WORLD_MATRIX (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void glsl_vertex_pipe_vertexblend(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    int i = state_id - STATE_TRANSFORM(WINED3D_TS_WORLD_MATRIX(0));
    context->constant_update_mask |= WINED3D_SHADER_CONST_FFP_VERTEXBLEND_INDEX(i);
}