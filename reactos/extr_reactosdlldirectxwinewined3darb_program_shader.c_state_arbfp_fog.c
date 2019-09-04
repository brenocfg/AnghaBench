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
struct wined3d_state {scalar_t__* render_states; } ;
struct wined3d_context {int fog_source; scalar_t__ last_was_rhw; } ;
typedef  enum fogsource { ____Placeholder_fogsource } fogsource ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int FOGSOURCE_COORD ; 
 int FOGSOURCE_FFP ; 
 int FOGSOURCE_VS ; 
 int /*<<< orphan*/  STATE_RENDER (size_t) ; 
 int /*<<< orphan*/  STATE_SHADER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_context*,struct wined3d_state const*,scalar_t__) ; 
 scalar_t__ WINED3D_FOG_NONE ; 
 size_t WINED3D_RS_FOGENABLE ; 
 size_t WINED3D_RS_FOGEND ; 
 size_t WINED3D_RS_FOGSTART ; 
 size_t WINED3D_RS_FOGTABLEMODE ; 
 size_t WINED3D_RS_FOGVERTEXMODE ; 
 int /*<<< orphan*/  WINED3D_SHADER_TYPE_PIXEL ; 
 int /*<<< orphan*/  fragment_prog_arbfp (struct wined3d_context*,struct wined3d_state const*,scalar_t__) ; 
 int /*<<< orphan*/  isStateDirty (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_fogstartend (struct wined3d_context*,struct wined3d_state const*,int /*<<< orphan*/ ) ; 
 scalar_t__ use_vs (struct wined3d_state const*) ; 

__attribute__((used)) static void state_arbfp_fog(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    enum fogsource new_source;
    DWORD fogstart = state->render_states[WINED3D_RS_FOGSTART];
    DWORD fogend = state->render_states[WINED3D_RS_FOGEND];

    TRACE("context %p, state %p, state_id %#x.\n", context, state, state_id);

    if (!isStateDirty(context, STATE_SHADER(WINED3D_SHADER_TYPE_PIXEL)))
        fragment_prog_arbfp(context, state, state_id);

    if (!state->render_states[WINED3D_RS_FOGENABLE])
        return;

    if (state->render_states[WINED3D_RS_FOGTABLEMODE] == WINED3D_FOG_NONE)
    {
        if (use_vs(state))
        {
            new_source = FOGSOURCE_VS;
        }
        else
        {
            if (state->render_states[WINED3D_RS_FOGVERTEXMODE] == WINED3D_FOG_NONE || context->last_was_rhw)
                new_source = FOGSOURCE_COORD;
            else
                new_source = FOGSOURCE_FFP;
        }
    }
    else
    {
        new_source = FOGSOURCE_FFP;
    }

    if (new_source != context->fog_source || fogstart == fogend)
    {
        context->fog_source = new_source;
        state_fogstartend(context, state, STATE_RENDER(WINED3D_RS_FOGSTART));
    }
}