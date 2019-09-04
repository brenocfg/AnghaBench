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
struct wined3d_state {TYPE_3__* ps_consts_i; scalar_t__* render_states; scalar_t__* ps_consts_b; } ;
struct TYPE_5__ {unsigned int local_bool_consts; int integer_constants; int local_int_consts; } ;
struct wined3d_shader {TYPE_2__ reg_maps; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_d3d_info {int /*<<< orphan*/  vs_clipping; } ;
struct TYPE_4__ {int /*<<< orphan*/  position_transformed; } ;
struct wined3d_context {TYPE_1__ stream_info; struct wined3d_d3d_info* d3d_info; struct wined3d_gl_info* gl_info; } ;
struct arb_ps_compile_args {unsigned int bools; int clip; scalar_t__** loop_ctrl; int /*<<< orphan*/  super; } ;
typedef  int WORD ;
struct TYPE_6__ {scalar_t__ z; scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 size_t NV_FRAGMENT_PROGRAM_OPTION ; 
 int WINED3D_MAX_CONSTS_B ; 
 int WINED3D_MAX_CONSTS_I ; 
 size_t WINED3D_RS_CLIPPING ; 
 size_t WINED3D_RS_CLIPPLANEENABLE ; 
 int /*<<< orphan*/  find_ps_compile_args (struct wined3d_state const*,struct wined3d_shader const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct wined3d_context const*) ; 
 int /*<<< orphan*/  memset (scalar_t__**,int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void find_arb_ps_compile_args(const struct wined3d_state *state,
        const struct wined3d_context *context, const struct wined3d_shader *shader,
        struct arb_ps_compile_args *args)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_d3d_info *d3d_info = context->d3d_info;
    int i;
    WORD int_skip;

    find_ps_compile_args(state, shader, context->stream_info.position_transformed, &args->super, context);

    /* This forces all local boolean constants to 1 to make them stateblock independent */
    args->bools = shader->reg_maps.local_bool_consts;

    for (i = 0; i < WINED3D_MAX_CONSTS_B; ++i)
    {
        if (state->ps_consts_b[i])
            args->bools |= ( 1u << i);
    }

    /* Only enable the clip plane emulation KIL if at least one clipplane is enabled. The KIL instruction
     * is quite expensive because it forces the driver to disable early Z discards. It is cheaper to
     * duplicate the shader than have a no-op KIL instruction in every shader
     */
    if (!d3d_info->vs_clipping && use_vs(state)
            && state->render_states[WINED3D_RS_CLIPPING]
            && state->render_states[WINED3D_RS_CLIPPLANEENABLE])
        args->clip = 1;
    else
        args->clip = 0;

    /* Skip if unused or local, or supported natively */
    int_skip = ~shader->reg_maps.integer_constants | shader->reg_maps.local_int_consts;
    if (int_skip == 0xffff || gl_info->supported[NV_FRAGMENT_PROGRAM_OPTION])
    {
        memset(args->loop_ctrl, 0, sizeof(args->loop_ctrl));
        return;
    }

    for (i = 0; i < WINED3D_MAX_CONSTS_I; ++i)
    {
        if (int_skip & (1u << i))
        {
            args->loop_ctrl[i][0] = 0;
            args->loop_ctrl[i][1] = 0;
            args->loop_ctrl[i][2] = 0;
        }
        else
        {
            args->loop_ctrl[i][0] = state->ps_consts_i[i].x;
            args->loop_ctrl[i][1] = state->ps_consts_i[i].y;
            args->loop_ctrl[i][2] = state->ps_consts_i[i].z;
        }
    }
}