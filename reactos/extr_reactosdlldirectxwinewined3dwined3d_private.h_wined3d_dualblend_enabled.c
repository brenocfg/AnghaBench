#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_state {scalar_t__* render_states; TYPE_1__* fb; } ;
struct wined3d_gl_info {int /*<<< orphan*/ * supported; } ;
struct TYPE_2__ {int /*<<< orphan*/ * render_targets; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARB_BLEND_FUNC_EXTENDED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WINED3D_BLEND_INVSRC1ALPHA ; 
 scalar_t__ WINED3D_BLEND_SRC1COLOR ; 
 size_t WINED3D_RS_ALPHABLENDENABLE ; 
 size_t WINED3D_RS_DESTBLEND ; 
 size_t WINED3D_RS_DESTBLENDALPHA ; 
 size_t WINED3D_RS_SRCBLEND ; 
 size_t WINED3D_RS_SRCBLENDALPHA ; 

__attribute__((used)) static inline BOOL wined3d_dualblend_enabled(const struct wined3d_state *state, const struct wined3d_gl_info *gl_info)
{
    if (!state->fb->render_targets[0]) return FALSE;
    if (!state->render_states[WINED3D_RS_ALPHABLENDENABLE]) return FALSE;
    if (!gl_info->supported[ARB_BLEND_FUNC_EXTENDED]) return FALSE;

#define IS_DUAL_SOURCE_BLEND(x) ((x) >= WINED3D_BLEND_SRC1COLOR && (x) <= WINED3D_BLEND_INVSRC1ALPHA)
    if (IS_DUAL_SOURCE_BLEND(state->render_states[WINED3D_RS_SRCBLEND]))  return TRUE;
    if (IS_DUAL_SOURCE_BLEND(state->render_states[WINED3D_RS_DESTBLEND])) return TRUE;
    if (IS_DUAL_SOURCE_BLEND(state->render_states[WINED3D_RS_SRCBLENDALPHA]))  return TRUE;
    if (IS_DUAL_SOURCE_BLEND(state->render_states[WINED3D_RS_DESTBLENDALPHA])) return TRUE;
#undef IS_DUAL_SOURCE_BLEND

    return FALSE;
}