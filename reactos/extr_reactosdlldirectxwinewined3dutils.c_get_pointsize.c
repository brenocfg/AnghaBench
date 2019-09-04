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
struct wined3d_state {TYPE_1__* viewports; scalar_t__* render_states; } ;
struct wined3d_context {int dummy; } ;
struct TYPE_2__ {float height; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 size_t WINED3D_RS_POINTSCALEENABLE ; 
 size_t WINED3D_RS_POINTSCALE_A ; 
 size_t WINED3D_RS_POINTSCALE_B ; 
 size_t WINED3D_RS_POINTSCALE_C ; 
 size_t WINED3D_RS_POINTSIZE ; 

void get_pointsize(const struct wined3d_context *context, const struct wined3d_state *state,
        float *out_pointsize, float *out_att)
{
    /* POINTSCALEENABLE controls how point size value is treated. If set to
     * true, the point size is scaled with respect to height of viewport.
     * When set to false point size is in pixels. */
    union
    {
        DWORD d;
        float f;
    } pointsize, a, b, c;

    out_att[0] = 1.0f;
    out_att[1] = 0.0f;
    out_att[2] = 0.0f;

    pointsize.d = state->render_states[WINED3D_RS_POINTSIZE];
    a.d = state->render_states[WINED3D_RS_POINTSCALE_A];
    b.d = state->render_states[WINED3D_RS_POINTSCALE_B];
    c.d = state->render_states[WINED3D_RS_POINTSCALE_C];

    /* Always use first viewport, this path does not apply to d3d10/11 multiple viewports case. */
    if (state->render_states[WINED3D_RS_POINTSCALEENABLE])
    {
        float scale_factor = state->viewports[0].height * state->viewports[0].height;

        out_att[0] = a.f / scale_factor;
        out_att[1] = b.f / scale_factor;
        out_att[2] = c.f / scale_factor;
    }
    *out_pointsize = pointsize.f;
}