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
struct wined3d_context {int dummy; } ;
typedef  int DWORD ;

/* Variables and functions */
 int STATE_TEXTURESTAGE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int) ; 
 int WINED3D_HIGHEST_TEXTURE_STATE ; 
 int /*<<< orphan*/  WINED3D_TSS_ALPHA_OP ; 
 int /*<<< orphan*/  WINED3D_TSS_COLOR_OP ; 
 int /*<<< orphan*/  context_apply_state (struct wined3d_context*,struct wined3d_state const*,int) ; 
 int /*<<< orphan*/  isStateDirty (struct wined3d_context*,int) ; 

__attribute__((used)) static void nvrc_resultarg(struct wined3d_context *context, const struct wined3d_state *state, DWORD state_id)
{
    DWORD stage = (state_id - STATE_TEXTURESTAGE(0, 0)) / (WINED3D_HIGHEST_TEXTURE_STATE + 1);

    TRACE("Setting result arg for stage %u.\n", stage);

    if (!isStateDirty(context, STATE_TEXTURESTAGE(stage, WINED3D_TSS_COLOR_OP)))
    {
        context_apply_state(context, state, STATE_TEXTURESTAGE(stage, WINED3D_TSS_COLOR_OP));
    }
    if (!isStateDirty(context, STATE_TEXTURESTAGE(stage, WINED3D_TSS_ALPHA_OP)))
    {
        context_apply_state(context, state, STATE_TEXTURESTAGE(stage, WINED3D_TSS_ALPHA_OP));
    }
}