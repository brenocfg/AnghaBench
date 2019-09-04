#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {float* render_states; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_glAlphaFunc ) (scalar_t__,float) ;} ;
struct TYPE_4__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  scalar_t__ GLint ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t WINED3D_RS_ALPHAFUNC ; 
 size_t WINED3D_RS_ALPHAREF ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,float) ; 
 scalar_t__ wined3d_gl_compare_func (float) ; 

__attribute__((used)) static void glsl_fragment_pipe_alpha_test_func(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    GLint func = wined3d_gl_compare_func(state->render_states[WINED3D_RS_ALPHAFUNC]);
    float ref = state->render_states[WINED3D_RS_ALPHAREF] / 255.0f;

    if (func)
    {
        gl_info->gl_ops.gl.p_glAlphaFunc(func, ref);
        checkGLcall("glAlphaFunc");
    }
}