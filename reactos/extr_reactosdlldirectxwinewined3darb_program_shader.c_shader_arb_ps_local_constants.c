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
struct wined3d_state {TYPE_3__* ps_consts_i; int /*<<< orphan*/ ** texture_states; } ;
struct wined3d_gl_info {int dummy; } ;
struct wined3d_context {scalar_t__ render_offscreen; struct wined3d_gl_info* gl_info; } ;
struct arb_ps_compiled_shader {unsigned char numbumpenvmatconsts; scalar_t__ ycorrection; scalar_t__* int_consts; int /*<<< orphan*/  num_int_consts; TYPE_2__* luminanceconst; TYPE_1__* bumpenvmatconst; } ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {scalar_t__ const_num; } ;
struct TYPE_4__ {int texunit; scalar_t__ const_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAGMENT_PROGRAM_ARB ; 
 scalar_t__ WINED3D_CONST_NUM_UNUSED ; 
 unsigned char WINED3D_MAX_CONSTS_I ; 
 size_t WINED3D_TSS_BUMPENV_LSCALE ; 
 size_t WINED3D_TSS_BUMPENV_MAT00 ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glProgramLocalParameter4fvARB (int /*<<< orphan*/ ,scalar_t__,float const*) ; 

__attribute__((used)) static void shader_arb_ps_local_constants(const struct arb_ps_compiled_shader *gl_shader,
        const struct wined3d_context *context, const struct wined3d_state *state, UINT rt_height)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    unsigned char i;

    for(i = 0; i < gl_shader->numbumpenvmatconsts; i++)
    {
        int texunit = gl_shader->bumpenvmatconst[i].texunit;

        /* The state manager takes care that this function is always called if the bump env matrix changes */
        const float *data = (const float *)&state->texture_states[texunit][WINED3D_TSS_BUMPENV_MAT00];
        GL_EXTCALL(glProgramLocalParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB,
                gl_shader->bumpenvmatconst[i].const_num, data));

        if (gl_shader->luminanceconst[i].const_num != WINED3D_CONST_NUM_UNUSED)
        {
            /* WINED3D_TSS_BUMPENVLSCALE and WINED3D_TSS_BUMPENVLOFFSET are next to each other.
             * point gl to the scale, and load 4 floats. x = scale, y = offset, z and w are junk, we
             * don't care about them. The pointers are valid for sure because the stateblock is bigger.
             * (they're WINED3D_TSS_TEXTURETRANSFORMFLAGS and WINED3D_TSS_ADDRESSW, so most likely 0 or NaN
            */
            const float *scale = (const float *)&state->texture_states[texunit][WINED3D_TSS_BUMPENV_LSCALE];
            GL_EXTCALL(glProgramLocalParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB,
                    gl_shader->luminanceconst[i].const_num, scale));
        }
    }
    checkGLcall("Load bumpmap consts");

    if(gl_shader->ycorrection != WINED3D_CONST_NUM_UNUSED)
    {
        /* ycorrection.x: Backbuffer height(onscreen) or 0(offscreen).
        * ycorrection.y: -1.0(onscreen), 1.0(offscreen)
        * ycorrection.z: 1.0
        * ycorrection.w: 0.0
        */
        float val[4];
        val[0] = context->render_offscreen ? 0.0f : (float) rt_height;
        val[1] = context->render_offscreen ? 1.0f : -1.0f;
        val[2] = 1.0f;
        val[3] = 0.0f;
        GL_EXTCALL(glProgramLocalParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, gl_shader->ycorrection, val));
        checkGLcall("y correction loading");
    }

    if (!gl_shader->num_int_consts) return;

    for (i = 0; i < WINED3D_MAX_CONSTS_I; ++i)
    {
        if(gl_shader->int_consts[i] != WINED3D_CONST_NUM_UNUSED)
        {
            float val[4];
            val[0] = (float)state->ps_consts_i[i].x;
            val[1] = (float)state->ps_consts_i[i].y;
            val[2] = (float)state->ps_consts_i[i].z;
            val[3] = -1.0f;

            GL_EXTCALL(glProgramLocalParameter4fvARB(GL_FRAGMENT_PROGRAM_ARB, gl_shader->int_consts[i], val));
        }
    }
    checkGLcall("Load ps int consts");
}