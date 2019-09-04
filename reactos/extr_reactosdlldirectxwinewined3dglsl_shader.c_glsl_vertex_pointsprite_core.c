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
struct wined3d_state {scalar_t__ gl_primitive_type; int /*<<< orphan*/ * render_states; } ;
struct wined3d_context {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ GL_POINTS ; 
 size_t WINED3D_RS_POINTSPRITEENABLE ; 

__attribute__((used)) static void glsl_vertex_pointsprite_core(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    static unsigned int once;

    if (state->gl_primitive_type == GL_POINTS && !state->render_states[WINED3D_RS_POINTSPRITEENABLE] && !once++)
        FIXME("Non-point sprite points not supported in core profile.\n");
}