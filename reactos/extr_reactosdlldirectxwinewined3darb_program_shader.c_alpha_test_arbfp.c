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
struct wined3d_state {scalar_t__* render_states; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_glAlphaFunc ) (int,float) ;int /*<<< orphan*/  (* p_glDisable ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glEnable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GL_ALPHA_TEST ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 size_t WINED3D_RS_ALPHAFUNC ; 
 size_t WINED3D_RS_ALPHAREF ; 
 size_t WINED3D_RS_ALPHATESTENABLE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int,float) ; 
 int wined3d_gl_compare_func (scalar_t__) ; 

__attribute__((used)) static void alpha_test_arbfp(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    int glParm;
    float ref;

    TRACE("context %p, state %p, state_id %#x.\n", context, state, state_id);

    if (state->render_states[WINED3D_RS_ALPHATESTENABLE])
    {
        gl_info->gl_ops.gl.p_glEnable(GL_ALPHA_TEST);
        checkGLcall("glEnable GL_ALPHA_TEST");
    }
    else
    {
        gl_info->gl_ops.gl.p_glDisable(GL_ALPHA_TEST);
        checkGLcall("glDisable GL_ALPHA_TEST");
        return;
    }

    ref = ((float)state->render_states[WINED3D_RS_ALPHAREF]) / 255.0f;
    glParm = wined3d_gl_compare_func(state->render_states[WINED3D_RS_ALPHAFUNC]);

    if (glParm)
    {
        gl_info->gl_ops.gl.p_glAlphaFunc(glParm, ref);
        checkGLcall("glAlphaFunc");
    }
}