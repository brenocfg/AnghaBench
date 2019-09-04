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
struct wined3d_state {int /*<<< orphan*/ ** texture_states; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_device {struct shader_arb_priv* shader_priv; int /*<<< orphan*/ * shader_backend; } ;
struct wined3d_context {struct wined3d_device* device; struct wined3d_gl_info* gl_info; } ;
struct wined3d_color {int /*<<< orphan*/  r; } ;
struct shader_arb_priv {int* pshader_const_dirty; int /*<<< orphan*/  highest_dirty_ps_const; } ;
typedef  int DWORD ;

/* Variables and functions */
 int ARB_FFP_CONST_CONSTANT (int) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 int STATE_TEXTURESTAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WINED3D_HIGHEST_TEXTURE_STATE ; 
 size_t WINED3D_TSS_CONSTANT ; 
 int /*<<< orphan*/  arb_program_shader_backend ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glProgramEnvParameter4fvARB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_ps (struct wined3d_state const*) ; 
 int /*<<< orphan*/  wined3d_color_from_d3dcolor (struct wined3d_color*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void state_tss_constant_arbfp(struct wined3d_context *context,
        const struct wined3d_state *state, DWORD state_id)
{
    DWORD stage = (state_id - STATE_TEXTURESTAGE(0, 0)) / (WINED3D_HIGHEST_TEXTURE_STATE + 1);
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct wined3d_device *device = context->device;
    struct wined3d_color color;

    if (device->shader_backend == &arb_program_shader_backend)
    {
        struct shader_arb_priv *priv;

        /* Don't load the parameter if we're using an arbfp pixel shader, otherwise we'll overwrite
         * application provided constants.
         */
        if (use_ps(state))
            return;

        priv = device->shader_priv;
        priv->pshader_const_dirty[ARB_FFP_CONST_CONSTANT(stage)] = 1;
        priv->highest_dirty_ps_const = max(priv->highest_dirty_ps_const, ARB_FFP_CONST_CONSTANT(stage) + 1);
    }

    wined3d_color_from_d3dcolor(&color, state->texture_states[stage][WINED3D_TSS_CONSTANT]);
    GL_EXTCALL(glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_CONSTANT(stage), &color.r));
    checkGLcall("glProgramEnvParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, ARB_FFP_CONST_CONSTANT(stage), &color.r)");
}