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
struct wined3d_state {int /*<<< orphan*/ * render_states; } ;
struct wined3d_context {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 size_t WINED3D_RS_POINTSIZE_MAX ; 
 size_t WINED3D_RS_POINTSIZE_MIN ; 

void get_pointsize_minmax(const struct wined3d_context *context, const struct wined3d_state *state,
        float *out_min, float *out_max)
{
    union
    {
        DWORD d;
        float f;
    } min, max;

    min.d = state->render_states[WINED3D_RS_POINTSIZE_MIN];
    max.d = state->render_states[WINED3D_RS_POINTSIZE_MAX];

    if (min.f > max.f)
        min.f = max.f;

    *out_min = min.f;
    *out_max = max.f;
}